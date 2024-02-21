#include "component.h"
#include <algorithm>
#include <random>
#include <time.h>

Poker::Poker() {
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 14; j++) cards.push_back(make_pair(j, i));
	}
	top_card_ind = 0;
}

void Poker::shuffle() {
	default_random_engine e(time(0));
	::shuffle(cards.begin(), cards.end(), e);     
}

pair<int,int> Poker::deal() {
	return cards[top_card_ind++];
}

