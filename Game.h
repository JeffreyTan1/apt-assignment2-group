#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H

#include <string>
#include <vector>


class LinkedList;
class Tile;
class Board;
class Player;

class Game
{
public:
    Game(Player *player1, Player *player2, LinkedList *bag, Board *board, Player* currentPlayer);

    ~Game();

    void playTurn(std::vector<std::string> userInput);
    void executeGameplay();
    void switchPlayer();
    void playTile(Tile *tile, int row, int col);
    void replaceTile(Tile *tile);
    void drawCard();
    bool isValidMove(Tile *userTile, int row, int col);
    bool compareTiles(Tile *tile, Tile *other, bool diffShape);
    bool checkNeighbours(int row, int col, bool diffShape, Tile* originalTile);



private:
    Player *player1;
    Player *player2;
    LinkedList *bag;
    Board *board;
    Player* currentPlayer;
    bool gameOver;
};

#endif // ASSIGN2_GAME_H