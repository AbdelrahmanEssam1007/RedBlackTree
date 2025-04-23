# Dictionary - Red-Black Tree Based Word Lookup

## Overview

**Dictionary** is a fast and efficient word lookup system developed in **C++**, using a custom-built **Red-Black Tree** as the underlying data structure. Designed for quick and scalable dictionary operations, this project focuses on supporting word insertion and lookup functionalities, with automatic tree balancing to ensure optimal performance.

The dictionary project emphasizes the implementation of a core data structure from scratch, highlighting key computer science concepts such as tree rotations, balancing, and traversal. It's ideal for educational use and practical exploration of Red-Black Trees.

## Completed Features

### Core Functionality

#### Dictionary Operations
*  Insert new words into the dictionary with associated definitions.
*  Lookup existing words and retrieve their definitions.
*  Prevents duplicate word entries.

#### Red-Black Tree Implementation
*  Fully functional Red-Black Tree from scratch.
*  Automatic self-balancing on insertions using rotations and recoloring.
*  Maintains O(log n) performance for all operations.
*  Only **inorder traversal** supported for displaying all words in sorted order.

#### Console Interface
*  Simple and interactive command-line interface.
*  Allows user to insert and look up words.
*  Option to display all words in sorted order using inorder traversal.

## Technical Details

### Technology Stack

*  **Language:** C++
*  **Data Structure:** Red-Black Tree (custom implementation)
*  **Build System:** (CMake)
*  **Platform:** Cross-platform (Windows/Linux)

### Red-Black Tree Mechanics

*  Nodes contain a word-definition pair and color flag (Red/Black).
*  Balancing ensured using left/right rotations and color adjustments.
*  Only insertions are supported (no deletion or updates yet).
*  Inorder traversal used for sorted word output.

### Design Principles

*  Object-oriented design with a dedicated `RedBlackTree` class.
*  Clean separation of user interface and data logic.
*  Adheres to C++ best practices for modularity and maintainability.

## Project Members

* Abdelrahman Essam
* Ahmed Alaa
* Mahmoud Waleed

## Contributing

Contributions are welcome! If you'd like to enhance functionality or fix bugs, feel free to fork the repo and submit a pull request. For larger changes, consider opening an issue first for discussion.
