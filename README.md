# Balanced HashMap in C++ Using Linked List and AVL Tree

## Overview
This project implements a **HashMap** in C++ using a combination of **Linked List** and **AVL Tree** to address the unbalanced nature of traditional HashMap implementations. The default HashMap in C++ (such as `std::unordered_map`) typically handles collisions using **separate chaining** with linked lists. However, this can lead to performance degradation due to long chains in the event of excessive collisions.

In this project, we mitigate this issue by using an AVL Tree once the number of collisions in a bucket exceeds a certain threshold. This keeps operations efficient even in cases of high collision frequency.

---

## Problems with Original HashMap in C++
The default HashMap in C++ uses a **linked list** for separate chaining to handle collisions. When multiple keys map to the same hash bucket, they are stored in a linked list.

### Issues:
1. **Unbalanced Growth**: If there are too many collisions, the linked list in the bucket can grow long, leading to inefficient operations. The time complexity for search, insert, and delete in such cases becomes **O(n)** in the worst case.
2. **Performance Degradation**: As the number of collisions increases, the lookup performance degrades, leading to significant slowdowns in real-world scenarios.

---

## AVL Tree Integration
To solve the problem of unbalanced growth in linked lists, we use an **AVL Tree**. AVL trees are self-balancing binary search trees where the height of the two child subtrees of any node differs by at most 1. This ensures that the tree remains balanced at all times, providing efficient lookup, insert, and delete operations.

### Advantages of Using AVL Tree:
1. **Balanced Structure**: Ensures that the height of the tree is logarithmic relative to the number of nodes, providing **O(log n)** time complexity for operations.
2. **Efficient Collision Handling**: Once the number of elements in a bucket exceeds a threshold, the linked list is replaced with an AVL tree, maintaining performance even under high collision scenarios.
3. **Improved Worst-Case Time Complexity**: In case of high collisions, operations in the bucket remain efficient due to the **O(log n)** complexity of the AVL Tree.

---

## How to Use the Balanced HashMap

1. **Clone the Repository**:
    ```bash
    git clone URL
    ```
    
2. **Build the Project**:
    Compile the source code using any C++ compiler. For example, using g++:
    ```bash
    g++ -o hashmap hashmap.cpp
    ```

3. **Run the Program**:
    After compiling, run the executable:
    ```bash
    ./hashmap
    ```

4. **Basic Operations**:
    - **Insert a Key-Value Pair**:
      The `insert` function allows you to add key-value pairs to the HashMap.
      ```cpp
      hashMap.insert("apple", 10);
      ```
    - **Find a Value by Key**:
      The `find` function lets you search for a value associated with a key.
      ```cpp
      int* value = hashMap.find("apple");
      if (value) {
          cout << "Value for apple: " << *value << endl;
      } else {
          cout << "Key not found!" << endl;
      }
      ```
    - **Print the HashMap**:
      The `print` function prints the entire HashMap, including the keys stored in both the linked lists and AVL Trees.
      ```cpp
      hashMap.print();
      ```

---

## Time Complexity Comparison

Here’s a table comparing the time complexities of basic operations in the traditional HashMap and the Balanced HashMap with AVL Trees:

| **Operation**               | **Traditional HashMap (Linked List)** | **Balanced HashMap (AVL Tree)** |
|-----------------------------|---------------------------------------|---------------------------------|
| Insert, Search, Delete       | O(1) average, O(n) worst-case         | O(1) average, O(log n) worst-case |
| Conversion to AVL Tree       | N/A                                   | O(k log k), where k is the number of nodes in the bucket |
---

## Advantages of This HashMap Implementation
1. **Efficient Collision Resolution**: The switch from linked lists to AVL Trees ensures that even with a large number of collisions, the time complexity remains efficient.
2. **Self-Balancing Trees**: AVL Trees maintain the balance of the tree, ensuring that the height of the tree is minimized and operations remain fast.
3. **Scalable**: This implementation can handle large sets of key-value pairs with high collision rates.
