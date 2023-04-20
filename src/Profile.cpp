#include "Profile.h"

#include <iostream>

namespace Logger {
	Profile::Profile(std::string _name, uint8 _background) {
		name = _name;
		background = Color::MakeColor(Color::None, _background);
	}

	Profile::~Profile() {

	}

	void Profile::Print(std::string str, uint8 color) {
		SetConsoleColor(color + background);

		std::cout << str;

		SetConsoleColor(Color::MakeColor(Color::White, Color::Black));
	}
}