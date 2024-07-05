#include "MarqueeConsole.h"
#include "ConsoleManager.h"
#include "MarqueeWorkerThread.h"
#include <string>
#include "Commands.h"
#include <thread>

MarqueeConsole::MarqueeConsole(int polling_rate) {
	this->polling_rate_ = polling_rate;
}

void MarqueeConsole::UpdateInputLog(const std::string& input) {
	input_log_.push_back(input);
}

void MarqueeConsole::Run() {
	MarqueeWorkerThread* marquee_worker_thread = new MarqueeWorkerThread(50, "Hello world in marquee!");
	marquee_worker_thread->Start();
	ConsoleManager console_manager;
	char key_pressed;
	std::string input_prompt = "Enter a command for MARQUEE_CONSOLE: ";
	std::string input_command = "";
	int display_window_height = console_manager.GetDisplayWindowBounds().Bottom;
	bool running = true;

	while (running == true) {
		key_pressed = NULL;
		console_manager.WriteAtPosition(input_prompt + input_command, 0, display_window_height);
		console_manager.PollKeyboard(key_pressed);
		std::this_thread::sleep_for(std::chrono::milliseconds(polling_rate_));
		
		// Carriage return or enter key
		if (key_pressed != '\r') {
			// 127 - delete key
			// 8 - backspace key
			if (key_pressed != 127 && key_pressed != 8) {
				input_command += key_pressed;
			}
		} else {
			UpdateInputLog(input_command);
			input_command = "";
			//marquee_worker_thread->SetBoundsBottomPad(marquee_worker_thread->GetBoundsBottomPad() + 1);
		}
	}
}
