#include "GameSaver.h"
#include <fstream>
#include "Player.h"
#include "Board.h"
#include "LinkedList.h"
using std::endl;

GameSaver::GameSaver(Player *player1, Player *player2, Board *board, LinkedList *bag, Player *currentPlayer)
{
    outFile.open("output.txt");

    outputPlayer(player1);
    outputPlayer(player2);

    outFile << "26, 26" << endl;

    outFile << board->getState() << endl;

    outFile << bag->toString() << endl;
    outFile << currentPlayer->getName();
}

void GameSaver::outputPlayer(Player *player)
{
    outFile << player->getName() << endl;
    outFile << player->getPoints() << endl;
    outFile << player->getHand()->toString() << endl;
}
