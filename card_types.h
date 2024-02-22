#pragma once
#include<vector>
#include<map>
#include<set>
#include<string>
#include "component.h"

extern const std::vector<std::string> COLOR_NAMES;

std::vector<std::set<int>> color_counter(std::vector<Card> cards);

std::map<int,int> number_counter(std::vector<Card> cards);

bool is_royal_flush(std::vector<std::set<int>> color_cnt);
	
bool is_straight_flush(std::vector<std::set<int>> color_cnt);

bool is_four_of_a_kind(std::vector<std::set<int>> color_cnt);

bool is_full_house(std::map<int,int> num_cnt);

bool is_flush(std::vector<std::set<int>> color_cnt);

bool is_straight(std::map<int,int> num_cnt); 

bool is_three_of_a_kind(std::map<int,int> num_cnt);

bool is_two_pairs(std::map<int,int> num_cnt);

bool is_one_pair(std::map<int,int> num_cnt);

int high_card(std::vector<Card> cards); 

