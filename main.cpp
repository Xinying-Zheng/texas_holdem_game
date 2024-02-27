#include "component.h"
#include "test.h"
#include "process.h"

int main(int argc, char** argv) {
	if (argc > 1) {
		if (std::string(argv[1]) == "test") test();
		return 0;
	}
	std::cout << "Please key [player number] [chip amount per player] and [blind bet number]" << std::endl;
	int ply_num, chip_num, blind_bet;
	std::cin >> ply_num >> chip_num >> blind_bet;
	std::cout << "Game start, you are Player 0" << std::endl;
	Game game(ply_num, chip_num, blind_bet);

	for (; ;) {
		game.poker.shuffle();
		round_process(game);
		// clean player's hold, table
		game.dealer.move_button();
		for (auto &p : game.players) p.clean_hold();
		game.table = Table();
	}
return 0;
}


