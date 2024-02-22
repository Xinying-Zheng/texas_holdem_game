#include "component.h"
#include <algorithm>
#include <random>
#include <time.h>

Poker::Poker() {
	for (int d = 0; d < 4; d++) {
		// 0:Spade 1:Heart 2:Diamond 3:Club
		for (int n = 1; n < 14; n++) cards.push_back(Card(n, d));
	}
	top_card_ind = 0;
}

void Poker::shuffle() {
	std::default_random_engine e(time(0));
	std::shuffle(cards.begin(), cards.end(), e);     
}

Card Poker::deal() {
	return cards[top_card_ind++];
}

