#include <iostream>
using namespace std;

// Node structure for singly circular linked list
struct Node {
    int data;
    Node* next;
};

// Create a new node
Node* createNode(int val) {
    Node* newNode = new Node;
    newNode->data = val;
    newNode->next = nullptr;
    return newNode;
}

// Build circular linked list with n nodes (1 to n)
Node* buildCircularList(int n, Node*& tail) {
    if (n <= 0) {
        tail = nullptr;
        return nullptr;
    }
    
    // Create first node
    Node* head = createNode(1);
    tail = head;
    
    // Create remaining nodes
    for (int i = 2; i <= n; i++) {
        Node* newNode = createNode(i);
        tail->next = newNode;
        tail = newNode;
    }
    
    // Make it circular
    tail->next = head;
    return head;
}
    
    // Josephus simulation: delete every m-th node and print deleted values
void josephusSimulation(Node*& head, Node*& tail, int n, int m) {
    if (head == nullptr || n <= 0) return;
    
    Node* current = head;
    Node* prev = tail; // prev points to the node before current
    int remaining = n;
    
    while (remaining > 1) {
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
        
        // Delete the node and update remaining count
        delete toDelete;
        remaining--;
    }
    
    // Handle the last remaining node
    if (remaining == 1 && head != nullptr) {
        cout << head->data << endl;
        delete head;
        head = nullptr;
        tail = nullptr;
        remaining = 0;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    Node* tail = nullptr;
    Node* head = buildCircularList(n, tail);
    josephusSimulation(head, tail, n, m);
    
    return 0;
}