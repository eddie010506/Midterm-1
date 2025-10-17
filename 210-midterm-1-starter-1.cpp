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
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}