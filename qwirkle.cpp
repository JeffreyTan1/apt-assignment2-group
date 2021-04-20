
#include "LinkedList.h"

#include <iostream>
#include <exception>

#define EXIT_SUCCESS    0

void runMenu(int userChoice);

int main(void) {
   LinkedList* list = new LinkedList();
   delete list;
   int userChoice;
   std::cout << "Menu" << std::endl;
   std::cout << "---" << std::endl;
   std::cout << "1. New Game" << std::endl;
   std::cout << "2. Load game" << std::endl;
   std::cout << "3. Credits (Show student information)" << std::endl;
   std::cout << "4. Quit" << std::endl;
   std::cout << "> ";
   try {
      std::cin >> userChoice;
      if(std::cin.fail()) {
         throw std::invalid_argument("Invalid input, please try again");
      }
      runMenu(userChoice);
   }
   catch(std::invalid_argument& e) {
      std::cout << e.what() << std::endl << std::endl;
      std::cin.clear();
   }
   return EXIT_SUCCESS;
}

void runMenu(int userChoice) {
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
   }
}