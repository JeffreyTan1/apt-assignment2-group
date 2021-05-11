#include "GameInit.h"
#include "Tile.h"
#include "LinkedList.h"
#include "Board.h"
#include "Player.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <random>
#define ASCII_CONVERTER_DIGIT 48
#define ASCII_CONVERTER_LETTER 65
using std::atoi;
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::stoi;

GameInit::GameInit()
{
    board = new Board();
    bag = new LinkedList();
    newRandomBag();

    newPlayer(1);
    newPlayer(2);
    cin.ignore();

    cout << "player 1 name:" << player1->getName() << endl;

    currPlayer = player1;

    cout << "current player name:" << currPlayer->getName() << endl;

    //End of initialiser
}

void GameInit::newRandomBag()
{
    //create a vector containing all tiles
    std::vector<Tile *> allTiles;

    char colours[6] = {'R', 'O', 'Y', 'G', 'B', 'P'};

    int shapes[6] = {1, 2, 3, 4, 5, 6};

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            for (int k = 0; k < 6; k++)
            {
                Tile *newTile = new Tile(colours[j], shapes[k]);
                allTiles.push_back(newTile);
            }
        }
    }

    //shuffle the vector
    std::default_random_engine engine(10);
    std::shuffle(allTiles.begin(), allTiles.end(), engine);
    //add tiles to bag
    for (int i = 0; i < 72; i++)
    {
        bag->addBack(allTiles.at(i));
    }
}

void GameInit::newPlayer(int pNum)
{
    //Create player 1 data structures
    cout << "Enter a name for player " << pNum << " (uppercase characters only)" << endl;
    std::string name;
    cin >> name;
    LinkedList *hand = new LinkedList();
    for (int i = 0; i < 6; i++)
    {

        hand->addBack(bag->get(0));
        bag->removeFront();
    }

    if (pNum == 1)
    {
        player1 = new Player(name, 0, hand);
    }
    else if (pNum == 2)
    {
        player2 = new Player(name, 0, hand);
    }
}

GameInit::GameInit(std::string filename)
{
    board = new Board();
    bag = new LinkedList();

    ifstream saveFile("s.txt");

    std::string line1;
    std::string line2;
    std::string line3;

    for (int i = 0; i < 2; i++)
    {
        std::getline(saveFile, line1);
        line1.pop_back();
        std::getline(saveFile, line2);
        line2.pop_back();
        std::getline(saveFile, line3);
        line3.pop_back();
        loadPlayer(line1, line2, line3, i + 1);
    }

    std::string line4;
    std::getline(saveFile, line4);
    line4.pop_back();
    loadBoardSize(line4);

    std::string line5;
    std::getline(saveFile, line5);
    line5.pop_back();
    loadBoardState(line5);

    std::string line6;
    std::getline(saveFile, line6);
    line6.pop_back();
    loadBagState(line6);

    std::string line7;
    std::getline(saveFile, line7);
    line7.pop_back();
    loadCurrPlayer(line7);

    saveFile.close();
    //End of initialiser
}

void GameInit::loadPlayer(std::string line1, std::string line2, std::string line3, int pNum)
{
    int points = stoi(line2);
    std::stringstream ss(line3);

    LinkedList *hand = new LinkedList();

    while (ss.good())
    {
        std::string substr;
        std::getline(ss, substr, ',');
        char colour = substr.at(0);
        int shape = substr.at(1) - ASCII_CONVERTER_DIGIT;
        Tile *newTile = new Tile(colour, shape);
        hand->addBack(newTile);
    }

    if (pNum == 1)
    {
        player1 = new Player(line1, points, hand);
    }
    else if (pNum == 2)
    {
        player2 = new Player(line1, points, hand);
    }
}

void GameInit::loadBoardSize(std::string line4)
{
    std::stringstream ss(line4);

    for (int i = 0; i < 2; i++)
    {
        std::string substr;
        std::getline(ss, substr, ',');
        if (i == 0)
        {
            bHeight = stoi(substr);
        }
        else
        {
            bWidth = stoi(substr);
        }
    }
}

void GameInit::loadBoardState(std::string line5)
{
    std::stringstream ss(line5);
    int iter = 0;
    while (ss.good())
    {
        char tileChar;
        int tileShape;
        int boardRow;
        int boardCol;

        std::string substr;
        std::getline(ss, substr, ',');

        if (iter == 0)
        {
            tileChar = substr.at(0);
            tileShape = (int)substr.at(1) - ASCII_CONVERTER_DIGIT;
            boardRow = (int)substr.at(3) - ASCII_CONVERTER_LETTER;
            boardCol = (int)substr.at(4) - ASCII_CONVERTER_DIGIT;
        }
        else
        {
            tileChar = substr.at(1);
            tileShape = (int)substr.at(2) - ASCII_CONVERTER_DIGIT;
            boardRow = (int)substr.at(4) - ASCII_CONVERTER_LETTER;
            boardCol = (int)substr.at(5) - ASCII_CONVERTER_DIGIT;
        }

        Tile *newTile = new Tile(tileChar, tileShape);

        board->placeTile(newTile, boardRow, boardCol);

        iter++;
    }
}

void GameInit::loadBagState(std::string line6)
{
    std::stringstream ss(line6);

    while (ss.good())
    {
        std::string substr;
        std::getline(ss, substr, ',');
        char colour = substr.at(0);
        int shape = (int)substr.at(1);

        Tile *newTile = new Tile(colour, shape);
        bag->addBack(newTile);
    }
}

void GameInit::loadCurrPlayer(std::string line7)
{
    if (player1->getName().compare(line7))
    {
        currPlayer = player1;
    }
    else if (player2->getName().compare(line7))
    {
        currPlayer = player2;
    }
}

Player *GameInit::getPlayer1()
{
    return player1;
}

Player *GameInit::getPlayer2()
{
    return player2;
}

Board *GameInit::getBoard()
{
    return board;
}

LinkedList *GameInit::getBag()
{
    return bag;
}

int GameInit::getBHeight()
{
    return bHeight;
}

int GameInit::getBWidth()
{
    return bWidth;
}

Player *GameInit::getCurrPlayer()
{
    return currPlayer;
}