#include "component.h"
#include "card_types.h"
#include <cstdlib>

Dealer::Dealer(int ply_num) : player_num(ply_num) {
	std::srand(time(NULL));	
	button = std::rand() % ply_num;	
}

std::pair<int,int> Dealer::judge_type(std::vector<Card> cards) {
	int hc = high_card(cards);
	std::vector<std::set<int>> color_cnt = color_counter(cards);
	std::map<int,int> num_cnt = number_counter(cards);
	if (is_royal_flush(color_cnt)) return {9, hc};
	else if (is_straight_flush(color_cnt)) return {8, hc};
	else if (is_four_of_a_kind(num_cnt)) return {7, hc};
	else if (is_full_house(num_cnt)) return {6, hc};
	else if (is_flush(color_cnt)) return {5, hc};
	else if (is_straight(num_cnt)) return {4, hc};
	else if (is_three_of_a_kind(num_cnt)) return {3, hc};
	else if (is_two_pairs(num_cnt)) return {2, hc};
	else if (is_one_pair(num_cnt)) return {1, hc};
	else return {0, hc};	
}

// return the greatest card type
std::pair<int,int> Dealer::compare(std::set<std::pair<int,int>> types) {
	return *types.rbegin();
}

void Dealer::move_button() {
	button = (button + 1) % player_num;
}

int Dealer::get_button() {
	return button;
}

