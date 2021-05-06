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

bool LinkedList::isEmpty()
{
   bool empty = false;
   if (head == nullptr)
   {
      empty = true;
   }
   return empty;
}

std::string LinkedList::toString()
{
   std::string linkedListString = "";
   if (head != nullptr)
   {
      Node *currentNode = head;
      bool cont = true;
      while (cont)
      {
         linkedListString = linkedListString + currentNode->getTile()->toString();

         if (currentNode->getNext() == nullptr)
         {
            cont = false;
         }
         else
         {
            linkedListString = linkedListString + ",";
            currentNode = currentNode->getNext();
         }
      }
   }

   return linkedListString;
}

void LinkedList::removeElement(Tile *tile)
{

   if (head != nullptr)
   {
      Node *previousNode = nullptr;
      Node *currentNode = head;
      bool cont = true;

      while (cont)
      {
         //If the tile is identified
         if (currentNode->getTile()->equals(tile))
         {
            //check for if current node has a next node
            if (currentNode->getNext() != nullptr)
            {
               //HAS NEXT NODE CONDITION

               //check for if current node has a previous node
               if (previousNode != nullptr)
               {
                  previousNode->setNext(currentNode->getNext());
                  delete currentNode;
               }
               // else node which contians tile is at the head of LL which has other nodes
               else
               {
                  head = currentNode->getNext();
                  delete currentNode;
               }
            }
            else
            {
               //DOES NOT HAVE NEXT NODE CONDITION

               //check if current node has a previous node
               if (previousNode != nullptr)
               {
                  //node is at the end of the LL
                  previousNode->setNextNullptr();
               }
               else
               {
                  //node is head of a LL which just has the one node
                  delete head;
                  head = nullptr;
               }
            }
            //end while loop
            cont = false;
         }

         // if node is not found in this iteration then the node must be further on in the list
         // we assume that the tile will always be contained by a node in the LL if removeElement is called
         else
         {
            previousNode = currentNode;
            currentNode = currentNode->getNext();
         }
      }
   }
}