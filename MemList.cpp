// Copyright (c) 2018 Jason Graalum
//
// 
// MemList.cpp
//
// // Class implementation of MemList for New Beginnings Final Proficiency Exam
// 2018

#include "MemList.hpp"
#include "MemBlock.hpp"
#include <iostream>

/////////////////////////////////////////////////////////////////////////////////
// Level 0 Methods
/////////////////////////////////////////////////////////////////////////////////
// Default constructor which creates empty lists for both the Free and Reserved
// lists
//
// Level 0
//
MemList::MemList()
{
    free_head = NULL;
    reserved_head = NULL;
}
// Display the Free List
//
// Level 0
//
void MemList::displayFree() 
{
    std::cout << "Free Memory" << std::endl;
    MemBlock * current = free_head;
    free_head->printBlockInfoHeader();
    int count = 0;
    while(current) {
        current->printBlockInfo(count);
        current = current->getNext();
        count++;
    }
    std::cout << std::endl;
}

// Display the Reserved List
//
// Level 0
//
void MemList::displayReserved() 
{
    std::cout << "Reserved Memory" << std::endl;
    MemBlock * current = reserved_head;
    reserved_head->printBlockInfoHeader();

    int count = 0;
    while(current) {
        current->printBlockInfo(count);
        current = current->getNext();
        count++;
    }
    std::cout << std::endl;

}
/////////////////////////////////////////////////////////////////////////////////
// Level 1 Methods
/////////////////////////////////////////////////////////////////////////////////
// Parameterized constructor which create two lists of MemBlock 
// The Free List will contain a single MemBlock with all the memory(start_addr and mem_size)
// The Reserved List will be empty
//
// MemList = new MemList(start_addr, mem_size);
//
// Level 1
//
MemList::MemList(unsigned int s_addr, unsigned int block_size)
{
    // To be implemented(replace the two lines below)
   MemBlock * temp = new MemBlock;
   temp->setSize(block_size);
   temp->setAddr(s_addr); 
   
   free_head = temp; 

   mem_size = block_size;
   
   reserved_head = NULL;
}

// Find the first MemBlock in the Free list which greater than or equal to the amount requested(via 
// the function argument). Update the MemBlock in the Free List - change the start_addr and mem_size
// by the amount of memory being reserved.
// Add the newly reserved memory into a new MemBlock in the Reserved List
// If no MemBlock in the Free List is large enough return NULL, otherwise return a pointer to 
// the new MemBlock in the Reserved List.
//
// Level 1
//
MemBlock * MemList::reserveMemBlock(unsigned int block_size)
{

   MemBlock * temp = new MemBlock();
   temp->setSize(block_size);
   temp->setAddr(1000000); //hopefully you don't use one million as a test address
   temp->setNext(NULL);

    // if my first block is big enough, grab from there.
   if(free_head->getSize() >= block_size) {
      temp->setAddr(free_head->getAddr());
      //temp = free_head;
      free_head->setAddr(free_head->getAddr() + block_size);
      free_head->setSize(free_head->getSize() - block_size);
   } else { // otherwise look through all free blocks and do same
      MemBlock * current = free_head; 
      while(current->getNext() && (temp->getAddr() == 1000000)) {
         if(current->getSize() >= block_size) { //if a block is large enough
            temp->setAddr(current->getAddr()); //make that block's address my new reserved address
            current->setAddr(current->getAddr() + block_size); //scoot up the free block's address
            current->setSize(current->getSize() - block_size);
         }
         current = current->getNext();
         //current->setAddr(current->getNext()->getAddr()); // on to the next one
      }
   } 

// Now that the block has been grabbed, add it to reserved list
   if(temp->getAddr() != 1000000) { // if my previous loop changed address from default 
  //    return temp;
  // }

      if(reserved_head) { // Case 1: adding to extant reserved list; add before head
         temp->setNext(reserved_head);//         reserved_head = temp; //->setAddr(temp->getAddr());
         reserved_head = temp;
      } else { // Case 2: adding to empty reserved list
         reserved_head = temp;
         //reserved_head->setAddr(temp->getAddr());
      }   

   return temp;
   }
    return NULL;
}


// Return the total size of all blocks in the Reserved List
//
// Level 1
//
unsigned int MemList::reservedSize()
{
   unsigned int totalSize = 0; 
   MemBlock * current;
   // To be implemented
   if(!reserved_head) {
      return 0;
   } else {
      current = reserved_head;
      totalSize += current->getSize();
      while(current->getNext()) {
         current = current->getNext();
         totalSize += current->getSize();
      }
   }
   
   return totalSize;
}

// Return the total size of all blocks in the Free List
//
// Level 1
unsigned int MemList::freeSize()
{
   unsigned int totalSize = 0; 
   MemBlock * current;
   if(!free_head) {
      return 0;
   } else {
      current = free_head;
      totalSize += current->getSize();
      while(current->getNext()) {
         current = current->getNext();
         totalSize += current->getSize();
      }
   }
   
   return totalSize;
}

/////////////////////////////////////////////////////////////////////////////////
// Level 2 Methods
/////////////////////////////////////////////////////////////////////////////////
// Removes the MemBlock provided(via the pointer) from the Reserved List and adds it
// back into the Free List - it must be added back "in order of starting address".
//
// (Challenge) If the MemBlock to be freed does exist or it is a bad block(it overlaps 
// with a block in the Free list), return false.  Otherwise return true.
//
// Level 2
//
bool MemList::freeMemBlock(MemBlock * block_to_free)
{
    // To be implemented
    return false;
}



// Return a pointer to the MemBlock with the largest size from the Free List
//
// Level 2
//
MemBlock * MemList::maxFree() 
{
   MemBlock * current;
   MemBlock * largest_block;
   int largest_val = 0;

   if(free_head){
      current = free_head; 
      largest_val = current->getSize();
      largest_block = current;
      while(current->getNext()) {
         current = current->getNext();
         if(current->getSize() > largest_val) {
            largest_val = current->getSize();
            largest_block = current;
         }
      }
   }

   return largest_block;
}

// Return a pointer to the MemBlcok with the smallest size from the Free List
//
// Level 2
//
MemBlock * MemList::minFree()
{
    // To be implemented
    return NULL;
}

// Return the number of MemBlocks in the Free List
//
// Level 2
//
unsigned int MemList::freeBlockCount()
{
    // To be implemented
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////
// Level 3 Methods
/////////////////////////////////////////////////////////////////////////////////
// Iterate through the Free List - combine any blocks that are adjacent
// Return the number of MemBlocks removed
//
// Level 3
//
unsigned int MemList::defragFree()
{
    // To be implemented
    return 0;
}

// Return the start address of the smallest block that fits the size requested
// Ex:  MemList_Obj->minMax(100);  // Return the address of the smallest block 
//                                    that is greater than 100
// The return values are the same as in the "reserveMemBlock" member function.
//
// Level 3
//
MemBlock * MemList::reserveMinMemBlock(unsigned int)
{
    // To be implemented
    return NULL;
}




