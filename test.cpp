#include "test.h"
#include "component.h"
#include "card_types.h"

void test() {
	std::cout << "Testing start" << std::endl;
	test_judge_and_compare();
	std::cout << "All tests PASS" << std::endl;
}

void test_judge_and_compare() {
	Dealer d(10);
	// royal_flush
	std::vector<Card> c1 = {Card(10, 0), Card(11, 0), Card(12, 0), Card(13, 0), Card(1, 0), Card(1, 1), Card(10, 1)};
	Result r1(1);
	d.judge_type(r1, c1);
	assert(r1.type == 9);
	assert(r1.high_card == 14);
	std::cout << "royal flush " << r1.type << ' ' << r1.high_card << std::endl;
	// straight_flush
	std::vector<Card> c2 = {Card(10, 0), Card(11, 0), Card(12, 0), Card(13, 0), Card(9, 0), Card(10, 1), Card(10, 2)};
	Result r2(2);
	d.judge_type(r2, c2);
	assert(r2.type == 8);
	assert(r2.score == 13);
	std::cout << "straight flush " << r2.type << ' ' << r2.score << std::endl;
	// four_of_kind
	std::vector<Card> c3 = {Card(1, 0), Card(1, 2), Card(10, 3), Card(13, 0), Card(1, 3), Card(1, 1), Card(10, 1)};
	Result r3(3);
	d.judge_type(r3, c3);
	assert(r3.type == 7);
	assert(r3.score == 14);
	std::cout << "four of a kind " << r3.type << ' ' << r3.score << std::endl;
	// full_house
	std::vector<Card> c4 = {Card(1, 0), Card(11, 0), Card(11, 2), Card(13, 0), Card(1, 2), Card(1, 1), Card(10, 1)};
	Result r4(4);
	d.judge_type(r4, c4);
	assert(r4.type == 6);
	assert(r4.score == 1411);
	std::cout << "full house " << r4.type << ' ' << r4.score << std::endl;
	// flush
	std::vector<Card> c5 = {Card(8, 2), Card(11, 2), Card(1, 2), Card(13, 2), Card(1, 0), Card(9, 2), Card(10, 1)};
	Result r5(5);
	d.judge_type(r5, c5);
	assert(r5.type == 5);
	assert(r5.score == 14);
	std::cout << "flush " << r5.type << ' ' << r5.score << std::endl;
	// straight
	std::vector<Card> c6 = {Card(10, 2), Card(11, 1), Card(12, 2), Card(13, 0), Card(1, 0), Card(1, 1), Card(10, 1)};
	Result r6(6);
	d.judge_type(r6, c6);
	assert(r6.type == 4);
	assert(r6.score == 14);
	std::cout << "straight " << r6.type << ' ' << r6.score << std::endl;
	// three kind
	std::vector<Card> c7 = {Card(1, 0), Card(1, 2), Card(12, 0), Card(13, 0), Card(5, 0), Card(1, 1), Card(10, 1)};
	Result r7(7);
	d.judge_type(r7, c7);
	assert(r7.type == 3);
	assert(r7.score == 14);
	std::cout << "three of a kind " << r7.type << ' ' << r7.score << std::endl;
	// two pair	
	std::vector<Card> c8 = {Card(1, 0), Card(1, 2), Card(12, 0), Card(12, 1), Card(5, 0), Card(4, 1), Card(10, 1)};
	Result r8(8);
	d.judge_type(r8, c8);
	assert(r8.type == 2);
	assert(r8.score == 1400 + 12);
	std::cout << "two pair" << r8.type << ' ' << r8.score << std::endl;
	// one pair
	std::vector<Card> c9 = {Card(1, 0), Card(1, 2), Card(12, 0), Card(13, 0), Card(5, 0), Card(4, 1), Card(10, 1)};
	Result r9(9);
	d.judge_type(r9, c9);
	assert(r9.type == 1);
	assert(r9.score == 14);
	std::cout << "one pair " << r9.type << ' ' << r9.score << std::endl;
	// on pair
	std::vector<Card> c0 = {Card(1, 0), Card(3, 2), Card(12, 0), Card(13, 0), Card(5, 0), Card(2, 1), Card(8, 1)};
	Result r0(0);
	d.judge_type(r0, c0);
	assert(r0.type == 0);
	assert(r0.score == 14);
	std::cout << "no pair " << r0.type << ' ' << r0.score << std::endl;

// compare
	std::vector<Result> res = {r1, r2, r3, r4, r5, r6, r7, r8, r9, r0};
	std::set<int> winners = d.compare(res);
	assert(winners.size() == 1);
	assert(*winners.begin() == 1);

	std::cout << "test_judge_and_compare PASS" << std::endl;
}
