#include <iostream>
using namespace std;

// Node structure for singly circular linked list
struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

class CircularLinkedList {
private:
    Node* head;
    Node* tail;
    int size;
    
public:
    CircularLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    // Build circular linked list with n nodes (1 to n)
    void buildList(int n) {
        if (n <= 0) return;
        
        // Create first node
        head = new Node(1);
        tail = head;
        size = 1;
        
        // Create remaining nodes
        for (int i = 2; i <= n; i++) {
            Node* newNode = new Node(i);
            tail->next = newNode;
            tail = newNode;
            size++;
        }
        
        // Make it circular
        tail->next = head;
    }
    
    // Josephus simulation: delete every m-th node and print deleted values
    void josephusSimulation(int m) {
        if (head == nullptr || size == 0) return;
        
        Node* current = head;
        Node* prev = tail; // prev points to the node before current
        
        while (size > 0) {
            // Move (m-1) steps to find the m-th node
            for (int i = 1; i < m; i++) {
                prev = current;
                current = current->next;
            }
            
            // Delete current node
            Node* toDelete = current;
            cout << toDelete->data << endl;
            
            // Update links
            prev->next = current->next;
            
            // Update head/tail if necessary
            if (toDelete == head) {
                head = current->next;
            }
            if (toDelete == tail) {
                tail = prev;
            }
            
            // Move to next node
            current = current->next;
            
            // Delete the node and update size
            delete toDelete;
            size--;
            
            // Handle case when list becomes empty
            if (size == 0) {
                head = nullptr;
                tail = nullptr;
            }
        }
    }
    
    // Destructor to clean up memory
    ~CircularLinkedList() {
        if (head == nullptr) return;
        
        Node* current = head;
        Node* nextNode;
        
        // Delete all nodes
        for (int i = 0; i < size; i++) {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
        
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    
    CircularLinkedList list;
    list.buildList(n);
    list.josephusSimulation(m);
    
    return 0;
}