#include "card_types.h"
#include "component.h"
#include <iostream>

const std::vector<std::string> COLOR_NAMES = {"Spade", "Heart", "Diamond", "Club"};

void card_counter(const std::vector<Card>& cards, Result& res) {
	std::vector<std::set<int>> color_cnt(4); // 4 colors
	for (auto c : cards) color_cnt[c.color].insert(c.number);
	std::map<int,int> num_cnt;
	for (auto c : cards) num_cnt[c.number]++;
	
	for (auto [num, cnt] : num_cnt) {
		if (cnt == 4) res.four_num = num;
		else if (cnt == 3) {
			if (res.three_num == 1) res.pair_num.push_back(num);
			else {
				if (res.three_num != 0) res.pair_num.push_back(res.three_num);
				res.three_num = num;
			}
		}
	}
	res.high_card = high_card(cards);

	if (num_cnt.count(1)) num_cnt[14] = num_cnt[1];
	int len = 1, max_len = 1, pre = -1;
	for (auto [n, cnt] : num_cnt) {
		if (pre == -1) len++;
		else {
			if (pre + 1 == n) len++;
			else {
				if (len > 4) res.straight_tail = pre, res.straight_len = len;
				len = 1;
			}
		}
		pre = n;
	}
	if (len > 4) res.straight_tail = pre, res.straight_len = len;

	for (auto c : color_cnt) {
		if (c.size() > 4) res.same_color = c;
	}	
}


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

bool is_royal_flush(Result& res) {
	if (res.straight_tail != 14) return false;
	for (auto ele : {1, 13, 12, 11, 10}) {
		if (!res.same_color.count(ele)) return false;
	}
	res.type = 9;
	return true;
}

bool is_straight_flush(Result& res) {
	for (int tail = res.straight_tail - (res.straight_len - 5); tail < res.straight_tail + 1; tail++) {
		int num = tail;
		for (; num > tail - 5; num--) {
			if (!res.same_color.count(num)) break;
		}
		if (num == tail - 5) {
			res.type = 8;
			res.score = tail;
		}
	}
	return res.type == 8 ? true : false;
}

bool is_four_of_a_kind(Result& res) {
	if (res.four_num != 0) {
		res.type = 7;
		res.score = res.four_num == 1 ? 14 : res.four_num;
		return true;
	}
	return false;
}

bool is_full_house(Result& res) {
	if (res.three_num != 0 && res.pair_num.size() != 0) {
		res.type = 6;
		res.score = (res.four_num == 1 ? 14 : res.three_num) * 100 + *(res.pair_num.rbegin());
		return true;
	}
	return false;
}

bool is_flush(Result& res) {
	if (res.same_color.size() != 0) {
		res.type = 5;
		res.score = res.high_card;
		return true;
	}
	return false;
}

bool is_straight(Result& res) {
	if (res.straight_tail != 0) {
		res.type = 4;
		res.score = res.straight_tail;
		return true;
	}
	return false;
}

bool is_three_of_a_kind(Result& res) {
	if (res.three_num != 0) {
		res.type = 3;
		res.score = (res.three_num == 1 ? 14 : res.three_num);
		return true;
	}
	return false;
}

bool is_two_pairs(Result& res) {
	int n = res.pair_num.size();
	if (n > 1) {
		res.type = 2;
		res.score = (res.pair_num[0] == 1 ? (1400 + res.pair_num[n-1]) : res.pair_num[n-1] * 100 + res.pair_num[n-2]);
		return true;
	}
	return false;
}

bool is_one_pair(Result& res) {
	int n = res.pair_num.size();
	if (n > 0) {
		res.type = 1;
		res.score = (res.pair_num[0] == 1 ? 14 : res.pair_num[n-1]);
		return true;
	}
	return false;
}

int high_card(std::vector<Card> cards) {
	std::sort(cards.begin(), cards.end());
	// "Ace" greater than "King"
	return cards[0].number == 1 ? 14 : cards[cards.size()-1].number;
}

