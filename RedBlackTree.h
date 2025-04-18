//
// Created by Ryzen 2700 on 15-Mar-25.
//

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#endif  // REDBLACKTREE_H

#include <iostream>

enum Color { RED, BLACK };

// Node of the Red-Black Tree
template <typename T>
struct Node {
  T data;
  Node* parent;
  Node* left;
  Node* right;
  Color color;

  explicit Node(const T& data) : data(data), parent(nullptr), left(nullptr), right(nullptr), color(RED) {}
};

template <typename T>
class RedBlackTree {
 private:
  Node<T>* root;

  // Performs a left rotation around the given node
  void LeftRotate(Node<T>* node) {
    if (!node || !node->right) return;

    Node<T>* child = node->right;

    // Move child's left subtree up
    node->right = child->left;
    if (child->left) child->left->parent = node;

    // Link child's parent to node's parent
    child->parent = node->parent;
    if (!node->parent)
      root = child;
    else if (node == node->parent->left)
      node->parent->left = child;
    else
      node->parent->right = child;

    // Put node on child's left
    child->left = node;
    node->parent = child;
  }

  // Performs a right rotation around the given node
  void RightRotate(Node<T>* node) {
    if (!node || !node->left) return;

    Node<T>* child = node->left;

    // Move child's right subtree up
    node->left = child->right;
    if (child->right) child->right->parent = node;

    // Link child's parent to node's parent
    child->parent = node->parent;
    if (!node->parent)
      root = child;
    else if (node == node->parent->left)
      node->parent->left = child;
    else
      node->parent->right = child;

    // Put node on child's right
    child->right = node;
    node->parent = child;
  }

  // Fix Red-Black Tree properties after insertion
  void FixInsert(Node<T>* node) {
    while (node != root && node->parent->color == RED) {
      if (node->parent == node->parent->parent->left) {
        Node<T>* uncle = node->parent->parent->right;

        if (uncle && uncle->color == RED) {
          node->parent->color = BLACK;
          uncle->color = BLACK;
          node->parent->parent->color = RED;
          node = node->parent->parent;
        } else {
          if (node == node->parent->right) {
            node = node->parent;
            LeftRotate(node);
          }
          node->parent->color = BLACK;
          node->parent->parent->color = RED;
          RightRotate(node->parent->parent);
        }
      } else {
        Node<T>* uncle = node->parent->parent->left;

        if (uncle && uncle->color == RED) {
          node->parent->color = BLACK;
          uncle->color = BLACK;
          node->parent->parent->color = RED;
          node = node->parent->parent;
        } else {
          if (node == node->parent->left) {
            node = node->parent;
            RightRotate(node);
          }
          node->parent->color = BLACK;
          node->parent->parent->color = RED;
          LeftRotate(node->parent->parent);
        }
      }
    }
    root->color = BLACK;
  }

  // Replaces subtree rooted at u with subtree rooted at v
  void Transplant(Node<T>* u, Node<T>* v) {
    if (!u->parent)
      root = v;
    else if (u == u->parent->left)
      u->parent->left = v;
    else
      u->parent->right = v;

    if (v) v->parent = u->parent;
  }

  // Recursive tree printer
  void PrintHelper(Node<T>* root, std::string indent, const bool last) {
    if (root) {
      std::cout << indent;
      std::cout << (last ? "R----" : "L----");

      std::string sColor = root->color == RED ? "RED" : "BLACK";
      std::cout << root->data << "(" << sColor << ")" << std::endl;

      indent += last ? "   " : "|  ";
      PrintHelper(root->left, indent, false);
      PrintHelper(root->right, indent, true);
    }
  }

 public:
  // Constructor
  RedBlackTree() : root(nullptr) {}

  // Destructor
  virtual ~RedBlackTree() = default;

  // Returns root of the tree
  Node<T>* GetRoot() {
    return root;
  }

  // Inserts data into the tree
  bool Insert(const T& data) {
    Node<T>* y = nullptr;
    Node<T>* x = root;

    while (x) {
      y = x;
      if (data < x->data)
        x = x->left;
      else if (data > x->data)
        x = x->right;
      else {
        std::cout << "ERROR : item already exists ! \n ";
        return false;
      }
    }

    auto* node = new Node<T>(data);
    node->parent = y;

    if (!y)
      root = node;
    else if (data < y->data)
      y->left = node;
    else
      y->right = node;

    FixInsert(node);
    return true;
  }

  // Prints the tree visually
  void PrintTree() {
    if (root)
      PrintHelper(root, "", true);
    else
      std::cout << "Tree is empty\n";
  }

  // Searches for a value
  void Search(const T& data) {
    Node<T>* node = root;
    while (node) {
      if (data < node->data)
        node = node->left;
      else if (data > node->data)
        node = node->right;
      else {
        std::cout << "Found : " << node->data << std::endl;
        return;
      }
    }
    std::cout << "Item Not found\n";
  }

  // Returns height of the tree
  int PrintTreeHeight(Node<T>* root) {
    if (!root) return 0;
    return 1 + std::max(PrintTreeHeight(root->left), PrintTreeHeight(root->right));
  }

  // Returns number of black nodes to the leftmost leaf
  int GetBlackHeight(Node<T>* node) {
    int height = 0;
    while (node) {
      if (node->color == BLACK) ++height;
      node = node->left;
    }
    return height;
  }

  // Returns number of nodes in the subtree
  int GetSize(Node<T>* node) {
    if (!node) return 0;
    return 1 + GetSize(node->left) + GetSize(node->right);
  }
};
