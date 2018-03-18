#include <iostream>
#include "pa2.h"
#include <limits>
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

//method for adding new nodes to Linked List
void LinkedList::addNode(string _state) {
    node *state = new node;      // creates a space in memeory for new Node
    state -> data = _state;      // assigns passed in string to data section of new node
    state -> next = nullptr;     //

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
        if (i % 8 == 0){
            tempString += "\n";
        }
        tempString += tempNode -> data + " ";
        tempNode = tempNode -> next;
    }

    cout << tempString;
}

void LinkedList::bestFit(string progName, int sizeReq) {
    if (sizeReq % 4 == 0) {
        sizeReq = sizeReq / 4;          // converts size input by user from KB to number of nodes
    }
    else {
        sizeReq = (sizeReq / 4) + 1;   // converts size input by user from KB to number of nodes
    }
    node *start = nullptr;                // value that stores the starting position of the best fitting chunk
    node *temp = head;                // temp value used to move through linked list
    node *posStart = head;            // value that temporarily holds the starting position of each chunk
    int smallestFit = size;           // used to track the smallest chunk encountered as temp moves through the linked list
    int length = 0;                   // used to track the length of the current chunk

    // prevents entry of a program name that already exists in memory list
    for (int i = 0; i < size; i++) {
        if (temp->data == progName) {
            cout << "Error, Program " << progName << " already running." << endl;
            return;
        }

        temp = temp -> next;
    }

    temp = head;

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

    //checks to ensure the final chunk of space in the linked list isn't the best fit, if it is best fit, start is set to posStart
    if(start != posStart /*|| !start*/) {
        temp = posStart;
        int counter = 0;
        while (temp) {
            counter++;
            temp = temp->next;
        }

        if(counter >= sizeReq && counter <= smallestFit) {
            start = posStart;
        }
    }

    //assigns the program to it's appropriate nodes in memory if start != null
    if (start) {
        for (int i = 0; i < sizeReq; i++) {
            start->data = progName;

            if (start->next != nullptr) {
                start = start->next;
            }
        }
    }

    // displays error message is program is too large for available memory
    if (!start){
        cout << "Error, Not enough memory for Program " << progName << endl;
        return;
    }

    cout << "Program " << progName << " added successfully: " << sizeReq << " page(s) used.";
}

void LinkedList::worstFit(string progName, int sizeReq) {
    if (sizeReq % 4 == 0) {
        sizeReq = sizeReq / 4;          // converts size input by user from KB to number of nodes
    }
    else {
        sizeReq = (sizeReq / 4) + 1;   // converts size input by user from KB to number of nodes
    }
    node *start = nullptr;                // value that stores the starting position of the worst fitting chunk
    node *temp = head;                // temp value used to move through linked list
    node *posStart = head;            // value that temporarily holds the starting position of each chunk
    int largestFit = 0;           // used to track the largest chunk encountered as temp moves through the linked list
    int length = 0;                   // used to track the length of the current chunk


    // prevents entry of a program name that already exists in memory list
    for (int i = 0; i < size; i++) {
        if (progName ==  temp -> data){
            cout << "Error, Program " << progName << " already running." << endl;
            return;
        }
        temp = temp -> next;
    }

    temp = head;

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

        //if temp no longer points to a free node, checks if program will fit in current chunk, if it will, sets largest fit to the length of current chunk
        if (temp->data != "Free") {
            if ((length >= sizeReq)){
                if (length > largestFit){
                    largestFit = length;
                    start = posStart;
                }
            }

            //resets length to 0 for use in next free chunk
            length = 0;
        }

        temp = temp->next;
    }

    //checks to ensure the final chunk of space in the linked list isn't the worst fit, if it is worst fit, start is set to posStart
    if(start != posStart) {
        temp = posStart;
        int counter = 0;
        while (temp) {
            counter++;
            temp = temp->next;
        }

        if(counter >= sizeReq && counter > largestFit) {
            start = posStart;
        }
    }

    //assigns the program to it's appropriate nodes in memory if start != null
    if (start) {
        for (int i = 0; i < sizeReq; i++) {
            start->data = progName;
            if (start->next != nullptr) {
                start = start->next;
            }
        }
    }

    // displays error message is program is too large for available memory
    if (!start){
        cout << "Error, Not enough memory for Program " << progName << endl;
        return;
    }

    cout << "Program " << progName << " added successfully: " << sizeReq << " page(s) used.";
}

void LinkedList::killProgram(string progName) {
    node *temp = head;
    int memoryReclaimed = 0;

    for (int i = 0; i < size; i++) {
        if (temp->data == progName){
            temp->data = "Free";
            memoryReclaimed++;
        }

        temp = temp->next;
    }

    cout << "Program " << progName << " successfully killed, " << memoryReclaimed << " page(s) reclaimed.";
}

// Method counts number of fragments
void LinkedList::fragmentCheck() {
    node *temp = head;
    int numFragments = 0;
    bool newFragment = false;

    // Checks the first node for data and increments numFragments if it contains data
    if (temp->data != "Free"){
        numFragments++;
    }

    //iterates through linked list
    for (int i = 0; i < size; i++){

        // if the end of a fragments is found, newFragment becomes true
        if (temp->data == "Free"){
            newFragment = true;
        }

        // increments numFragments if
        if (temp->data != "Free"){
            if (newFragment){
                numFragments++;
                newFragment = false;
            }
        }

        temp = temp->next;
    }

    cout << "There is(are) " << numFragments << " fragment(s)" << endl;
}

/*
 * LinkedList class methods end
 */

int main(int argc, char *argv[]) {
    string cmdLine;

    if (argv[1] == nullptr) {
        cmdLine = "";
    }

    else {
        cmdLine = argv[1];
    }

    LinkedList memoryList;
    int memorySelection = 0;
    string programName = " ";
    int programSize = 0;

    if (cmdLine == "best") {
        while (memorySelection != 5) {
            cout << endl << "Using best fit algorithm" << endl;
            cout << endl;
            cout << "1. Add program" << endl;
            cout << "2. Kill program" << endl;
            cout << "3. Fragmentation" << endl;
            cout << "4. Print memory" << endl;
            cout << "5. Exit" << endl;

            cout << endl;
            cout << "choice - ";

            cin >> memorySelection;

            // if statement ensures user input is of proper type
            if (cin.fail()) {
                cin.clear();
                std::cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

                // setting memorySelection to -1 triggers default (input validation) case in switch statement
                memorySelection = -1;
            }

            cout << endl;

            switch (memorySelection) {
                case 1:
                    cout << "Program name - ";
                    cin >> programName;
                    cout << endl;
                    cout << "Program Size (KB) - ";
                    cin >> programSize;

                    if (programSize < 1) {
                        cout << "Invalid input, program size must be greater than zero." << endl;
                        break;
                    }

                    cout << endl;
                    memoryList.bestFit(programName, programSize);
                    break;

                case 2:
                    cout << "Program name - " << endl;
                    cin >> programName;
                    memoryList.killProgram(programName);
                    break;

                case 3:
                    memoryList.fragmentCheck();
                    break;

                case 4:
                    memoryList.printList();
                    break;

                case 5:
                    return 0;

                default:
                    cout << "Error, invalid input. Please input an integer between 1 and 5";
                    break;
            }
        }
    }

    else if (cmdLine == "worst") {
        while (memorySelection != 5) {
            cout << endl << endl << "Using worst fit algorithm" << endl;
            cout << endl;
            cout << "1. Add program" << endl;
            cout << "2. Kill program" << endl;
            cout << "3. Fragmentation" << endl;
            cout << "4. Print memory" << endl;
            cout << "5. Exit" << endl;

            cout << endl;
            cout << "choice - ";
            cin >> memorySelection;

            // if statement ensures user input is of proper type
            if (cin.fail()) {
                cin.clear();
                std::cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

                // setting memorySelection to -1 triggers default (input validation) case in switch statement
                memorySelection = -1;
            }

            cout << endl;

            switch (memorySelection) {
                case 1:
                    cout << "Program name - ";
                    cin >> programName;
                    cout << endl;
                    cout << "Program Size (KB) - " ;
                    cout << endl;
                    cin >> programSize;

                    if (programSize < 1) {
                        cout << "Invalid input, program size must be greater than zero." << endl;
                        break;
                    }

                    memoryList.worstFit(programName, programSize);
                    break;

                case 2:
                    cout << "Program name - " << endl;
                    cin >> programName;
                    memoryList.killProgram(programName);
                    break;

                case 3:
                    memoryList.fragmentCheck();
                    break;

                case 4:
                    memoryList.printList();
                    break;

                case 5:
                    return 0;

                default:
                    cout << "Error, invalid input. Please input an integer between 1 and 5";
                    break;
            }
        }
    }

    else {
        cout << "Error, invalid or missing command line argument. Please enter 'best' or 'worst' in command line.";
    }

    return 0;
}