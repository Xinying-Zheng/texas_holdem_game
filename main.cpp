#include "component.h"

int round_process(Game &game);

int main() {
	std::cout << "Please key [player number] [chip amount per player] and [blind bet number]" << std::endl;
	int ply_num, chip_num, blind_bet;
	std::cin >> ply_num >> chip_num >> blind_bet;
	Game game(ply_num, chip_num, blind_bet);
	game.poker.shuffle();
	round_process(game);
//
	
return 0;
}

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
	int speak_order = small_blind;
	std::set<int> noalive, raise;
	int pre_raise = big_blind;
	for (int p = (big_blind + 1) % ply_num; p != pre_raise && noalive.size() != ply_num - 1; p = (p+1)%ply_num) {
		if (noalive.count(p)) continue;
		std::cout << "player " + std::to_string(p) + " action" << std::endl;
		std::cout << "Please choose: fold(f), call(c)";
	   	if (!raise.count(p)) {
			std::cout << " raise(r), all in(a)";
		} if (round_bet[p] >= game.table.get_cur_chip()) {
			std::cout << " check in(k)" << std::endl;
		}
		char act;
		int diff = game.table.get_cur_chip() - round_bet[p];
		std::cin >> act;
		if (act == 'f') {
			noalive.insert(p);
		} else if (act == 'c') {
			game.table.raise_cur_chip_sum(diff);
			game.players[p].call(diff);
			round_bet[p] += diff;
		} else if (act == 'r' || 'a') {
			int amt;
			if (act == 'r') {
				std::cout << "How much chip do you want to raise?" << std::endl;
				std::cin >> amt;
			} else {
				amt = game.players[p].get_chip_num();
			}
			game.players[p].raise(amt);
			round_bet[p] += amt;
			game.table.raise_cur_chip_sum(amt);
			game.table.raise_cur_chip_to(round_bet[p]);
			raise.insert(p);
		} 
	}
// if nobody raise, big blind win, and if has someone raise pre_raise != big_blind, big_blind can raise one time.
	if (noalive.size() == ply_num - 1) return *noalive.begin();		
	
	return -1;	
}

void action_process();

int Test() {
	std::cout << "Please key [player number] and [chip amount per player]" << std::endl;
	int ply_num, chip_num;
	std::cin >> ply_num >> chip_num;
	Game game(ply_num, chip_num, 10);
	for (auto x : game.poker.get_cards()) std::cout << x.card_info() << ' ';
	std::cout << std::endl;
	game.poker.shuffle();
	for (auto x : game.poker.get_cards()) std::cout << x.card_info() << ' ';
	std::cout << std::endl;
	// deal card
	for (auto &p : game.players) {
		p.set_hold(game.poker.deal());
		p.set_hold(game.poker.deal());
		auto hold = p.get_hold();
		std::cout << hold[0].card_info() << ' ' << hold[1].card_info() << std::endl;
	}
	game.poker.deal(); // drop
	for (int i = 0; i < 3; i++) {
		game.table.set_community_cards(game.poker.deal());
	}
	game.poker.deal(); // drop
	game.table.set_community_cards(game.poker.deal());
	game.poker.deal(); // drop
	game.table.set_community_cards(game.poker.deal());
	for (auto c : game.table.get_community_cards()) {
		std::cout << c.card_info() << ' ';
	}
	std::cout << std::endl;

	// judge
	for (auto p : game.players) {
		auto tmp = game.table.get_community_cards(); 
		for(auto c : p.get_hold()) tmp.push_back(c);
		auto type = game.dealer.judge_type(tmp);
		std::cout << type.first << ' ' << type.second << std::endl;
	}

return 0;

}
