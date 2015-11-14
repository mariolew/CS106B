/*
 * File: pqueue.cpp (heap version)
 * -------------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file implements the pqueue.h interface using a heap as the
 * underlying representation.  Only the copy constructor and assignment
 * operator are included.  Your job is to include definitions for the
 * other exported methods and to make a change to the definition of the
 * assignment operator so that it deletes any old storage.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
using namespace std;

// TODO: Add your method definitions here

/*
 * Constructor: PriorityQueue
 * Usage: PriorityQueue pq;
 * ---------------------------
 * Initializes a new priority queue, which is initially empty.
 */

PriorityQueue::PriorityQueue() {
    capacity = INITIAL_CAPACITY;
    count = 0;
    array = new ValuePriorityPair[capacity];
}

/*
 * Destructor: ~PriorityQueue
 * --------------------------
 * Frees any array storage associated with this priority queue.
 */

PriorityQueue::~PriorityQueue() {
    delete [] array;
}

/*
 * Method: size
 * Usage: int n = pq.size();
 * -------------------------
 * Returns the number of values in the priority queue.
 */

int PriorityQueue::size() {
    return count;
}

/*
 * Method: isEmpty
 * Usage: if (pq.isEmpty()) ...
 * ----------------------------
 * Returns true if the priority queue contains no elements.
 */

bool PriorityQueue::isEmpty() {
    return count == 0;
}

/*
 * Method: clear
 * Usage: pq.clear();
 * ------------------
 * Removes all elements from the priority queue.
 */

void PriorityQueue::clear() {
    count = 0;
}

/*
 * Method: enqueue
 * Usage: pq.enqueue(value, priority);
 * -----------------------------------
 * Adds value to the queue with the specified priority.  Lower priority
 * numbers correspond to higher priorities, which means that all
 * priority 1 elements are dequeued before any priority 2 elements.
 * If not specified, the priority is set to 1.
 */

void PriorityQueue::enqueue(std::string value, double priority) {
    if (count == capacity) expandCapacity();
    int index = count;
    array[index].value = value;
    array[index].priority = priority;
    int parent = (index - 1) / 2;
    while (array[parent].priority >= array[index].priority && index != 0) {
        swap(parent, index);
        index = parent;
        parent = (index - 1) / 2;
    }
    count++;
    /* DEBUG
    for (int i = 0;i < count;i++) {
        cout << "haha" << array[i].priority << endl;
    }*/
}

/*
 * Method: dequeue
 * Usage: std::string first = pq.dequeue();
 * ------------------------------
 * Removes and returns the highest priority value.  If multiple
 * entries in the queue have the same priority, those values are
 * dequeued in the same order in which they were enqueued.
 */

string PriorityQueue::dequeue() {
    if (isEmpty()) {
        cout << "The queue is empty." << endl;
        return "";
    }
    string result = array[0].value; //cout << "haha" << array[count - 1].priority << endl;
    array[0] = array[count - 1];
    count--;
//    if (count > 1) {
//        int index = 1;
//        if (count > 2 && array[1].priority > array[2].priority) {
//            index = 2;
//        }
//        swap(0, index);
//    }
    swapRec(0);

    return result;
}

/*
 * Method: peek
 * Usage: std::string first = pq.peek();
 * ---------------------------
 * Returns the value of highest priority in the queue, without
 * removing it.
 */

string PriorityQueue::peek() {
    if (isEmpty()) {
        cout << "The queue is empty." << endl;
        return "";
    }
    return array[0].value;
}

/*
 * Method: peekPriority
 * Usage: double priority = pq.peekPriority();
 * -------------------------------------------
 * Returns the priority of the first element in the queue, without
 * removing it.
 */

double PriorityQueue::peekPriority() {
    if (isEmpty()) {
        cout << "The queue is empty." << endl;
        return -1;
    }
    return array[0].priority;
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
      // TODO: Include code to delete any data from the old queue
      if (array !=NULL) delete [] array;
      deepCopy(src);
   }
   return *this;
}
