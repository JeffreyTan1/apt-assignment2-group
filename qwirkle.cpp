
#include "LinkedList.h"

#include <iostream>
#include <exception>
#include <limits>

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
      while (cin.fail())
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
      //New game
      cout << "Choice 1 selected \n \n";
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