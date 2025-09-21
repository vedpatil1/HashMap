#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define mod 1000000007

//Linked list node
template <typename K, typename V>
struct ListNode {
    K key;
    V value;
    ListNode* next;

    ListNode(const K &key, const V &value) {
        this->key = key;
        this->value = value;
        this->next = NULL;
    }
};

// AVL Tree Node
template<typename K, typename V>
class AVLTreeNode{
public:
    K key;
    V value;
    AVLTreeNode* left;
    AVLTreeNode* right;
    int height;

    AVLTreeNode(K key, V value) {
        this->key = key;
        this->value = value;
        this->left = NULL;
        this->right = NULL;
        this->height = 1;
    }
};

// AVL Tree
template<typename K, typename V>
class AVLTree {
// Private variables and functions
private:
    AVLTreeNode<K, V>* root;

    int height(AVLTreeNode<K, V>* node) {
        if (node == NULL) return 0;
        return node->height;
    }

    int getBalance(AVLTreeNode<K, V>* node) {
        if (node == NULL) return 0;
        return height(node->left) - height(node->right);
    }
    // Right rotate
    AVLTreeNode<K, V>* rightRotate(AVLTreeNode<K, V>* y) {
        AVLTreeNode<K, V>* x = y->left;
        AVLTreeNode<K, V>* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x;
    }
    // Left rotate
    AVLTreeNode<K, V>* leftRotate(AVLTreeNode<K, V>* x) {
        AVLTreeNode<K, V>* y = x->right;
        AVLTreeNode<K, V>* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }
    // Insertion in AVL tree and checking balance of the nodes for rotation
    AVLTreeNode<K, V>* insert(AVLTreeNode<K, V>* node, const K &key, const V &value) {
        if (!node) return new AVLTreeNode<K, V>(key, value);

        if (key < node->key) {
            node->left = insert(node->left, key, value);
        }
        else if (key > node->key) {
            node->right = insert(node->right, key, value);
        }
        else {
            node->value = value;
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key) {
            return rightRotate(node);
        }
        if (balance < -1 && key > node->right->key) {
            return leftRotate(node);
        }
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }
    // Finding the node with the key in AVL Tree
    AVLTreeNode<K, V>* find(AVLTreeNode<K, V>* node, const K &key) {
        if (!node || node->key == key) return node;

        if (key < node->key) {
            return find(node->left, key);
        }
        return find(node->right, key);
    }
    // Inorder traversal of AVL Tree
    void inorder(AVLTreeNode<K, V>* node) {
        if (node) {
            inorder(node->left);
            cout << node->key << ": " << node->value << " | ";
            inorder(node->right);
        }
    }
// Performing the operations
public:
    AVLTree() {
        root = NULL;
    }

    void insert(const K &key, const V &value) {
        root = insert(root, key, value);
    }

    V* find(const K &key) {
        AVLTreeNode<K, V>* node = find(root, key);
        if (node) return &node->value;
        return NULL;
    }

    void printInorder() {
        inorder(root);
        cout << "\n";
    }
};

// Custom Hash Map
template<typename K, typename V>
class CustomHashMap {
// Private variables and functions
private:
    static const int max_threshold = 8;
    vector<ListNode<K, V>*> table; // Linked List
    vector<AVLTree<K, V>> avlTable; // AVL Tree
    int capacity; // Size of the hash table
    hash<K> hashFunction; // Hash function

    // Hash function to get the index of the key
    int getHashIndex(const K &key) {
        return hashFunction(key) % capacity;
    }

    // Converting linked list to AVL Tree
    void convertToAVL(int index) {
        if (!table[index]) return;

        avlTable[index] = AVLTree<K, V>();
        ListNode<K, V>* current = table[index];
        while (current) {
            avlTable[index].insert(current->key, current->value);
            ListNode<K, V>* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        table[index] = nullptr;
    }

public:
    // Constructor to initialize the hash table and AVL table with the given size
    CustomHashMap(int size){
        capacity = size;
        table.resize(capacity, nullptr);
        avlTable.resize(capacity);
    }

    // Inserting the key value pair in the hash table
    void insert(const K &key, const V &value) {
        int index = getHashIndex(key);

        // Check if map is already using AVL Tree
        if (avlTable[index].find(key)) {
            avlTable[index].insert(key, value);
            return;
        }

        // If not then insert into linked list
        if (!table[index]) {
            table[index] = new ListNode<K, V>(key, value);
        } else {
            ListNode<K, V>* current = table[index];
            while (current->next && current->key != key) {
                current = current->next;
            }
            if (current->key == key) {
                current->value = value;
                return;
            }
            current->next = new ListNode<K, V>(key, value);
        }

        // Condition to check if avl tree is needed
        if (table[index] && avlTable[index].find("") == nullptr) {
            int count = 0;
            ListNode<K, V>* current = table[index];
            while (current) {
                count++;
                current = current->next;
            }
            if (count >= max_threshold) {
                convertToAVL(index);
            }
        }

    }

    // Finding the value for the given key
    V* find(const K &key) {
        int index = getHashIndex(key);

        if (avlTable[index].find(key)) {
            return avlTable[index].find(key);
        }

        ListNode<K, V>* current = table[index];
        while (current) {
            if (current->key == key) {
                return &current->value;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Printing the hash table
    void print() {
        for (int i = 0; i < capacity; ++i) {
            cout << "Bucket " << i << ": ";
            if (avlTable[i].find("") != nullptr) {
                avlTable[i].printInorder();
            } else {
                ListNode<K, V>* current = table[i];
                while (current) {
                    cout << current->key << ": " << current->value << " | ";
                    current = current->next;
                }
                cout << endl;
            }
        }
    }
};

// Main function
int main() {
    CustomHashMap<string, int> hashMap(10);

    // Inserting key value pairs
    hashMap.insert("apple", 10);
    hashMap.insert("banana", 20);
    hashMap.insert("cherry", 30);
    hashMap.insert("date", 40);
    hashMap.insert("elderberry", 50);
    hashMap.insert("fig", 60);
    hashMap.insert("grape", 70);
    hashMap.insert("honeydew", 80);
    hashMap.insert("kiwi", 90);
    hashMap.insert("lemon", 100);
    hashMap.insert("mango", 50);
    hashMap.insert("apricot", 60);
    hashMap.insert("jackfruit", 70);
    hashMap.insert("dragonfruit", 80);

    string key = "banana";
    int* value = hashMap.find(key);
    if (value) {
        cout << "Value for " << key << ": " << *value << endl;
    } else {
        cout << key << " not found!" << endl;
    }

    hashMap.print();
    return 0;
}