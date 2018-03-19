#include <iostream>
#include "pa2.h"
#include <limits>
using namespace std;

/*
 * LinkedList class methods start
 */

LinkedList::LinkedList(){
    head = nullptr;       // variable for first node in linked list
    tail = nullptr;       //variable for last node in linked list
    size = 0;             // keeps track of size of linked list
    initialSize = 32;     // variable for selecting initial size of linked list

    // creates the initial nodes of the linked list, initialsize variable determines number of nodes created
    for(int i = 0; i < initialSize; i++)
        this->LinkedList::addNode("Free");
}

//method for adding new nodes to Linked List
void LinkedList::addNode(string _state) {
    node *state = new node;      // creates a space in memeory for new Node
    state -> data = _state;      // assigns passed in string to data section of new node
    state -> next = nullptr;     //initializes the next link to null

    // statement triggered when adding first node, sets head and tail to only node in list
    if (head == nullptr) {
        head = state;
        tail = state;
    }

    //adds data to current tail and sets tail to next node
    else {
        tail -> next = state;
        tail = tail -> next;
    }

    size++;
}

// Creates a string representing the current state of data in linked list and prints it
void LinkedList::printList(){
    string tempString;
    node *tempNode = head;

    //iterates through the linked list adding data stored at each link to tempString variable
    for (int i = 0; i < size; i++) {
        if (i % 8 == 0){
            tempString += "\n";
        }

        if (tempNode->data != "Free"){
            tempString += tempNode -> data + "   ";
        }

        else{
            tempString += tempNode -> data + " ";
        }

        tempNode = tempNode -> next;
    }

    cout <<  tempString;
}

//method used to add new programs when Best Fit is selected via command line arguement
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
    int avilableMem = 0;

    //checks to see if any memory is available before entering method body
    for (int i = 0; i < size; i++) {
        if (temp->data == "Free") {
            avilableMem++;
        }

        temp = temp->next;
    }

    temp = head;

    if (avilableMem == 0){
        cout << "Error, Not enough memory for Program " << progName << endl;
        return;
    }

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
    if(start != posStart) {
        temp = posStart;
        int counter = 0;

        while (temp && (temp->data == "Free")) {
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

    // displays error message if program is too large for available memory
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
        while (temp && temp->data == "Free") {
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

// method used to remove programs from memory as user's request
void LinkedList::killProgram(string progName) {
    node *temp = head;          //temporary variable used to move through linked list
    int memoryReclaimed = 0;    // variable tracks how much memory is being reclaimed

    // moves through linked list setting node data that match passed in string to "Free"
    for (int i = 0; i < size; i++) {
        if (temp->data == progName){
            temp->data = "Free";
            memoryReclaimed++;
        }

        temp = temp->next;
    }

    // Error message triggered with user tries to remove program that doesn't exist in memory
    if (memoryReclaimed == 0) {
        cout << "Error, no program named " << progName << " exists in memory.";
        return;
    }

    cout << "Program " << progName << " successfully killed, " << memoryReclaimed << " page(s) reclaimed.";
}

// Method counts number of fragments
void LinkedList::fragmentCheck() {
    node *temp = head;         //temp variable used to move through linked list
    int numFragments = 0;      // Tracks number of fragments found
    bool newFragment = false;  // variable used to keep track of when a previous fragment has eneded

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

        // increments numFragments if program is encountered when newFragment is set to true
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
    string cmdLine; // variable that stores command line arguement "best" or "worst"

    // input validation statement to prevent crash if commandline arguements are left blank
    if (argv[1] == nullptr) {
        cmdLine = "";
    }

    // sets cmdLine to command line arguement entered by user
    else {
        cmdLine = argv[1];
    }

    LinkedList memoryList;      // Linked list used to store programs
    int memorySelection = 0;   // variable used as arguement in switch statement, stores users menu choice
    string programName = " ";  //variable used to stores program names entered by user
    int programSize = 0;       //variable used to store program size entered by user

    // if statement that selects best fit algorithm if command line arguement is "best"
    if (cmdLine == "best") {
        while (memorySelection != 5) {
            cout << endl << endl << "Using best fit algorithm" << endl;
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
                // adds program using best case algorithm
                case 1:
                    cout << "Program name - ";
                    cin >> programName;
                    cout << endl;
                    cout << "Program Size (KB) - ";
                    cin >> programSize;

                    //input validation for negative entries by user
                    if (programSize < 1) {
                        cout << "Invalid input, program size must be greater than zero." << endl;
                        break;
                    }

                    cout << endl;
                    memoryList.bestFit(programName, programSize);  // calls best fit algorithm method
                    break;

                 // kills program entered by user
                case 2:
                    cout << "Program name - " << endl;
                    cin >> programName;
                    memoryList.killProgram(programName);
                    break;

                 // calls method that counts number of fragments
                case 3:
                    memoryList.fragmentCheck();
                    break;

                // Call method that prints current memory state
                case 4:
                    memoryList.printList();
                    break;

                // terminates program
                case 5:
                    return 0;

                // default case used to print input validation error message to the screen
                default:
                    cout << "Error, invalid input. Please input an integer between 1 and 5";
                    break;
            }
        }
    }
        // if statement that selects worst fit algorithm if command line arguement is "worst"
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
                // adds program using worst case algorithm
                case 1:
                    cout << "Program name - ";
                    cin >> programName;
                    cout << endl;
                    cout << "Program Size (KB) - " ;
                    cout << endl;
                    cin >> programSize;

                    //input validation for negative entries by user
                    if (programSize < 1) {
                        cout << "Invalid input, program size must be greater than zero." << endl;
                        break;
                    }

                    memoryList.worstFit(programName, programSize);  // calls method that uses worst fit algorithm
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