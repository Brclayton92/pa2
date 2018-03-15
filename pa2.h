//
// Created by Brock on 3/13/2018.
//

#ifndef PA2_PA2_H
#define PA2_PA2_H

using namespace std;
#include "string"

struct node {
    string data;
    node *next;
};

class LinkedList {
    private:
        node *head;
        node *tail;
        int size;
        int initialSize;

    public:
        LinkedList();
        void addNode(string _state);
        void printList();
        void bestFit(string progName, int sizeReq);
        void killProgram(string progName);
};

#endif //PA2_PA2_H
