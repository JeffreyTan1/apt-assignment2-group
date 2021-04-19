
#include "LinkedList.h"

LinkedList::LinkedList() {
   head = nullptr;
}

LinkedList::LinkedList(LinkedList& other) 
{
   // TODO
}

LinkedList::~LinkedList() {
   delete head;
}

int LinkedList::size() {
   int count = 0;

   if (head != nullptr) {
      Node currentNode = *head;

      while (currentNode.next != nullptr) {
         count++;
         currentNode = *currentNode.next;
      }
      count++;
   }

   return count;
}

Tile* LinkedList::get(int index) {
   Tile* tile = nullptr;

   if (index >= 0 && index <= size() && head != nullptr){
      Node currentNode = *head;

      for (int i = 0; i < index; i++) {
         currentNode = *currentNode.next;
      }

      tile = currentNode.tile;
   }

   return tile;
}

void LinkedList::addFront(Tile* tile) {
   head = new Node(tile, head);
}

void LinkedList::addBack(Tile* tile) {
   if (head != nullptr) {
      Node currentNode = *head;
      while (currentNode.next != nullptr) {
         currentNode = *currentNode.next;
      }
      Node* newNode = new Node(tile);
      currentNode.setNext(newNode);
   }
}

void LinkedList::removeBack() {
   // TODO
}

void LinkedList::removeFront() {
   // TODO
}

void LinkedList::clear() {
   // TODO
}
