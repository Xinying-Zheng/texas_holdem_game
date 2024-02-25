#pragma once
#include<vector>
#include<map>
#include<set>
#include<string>
#include "component.h"

extern const std::vector<std::string> COLOR_NAMES;

void card_counter(const std::vector<Card>& cards, Result& res);

bool is_royal_flush(Result& res);
	
bool is_straight_flush(Result& res);

bool is_four_of_a_kind(Result& res);

bool is_full_house(Result& res);

bool is_flush(Result& res);

bool is_straight(Result& res); 

bool is_three_of_a_kind(Result& res);

bool is_two_pairs(Result& res);

bool is_one_pair(Result& res);

int high_card(std::vector<Card> cards); 

