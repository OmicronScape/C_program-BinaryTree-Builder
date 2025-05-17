# C_program-BinaryTree-Builder
This program constructs a binary tree from user-provided postorder and inorder traversals, displays its preorder, postorder, and node depths, and checks if one node is an ancestor of another. All input values must be unique non-negative integers.
# BinaryTree Toolkit

## Description

BinaryTree Toolkit is a command-line C program that constructs a binary tree from user-provided postorder and inorder traversals. It allows you to analyze the tree by displaying its preorder and postorder traversals, calculating the depth of each node, and checking ancestor-descendant relationships between nodes.

---

## Features

- **Tree Construction:** Rebuilds a binary tree from postorder and inorder traversals.
- **Traversal Display:** Prints preorder and postorder traversals with node positions.
- **Depth Calculation:** Computes and displays the depth of each node.
- **Ancestor Check:** Determines if one node is an ancestor of another.

---

## Usage Instructions

1. **Compile the program:**
   ```
   gcc -o binarytree ypoergasia_dendro_4.c
   ```

2. **Run the program:**
   ```
   ./binarytree
   ```

3. **Follow the prompts:**
   - Enter the postorder traversal (unique, non-negative integers).
   - Enter the inorder traversal (same values, different order).
   - The program will display the traversals, node depths, and prompt you to enter two values to check for an ancestor relationship.

---

## Example

```
Δώσε μεταδιάταξη:
1 3 2 5 7 6 4
Δώσε ενδοδιάταξη:
1 2 3 4 5 6 7
Προδιάταξη:
Node: 4, Preorder number: 1
...
Δώσε δύο τιμές: 2 7
Ο κόμβος με τιμή 2 είναι πρόγονος του κόμβου με τιμή 7.
```

---

## Notes

- The tree size is set by the constant `#define N 7`. Change this value in the source code to adjust the number of nodes.
- All input values must be unique and non-negative.
- The program will terminate if invalid input is detected or if memory allocation fails.

---
