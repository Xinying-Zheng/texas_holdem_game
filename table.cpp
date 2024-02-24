#include "component.h"

Table::Table(): cur_chip(Chip(0)), cur_chip_sum(Chip(0)), game_phase(0) {};

void Table::set_community_cards(Card card) {
	community_cards.push_back(card);
}

std::string Table::flop() {
	game_phase = 1;
	return community_cards[0].card_info() + " " + community_cards[1].card_info() + " " + community_cards[2].card_info();
}
	
std::string Table::turn() {
	game_phase = 2;
	return community_cards[3].card_info();
}

std::string Table::river() {
	game_phase = 3;
	return community_cards[4].card_info();
}

int Table::get_cur_chip() {
	return cur_chip.get_chip_num();
}

int Table::get_cur_chip_sum() {
	return cur_chip_sum.get_chip_num();
}

void Table::raise_cur_chip_to(int amount) {
	cur_chip.set(amount);
	std::cout << "Current chip is " + std::to_string(cur_chip.get_chip_num()) << std::endl;
}

void Table::raise_cur_chip_sum(int amount) {
	cur_chip_sum.increase(amount);
}

std::vector<Card> Table::get_community_cards() {
	return community_cards;
}

std::string Table::get_table_info() {
	std::string info;
	if (game_phase == 0) {
		info += "* * * * *";
	} else if (game_phase == 1) {
		info += community_cards[0].card_info() + " " + community_cards[1].card_info() + " " + community_cards[2].card_info() + " * *";
	} else if (game_phase == 2) {
		info += community_cards[0].card_info() + " " + community_cards[1].card_info() + " " + community_cards[2].card_info() + " " + community_cards[3].card_info() + " *";
	} else if (game_phase == 3) {
		info += community_cards[0].card_info() + " " + community_cards[1].card_info() + " " + community_cards[2].card_info() + " " + community_cards[3].card_info() + " " + community_cards[4].card_info();
	}
	info += " cur chip: " + std::to_string(cur_chip.get_chip_num()) + " total chip: " + std::to_string(cur_chip_sum.get_chip_num());

	return info;
}

void Table::reset_table() {
	community_cards.clear();
	cur_chip = 0;
	cur_chip_sum = 0;
	game_phase = 0;
}

