#include "component.h"

Chip::Chip(int num) : chip_num(num) {};

int Chip::get_chip_num() {
	return chip_num;
}

void Chip::increase(int amount) {
	chip_num += amount;
}

void Chip::decrease(int amount) {
	chip_num -= amount;
}
