/*
 * File: pqueue.cpp (linked-list version)
 * --------------------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file implements the pqueue.h interface using a linked list as the
 * underlying representation.  Only the copy constructor and assignment
 * operator are included.  Your job is to include definitions for the
 * other exported methods.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
using namespace std;

// TODO: Add your method definitions here
PriorityQueue::PriorityQueue() {
    count = 0;
    head = NULL;
}

PriorityQueue::~PriorityQueue() {
   /* Cell * cp = head;
    while (cp != NULL) {
        Cell * old = cp;
        cp = cp->link;
        delete old;
    }*/
    /* while (!isEmpty()) {
        dequeue();
    }*/
    clear();
}

int PriorityQueue::size() {
   return count;  // TODO: Replace this line with the necessary code
}

bool PriorityQueue::isEmpty() {
   return count == 0;  // TODO: Replace this line with the necessary code
}

void PriorityQueue::clear() {
   // TODO: Fill in the necessary code
    while (!isEmpty()) {
        dequeue();
    }
}

void PriorityQueue::enqueue(string value, double priority) {
   // TODO: Fill in the necessary code
   Cell * cp = new Cell;
   cp->value = value;
   cp->priority = priority;
   cp->link = NULL;
   if (head == NULL || head->priority > priority) {
       cp->link = head;
       head = cp;
   }
   else {
       Cell * iter = head;
       while (iter->link != NULL) {
           if (iter->link->priority > priority)
               break;
           iter = iter->link;
       }
       cp->link = iter->link;
       iter->link = cp;
   }
   //tail = cp;
   count++;
}

string PriorityQueue::dequeue() {
   // TODO: Replace this line with the necessary code
    if (isEmpty()) {
        cout << "The queue is empty." << endl;
        return "";
    }
    string result = head->value;
    Cell * cp = head;
    head = cp->link;
    delete cp;
    count--;
    return result;
}

string PriorityQueue::peek() {
    if (isEmpty()) {
        cout << "The queue is empty." << endl;
        return "";
    }
   return head->value;  // TODO: Replace this line with the necessary code
}

double PriorityQueue::peekPriority() {
    if (isEmpty()) {
        cout << "The queue is empty." << endl;
        return 0;
    }
   return head->priority;  // TODO: Replace this line with the necessary code
}
/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * The constructor and assignment operators follow a standard paradigm,
 * as described in the textbook.
 */

PriorityQueue::PriorityQueue(const PriorityQueue & src) {
   deepCopy(src);
}

PriorityQueue & PriorityQueue::operator=(const PriorityQueue & src) {
   if (this != &src) {
      clear();
      deepCopy(src);
   }
   return *this;
}
