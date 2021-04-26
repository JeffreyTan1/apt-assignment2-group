
#ifndef ASSIGN2_GAMEINIT_H
#define ASSIGN2_GAMEINIT_H

#include <string>

class Node;
class Tile;
class Player;
class LinkedList;
class Board;

class GameInit
{
public:
   GameInit();
   GameInit(std::string filename);
   ~GameInit();

   Player* getPlayer1();
   Player* getPlayer2();
   Board* getBoard();
   LinkedList* getBag();


private:
   Player *player1;
   Player *player2;
   Board* board;
   LinkedList *bag;


};

#endif // ASSIGN2_GAMEINIT_H
