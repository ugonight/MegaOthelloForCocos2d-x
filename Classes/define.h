#pragma once

//‚ ‚ñ‚Ü‚è‚æ‚­‚È‚¢difine.h

#define FONT_NAME "fonts/mgenplus-1cp-medium.ttf"

const int SCREEN_SIZE_X = 1280;
const int SCREEN_SIZE_Y = 720;
const int COLORBIT = 16;

const char thinking[] = "thinking.ogg";
const char pachin[] = "pachin4.ogg";
const char pochi[] = "pochi.ogg";
const char cancel[] = "pochib.ogg";
const char fall[] = "fall.ogg";

const int MESSAGEWAIT = 120;
const int COMWAIT = 60;
const int FALLWAIT = 40;

enum ComType {
	com1,
	com1murora,
	com1mega,
	com1moroi,
	com2,
	com2murora,
	com2mega,
	com2moroi
};

enum BorW {
	none,
	black,
	white,
	gray
};