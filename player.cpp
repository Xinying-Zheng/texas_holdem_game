#include "component.h"

Player::Player(int chip_num) : chip(Chip(chip_num)), alive(true) {};

bool Player::is_alive() {
	return alive;
}

void Player::set_hold(Card card){
	hold.push_back(card);
}

std::vector<Card> Player::get_hold() {
	return hold;
}

int Player::get_chip_num() {
	return chip.get_chip_num();
}

void Player::bet(int amount) {
	chip.decrease(amount);
}

void Player::call(int amount) {
	chip.decrease(amount);
}

void Player::fold() {
	alive = false;
}	

void check() {}

void Player::raise(int amount) {
	chip.decrease(amount);
}

void Player::all_in() {
	chip.decrease(chip.get_chip_num());
}

void Player::win(int amount) {
	chip.increase(amount);
}

void Player::clean_hold() {
	hold.clear();
}
