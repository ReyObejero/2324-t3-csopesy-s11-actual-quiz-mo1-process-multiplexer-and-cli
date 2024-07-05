#pragma once

#include "Thread.h"
#include <string>

class MarqueeWorkerThread : public Thread {
public:
	MarqueeWorkerThread(int refresh_rate, std::string marquee_text);
	int GetBoundsBottomPad();
	void SetBoundsBottomPad(int pad);

private:
	int refresh_rate_;
	std::string marquee_text_;
	int bounds_bottom_pad_;
	int min_marquee_pos_x_, min_marquee_pos_y_;
	int dx_, dy_;

	bool IsInBounds(int text_length, int pos_x, int pos_y, int display_window_width, int display_window_height);
	void CursorIncrementText(const std::string& text, int& current_pos_x, int& current_pos_y);
	void PrintHeaderLayout();
	void Run() override;
};