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
#define ASCII_CONVERTER_LETTER 65
using std::cin;
using std::cout;
using std::endl;

using std::atoi;
using std::ifstream;

GameInit::GameInit()
{
    board = new Board();

    bag = new LinkedList();

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

    //Create player 1 data structures
    cout << "Enter a name for player 1 (uppercase characters only)" << endl;
    std::string p1Name;
    cin >> p1Name;
    LinkedList *p1Hand = new LinkedList();
    for (int i = 0; i < 6; i++)
    {

        p1Hand->addBack(bag->get(0));
        bag->removeFront();
    }
    player1 = new Player(p1Name, 0, p1Hand);

    //Create player 2 data structures
    cout << "Enter a name for player 2 (uppercase characters only)" << endl;
    std::string p2Name;
    cin >> p2Name;
    LinkedList *p2Hand = new LinkedList();
    for (int i = 0; i < 6; i++)
    {
        p2Hand->addBack(bag->get(0));
        bag->removeFront();
    }
    player2 = new Player(p2Name, 0, p2Hand);
}

GameInit::GameInit(std::string filename)
{
    ifstream saveFile(filename);
    std::string input = NULL;
    //c-string for getline and get methods
    char line[256];

    //read player 1 data
    std::string p1Name;
    int p1Points;
    LinkedList *p1Hand = new LinkedList();

    saveFile >> p1Name;
    saveFile >> input;
    p1Points = stoi(input);

    saveFile.getline(line, 256);
    std::string convString(line);
    std::stringstream ss(convString);

    while (ss.good())
    {
        std::string substr;
        std::getline(ss, substr, ',');
        char colour = substr.at(0);
        int shape = (int)substr.at(1);

        Tile *newTile = new Tile(colour, shape);
        p1Hand->addBack(newTile);
    }

    player1 = new Player(p1Name, p1Points, p1Hand);

    //read player 2 data
    std::string p2Name;
    int p2Points;
    LinkedList *p2Hand = new LinkedList();

    saveFile >> p2Name;
    saveFile >> input;
    p2Points = stoi(input);

    saveFile.getline(line, 256);
    std::string convString2(line);
    std::stringstream ss2(convString2);

    while (ss.good())
    {
        std::string substr;
        std::getline(ss, substr, ',');
        char colour = substr.at(0);
        int shape = (int)substr.at(1);

        Tile *newTile = new Tile(colour, shape);
        p2Hand->addBack(newTile);
    }

    player2 = new Player(p2Name, p2Points, p2Hand);

    //read board size
    saveFile.getline(line, 256);
    std::string convString3(line);
    std::stringstream ss3(convString3);
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

    //read board state
    saveFile.getline(line, 256);
    std::string convString4(line);
    std::stringstream ss4(convString4);
    while (ss.good())
    {
        std::string substr;
        std::getline(ss, substr, ',');
        char tileChar = substr.at(0);
        int tileShape = (int)substr.at(1);

        int boardRow = substr.at(3) - ASCII_CONVERTER_LETTER;
        int boardCol = (int)substr.at(4);

        Tile *newTile = new Tile(tileChar, tileShape);

        board->placeTile(newTile, boardRow, boardCol);
    }

    //read bag
    saveFile.getline(line, 256);
    std::string convString5(line);
    std::stringstream ss5(convString5);

    while (ss.good())
    {
        std::string substr;
        std::getline(ss, substr, ',');
        char colour = substr.at(0);
        int shape = (int)substr.at(1);

        Tile *newTile = new Tile(colour, shape);
        bag->addBack(newTile);
    }

    //read current player
    saveFile >> input;

    if (player1->getName().compare(input))
    {
        currPlayer = player1;
    }
    else if (player2->getName().compare(input))
    {
        currPlayer = player2;
    }

    //End of initialiser
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