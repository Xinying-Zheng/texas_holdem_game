#include "component.h"

Game::Game(int ply_num, int chip_num): player_num(ply_num), dealer(ply_num) {
	for(int i = 0; i < ply_num; i++) players.push_back(Player(chip_num));
}
