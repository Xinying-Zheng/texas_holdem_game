#include<vector>
using namespace std;

class Poker {
public:
	vector<pair<int, int>> cards;
	int top_card_ind;
	Poker(); // initialize
	void shuffle();
	pair<int, int> deal();
};

class Dealer {
public:
	int speak_order;
	int judge();
	void next_order();
};

class Player {
public:
	int chip_num;
	vector<pair<int,int>> cards;
	void fall();
	void check();
	void raise();
};

class Table {
public:
	vector<pair<int,int>> cards;
	int cur_chip;
	int cur_chip_sum;
};

class Chip {
};

class Game {
	int player_num;
	int chip_num;
	vector<Player> players;
	Poker poker;
	Dealer dealer;
	Table table;
};
