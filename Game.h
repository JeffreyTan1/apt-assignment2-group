#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H

#include <string>

class LinkedList;
class Tile;
class Board;
class Player;

class Game
{
public:
    Game(Player *player1, Player *player2, LinkedList *bag, Board *board, Player* currentPlayer);

    ~Game();

    void PlayTurn(std::string tile, std::string location);
    void executeGameplay();



private:
    Player *player1;
    Player *player2;
    LinkedList *bag;
    Board *board;
    Player* currentPlayer;
};

#endif // ASSIGN2_NODE_H
