/*
 * File: pqueue.cpp (array version)
 * --------------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file implements the pqueue.h interface using a dynamic array as
 * the underlying representation.  Most of the code is already in place.
 * The only thing that is missing is the implementation of the actual
 * commands.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
using namespace std;

PriorityQueue::PriorityQueue() {
   // TODO: Fill in the necessary code
   capacity = INITIAL_CAPACITY;
   count = 0;
   array = new ValuePriorityPair[capacity];
}

PriorityQueue::~PriorityQueue() {
   // TODO: Fill in the necessary code
   delete [] array;
}

int PriorityQueue::size() {
   return count;  // TODO: Replace this line with the necessary code
}

bool PriorityQueue::isEmpty() {
   return count == 0;  // TODO: Replace this line with the necessary code
}

void PriorityQueue::clear() {
   // TODO: Fill in the necessary code
   count = 0;
}

void PriorityQueue::enqueue(string value, double priority) {
   // TODO: Fill in the necessary code
   if (count == capacity) expandCapacity();
   int slot = count - 1;
   //cout << value << priority << endl;
   while (array[slot].priority > priority && slot >= 0) {
       array[slot + 1].priority = array[slot].priority; //struct equal operation
       array[slot + 1].value = array[slot].value;
       slot--;
   }
   array[slot + 1].priority = priority;
   array[slot + 1].value = value;
   count++;
}

string PriorityQueue::dequeue() {
   if (isEmpty()) {
       cout << "The queue is empty." << endl;
       return "";
   }
   string value = array[0].value;
   for (int i = 0; i < count - 1; i++) {
       array[i].priority = array[i + 1].priority;
       array[i].value = array[i + 1].value;
   }
   count--;
   return value;  // TODO: Replace this line with the necessary code
}

string PriorityQueue::peek() {
    if (isEmpty()) {
        cout << "The queue is empty." << endl;
        return "";
    }
   return array[0].value;  // TODO: Replace this line with the necessary code
}

double PriorityQueue::peekPriority() {
    if (isEmpty()) {
        cout << "The queue is empty." << endl;
        return 0;
    }
   return array[0].priority;  // TODO: Replace this line with the necessary code
}

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * The constructor and assignment operators follow the standard
 * paradigm described in the textbook.
 */

PriorityQueue::PriorityQueue(const PriorityQueue & src) {
   deepCopy(src);
}

PriorityQueue & PriorityQueue::operator=(const PriorityQueue & src) {
   if (this != &src) {
      if (array != NULL) delete[] array;
      deepCopy(src);
   }
   return *this;
}
