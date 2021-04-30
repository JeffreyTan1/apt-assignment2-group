//Much of this header is from Timothy Wiley: PreRecVideos_w07/linkedlist

#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

class Node;

class Tile;

class LinkedList
{
public:
   LinkedList();
   LinkedList(LinkedList &other);
   ~LinkedList();

   /**
    * Return the current size of the Linked List.
    */
   int size();

   /**
    * Get the value at the given index.
    */
   Tile *get(int index);

   /**
    * Add the value to the back of the Linked List
    */
   void addBack(Tile *tile);

   /**
    * Add the value to the front of the Linked List
    */
   void addFront(Tile *tile);

   /**
    * Remove the value at the back of the Linked List
    */
   void removeBack();

   /**
    * Remove the value at the front of the Linked List
    */
   void removeFront();

   /**
    * Removes all values from the Linked List
    */
   void clear();

   /**
    * Checks if a tile exists in a Linked List
    */
   bool exists(Tile *tile);

   /**
    * Checks if a Linked List is empty
    */
   bool isEmpty();

   /**
    * Remove a given element from a Linked List
    */
   bool removeElement(Tile* tile);

private:
   Node *head;
};

#endif // ASSIGN2_LINKEDLIST_H
