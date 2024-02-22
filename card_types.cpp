#include "card_types.h"
#include "component.h"

std::vector<std::set<int>> decor_counter(std::vector<std::pair<int,int>> cards) {
	std::vector<std::set<int>> decor_cnt(5); // 4 types counter, from 1 to 4
	for (auto [x, y] : cards) decor_cnt[y].insert(x);
	return decor_cnt;
}

std::map<int,int> number_counte(std::vector<std::pair<int,int>> cards) {
	std::map<int,int> num_cnt;
	for (auto [x, y] : cards) num_cnt[x]++;
	return num_cnt;
}

bool is_royal_flush(std::vector<std::set<int>> decor_cnt) {
	for (auto d : decor_cnt) {
		int no_found = 0;
		for (auto ele : {1, 13, 12, 11, 10}) {
			if (!d.count(ele)) {
				no_found = 1;
				break;
			}
		}
		if (!no_found) return true;
	}
	return false;
}

bool is_straight_flush(std::vector<std::set<int>> decor_cnt) {
	for (auto d : decor_cnt) {
		if (d.size() < 5) continue;
		int len = 1, max_len = 1, pre = -1;
		for (auto c : d) {
			if (pre == -1) len++;
			else {
				if (pre + 1 == c) len++;
				else {
					max_len = std::max(len, max_len);
					len = 1;
				}
			}
			pre = c;
		}
		if(max_len >= 5) return true;
	}
	return false;
}

bool is_four_of_a_kind(std::vector<std::set<int>> decor_cnt) {
	for (auto d : decor_cnt) {
		if (d.size() > 3) return true;
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

bool is_flush(std::vector<std::set<int>> decor_cnt) {
	for (auto d : decor_cnt) {
		if (d.size() > 4) return true;
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
		if (cnt > 0) pair++;
	}
	if (pair > 0) return true;
	return false;
}

int high_card(std::vector<std::pair<int,int>> cards) {
	sort(cards.begin(), cards.end());
	// "Ace" greater than "King"
	return cards[0].first == 1 ? 14 : cards[cards.size()-1].first;
}

