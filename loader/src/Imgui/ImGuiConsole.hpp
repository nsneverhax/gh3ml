#pragma once

namespace nylon::internal
{
	class ImGuiConsole
	{
	private:
		char _buffer[256];

		void DrawLogWindow();
	public:
		void Draw();
	};
}