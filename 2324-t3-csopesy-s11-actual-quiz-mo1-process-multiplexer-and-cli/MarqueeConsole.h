#pragma once

#include <string>
#include <vector>

class MarqueeConsole {
public:
	MarqueeConsole(int polling_rate);

	void UpdateInputLog(const std::string& input);
	void Run();

private:
	int polling_rate_;
	std::vector<std::string> input_log_;
};