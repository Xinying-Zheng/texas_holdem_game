#include "component.h"
#include <algorithm>
#include <random>
#include <time.h>

Poker::Poker() {
	for (int i = 1; i < 5; i++) {
		// 1:Spade 2:Heart 3:Diamond 4:Club
		for (int j = 1; j < 14; j++) cards.push_back(std::make_pair(j, i));
	}
	top_card_ind = 0;
}

void Poker::shuffle() {
	std::default_random_engine e(time(0));
	std::shuffle(cards.begin(), cards.end(), e);     
}

std::pair<int,int> Poker::deal() {
	return cards[top_card_ind++];
}

