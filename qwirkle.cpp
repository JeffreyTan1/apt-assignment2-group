
#include "LinkedList.h"

#include <iostream>
#include <exception>

#define EXIT_SUCCESS    0

void runMenu(int userChoice, bool* stop);

int main(void) {
   LinkedList* list = new LinkedList();
   delete list;
   bool stop = false;
   bool* stopPtr = &stop;
   int userChoice;
   while(!stop) {
      std::cout << "Menu" << std::endl;
      std::cout << "---" << std::endl;
      std::cout << "1. New Game" << std::endl;
      std::cout << "2. Load game" << std::endl;
      std::cout << "3. Credits (Show student information)" << std::endl;
      std::cout << "4. Quit" << std::endl;
      std::cout << "> ";
      std::cin >> userChoice;
      while(std::cin.fail()) {
         std::cout <<"Invalid input, please try again \n> ";
         std::cin.clear();
         std::cin.ignore();
         std::cin >> userChoice;
      }
      runMenu(userChoice, stopPtr);
   }
   return EXIT_SUCCESS;
}

void runMenu(int userChoice, bool* stop) {
   if(userChoice==1) {
     //New game
     std::cout << "Choice 1 selected \n \n";
   }
   else if(userChoice==2) {
      //Load game
      std::cout << "Choice 2 selected \n \n";
   }
   else if(userChoice==3) {
      //Credits
      std::cout << "Choice 3 selected \n \n";
   }
   else if(userChoice==4) {
      //Quit
      std::cout << "Goodbye" << std::endl;
      *stop = true;
   }
}