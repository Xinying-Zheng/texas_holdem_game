#include "component.h"
#include "process.h"
#include "bot.h"

int round_process(Game &game) {
	// Shuffle
	std::cout << "Shuffling..." << std::endl;
	game.poker.shuffle();
	int button = game.dealer.get_button(), ply_num = game.player_num;
	
	// Dealing cards
	std::cout << "Dealing hold cards..." << std::endl << "(from button/player " + std::to_string(button) + ")" << std::endl;
	
	for (int i = 0; i < 2; i++) {
		for (int p = 0; p < ply_num; p++) {
			game.players[(p+button)%ply_num].set_hold(game.poker.deal());
			std::cout << "Dealing player " + std::to_string((p+button)%ply_num) << std::endl;
		}
	}
	std::cout << "Drop card" << std::endl;
	game.poker.deal(); // drop
	std::cout << "Deal 3 flop cards..." << std::endl; 
	for (int i = 0; i < 3; i++) game.table.set_community_cards(game.poker.deal());
	std::cout << "Drop card" << std::endl;
	game.poker.deal(); // drop
	std::cout << "Deal turn card..." << std::endl;
	game.table.set_community_cards(game.poker.deal());
	std::cout << "Drop card" << std::endl;
	game.poker.deal(); // drop
	std::cout << "Deal river card..." << std::endl;
	game.table.set_community_cards(game.poker.deal());
	std::cout << "Your hold cards are:";
	for (auto c : game.players[0].get_hold()) std::cout << " " + c.card_info();
	std::cout << std::endl;	

	// Blind bet
	int small_blind = (button + 1) % ply_num;
	int big_blind = (small_blind + 1) % ply_num;	
	std::vector<int> round_bet(ply_num, 0);
	std::cout << "Small Blind/player " + std::to_string(small_blind) + " and Big Blind/player " + std::to_string(big_blind) + " blind bet..." << std::endl;
	game.players[small_blind].bet(game.blind_bet_num);
	round_bet[small_blind] += game.blind_bet_num;
	game.players[big_blind].bet(game.blind_bet_num * 2);
	round_bet[big_blind] += game.blind_bet_num * 2;
	game.table.raise_cur_chip_to(game.blind_bet_num * 2);
	game.table.raise_cur_chip_sum(game.blind_bet_num * 3);
	
	// before flop action
	std::set<int> noalive;
	int all_in_flag = 0;
	all_in_flag = action_process(big_blind + 1, noalive, ply_num, game.table, game.players, round_bet, big_blind);
	if (all_in_flag) goto Final;
	if (noalive.size() == ply_num - 1) return *noalive.begin();		
	std::cout << game.table.flop() << std::endl;

	// before turn action
	all_in_flag = action_process(small_blind, noalive, ply_num, game.table, game.players, round_bet, -1);
	if (all_in_flag) goto Final;
	if (noalive.size() == ply_num - 1) return *noalive.begin();		
	std::cout << game.table.turn() << std::endl;
	
	// before river action
	all_in_flag = action_process(small_blind, noalive, ply_num, game.table, game.players, round_bet, -1);
	if (all_in_flag) goto Final;
	if (noalive.size() == ply_num - 1) return *noalive.begin();		
	std::cout << game.table.river() << std::endl;

	// after river action
Final:
	all_in_flag = action_process((all_in_flag == 0 ? small_blind : all_in_flag + ply_num), noalive, ply_num, game.table, game.players, round_bet, -1);
	
	// judge
	std::vector<Result> candidate;
	std::vector<Card> community = game.table.get_community_cards();
	for (int p = 0; p < ply_num; p++) {
		if (noalive.count(p)) continue;
		Result r(p);
		std::vector<Card> c = game.players[p].get_hold();
		c.insert(c.begin(), community.begin(), community.end());
		game.dealer.judge_type(r, c);
		candidate.push_back(r);
	}
	std::set<int> winners = game.dealer.compare(candidate);
	int winner_num = winners.size();
	std::cout << "Winner:";
	for (auto p : winners) {
		std::cout<< " Player " + std::to_string(p);
		game.players[p].win(game.table.get_cur_chip_sum() / winner_num);
	}
	std::cout << std::endl;
	return -1;	
}

int action_process(int speak_order, std::set<int>& noalive, int ply_num, Table& table, std::vector<Player>& players, std::vector<int>& round_bet, int pre_raise) {
	std::set<int> raise;
	for (int p = (speak_order) % ply_num; p != pre_raise && noalive.size() != ply_num - 1; p = (p+1)%ply_num) {
		if (noalive.count(p)) continue;
		std::cout << "player " + std::to_string(p) + " action" << std::endl;
		char act;
		if (p != 0) {
			act = robot_action(table, players[p]);
		} else {
			std::cout << "Please choose: fold(f), call(c)";
			if (!raise.count(p)) {
				std::cout << " raise(r), all in(a)";
			} if (round_bet[p] >= table.get_cur_chip()) {
				std::cout << " check in(k)" << std::endl;
			}
		}
		int diff = table.get_cur_chip() - round_bet[p];
		std::cin >> act;
		if (act == 'f') {
			noalive.insert(p);
		} else if (act == 'c') {
			table.raise_cur_chip_sum(diff);
			players[p].call(diff);
			round_bet[p] += diff;
		} else if (act == 'r' || 'a') {
			int amt;
			if (act == 'r') {
				if (p == 0) {
					std::cout << "How much chip do you want to raise?" << std::endl;
					std::cin >> amt;
				} else {
					amt = table.get_cur_chip();
				}
			} else {
				amt = players[p].get_chip_num();
			}
			players[p].raise(amt);
			round_bet[p] += amt;
			table.raise_cur_chip_sum(amt);
			table.raise_cur_chip_to(round_bet[p]);
			raise.insert(p);
			if (act == 'a') return p - ply_num;
		}
		if (pre_raise == -1) pre_raise = speak_order;
	}
	return 0;
}

