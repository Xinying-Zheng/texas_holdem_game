#include "component.h"
#include "bot.h"

char robot_action(const Table& table, Player& player) {
	std::cout << "robot action" << std::endl;
	int phase = table.get_game_phase();
	Dealer d;
	if (phase == 0) {
		int level = robot_judge_hold_level(player);
		player.set_hold_level(level);
		if (level > 5) return 'f';
		else if (level > 3) return 'c';
		else return 'r';
	} else if (phase == 1) {
		std::vector<Card> hold = player.get_hold();
		std::vector<Card> comm = table.get_community_cards();
		for (int i = 0; i < 3; i++) hold.push_back(comm[i]);
		Result r;
		d.judge_type(r, hold);
		if (r.type > 6) return 'a';
		else if (r.type > 1) return 'r';
		else if (r.type > 0) return 'c';
		else return 'f';
	} else if (phase == 2) {
		std::vector<Card> hold = player.get_hold();
		std::vector<Card> comm = table.get_community_cards();
		for (int i = 0; i < 4; i++) hold.push_back(comm[i]);
		Result r;
		d.judge_type(r, hold);
		if (r.type > 7) return 'a';
		else if (r.type > 4) return 'r';
		else if (r.type > 0) return 'c';
		else return 'f';
	} else if (phase == 3) {
		std::vector<Card> hold = player.get_hold();
		std::vector<Card> comm = table.get_community_cards();
		for (int i = 0; i < 3; i++) hold.push_back(comm[i]);
		Result r;
		d.judge_type(r, hold);
		if (r.type > 7) return 'a';
		else if (r.type > 6) return 'r';
		else if (r.type > 2) return 'c';
		else return 'f';
	}
	return 'f';
}	

int robot_judge_hold_level(Player player) {
	std::vector<Card> hold = player.get_hold();
	sort(hold.begin(), hold.end());
	bool same_color = (hold[0].color == hold[1].color);
	bool same_num = (hold[0].number == hold[1].number);
	if (same_num) {
		int num = hold[0].number;
		if (num == 1 || num == 13 || num == 12) return 1;
		else if (num == 11 || num == 10) return 2;
		else if (num == 9 || num == 8) return 3;
		else return 4;
	}
	if (hold[0].number == 1) {
		int num = hold[1].number;
		if (same_color) {
			if (num == 13) return 1;
			else if (num == 12 || num == 11) return 2;
			else return 3;
		} else {
			if (num == 13) return 1;
			else if (num == 12) return 2;
			else if (num == 11) return 3;
			else if (num > 4) return 4;
			else return 5;
		}
	}
	if (hold[1].number == 13) {
		int num = hold[0].number;
		if (same_color) {
			if (num == 12) return 2;
			else if (num == 11 || num == 10) return 3;
			else if (num == 9) return 4;
			else if (num == 8) return 5;
			else return 6;
		} else {
			if (num == 12) return 2;
			else if (num == 11) return 3;
			else if (num == 10) return 4;
			else if (num == 9) return 5;
			else return 6;
		}
	}
	if (hold[1].number == 12) {
		int num = hold[0].number;
		if (same_color) {
			if (num == 11) return 3;
			else if (num == 10 || num == 9) return 4;
			else if (num == 8) return 5;
			else return 6;
		} else {
			if (num == 11) return 3;
			else if (num == 10) return 4;
			else if (num == 9) return 5;
			else return 6;
		}
	}
	if (hold[1].number == 11) {
		int num = hold[0].number;
		if (same_color) {
			if (num == 10 || num == 9) return 4;
			else if (num == 8) return 5;
			else return 6;
		} else {
			if (num == 10) return 4;
			else if (num == 9 || num == 8) return 5;
			else return 6;
		}
	}
	if (hold[1].number == 10) {
		int num = hold[0].number;
		if (same_color) {
			if (num == 9 || num == 8) return 4;
			else if (num == 7) return 5;
			else return 6;
		} else {
			if (num == 9 || num == 10) return 5;
			else return 6;
		}
	}
	if (hold[1].number == 9) {
		int num = hold[0].number;
		if (same_color) {
			if (num == 8) return 4;
			else if (num == 7 || num == 6) return 5;
			else return 6;
		} else {
			if (num == 8 || num == 7) return 5;
			else return 6;
		}
	}
	if (hold[1].number == 8) {
		int num = hold[0].number;
		if (same_color) {
			if (num == 7) return 4;
			else if (num == 6) return 5;
			else return 6;
		} else {
			if (num == 7|| num == 6) return 5;
			else return 6;
		}
	}
	if (hold[1].number == 7) {
		int num = hold[0].number;
		if (same_color) {
			if (num == 6) return 4;
			else if (num == 5) return 5;
			else return 6;
		} else {
			if (num == 6) return 5;
			else return 6;
		}
	}
	if (hold[1].number == 6) {
		int num = hold[0].number;
		if (same_color) {
			if (num == 5) return 4;
			else if (num == 4) return 5;
			else  return 6;
		} else {
			if (num == 5) return 5;
			else return 6;
		}
	}

	if (hold[1].number == 5) {
		int num = hold[0].number;
		if (same_color && num == 4) return 5;
		else return 6;
	}
	if (hold[1].number == 4) {
		int num = hold[0].number;
		if (same_color && num == 3) return 5;
		else return 6;
	}
	return 6;
}











	
