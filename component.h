#pragma once
#include<vector>
#include<set>
#include<string>
#include<iostream>

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

class Result {
public:
	int player_id;
	int type;
	int four_num;
	int three_num;
	std::vector<int> pair_num;
	int high_card;
	int straight_tail; // we can proof there cam only be one tail
	int straight_len;
	std::set<int> same_color;
	int score;
	Result();
	Result(int ply_id);
	bool operator< (const Result& other) const;
};

class Dealer {
private:
	int player_num;
	int button;
public:
	Dealer(int ply_num);
	void judge_type(Result& res, std::vector<Card> cards);
	std::set<int> compare(std::vector<Result> res);
	int get_button();
	void move_button();
};

class Chip {
private:
	int chip_num;
public:
	Chip (int num);
	int get_chip_num();
	void increase(int amount);
	void decrease(int amount);
	void set(int amount);
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
	std::string turn();
	std::string river();
	int get_cur_chip();
	int get_cur_chip_sum();
	void raise_cur_chip_to(int amount);
	void raise_cur_chip_sum(int amount);
	std::vector<Card> get_community_cards();
	std::string get_table_info();
	void reset_table();
};

class Game {
public:
	int player_num;
	int round;
	int blind_bet_num;
	std::vector<Player> players;
	Poker poker;
	Dealer dealer;
	Table table;
	Game(int ply_num, int chip_num, int blind_bet);
};


