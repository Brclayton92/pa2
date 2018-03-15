#include <iostream>
#include "pa2.h"
using namespace std;

/*
 * LinkedList class methods start
 */

LinkedList::LinkedList(){
    head = nullptr;
    tail = nullptr;
    size = 0;
    initialSize = 32;

    for(int i = 0; i < initialSize; i++)
        this->LinkedList::addNode("Free");
}

void LinkedList::addNode(string _state) {
    node *state = new node;
    state -> data = _state;
    state -> next = nullptr;

    if (head == nullptr) {
        head = state;
        tail = state;
    }

    else {
        tail -> next = state;
        tail = tail -> next;
    }

    size++;
}

void LinkedList::printList(){
    string tempString;
    node *tempNode = head;

    for (int i = 0; i < size; i++) {
        tempString += tempNode -> data + " ";
        tempNode = tempNode -> next;
    }

    cout << tempString;
}

void LinkedList::bestFit(string progName, int sizeReq) {
    if (sizeReq % 4 == 0) {
        sizeReq = sizeReq / 4;
    }
    else {
        sizeReq = (sizeReq / 4) + 1;
    }
    node *start = head;
    node *temp = head;
    node *posStart = head;
    int smallestFit = size;
    int length = 0;

    //iterates through linked list
    for (int i = 0; i < size; i++){

        // check for free space where temp is currently pointing
        if (temp->data == "Free"){
            //if current node pointed to by temp is free, stores that nodes locations as a possible start, and increments length
            if (length == 0) {
                posStart = temp;
                length++;
            }

            //if node pointed to by temp is free and length != 0, increments length to count number of free spaces in a row
            else {
                length++;
            }
        }

        //if temp no longer points to a free node, checks if program will fit in current chunk, if it will, sets smallest fit to the length of current chunk
        if (temp->data != "Free") {
            if ((length >= sizeReq)){

                if (length < smallestFit){
                    smallestFit = length;
                    start = posStart;
                }
            }

            //resets length to 0 for use in next free chunk
            length = 0;
        }

        temp = temp->next;
    }

    //checks to ensure the final chunk of space in the linked list isnt the best fit, if it is best fit, start is set to posStart
    if(start != posStart) {
        temp = posStart;
        int counter = 0;
        while (temp) {
            counter++;
            temp = temp->next;
        }
        if(counter >= sizeReq && counter < smallestFit) {
            start = posStart;
        }
    }

    //assigns the program to it's appropriate place in memory
    for (int i = 0; i < sizeReq; i++) {
        start->data = progName;
        start = start->next;
    }
}

void LinkedList::killProgram(string progName) {
    node *temp = head;

    for (int i = 0; i < size; i++) {
        if (temp->data == progName){
            temp->data = "Free";
        }

        temp = temp->next;
    }
}

/*
 * LinkedList class methods end
 */

int main() {
    LinkedList list;
    list.printList();
    cout << endl << endl;
    list.bestFit("P1", 13);
    list.printList();
    cout << endl << endl;
    list.bestFit("P2", 9);
    list.printList();
    cout << endl << endl;
    list.bestFit("P3", 18);
    list.printList();
    cout << endl << endl;
    list.bestFit("P4", 21);
    list.printList();
    cout << endl << endl;
    list.bestFit("P5", 28);
    list.printList();
    cout << endl << endl;
    list.killProgram("P2");
    list.printList();
    cout << endl << endl;
    list.killProgram("P4");
    list.printList();
    cout << endl << endl;
    list.bestFit("p6", 8);
    list.printList();
    cout << endl << endl;
    list.bestFit("P8", 16);
    list.printList();
    cout << endl << endl;

    return 0;
}