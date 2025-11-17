#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for Trie Node
struct TrieNode {
    struct TrieNode* left;   // for '0'
    struct TrieNode* right;  // for '1'
    int isEnd;               // marks end of string
};

// Create a new node
struct TrieNode* createNode() {
    struct TrieNode* node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    node->left = NULL;
    node->right = NULL;
    node->isEnd = 0;
    return node;
} 

// Insert a binary string into trie
void insert(struct TrieNode* root, char* binaryStr) {
    struct TrieNode* curr = root;
    
    for (int i = 0; binaryStr[i] != '\0'; i++) {
        if (binaryStr[i] == '0') {
            if (curr->left == NULL) {
                curr->left = createNode();
            }
            curr = curr->left;
        } 
        if (binaryStr[i] == '1') {
            if (curr->right == NULL) {
                curr->right = createNode();
            }
            curr = curr->right;
        }
    }
    curr->isEnd = 1;  // Mark end of string
}

// Traverse and display all binary strings (PreOrder)
void displayAll(struct TrieNode* root, char* prefix, int level) {
    if (root == NULL)
        return;
    
    // If this is end of a string, print it
    if (root->isEnd) {
        prefix[level] = '\0';
        printf("%s\n", prefix);
    } 
    
    // Traverse left (0)
    if (root->left != NULL) {
        prefix[level] = '0';
        displayAll(root->left, prefix, level + 1);
    }
    
    // Traverse right (1)
    if (root->right != NULL) {
        prefix[level] = '1';
        displayAll(root->right, prefix, level + 1);
    }
}

// Wrapper function for display
void traverse(struct TrieNode* root) {
    char prefix[100];
    printf("Binary strings in trie:\n");
    displayAll(root, prefix, 0);
}

// Main function
int main() {
    struct TrieNode* root = createNode();
    
    // Set of binary strings
    char* binaryStrings[] = {"101", "110", "100", "111", "001"};
    int n = 5;
    
    printf("=== Binary Trie Construction ===\n\n");
    
    // Insert all strings
    printf("Inserting binary strings:\n");
    for (int i = 0; i < n; i++) {
        printf("Inserted: %s\n", binaryStrings[i]);
        insert(root, binaryStrings[i]);
    }
    
    printf("\n");
    
    // Traverse and display
    printf("=== Traversing Binary Trie ===\n\n");
    traverse(root);
    
    // Optional: Search demonstration
    printf("\n=== Search Demo ===\n\n");
    char* searchStrings[] = {"101", "111", "010", "100"};
    for (int i = 0; i < 4; i++) {
        printf("Search '%s': %s\n", searchStrings[i], 
               search(root, searchStrings[i]) ? "FOUND" : "NOT FOUND");
    }
    
    return 0;
}