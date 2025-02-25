#include <Nylon/CommandConsole.hpp>
#include "Main.hpp"

#include "Imgui/ImGui.hpp"

extern nylon::CommandConsole nylon::Console = { };

//void in::ImGuiConsole::DrawLogWindow()
//{
//	float footerHeightReserved = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
//	if (ImGui::BeginChild("ScrollRegion", ImVec2(0, footerHeightReserved), false, 0))
//	{
//		ImGui::PushTextWrapPos();
//
//
//
//		ImGui::PopTextWrapPos();
//		ImGui::EndChild();
//	}
//}

#pragma region Callbacks
bool HelpCommandCallback(nylon::CommandConsole& caller, std::vector<std::string> arguments)
{
	if (arguments.size() == 1)
	{
		std::string funcList = { };
		int i = 0;
		auto commands = caller.GetCommands();
		for (auto kv : commands)
		{
			if (i != 0 && i != commands.size())
				funcList.append(", ");

			funcList.append(kv.first);
			i++;
		}
		caller.PushHistory(funcList);
	}
	else if (arguments.size() == 2)
	{
		if (caller.HasConsoleCommand(arguments[1]))
		{
			auto command = caller.GetConsoleCommand(arguments[1]);
			if (command.Description.size() == 0)
				caller.PushHistory(std::format("Command: '{}' has no help.", command.Name));
			else
				caller.PushHistory(command.Description);

			if (command.ExampleUsage.size() != 0)
				caller.PushHistory(std::format("Example Usage: {}", command.ExampleUsage));
		}
		else
			caller.PushHistory(std::format("Unrecognized Command: '{}'", arguments[1]));
	}
	else
		caller.PushHistory("Invalid argument count.");

	return true;
}

bool ColonThreeCommandCallback(nylon::CommandConsole& caller, std::vector<std::string> arguments)
{
	caller.PushHistory(":3");

	return true;
}
bool WriteMemoryCommandCallback(nylon::CommandConsole& caller, std::vector<std::string> arguments)
{
	if (arguments.size() != 4)
	{
		caller.PushHistory("Invalid argument count.");
		return false;
	}

	int address = 0;
	try
	{
		address = std::stoi(arguments[1]);
	}
	catch (std::invalid_argument const& ex)
	{
		caller.PushHistory(std::format("Address was invalid: '{}'", arguments[1]));
		return false;
	}
	catch (std::out_of_range const& ex)
	{
		caller.PushHistory(std::format("Address was out of range: '{}'", arguments[1]));
		return false;
	}

	if (arguments[2] != "float")
	{
		int value = 0;
		try
		{
			address = std::stoi(arguments[3]);
		}
		catch (std::invalid_argument const& ex)
		{
			caller.PushHistory(std::format("Value was invalid: '{}'", arguments[3]));
			return false;
		}
		catch (std::out_of_range const& ex)
		{
			caller.PushHistory(std::format("Value was out of range: '{}'", arguments[3]));
			return false;
		}

		bool success = false;

		if (arguments[2] == "uint8")
			success = nylon::WriteMemory(address, static_cast<uint8_t>(value));
		else if (arguments[2] == "int8")
			success = nylon::WriteMemory(address, static_cast<int8_t>(value));
		else if (arguments[2] == "uint16")
			success = nylon::WriteMemory(address, static_cast<uint16_t>(value));
		else if (arguments[2] == "int16")
			success = nylon::WriteMemory(address, static_cast<int16_t>(value));
		else if (arguments[2] == "uint32")
			success = nylon::WriteMemory(address, static_cast<uint32_t>(value));
		else if (arguments[2] == "int32")
			success = nylon::WriteMemory(address, static_cast<int32_t>(value));

		if (success)
			caller.PushHistory(std::format("Wrote '{0}' as {1} to 0x{2:6X}", value, arguments[2], address));
		else
			caller.PushHistory(std::format("An unknown error occured when writing '{0}' as {1} to 0x{2:6X}", value, arguments[2], address));
	}
	else
	{
		float value = 0;
		try
		{
			address = std::stof(arguments[3]);
		}
		catch (std::invalid_argument const& ex)
		{
			caller.PushHistory(std::format("Value was invalid: '{}'", arguments[3]));
			return false;
		}
		catch (std::out_of_range const& ex)
		{
			caller.PushHistory(std::format("Value was out of range: '{}'", arguments[3]));
			return false;
		}

		if (nylon::WriteMemory(address, static_cast<float>(value)))
			caller.PushHistory(std::format("Wrote '{0}' as {1} to 0x{2:6X}", value, arguments[2], address));
		else
			caller.PushHistory(std::format("An unknown error occured when writing '{0}' as {1} to 0x{2:6X}", value, arguments[2], address));
	}
	return true;
}

int TextInputCallback_CallbackHistory(nylon::CommandConsole* console, ImGuiInputTextCallbackData* data)
{
	return 0;
}
int TextInputCallback_CallbackCompletion(nylon::CommandConsole* console, ImGuiInputTextCallbackData* data)
{
	return 0;
}
int TextInputCallback_EnterReturnsTrue(nylon::CommandConsole* console, ImGuiInputTextCallbackData* data)
{
	return 0;
}

int TextInputCallback(ImGuiInputTextCallbackData* data)
{
	nylon::CommandConsole* console = reinterpret_cast<nylon::CommandConsole*>(data->UserData);
	switch (data->EventFlag)
	{
	case ImGuiInputTextFlags_CallbackHistory:
		return TextInputCallback_CallbackHistory(console, data);
	case ImGuiInputTextFlags_CallbackCompletion:
		return TextInputCallback_CallbackCompletion(console, data);
	case ImGuiInputTextFlags_EnterReturnsTrue:
		return TextInputCallback_EnterReturnsTrue(console, data);
	default:
		break;
	}
	return 0;
}
#pragma endregion

std::vector<std::string> nylon::CommandConsole::ParseArguments()
{
	std::vector<std::string> tokens;
	size_t pos = 0;
	std::string token;
	std::string s = { m_inputBuffer };
	while ((pos = s.find(' ')) != std::string::npos) {
		token = s.substr(0, pos);
		tokens.push_back(token);
		s.erase(0, pos + 1);
	}
	tokens.push_back(s);

	return tokens;
}
void nylon::CommandConsole::DrawLog()
{
	const float footerHeightToReserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();

	ImGui::PushTextWrapPos();

	if (ImGui::BeginChild("##ScrollRegion", ImVec2(0, -footerHeightToReserve), false, 0))
	{
		if (!m_history.empty())
		{

			for (auto it = m_history.rbegin(); it != m_history.rend(); it++)
			{
				ImGui::Text(it->c_str());
			}
		}

		if (m_shouldScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			ImGui::SetScrollHereY(1.0f);

		m_shouldScroll = false;

		ImGui::EndChild();
	}

	ImGui::PopTextWrapPos();
}

nylon::CommandConsole::CommandConsole()
{
	ZeroMemory(m_inputBuffer, sizeof(m_inputBuffer));
	m_inputHistory.reserve(CommandConsole::DefaultHistorySize);
	m_history.reserve(CommandConsole::DefaultHistorySize);

	RegisterCommand(ConsoleCommand("help", "Displays help for a given command.", "help <command>", HelpCommandCallback));
	RegisterCommand(ConsoleCommand(":3", ":3", ":3", ColonThreeCommandCallback));
	RegisterCommand(ConsoleCommand("monitorvar", "", "", nullptr));
	RegisterCommand(ConsoleCommand("writemem", "Write a value at a given memory address", "writemem <address> <uint8|int8|uint16|int16|uint32|int32|float> <value>", WriteMemoryCommandCallback));
}

bool nylon::CommandConsole::RegisterCommand(const ConsoleCommand& command)
{
	if (m_commands.contains(command.Name))
		return false;

	m_commands.insert({ std::string(command.Name), ConsoleCommand(command) });

	return true;
}
const std::map<std::string, nylon::ConsoleCommand>& nylon::CommandConsole::GetCommands() const
{
	return m_commands;
}
const char* nylon::CommandConsole::GetInputBuffer() const
{
	return m_inputBuffer;
}

void nylon::CommandConsole::SetHistorySize(uint32_t size)
{
	//m_history.resize(size);
}
uint32_t nylon::CommandConsole::GetHistorySize() const
{
	return m_history.size();
}
void nylon::CommandConsole::PushHistory(std::string_view text)
{
	m_history.insert(m_history.begin(), std::string(text));

	if (m_history.size() >= CommandConsole::DefaultHistorySize)
		m_history.pop_back();

	m_shouldScroll = true;
}
const nylon::ConsoleHistory& nylon::CommandConsole::GetHistory() const
{
	return m_history;
}
void nylon::CommandConsole::ClearHistory()
{
	m_history.clear();
}
bool nylon::CommandConsole::HasConsoleCommand(const std::string& name) const
{
	return m_commands.contains(name);
}
const nylon::ConsoleCommand& nylon::CommandConsole::GetConsoleCommand(const std::string& name)
{
	return m_commands[name];
}

void nylon::CommandConsole::Draw()
{
	if (!ImGui::Begin("Nylon Console"))
	{
		ImGui::End();
		return;
	}

	DrawLog();

	ImGui::Separator();

	ImGuiInputTextFlags inputTextFlags =
		ImGuiInputTextFlags_CallbackHistory  | ImGuiInputTextFlags_CallbackCompletion |
		ImGuiInputTextFlags_EnterReturnsTrue;

	ImGui::PushItemWidth(ImGui::GetWindowWidth() - (ImGui::GetStyle().WindowPadding.x * 2));

	bool reclaimFocus = false;

	if (ImGui::InputText("##Input", m_inputBuffer, sizeof(m_inputBuffer) - 1, inputTextFlags, TextInputCallback, this))
	{
		if (m_inputBuffer[0] != '\0')
		{
			PushHistory(std::format("] {}", m_inputBuffer));

			
			auto arguments = ParseArguments();

			m_shouldScroll = true;

			reclaimFocus = true;

			if (!m_commands.contains(arguments[0]))
				PushHistory(std::format("Unrecognized Command: '{}'", arguments[0]));
			else
			{
				ConsoleCommandCallback callback = m_commands[arguments[0]].Callback;

				if (callback == nullptr)
					PushHistory(std::format("Command: '{}' had a null callback!", arguments[0]));
				else
				{

					callback(*this, arguments);
				}
			}
		}
		ZeroMemory(m_inputBuffer, sizeof(m_inputBuffer));
	}

	ImGui::PopItemWidth();

	ImGui::SetItemDefaultFocus();
	if (reclaimFocus)
		ImGui::SetKeyboardFocusHere(-1);

	ImGui::End();
}