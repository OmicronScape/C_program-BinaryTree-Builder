#include <stdio.h>
#include <stdlib.h>
#define N 7     /* Define the size of the tree (number of nodes) */
/* Tree node structure */
/*|-----------------------> Program User Manual <------------------------|
    ------------>The program performs the following functions<-------------
    - Creates a binary tree based on postorder and inorder traversals.
    - Calculates and displays preorder, postorder, and node depths.
    - Checks if a node is an ancestor of another node.

                      ---->>>>>Usage Instructions<<<<<--------
    - Run the program.
    - Enter the postorder and inorder traversals of the nodes.
    - Each number must be a non-negative integer and unique.

                    ------>>>>>>>>Functions<<<<<<--------
    - Entertraversal: Input and check traversal values.
    - Processtraversals: Reconstruct tree from traversals.
    - Preorder: Calculate and print preorder traversal.
    - Postorder: Calculate and print postorder traversal.
    - Depth: Calculate and print node depths.
    - Search: Search for a node with a specific value.
    - Ancestor: Check ancestor-descendant relationship.

                          ********Notes*********
    - The tree size is set by the constant #define N 7.
    - On input error or malloc failure, the program exits.
    - Memory is dynamically allocated with malloc for each node.
    ***malloc--->With malloc we "reserve space" in memory for new nodes.
     If "reserving space" fails, the program stops to prevent damage.***
*/

typedef struct node
{  /* Tree node structure */
    int key;    			/* node value */
    int depth;				/* depth */
    int preorder;			/* preorder position */
    int postorder;			/* postorder position */
    struct node *left;		/* left child */
    struct node *right;		/* right child */
} treenode;					

/* Traversal input.
   Function that reads a traversal (postorder or inorder)
   and stores it in the integer array order with size numbers.
 */
void Entertraversal(int *order, int size) {
    int i, j, num;
    int is_unique;

    for (i = 0; i < size; i++) {
        do {
            is_unique = 1; // Initialize as unique number
            printf("Enter value for position %d: ", i + 1);
            if (scanf("%d", &num) != 1 || num < 0) { // Check for valid non-negative input
                printf("Error: Number must be a non-negative integer.\n");
                is_unique = 0; // Number is not valid
                while (getchar() != '\n') continue; // Clear input buffer
                continue;
            }

            // Check for uniqueness
            for (j = 0; j < i; j++) {
                if (order[j] == num) { // Check if number already exists in array
                    printf("Error: Number %d has already been entered.\n", num);
                    is_unique = 0; // Number is not unique
                    break;
                }
            }
        } while (!is_unique);

        order[i] = num; // Store value in array
    }

    // Print array for verification
    printf("Array contents: ");
    for (int k = 0; k < size; k++) {
        printf("%d ", order[k]);
    }
    printf("\n");
}

/* The function takes two traversals (postorder and inorder)
   for size elements and reconstructs the corresponding binary tree.
   Implemented recursively.
*/
treenode *Processtraversals(int *postorder, int *inorder, int size) {
    if (size == 0) {
        return NULL;
    }

    treenode *root = (treenode *)malloc(sizeof(treenode));
    if (root == NULL) {
        printf("Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    root->key = postorder[size - 1];
    root->left = NULL;
    root->right = NULL;

    printf("Creating node with value: %d\n", root->key);

    int rootIndex = 0;
    while (rootIndex < size && inorder[rootIndex] != root->key) {
        rootIndex++;
    }

    if (rootIndex == size) {
        printf("Error: Root %d not found in inorder traversal.\n", root->key);
        free(root);
        return NULL;
    }

    printf("Root %d found at position %d in inorder.\n", root->key, rootIndex);

    root->left = Processtraversals(postorder, inorder, rootIndex);
    root->right = Processtraversals(postorder + rootIndex, inorder + rootIndex + 1, size - rootIndex - 1);

    return root;
}

/* Question 3.
   The function takes a pointer to the root of a tree structure
   and prints the preorder traversal. At the same time, it updates
   the preorder number of each node.
 */
void Preorder(treenode* node, int* number)
{
    if (node == NULL || node->key == -1)
    {
        return; // Skip nodes with value -1
    }

    /*Process current node (root)*/
    node->preorder = (*number)++;  /*Update preorder position and increment counter*/
    printf("Node: %d, Preorder number: %d\n", node->key, node->preorder);  /*Print node value*/

    /*Recursive call on left subtree*/
    Preorder(node->left, number);

    /*Recursive call on right subtree*/
    Preorder(node->right, number);
}

/* Question 4.
  The function performs postorder traversal
  on a tree structure, starting from the root, updating the postorder
  number of each node and printing the results.
 */
void Postorder(treenode* node, int* number)
{
    if (node == NULL || node->key == -1)
    {
        return; // Skip nodes with value -1
    }

    /*Recursive call on left subtree */
    Postorder(node->left, number);

    /*Recursive call on right subtree */
    Postorder(node->right, number);

    /*Process current node (root)*/
    node->postorder = (*number)++;
    printf("Node: %d, Postorder number: %d\n", node->key, node->postorder); /*Print node value*/
}

/* 
  The function calculates the depth of each node in a tree structure
  and stores it in the `depth` field of the node.
  At the same time, it prints the key and depth of each node.
  Question 5.
 */ 
void Depth(treenode* node, int depth)
{
    if (node == NULL || node->key == -1)
    {
        return; // Skip nodes with value -1
    }

    node->depth = depth;
    printf("Node: %d, Depth: %d\n", node->key, depth);/*Print key and depth*/

    /*Recursive call on left subtree, increasing depth by 1*/
    Depth(node->left, depth + 1);

    /*Recursive call on right subtree, increasing depth by 1*/
    Depth(node->right, depth + 1);
}

/* Function to find an element in the tree. Used as a helper in the implementation of
int Ancestor() */
treenode *search(treenode *v, int value) {
    // Check if node is NULL
    if (v == NULL) {
        return NULL;
    }
    // Check if current node's key is the target
    if (v->key == value) return v;
    // Search in left subtree
    treenode *node = search(v->left, value);
    // If not found in left, search in right subtree
    if (node == NULL) node = search(v->right, value);
    return node;
}

/*
  The function takes as arguments a pointer to the root of a tree structure and two values value1 and value2 and returns if the node containing value1 is an ancestor of the node containing value2.
 Returns 1 if it is an ancestor, 0 if not, and -1 in case of error.
 */
int Ancestor(treenode *root, int value1, int value2)
{
    treenode *node1 = search(root, value1);
    treenode *node2 = search(root, value2);

    /*If either node is not found, return -1*/
    if (node1 == NULL || node2 == NULL)
    {
        return -1;
    }
     // Print info for nodes
     printf("Value %d has preorder: %d, postorder: %d\n", value1, node1->preorder, node1->postorder);
     printf("Value %d has preorder: %d, postorder: %d\n", value2, node2->preorder, node2->postorder);
 
     // Check if node1 is ancestor of node2
     if (node1->preorder < node2->preorder && node1->postorder > node2->postorder)
     {
         return 1; // node1 is ancestor of node2
     }
    /*Otherwise, no ancestor-descendant relationship*/
    return 0;
}

int main() {
    int inorder[N];
    int postorder[N];
    treenode *root = NULL;
    int value1, value2, relationship;
    int num = 0;

    // Input postorder
    printf("Enter postorder:\n");
    Entertraversal(postorder, N);

    // Input inorder
    printf("Enter inorder:\n");
    Entertraversal(inorder, N);

    // Print arrays for verification
    printf("Postorder array contents: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", postorder[i]);
    }
    printf("\n");

    printf("Inorder array contents: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", inorder[i]);
    }
    printf("\n");

    // Create tree from traversals
    root = Processtraversals(postorder, inorder, N);
    if (root == NULL) {
        printf("Error creating tree.\n");
        return -1;
    }

    // Calculate and display preorder
    num = 1;
    printf("\nPreorder:\n");
    Preorder(root, &num);
    printf("\n");

    // Calculate and display postorder
    num = 1;
    printf("Postorder:\n");
    Postorder(root, &num);
    printf("\n");

    // Calculate and display depth
    printf("Depth:\n");
    Depth(root, 0);
    printf("\n");

    // Check ancestor-descendant relationship
    printf("Enter two values: ");
    if (scanf("%d %d", &value1, &value2) != 2) {
        printf("Error in value input.\n");
        return -1;
    }
    relationship = Ancestor(root, value1, value2);

    // Display result
    if (relationship == 1) {
        printf("Node with value %d is an ancestor of node with value %d.\n", value1, value2);
    } else if (relationship == 0) {
        printf("No ancestor-descendant relationship.\n");
    } else {
        printf("One of the values does not exist in the tree.\n");
    }
    return 0;
}
