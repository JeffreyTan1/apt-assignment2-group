
#include "LinkedList.h"

#include <iostream>

#define EXIT_SUCCESS    0

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
