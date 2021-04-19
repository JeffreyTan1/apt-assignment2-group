
#include "LinkedList.h"

LinkedList::LinkedList() {
   head = nullptr;
}

LinkedList::LinkedList(LinkedList& other) 
{
   if (other.head != nullptr)
   {
      for (int i = 0; i < other.size(); i++) {
      Tile* tile = other.get(i);
      this->addBack(tile);
   }
   //If the other linked list is empty then just call normal constructor
   } else {
      LinkedList();
   }
}

LinkedList::~LinkedList() {
   delete head;
}

int LinkedList::size() {
   int count = 0;

   if (head != nullptr) {
      Node* currentNode = head;

      while (currentNode->next != nullptr) {
         count++;
         currentNode = currentNode->next;
      }
      count++;
   }

   return count;
}

Tile* LinkedList::get(int index) {
   Tile* rTile = nullptr;

   if (index >= 0 && index <= size() && head != nullptr){
      Node *currentNode = head;

      for (int i = 0; i < index; i++) {
         currentNode = currentNode->next;
      }

      rTile = currentNode->tile;
   }

   return rTile;
}

void LinkedList::addFront(Tile* tile) {
   if (head != nullptr) {
      head = new Node(tile, head);
   } else {
      head = new Node(tile);
   }
}

void LinkedList::addBack(Tile* tile) {
   if (head != nullptr) {
      Node *currentNode = head;
      while (currentNode->next != nullptr) {
         currentNode = currentNode->next;
      }
      Node* newNode = new Node(tile);
      currentNode->setNext(newNode);
   }
}

void LinkedList::removeBack() {
   if (head != nullptr) {
      Node* currentNode = head;
      Node* previousNode = nullptr;
      while (currentNode->next != nullptr) {
         previousNode = currentNode;
         currentNode = currentNode->next;
      }
      previousNode->setNextNullptr();
      delete currentNode;
   }
}

void LinkedList::removeFront() {
   if (head != nullptr) {
      if (head->next != nullptr) {
         Node* removeNode = head;
         head = head->next;
         delete removeNode;
      } else {
         delete head;
         head = nullptr;
      }
   }
}

void LinkedList::clear() {
      delete head;
}
