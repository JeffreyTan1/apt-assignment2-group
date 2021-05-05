
#include "LinkedList.h"
#include <iostream>
#include <exception>
#include <limits>
#include "Board.h"
#include "GameInit.h"
#include "Game.h"

#define EXIT_SUCCESS 0

using std::cin;
using std::cout;
using std::endl;

void runMenu(int userChoice, bool *stop);

int main(void)
{
   cout << "Welcome to Qwirkle!" << endl;
   cout << "-------------------" << endl;

   LinkedList *list = new LinkedList();
   delete list;
   bool stop = false;
   bool *stopPtr = &stop;
   int userChoice;
   
   while (!stop)
   {
      cout << "Menu" << endl;
      cout << "---" << endl;
      cout << "1. New Game" << endl;
      cout << "2. Load game" << endl;
      cout << "3. Credits (Show student information)" << endl;
      cout << "4. Quit" << endl;
      cout << "> ";
      cin >> userChoice;
      while (cin.fail()||userChoice<1||userChoice>4)
      {
         cout << "Invalid input, please try again \n> ";
         cin.clear();
         cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
         cin >> userChoice;
      }
      runMenu(userChoice, stopPtr);
   }
   return EXIT_SUCCESS;
}

void runMenu(int userChoice, bool *stop)
{
   if (userChoice == 1)
   {
      cout << "Choice 1 selected \n \n";
      GameInit *gameInit = new GameInit();
      Game *game = new Game(gameInit->getPlayer1(), gameInit->getPlayer2(), gameInit->getBag(), gameInit->getBoard(), gameInit->getPlayer1());
      game->executeGameplay();
      delete game;
     
      //New game
      //why no ** ???
      // cout << "Choice 1 selected \n \n";
      // Board* board= new Board();
      // board->setBoard();
      // Tile* vent= new Tile('G',5);
      // Tile* vent2= new Tile('R',5);
      // board->addTile(vent,"A",3);
      // board->addTile(vent2,"B",4);
      // board->toString();

   }
   else if (userChoice == 2)
   {
      //Load game
      cout << "Choice 2 selected \n \n";
   }
   else if (userChoice == 3)
   {
      //Credits
      cout << "Choice 3 selected \n \n";
   }
   else if (userChoice == 4)
   {
      //Quit
      cout << "Goodbye" << endl;
      *stop = true;
   }
}