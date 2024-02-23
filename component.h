#pragma once
#include<vector>
#include<set>
#include<string>

class Card {
public:
	int number;
	int color;
	Card(int n, int d);
	std::string card_info();
	bool operator< (const Card& other) const;
};

class Poker {
private:
	std::vector<Card> cards;
	int top_card_ind;
public:
	Poker(); // initialize
	void shuffle();
	Card deal();
	std::vector<Card> get_cards();
};

class Dealer {
private:
	int speak_order;
	int player_num;
public:
	Dealer(int ply_num);
	std::pair<int,int> judge_type(std::vector<Card> cards);
	std::pair<int,int> compare(std::set<std::pair<int,int>> types);
	int cur_order();
	void next_order();
};

class Chip {
private:
	int chip_num;
public:
	Chip (int num);
	int get_chip_num();
	void increase(int amount);
	void decrease(int amount);
};

class Player {
private:
	Chip chip;
	std::vector<Card> hold;
	bool alive;
public:
	Player(int chip_num);
	bool is_alive();
	void set_hold(Card card);
	std::vector<Card> get_hold();
	int get_chip_num();	
	void bet(int amount);
	void call(int amount);
	void fold();
	void check();
	void raise(int amount);
	void all_in();
	void win(int amount);
};

class Table {
private:
	std::vector<Card> community_cards;
	Chip cur_chip;
	Chip cur_chip_sum;
	int game_phase;
public:
	Table();
	void set_community_cards(Card card);
	std::string flop();
	std::string trun();
	std::string river();
	int get_cur_chip();
	int get_cur_chip_sum();
	void raise_cur_chip(int amount);
	void raise_cur_chip_sum(int amount);
	std::vector<Card> get_community_cards();
	std::string get_table_info();
	void reset_table();
};

class Game {
public:
	int player_num;
	std::vector<Player> players;
	Poker poker;
	Dealer dealer;
	Table table;
	Game(int ply_num, int chip_num);
};
