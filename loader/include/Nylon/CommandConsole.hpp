#pragma once

#include <Nylon/Core.hpp>

#include <vector>
#include <map>

namespace nylon
{
	class CommandConsole;

	typedef bool(*ConsoleCommandCallback)(CommandConsole&, std::vector<std::string>);

	struct ConsoleCommand
	{
		ConsoleCommand()
		{

		}
		ConsoleCommand(std::string_view name, std::string_view description, ConsoleCommandCallback callback)
		{
			Name = std::string(name);
			Description = std::string(description);
			Callback = callback;
		}
		ConsoleCommand(const ConsoleCommand& source)
		{
			Name = source.Name;
			Description = source.Description;
			Callback = source.Callback;
		}

		std::string Name = { };
		std::string Description = { };
		ConsoleCommandCallback Callback = nullptr;
	};

	typedef std::vector<std::string> ConsoleHistory;

	class CommandConsole
	{
	private:
		bool m_shouldScroll = false;
		char m_inputBuffer[UINT8_MAX + 1];
		ConsoleHistory m_inputHistory = { };
		ConsoleHistory m_history = { };
		std::map<std::string, ConsoleCommand> m_commands = { };

		void DrawLog();
		
	public:
		const uint32_t DefaultInputBufferLength = UINT8_MAX + 1;
		const uint32_t DefaultHistorySize = 100;

		CommandConsole();
		bool RegisterCommand(const ConsoleCommand& command);

		const char* GetInputBuffer() const;


		void SetHistorySize(uint32_t size);
		uint32_t GetHistorySize() const;
		void PushHistory(std::string_view text);
		const ConsoleHistory& GetHistory() const;
		void ClearHistory();

		void Draw();
	};

	extern CommandConsole Console;
}