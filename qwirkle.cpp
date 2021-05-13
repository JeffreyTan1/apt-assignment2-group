
#include "LinkedList.h"
#include "GameInit.h"
#include "Game.h"
#include "Player.h"

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
      while (cin.fail() || userChoice < 1 || userChoice > 4)
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
      cout << "Starting a New Game" << endl
           << endl;
      GameInit *gameInit = new GameInit();
      Game *game = new Game(gameInit->getPlayer1(), gameInit->getPlayer2(), gameInit->getBag(), gameInit->getBoard(), gameInit->getCurrPlayer());
      game->executeGameplay(false);
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
      std::string fileName;
      cout << "Enter the filename from which to load a game" << endl;
      cin >> fileName;
      try
      {
         GameInit *gameInit = new GameInit(fileName);
         cout << "Qwirkle game successfully loaded" << endl;
         Game *game = new Game(gameInit->getPlayer1(), gameInit->getPlayer2(), gameInit->getBag(), gameInit->getBoard(), gameInit->getCurrPlayer());
         delete gameInit;
         game->executeGameplay(true);
         delete game;
      }
      catch (const std::invalid_argument &e)
      {
         cout << "File not found!" << endl;
      }
   }
   else if (userChoice == 3)
   {
      //Credits
      cout << "Choice 3 selected \n \n";
      std::string names[4] = {"Jeffrey Tan", "Mohammad Mahir Haque", "Sharshwot Karki", "Sidhra Fernando-Plant"};
      std::string studentIds[4] = {"S3851781",
                                   "S3815004",
                                   "S3841123",
                                   "S3873756"};
      std::string emailExt = "@student.rmit.edu.au";
      std::string emails[4] = {studentIds[0] + emailExt,
                               studentIds[1] + emailExt,
                               studentIds[2] + emailExt,
                               studentIds[3] + emailExt};

      cout << "---------------------------------------" << endl;
      for (int i = 0; i < 4; i++)
      {
         cout << "Name: " << names[i] << endl;
         cout << "Student ID: " << studentIds[i] << endl;
         cout << "Email: " << emails[i] << endl
              << endl;
      }
      cout << "---------------------------------------" << endl;
   }
   else if (userChoice == 4)
   {
      //Quit
      cout << "Goodbye" << endl;
      *stop = true;
   }
}