#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define M 4  // Order of B+ Tree (max children = 4)

struct BPlusNode {
    int num_keys;
    int keys[M - 1];
    struct BPlusNode *children[M];
    bool is_leaf;
    struct BPlusNode *next; // leaf chain
};

// Create a new node
struct BPlusNode* createNode(bool is_leaf) {
    struct BPlusNode *node = (struct BPlusNode*)malloc(sizeof(struct BPlusNode));
    node->num_keys = 0;
    node->is_leaf = is_leaf;
    node->next = NULL;

    for (int i = 0; i < M; i++) node->children[i] = NULL;

    return node;
}

// Split a full child
void splitChild(struct BPlusNode *parent, int index) {
    struct BPlusNode *child = parent->children[index];
    struct BPlusNode *newNode = createNode(child->is_leaf);

    int mid = M/2;

    // For leaf nodes
    if (child->is_leaf) {
        newNode->num_keys = mid;

        // Move half keys to new leaf
        for (int i = 0; i < mid; i++) {
            newNode->keys[i] = child->keys[i + mid];
        }

        child->num_keys = mid;

        // Link leaf nodes
        newNode->next = child->next;
        child->next = newNode;

        // Insert separator into internal parent
        for (int i = parent->num_keys; i > index; i--) {
            parent->children[i + 1] = parent->children[i];
            parent->keys[i] = parent->keys[i - 1];
        }

        parent->children[index + 1] = newNode;
        parent->keys[index] = newNode->keys[0];
        parent->num_keys++;
    }
    else {
        // Internal node splitting
        newNode->num_keys = mid - 1;

        for (int i = 0; i < mid - 1; i++)
            newNode->keys[i] = child->keys[i + mid];

        for (int i = 0; i < mid; i++)
            newNode->children[i] = child->children[i + mid];

        child->num_keys = mid - 1;

        for (int i = parent->num_keys; i > index; i--) {
            parent->children[i + 1] = parent->children[i];
            parent->keys[i] = parent->keys[i - 1];
        }

        parent->children[index + 1] = newNode;
        parent->keys[index] = child->keys[mid - 1];
        parent->num_keys++;
    }
}

// Insert into non-full node
void insertNonFull(struct BPlusNode *node, int key) {
    int i = node->num_keys - 1;

    if (node->is_leaf) {
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        node->keys[i+1] = key;
        node->num_keys++;
    }
    else {
        while (i >= 0 && node->keys[i] > key) i--;
        i++;

        if (node->children[i]->num_keys == M - 1) {
            splitChild(node, i);

            if (key > node->keys[i])
                i++;
        }
        insertNonFull(node->children[i], key);
    }
}

// Insert into B+ Tree
void insert(struct BPlusNode **root, int key) {
    if (*root == NULL) {
        *root = createNode(true);
        (*root)->keys[0] = key;
        (*root)->num_keys = 1;
        return;
    }

    if ((*root)->num_keys == M - 1) {
        struct BPlusNode *newRoot = createNode(false);
        newRoot->children[0] = *root;

        splitChild(newRoot, 0);
        *root = newRoot;
    }

    insertNonFull(*root, key);
}

// Print leaf level (B+ Tree property)
void printLeaves(struct BPlusNode *root) {
    if (!root) return;

    // Go to leftmost leaf
    while (!root->is_leaf)
        root = root->children[0];

    // Print linked leaves
    while (root != NULL) {
        for (int i = 0; i < root->num_keys; i++)
            printf("%d ", root->keys[i]);
        root = root->next;
    }
}

int main() {
    struct BPlusNode *root = NULL;

    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 5);
    insert(&root, 6);
    insert(&root, 12);
    insert(&root, 30);

    printf("Leaf-level traversal of B+ Tree: ");
    printLeaves(root);
    printf("\n");

    return 0;
}
