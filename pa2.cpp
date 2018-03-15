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
    sizeReq = sizeReq / 4;
    node *start = nullptr;
    node *temp = head->next;
    node *posStart = head->next;
    int smallestFit = size;
    int length = 0;

    for (int i = 0; i < size; i++){
        if (temp->data == "free" && length ==0){
            length++;
            posStart = temp;
        }

        else if (temp->data == "free"){
            length++;
        }

        else {
            if (length >= sizeReq){
                if (length < smallestFit){
                    start = posStart;
                }
            }

            length = 0;
        }

        temp = temp->next;
    }

    for (int i = 0; i < sizeReq; i++){
        start->data = progName;
        start = start->next;
    }
}

/*
 * LinkedList class methods end
 */

int main() {
    LinkedList list;
    list.bestFit("P1", 13);
    list.printList();

    return 0;
}