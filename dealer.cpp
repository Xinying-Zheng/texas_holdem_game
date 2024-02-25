#include "component.h"
#include "card_types.h"
#include <cstdlib>

Dealer::Dealer(int ply_num) : player_num(ply_num) {
	std::srand(time(NULL));	
	button = std::rand() % ply_num;	
}

void Dealer::judge_type(Result& res, std::vector<Card> cards) {
	card_counter(cards, res);
	if (is_royal_flush(res)) return;
	else if (is_straight_flush(res)) return;
	else if (is_four_of_a_kind(res)) return;
	else if (is_full_house(res)) return;
	else if (is_flush(res)) return;
	else if (is_straight(res)) return;
	else if (is_three_of_a_kind(res)) return;
	else if (is_two_pairs(res)) return;
	else if (is_one_pair(res)) return;
	else res.score = res.high_card;	
}

// return the greatest card type
std::set<int> Dealer::compare(std::vector<Result> res) {
	sort(res.rbegin(), res.rend());
	std::set<int> win;
	for (auto r : res) {
		if (r.type == res[0].type && r.score == res[0].score) win.insert(r.player_id);
	}
	return win;
}

void Dealer::move_button() {
	button = (button + 1) % player_num;
}

int Dealer::get_button() {
	return button;
}

