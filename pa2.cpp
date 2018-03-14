#include <iostream>
#include "pa2.h"
using namespace std;

LinkedList::LinkedList(){
    head = NULL;
    tail = NULL;
    size = 0;
}

void LinkedList::addNode(string _state) {
    node *state = new node;
    state -> data = _state;
    state -> next = NULL;

    if (head == NULL) {
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

int main() {
    LinkedList list;
    list.addNode("free");
    list.addNode("free");
    list.addNode("P1");
    list.addNode("P1");
    list.addNode("P2");
    list.addNode("free");
    list.printList();

    return 0;
}