.default: all

all: qwirkle

clean:
	rm -rf qwirkle *.o *.dSYM

qwirkle: Tile.o Node.o LinkedList.o Board.o Game.o GameInit.o Player.o qwirkle.o  
	g++ -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Werror -std=c++14 -g -O -c $^
