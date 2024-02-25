TARGET = texas_holdem_game
OBJ = main.o game.o poker.o card_types.o chip.o dealer.o player.o table.o card.o result.o test.o process.o

$(TARGET): $(OBJ)
	g++ -std=c++17 $(OBJ) -o $(TARGET) 

main.o: main.cpp component.h 
	g++ -c -std=c++17 main.cpp

game.o: game.cpp component.h
	g++ -c -std=c++17 game.cpp

poker.o: poker.cpp component.h
	g++ -c -std=c++17 poker.cpp

card_types.o: card_types.cpp component.h card_types.h
	g++ -c -std=c++17 card_types.cpp

chip.o: chip.cpp component.h
	g++ -c -std=c++17 chip.cpp

dealer.o : dealer.cpp component.h card_types.h
	g++ -c -std=c++17 dealer.cpp

player.o : player.cpp component.h
	g++ -c -std=c++17 player.cpp

table.o : table.cpp component.h
	g++ -c -std=c++17 table.cpp

card.o : card.cpp component.h card_types.h
	g++ -c -std=c++17 card.cpp

result.o : result.cpp component.h
	g++ -c -std=c++17 result.cpp

test.o : test.cpp component.h test.h card_types.h
	g++ -c -std=c++17 test.cpp

process.o : process.cpp component.h card_types.h process.h test.h
	g++ -c -std=c++17 process.cpp
