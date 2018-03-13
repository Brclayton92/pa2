//
// Created by Brock on 3/13/2018.
//

#ifndef PA2_PA2_H
#define PA2_PA2_H

struct node {
    int data;
    node *next;
};

class LinkedList {
    private:
        node *head;
        node *tail;
        int size;

    public:
        LinkedList();
        void addNode();
};

#endif //PA2_PA2_H
