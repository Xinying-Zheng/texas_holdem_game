TARGET = texas_holdem_game
OBJ = main.o game.o poker.o card_types.o chip.o dealer.o player.o table.o card.o

$(TARGET): $(OBJ)
	g++ -std=c++17 $(OBJ) -o $(TARGET) 

main.o: main.cpp 
	g++ -c -std=c++17 main.cpp

game.o: game.cpp
	g++ -c -std=c++17 game.cpp

poker.o: poker.cpp
	g++ -c -std=c++17 poker.cpp

card_types.o: card_types.cpp
	g++ -c -std=c++17 card_types.cpp

chip.o: chip.cpp
	g++ -c -std=c++17 chip.cpp

dealer.o : dealer.cpp
	g++ -c -std=c++17 dealer.cpp

player.o : player.cpp
	g++ -c -std=c++17 player.cpp

table.o : table.cpp
	g++ -c -std=c++17 table.cpp

card.o : card.cpp
	g++ -c -std=c++17 card.cpp
