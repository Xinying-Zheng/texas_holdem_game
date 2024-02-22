#include<vector>
#include<set>

class Poker {
private:
	std::vector<std::pair<int, int>> cards;
	int top_card_ind;
public:
	Poker(); // initialize
	void shuffle();
	std::pair<int, int> deal();
};

class Dealer {
private:
	int speak_order;
	int player_num;
public:
	Dealer(int ply_num);
	std::pair<int,int> judge_type(std::vector<std::pair<int,int>> cards);
	std::pair<int,int> compare(std::set<std::pair<int,int>> types);
	int cur_order();
	void next_order();
};

class Chip {
private:
	int chip_num;
public:
	int get_chip_num();
};

class Player {
private:
	Chip chip;
	std::vector<std::pair<int,int>> cards;
public:
	void fold();
	void check();
	void raise();
};

class Table {
private:
	std::vector<std::pair<int,int>> cards;
	Chip cur_chip;
	Chip cur_chip_sum;
};

class Game {
private:
	int player_num;
	Chip chip_per_people;
	std::vector<Player> players;
	Poker poker;
	Dealer dealer;
	Table table;
public:
	Game(int ply_num, int chip_num);
};
