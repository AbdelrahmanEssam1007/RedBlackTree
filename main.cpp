#include <fstream>
#include <iostream>
#include <random>
#include <string>

#include "RedBlackTree.h"

void LoadDictionary(RedBlackTree<std::string>& tree) {
  std::ifstream file("words.txt");

  if (!file.is_open()) {
    std::cerr << "Could not open file.txt" << std::endl;
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    tree.Insert(line);
  }
  file.close();
}

void SaveInOrder(Node<std::string>* node, std::ofstream& outFile) {
  if (node == nullptr) return;

  SaveInOrder(node->left, outFile);
  outFile << node->data << std::endl;
  SaveInOrder(node->right, outFile);
}

void SaveDictionary(RedBlackTree<std::string>& tree) {
std::ofstream file("words.txt");

  if (!file.is_open()) {
    std::cerr << "Could not open file.txt" << std::endl;
    return;
  }

  SaveInOrder(tree.GetRoot(), file);
  file.close();
  std::cout << "Dictionary saved to words.txt" << std::endl;

}

int main() {
  RedBlackTree<std::string> tree;
  LoadDictionary(tree);

  int choice;
  std::string input;

  do {
    std::cout << "\n====== Red-Black Tree Dictionary Menu ======\n";
    std::cout << "1. Search for a word\n";
    std::cout << "2. Insert a new word\n";
    std::cout << "3. Print the tree\n";
    std::cout << "4. Show tree info\n";
    std::cout << "5. Save dictionary\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
      case 1:
        std::cout << "Enter word to search: ";
        std::cin >> input;
        tree.Search(input);
        break;

      case 2:
        std::cout << "Enter word to insert: ";
        std::cin >> input;
        tree.Insert(input);
        break;

      case 3:
        std::cout << "Tree Structure:\n";
        tree.PrintTree();
        break;

      case 4:
        std::cout << "Tree height     : " << tree.PrintTreeHeight(tree.GetRoot()) << "\n";
        std::cout << "Black height    : " << tree.GetBlackHeight(tree.GetRoot()) << "\n";
        std::cout << "Number of nodes : " << tree.GetSize(tree.GetRoot()) << "\n";
        break;

      case 5:
        SaveDictionary(tree);
        break;

      case 0:
        std::cout << "Exiting program. Goodbye!\n";
        break;

      default:
        std::cout << "Invalid choice. Please try again.\n";
        break;
    }
  }
  while (choice != 0);

  return 0;
}
