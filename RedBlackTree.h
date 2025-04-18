//
// Created by Ryzen 2700 on 15-Mar-25.
//

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#endif  // REDBLACKTREE_H

#include <iostream>

enum Color { RED, BLACK };  // Node color for Red-Black Tree properties

// Definition of a single node in the Red-Black Tree
template <typename T>
struct Node {
  T data;
  Node* parent;
  Node* left;
  Node* right;
  Color color;

  // Constructor initializes node data and sets default values
  explicit Node(const T& data) : data(data), parent(nullptr), left(nullptr), right(nullptr), color(RED) {
    // New nodes are always inserted as RED initially
  }
};

template <typename T>
class RedBlackTree {
 private:
  Node<T>* root;  // Pointer to root node of the tree

  // Performs a left rotation around the given node
  void LeftRotate(Node<T>* node) {
    if (node == nullptr || node->right == nullptr) return;  // Can't rotate if node or right child is null

    Node<T>* child = node->right;  // Save right child
    node->right = child->left;  // Move left subtree of right child to be node's new right

    // If that subtree exists, set its parent to current node
    if (node->right != nullptr) node->right->parent = node;

    // Update child's parent to node's parent
    child->parent = node->parent;

    // If node was root, update root pointer
    if (node->parent == nullptr) root = child;
    // If node was a left child, update parent's left pointer
    else if (node == node->parent->left)
      node->parent->left = child;
    // Otherwise, node was a right child, update parent's right pointer
    else
      node->parent->right = child;

    // Make node the left child of its former right child
    child->left = node;
    node->parent = child;
  }

  // Performs a right rotation around the given node
  void RightRotate(Node<T>* node) {
    if (node == nullptr || node->left == nullptr) return;  // Can't rotate if node or left child is null

    Node<T>* child = node->left;  // Save left child
    node->left = child->right;  // Move right subtree of left child to node's new left

    // Update parent pointer if that subtree exists
    if (node->left != nullptr) node->left->parent = node;

    child->parent = node->parent;

    if (node->parent == nullptr)
      root = child;  // If node was root, child becomes new root
    else if (node == node->parent->left)
      node->parent->left = child;  // Update parent's left child pointer
    else
      node->parent->right = child;  // Update parent's right child pointer

    child->right = node;  // Make node the right child of its former left child
    node->parent = child;
  }

  // Fixes the Red-Black Tree properties after insertion
  void FixInsert(Node<T>* node) {
    while (node != root && node->parent->color == RED) {
      // If parent is left child of grandparent
      if (node->parent == node->parent->parent->left) {
        Node<T>* uncle = node->parent->parent->right;  // Uncle is the sibling of parent

        // Case 1: Uncle is RED – Recoloring
        if (uncle != nullptr && uncle->color == RED) {
          node->parent->color = BLACK;
          uncle->color = BLACK;
          node->parent->parent->color = RED;
          node = node->parent->parent;  // Move up two levels
        }
        else {
          // Case 2: node is right child – need to rotate left
          if (node == node->parent->right) {
            node = node->parent;
            LeftRotate(node);
          }
          // Case 3: node is left child – rotate right and recolor
          node->parent->color = BLACK;
          node->parent->parent->color = RED;
          RightRotate(node->parent->parent);
        }
      }
      // Symmetric case: parent is right child of grandparent
      else {
        Node<T>* uncle = node->parent->parent->left;

        // Mirror Case 1
        if (uncle != nullptr && uncle->color == RED) {
          node->parent->color = BLACK;
          uncle->color = BLACK;
          node->parent->parent->color = RED;
          node = node->parent->parent;
        }
        else {
          // Mirror Case 2: node is left child – rotate right
          if (node == node->parent->left) {
            node = node->parent;
            RightRotate(node);
          }
          // Mirror Case 3: node is right child – rotate left and recolor
          node->parent->color = BLACK;
          node->parent->parent->color = RED;
          LeftRotate(node->parent->parent);
        }
      }
    }
    root->color = BLACK;  // Root must always be black
  }

  // Replaces one subtree with another in the parent node
  void Transplant(Node<T>* u, Node<T>* v) {
    if (u->parent == nullptr)
      root = v;  // u was root, so v becomes new root
    else if (u == u->parent->left)
      u->parent->left = v;  // u was left child
    else
      u->parent->right = v;  // u was right child

    if (v != nullptr) v->parent = u->parent;  // Set v’s parent
  }

  // Recursive helper to print the tree structure
  void PrintHelper(Node<T>* root, std::string indent, const bool last) {
    if (root != nullptr) {
      std::cout << indent;
      if (last) {
        std::cout << "R----";  // Indicates right child
        indent += "   ";
      }
      else {
        std::cout << "L----";  // Indicates left child
        indent += "|  ";
      }

      std::string sColor = root->color == RED ? "RED" : "BLACK";
      std::cout << root->data << "(" << sColor << ")" << std::endl;
      PrintHelper(root->left, indent, false);
      PrintHelper(root->right, indent, true);
    }
  }

 public:
  RedBlackTree() : root(nullptr) {
  }  // Constructor initializes empty tree

  virtual ~RedBlackTree() = default;  // Virtual destructor

  Node<T>* GetRoot() {
    return root;  // Return pointer to root node
  }

  // Public method to insert data into the tree
  bool Insert(const T& data) {
    Node<T>* y = nullptr;  // y will track parent
    Node<T>* x = root;  // x traverses the tree

    // Traverse tree to find proper insertion point
    while (x != nullptr) {
      y = x;
      if (data < x->data) {
        x = x->left;  // Move to left subtree if data is smaller
      }
      else if (data > x->data) {
        x = x->right;  // Move to right subtree if data is greater
      }
      else {
        // Duplicate value found
        std::cout << "ERROR : item already exists ! \n ";
        return false;
      }
    }

    // Create new node and insert
    auto* node = new Node<T>(data);
    node->parent = y;

    if (y == nullptr)
      root = node;  // Tree was empty, node becomes root
    else if (node->data < y->data)
      y->left = node;  // Node is left child
    else
      y->right = node;  // Node is right child

    FixInsert(node);  // Fix violations after insertion
    return true;
  }

  // Print the tree visually
  void PrintTree() {
    if (root != nullptr)
      PrintHelper(root, "", true);
    else
      std::cout << "Tree is empty\n";
  }

  // Search for a value and print result
  void Search(const T& data) {
    Node<T>* node = root;
    while (node != nullptr) {
      if (data < node->data)
        node = node->left;  // Move left if data is smaller
      else if (data > node->data)
        node = node->right;  // Move right if data is larger
      else {
        std::cout << "Found : " << node->data << std::endl;
        return;
      }
    }
    std::cout << "Item Not found\n";
  }

  // Return the height of the tree from the given root node
  int PrintTreeHeight(Node<T>* root) {
    if (root == nullptr) return 0;
    return 1 + std::max(PrintTreeHeight(root->left), PrintTreeHeight(root->right));
  }

  // Return black-height (number of black nodes from node to leaf)
  int GetBlackHeight(Node<T>* node) {
    int height = 0;
    while (node != nullptr) {
      if (node->color == BLACK) ++height;  // Only count black nodes
      node = node->left;
    }
    return height;
  }

  // Return number of nodes in subtree rooted at given node
  int GetSize(Node<T>* node) {
    if (node == nullptr) return 0;
    return 1 + GetSize(node->left) + GetSize(node->right);  // Count node and recurse
  }
  
};
