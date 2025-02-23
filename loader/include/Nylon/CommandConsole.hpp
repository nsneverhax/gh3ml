#pragma once

#include <Nylon/Core.hpp>

#include <vector>
#include <map>

namespace nylon
{
	struct ConsoleVar
	{
		ConsoleVar()
		{

		}
		ConsoleVar(const ConsoleVar& source)
		{
			Name = source.Name;
			Description = source.Description;
		}

		std::string Name = { };
		std::string Description = { };

	};

	typedef std::vector<std::string> ConsoleHistory;

	class CommandConsole
	{
	private:
		bool m_shouldScroll = false;
		char m_inputBuffer[UINT8_MAX + 1];
		ConsoleHistory m_inputHistory = { };
		ConsoleHistory m_history = { };
		std::map<std::string, ConsoleVar> m_conVars = { };

		void PushHistory(std::string_view text);

		void DrawLog();
		
	public:
		const uint32_t DefaultInputBufferLength = UINT8_MAX + 1;
		const uint32_t DefaultHistorySize = 100;

		CommandConsole();

		const char* GetInputBuffer() const;

		void SetHistorySize(uint32_t size);
		uint32_t GetHistorySize() const;
		const ConsoleHistory& GetHistory() const;
		void ClearHistory();


		void Draw();
	};

	extern CommandConsole Console;
}