#include "Game.h"
#include "LinkedList.h"
#include "Player.h"
#include "Board.h"
#include "Tile.h"

Game::Game(Player *player1, Player *player2, LinkedList *bag, Board *board, std::string currentPlayer)
{
    this->player1 = player1;
    this->player2 = player2;
    this->bag = bag;
    this->board = board;
    this->currentPlayer = currentPlayer;
}

Game::~Game()
{
    delete player1;
    delete player2;
    delete bag;
    delete board;
}

