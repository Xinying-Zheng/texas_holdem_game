#include "component.h"

Result::Result(): player_id(-1), type(0), four_num(0), three_num(0), high_card(0), straight_tail(0), straight_len(0), score(0){}

Result::Result(int ply_id): player_id(ply_id), type(0), four_num(0), three_num(0), high_card(0), straight_tail(0), straight_len(0), score(0){}

bool Result::operator< (const Result& other) const {
	if (type < other.type) return true;
	if (type == other.type && score < other.score) return true;
	return false;
}


