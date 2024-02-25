#pragma once
#include "component.h"

int round_process(Game &game);
int action_process(int speak_order, std::set<int>& noalive, int ply_num, Table& table, std::vector<Player>& players, std::vector<int>& round_bet, int pre_raise);
	
