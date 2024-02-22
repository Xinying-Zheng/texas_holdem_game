#include "component.h"
#include "card_types.h"

Card::Card(int n, int d) : number(n), color(d) {};

std::string Card::card_info() {
	std::string color_str, number_str;
	color_str = COLOR_NAMES[color];
	if (number == 1) number_str = "A";
	else if (number == 10) number_str = "T";
	else if (number == 11) number_str = "J";
	else if (number == 12) number_str = "Q";
	else if (number == 13) number_str = "K";
	else number_str = std::to_string(number);
	return color_str + number_str;
}

bool Card::operator< (const Card& other) const {
	return number < other.number;
}
