
#include "LinkedList.h"

#include <iostream>

#define EXIT_SUCCESS    0

void runMenu(int userChoice);

int main(void) {
   LinkedList* list = new LinkedList();
   delete list;
   std::cout << "Menu" << std::endl;
   std::cout << "---" << std::endl;
   std::cout << "1. New Game" << std::endl;
   std::cout << "2. Load game" << std::endl;
   std::cout << "3. Credits (Show student information)" << std::endl;
   std::cout << "4. Quit" << std::endl;

   return EXIT_SUCCESS;
}

void runMenu(int userChoice) {
   if(userChoice==1) {
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