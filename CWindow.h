#ifndef CWINDOW_H
#define CWINDOW_H

#include <iostream>
#include <string>
#include <windows.h>

using std::string;

#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80

namespace Color {
	enum {
		BLACK = 0,
		DARKBLUE = FOREGROUND_BLUE,
		DARKGREEN = FOREGROUND_GREEN,
		DARKCYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
		DARKRED = FOREGROUND_RED,
		DARKMAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
		DARKYELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
		DARKGRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		GRAY = FOREGROUND_INTENSITY,
		BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		CYAN = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
		RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
		MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	};
}

class CWindow {
public:
	static void gotoxy(int x, int y, bool isHangul = true) {
		COORD pos = { short(isHangul ? x * 2 : x), short(y) };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}
	static void setColorText(string text, int fontcolor = Color::DARKGRAY, int backcolor = Color::BLACK)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backcolor * 16 + fontcolor);
		std::cout << text;
	}
	static void removeCursor()
	{
		CONSOLE_CURSOR_INFO curInfo;
		GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
		curInfo.bVisible = 0;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	}
};

#endif