#include "LinkedList.h"
#include "Node.h"
#include "Tile.h"

LinkedList::LinkedList()
{
   head = nullptr;
}

LinkedList::LinkedList(LinkedList &other)
{
   if (other.head != nullptr)
   {
      for (int i = 0; i < other.size(); i++)
      {
         Tile *tile = other.get(i);
         this->addBack(tile);
      }
      //If the other linked list is empty then just call normal constructor
   }
   else
   {
      LinkedList();
   }
}

LinkedList::~LinkedList()
{
   delete head;
}

int LinkedList::size()
{
   int count = 0;

   if (head != nullptr)
   {
      Node *currentNode = head;

      while (currentNode->getNext() != nullptr)
      {
         count++;
         currentNode = currentNode->getNext();
      }
      count++;
   }

   return count;
}

Tile *LinkedList::get(int index)
{
   Tile *rTile = nullptr;

   if (index >= 0 && index < size() && head != nullptr)
   {
      Node *currentNode = head;

      for (int i = 0; i < index; i++)
      {
         currentNode = currentNode->getNext();
      }

      rTile = currentNode->getTile();
   }

   return rTile;
}

void LinkedList::addFront(Tile *tile)
{
   if (head != nullptr)
   {
      head = new Node(tile, head);
   }
   else
   {
      head = new Node(tile);
   }
}

void LinkedList::addBack(Tile *tile)
{
   if (head != nullptr)
   {
      Node *currentNode = head;
      while (currentNode->getNext() != nullptr)
      {
         currentNode = currentNode->getNext();
      }
      Node *newNode = new Node(tile);
      currentNode->setNext(newNode);
   }
   else
   {
      head = new Node(tile);
   }
}

void LinkedList::removeBack()
{
   if (head != nullptr)
   {
      Node *currentNode = head;
      Node *previousNode = nullptr;
      bool cont = true;
      while (cont)
      {
         previousNode = currentNode;

         if (currentNode->getNext() != nullptr)
         {
            currentNode = currentNode->getNext();
         }
         else
         {
            cont = false;
         }
      }
      previousNode->setNextNullptr();
      delete currentNode;
      currentNode = nullptr;
   }
}

void LinkedList::removeFront()
{
   if (head != nullptr)
   {
      if (head->getNext() != nullptr)
      {
         Node *removeNode = head;
         head = head->getNext();
         delete removeNode;
      }
      else
      {
         delete head;
         head = nullptr;
      }
   }
}

void LinkedList::clear()
{
   delete head;
}

bool LinkedList::exists(Tile *tile)
{
   bool exists = false;
   if (head != nullptr)
   {
      Node *currentNode = head;
      bool cont = true;
      while (cont)
      {
         if ((currentNode->getTile())->equals(tile))
         {
            exists = true;
            break;
         }
         if (currentNode->getNext() != nullptr)
         {
            currentNode = currentNode->getNext();
         }
         else
         {
            cont = false;
         }
      }
   }

   return exists;
}

bool LinkedList::removeElement(Tile* tile) {
   //TO DO
   return true;
}

bool LinkedList::isEmpty() {
   //TO DO
   return true;
}