#include<iostream>
#include "component.h"

int main() {
	std::cout << "Please key [player number] and [chip amount per player]" << std::endl;
	int ply_num, chip_num;
	std::cin >> ply_num >> chip_num;
	Game game(ply_num, chip_num);
	game.poker.shuffle();

	// deal card
	for (auto &p : game.players) {
		p.set_hold(game.poker.deal());
		p.set_hold(game.poker.deal());
	}
	game.poker.deal(); // drop
	for (int i = 0; i < 3; i++) {
		game.table.set_community_cards(game.poker.deal());
	}
	game.poker.deal(); // drop
	game.table.set_community_cards(game.poker.deal());
	game.poker.deal(); // drop
	game.table.set_community_cards(game.poker.deal());

	// judge
	for (auto p : game.players) {
		auto tmp = game.table.get_community_cards(); 
		for(auto c : p.get_hold()) tmp.push_back(c);
		auto type = game.dealer.judge_type(tmp);
		std::cout << type.first << ' ' << type.second << std::endl;
	}

return 0;
}

int Test() {
	std::cout << "Please key [player number] and [chip amount per player]" << std::endl;
	int ply_num, chip_num;
	std::cin >> ply_num >> chip_num;
	Game game(ply_num, chip_num);
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
