#include <iostream> // including iostream library
using namespace std;// using namespace to simplify the code

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20; // declaring constants to set max and min values
//making the class of doublylinkedlist
class DoublyLinkedList {
//private means they can only be accessed by the class's own method
private:
//defining a structure named node
    struct Node {
        int data;
        //pointer for previous and next node on the list
        Node* prev;
        Node* next;
        //constructor for the new node
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;// pointer that will always point to the first node
    Node* tail;// pointer that will always point to the last node

public:// public so it can be accessed outside the class
    DoublyLinkedList() { head = nullptr; tail = nullptr; }//constructor for DoublyLinkedList class, classed when a new list is made
// this insert after inserts a new node with given values
    void insert_after(int value, int position) {
        //checking if the position is not negative
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }
        //creating a new node on the heap with specific values
        Node* newNode = new Node(value);
        //checking if the list is empty, if the list is empty the new node becomes both head and tail
        if (!head) {
            head = tail = newNode;
            return;
        }
        //creating a temporary pointer temp and setting on the start of the list
        Node* temp = head;
        //looping to move the temp pointer position times to find the node after which the user insert the new node
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        //checking if the pointer is out of bounds
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; //deleting a newnode to prevent memory leak
            return;
        }

        newNode->next = temp->next; // set the next pointer of the new node to point to what the current node's next was
        newNode->prev = temp; // set the prev pointer of the new node to pointthe current node
        if (temp->next) // checking if there is a node after the current one
            temp->next->prev = newNode;//updating the prev pointer to point at the new node
        else //temp was the last node
            tail = newNode;// the new node is the tail
        temp->next = newNode;
    }
    //method to delete the first node with the specific value
    void delete_val(int value) {
        if (!head) return;// if the list is empty just exit

        Node* temp = head;//creating a temp pointer which starts at the head
        
        while (temp && temp->data != value)// this loop goes through the list until it finds the node with the matching value or reaches the end
            temp = temp->next;

        if (!temp) return; //if the value is null or empty exit

        if (temp->prev)// if the node to be deleted has a previous node
            temp->prev->next = temp->next;//prev node pointer skips to the next node
        else// if the node is the head
            head = temp->next; // the next node becomes the head

        if (temp->next)// if the node to be deleted has a next nede
            temp->next->prev = temp->prev;// next's node prev pointer skips and goes to the prevnode
        else// if the node to be deleted is the tail
            tail = temp->prev; // tail gets updated to the previous node

        delete temp;// deallocates the memory for the node being deleted to prevent a memory leak.
    }

    void delete_pos(int pos) {//method to delete a node on a specific position
        if (!head) {//if the list is empty just exit
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {// if the wanted position is the first one just pop the first one
            pop_front();
            return;
        }
    
        Node* temp = head;//creating a temp pointer which starts at the head
    
        for (int i = 1; i < pos; i++){//moving temp to a specific position which is pos
            if (!temp) {// checking out of bound of the list
                cout << "Position doesn't exist." << endl;
                return;
            }
            else // if not at the end, move to the next node
                temp = temp->next;
        }
        if (!temp) {// checking again to see is the pos exists
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {// checking to see if the node is the last one
            pop_back();// if so, delete the last node by popback
            return;
        }
    
        Node* tempPrev = temp->prev;// gets the node before the one we want to delete
        tempPrev->next = temp->next;// the previous node's next pointer skips the node deleting
        temp->next->prev = tempPrev;// the next nodes' previous pointer skips the node deleting
        delete temp;//deleting the temp to free the memory
    }

    void push_back(int v) {// method that adds a new node with value v to the endof the list
        Node* newNode = new Node(v);// creates a new Node on the heap with the value v
        if (!tail)// checking if the list is empty
            head = tail = newNode;// if so new node becomes both head and tail
        else {// list not empty
            tail->next = newNode;// the current tail's next pointer is set to the new node
            newNode->prev = tail;// the new node's prev pointer is set the the previous node 
            tail = newNode;// tail pointer updated
        }
    }
    
    void push_front(int v) { // method that adds a new node with value v to the front of the list
        Node* newNode = new Node(v);// creates a new Node on the heap with the value v
        if (!head)// checking if the list is empty
            head = tail = newNode;// if so new node becomes both head and tail
        else {// list not empty
            newNode->next = head;// the new node's next pointer is set the the current head 
            head->prev = newNode;// the current head's prev pointer is set to the new node
            head = newNode;// the list's head pointer is updated to be the new node
        }
    }
    
    void pop_front() {//method removes the first node from the list

        if (!head) {// checking if the list is empty
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;//creating a temp pointer which starts at the head

        if (head->next) {// checking is there is more than one node
            head = head->next; // head pointer moved to the next one
            head->prev = nullptr;// new node prev pointer set to null
        }
        else// if there was only one node, list is empty so head and tail is null
            head = tail = nullptr;
        delete temp;// freeing up the memory
    }

    void pop_back() {//method removes the last node from the list
        if (!tail) {// checking if the list is empty
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;//creating a temp pointer which starts at the tail

        if (tail->prev) {
            tail = tail->prev;// tail pointer moved to the prev one
            tail->next = nullptr;// new node next pointer set to null because it is the last one now
        }
        else// the list has only one node, list is empty so head and tail is null
            head = tail = nullptr;
        delete temp;// freeing up the memory
    }
    //destructor of the class, automatically called when object goes out of scope
    ~DoublyLinkedList() {
        while (head) {// loop continues while the list is not empty
            Node* temp = head;// creates a temporary pointer to the current head
            head = head->next;//moving the head pointer to the next node
            delete temp; //freeing the memory
        }
    }
    void print() {//method prints all the elements of the list from head to tail
        Node* current = head; //creating a pointer starting at the head
        if (!current) {// checking if the list is empty
            cout << "List is empty." << endl;// if so print a message and exit
            return;
        }
        while (current) {// loop continues while the current is not at null
            cout << current->data << " ";// printing data of the current one
            current = current->next;// moving the pointer to the next node
        }
        cout << endl;
    }

    void print_reverse() {//method prints all the elements of the list from tail to head so reverse
        Node* current = tail;//creating a pointer starting at the tail
        if (!current) { // checking if the list is empty
            cout << "List is empty." << endl;// if so print a message and exit
            return;
        }
        while (current) {// loop continues while the current is not at null
            cout << current->data << " ";// printing data of the current one
            current = current->prev;// moving the pointer to the prev node
        }
        cout << endl;
    }
    //method to print every other element
    void every_other_element(){
        // creates a pointer current to go through the list, starting at the head
        Node* current = head;
        // checks if the list is empty
        if (!current) {
            // if so print a message and exit
            cout << "List is empty." << endl;
            return;
        }
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}