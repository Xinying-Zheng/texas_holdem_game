#include "card_types.h"
#include "component.h"

const std::vector<std::string> COLOR_NAMES = {"Spade", "Heart", "Diamond", "Club"};


std::vector<std::set<int>> color_counter(std::vector<Card> cards) {
	std::vector<std::set<int>> color_cnt(4); // 4 colors
	for (auto c : cards) color_cnt[c.color].insert(c.number);
	return color_cnt;
}

std::map<int,int> number_counter(std::vector<Card> cards) {
	std::map<int,int> num_cnt;
	for (auto c : cards) num_cnt[c.number]++;
	return num_cnt;
}

bool is_royal_flush(std::vector<std::set<int>> color_cnt) {
	for (auto c : color_cnt) {
		int no_found = 0;
		for (auto ele : {1, 13, 12, 11, 10}) {
			if (!c.count(ele)) {
				no_found = 1;
				break;
			}
		}
		if (!no_found) return true;
	}
	return false;
}

bool is_straight_flush(std::vector<std::set<int>> color_cnt) {
	for (auto c : color_cnt) {
		if (c.size() < 5) continue;
		int len = 1, max_len = 1, pre = -1;
		for (auto cd : c) {
			if (pre == -1) len++;
			else {
				if (pre + 1 == cd) len++;
				else {
					max_len = std::max(len, max_len);
					len = 1;
				}
			}
			pre = cd;
		}
		if(max_len >= 5) return true;
	}
	return false;
}

bool is_four_of_a_kind(std::map<int,int> num_cnt) {
	for (auto [n, cnt] : num_cnt) {
		if (cnt > 3) return true;
	}
	return false;
}

bool is_full_house(std::map<int,int> num_cnt) {
	int pair = 0, three = 0;
	for (auto [n, cnt] : num_cnt) {
		if (cnt > 2) three++;
		if (cnt > 1) pair++;
	}
	if (three > 0 && (pair - three) > 0) return true;
	else return false;
}

bool is_flush(std::vector<std::set<int>> color_cnt) {
	for (auto c : color_cnt) {
		if (c.size() > 4) return true;
	}
	return false;
}

bool is_straight(std::map<int,int> num_cnt) {
	if (num_cnt.count(1)) num_cnt[14] = num_cnt[1];
	int len = 1, max_len = 1, pre = -1;
	for (auto [n, cnt] : num_cnt) {
		if (pre == -1) len++;
		else {
			if (pre + 1 == n) len++;
			else {
				max_len = std::max(len, max_len);
				len = 1;
			}
		}
		pre = n;
	}
	if(max_len >= 5) return true;
	return false;
}

bool is_three_of_a_kind(std::map<int,int> num_cnt) {
	for (auto [n, cnt] : num_cnt) {
		if (cnt > 2) return true;
	}
	return false;
}

bool is_two_pairs(std::map<int,int> num_cnt) {
	int pair = 0;
	for (auto [n, cnt] : num_cnt) {
		if (cnt > 1) pair++;
	}
	if (pair > 1) return true;
	return false;
}

bool is_one_pair(std::map<int,int> num_cnt) {
	int pair = 0;
	for (auto [n, cnt] : num_cnt) {
		if (cnt > 1) pair++; 
	}
	if (pair > 0) return true;
	return false;
}

int high_card(std::vector<Card> cards) {
	std::sort(cards.begin(), cards.end());
	// "Ace" greater than "King"
	return cards[0].number == 1 ? 14 : cards[cards.size()-1].number;
}

