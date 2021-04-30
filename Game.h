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

    void playTurn(vector<string> userInput);
    void executeGameplay();
    void switchPlayer();
    void playTile(Tile* tile, char row, char col);
    void replaceTile(Tile* tile);
    void drawCard();



private:
    Player *player1;
    Player *player2;
    LinkedList *bag;
    Board *board;
    Player* currentPlayer;
    bool gameOver;
};

#endif // ASSIGN2_NODE_H
