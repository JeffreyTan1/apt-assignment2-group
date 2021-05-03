.default: all

all: qwirkle

clean:
	rm -rf qwirkle *.o *.dSYM

<<<<<<< HEAD
qwirkle: Tile.o Node.o LinkedList.o qwirkle.o Board.o Game.o Player.o
=======
qwirkle: Tile.o Node.o LinkedList.o qwirkle.o 
>>>>>>> af1778f7e8578e4805a51b52a3c3e80b7168c87f
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
