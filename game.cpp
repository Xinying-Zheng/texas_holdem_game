#include "component.h"

Game::Game(int ply_num, int chip_num, int blind_bet): player_num(ply_num), dealer(ply_num), round(0), blind_bet_num(blind_bet) {
	for(int i = 0; i < ply_num; i++) players.push_back(Player(chip_num));
}
