TARGET = texas_holdem
OBJ = main.o game.o poker.o card_types.o chip.o dealer.o player.o table.o 

$(TARGET): $(OBJ)
	g++ -o $(TARGET) $(OBJ)

main.o: main.cpp 
	g++ -c main.cpp

game.o: game.cpp
	g++ -c game.cpp

poker.o: poker.cpp
	g++ -c poker.cpp

card_types.o: card_types.cpp
	g++ -c card_types.cpp

chip.o: chip.cpp
	g++ -c chip.cpp

dealer.o : dealer.cpp
	g++ -c dealer.cpp

player.o : player.cpp
	g++ -c player.cpp

table.o : table.cpp
	g++ -c table.cpp
