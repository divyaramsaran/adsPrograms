#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for Compressed Trie Node
struct CompressedTrieNode {
    char* edgeLabel;                     // String stored on edge (NEW!)
    struct CompressedTrieNode* left;     // for '0'
    struct CompressedTrieNode* right;    // for '1'
    int isEnd;                           // marks end of string
};

// Create a new node
struct CompressedTrieNode* createNode() {
    struct CompressedTrieNode* node = (struct CompressedTrieNode*)malloc(sizeof(struct CompressedTrieNode));
    node->edgeLabel = NULL;
    node->left = NULL;
    node->right = NULL;
    node->isEnd = 0;
    return node;
}

// Helper function to find common prefix length
int commonPrefixLength(char* str1, char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i]) {
        i++;
    }
    return i;
}

// Helper function to copy substring
char* substring(char* str, int start, int len) {
    char* sub = (char*)malloc((len + 1) * sizeof(char));
    strncpy(sub, str + start, len);
    sub[len] = '\0';
    return sub;
}

// Insert a binary string into compressed trie
void insert(struct CompressedTrieNode* root, char* binaryStr) {
    if (binaryStr[0] == '\0') {
        root->isEnd = 1;
        return;
    }
    
    struct CompressedTrieNode** childPtr;
    
    // Determine which child (left for '0', right for '1')
    if (binaryStr[0] == '0') {
        childPtr = &(root->left);
    } else {
        childPtr = &(root->right);
    }
    
    // If child doesn't exist, create new edge with entire string
    if (*childPtr == NULL) {
        *childPtr = createNode();
        (*childPtr)->edgeLabel = strdup(binaryStr);
        (*childPtr)->isEnd = 1;
        return;
    }
    
    // Child exists, check for common prefix
    struct CompressedTrieNode* child = *childPtr;
    char* edgeLabel = child->edgeLabel;
    int commonLen = commonPrefixLength(edgeLabel, binaryStr);
    int edgeLabelLen = strlen(edgeLabel);
    int binaryStrLen = strlen(binaryStr);
    
    // Case 1: Complete match with edge label
    if (commonLen == edgeLabelLen && commonLen == binaryStrLen) {
        child->isEnd = 1;
        return;
    }
    
    // Case 2: Edge label is prefix of binary string
    if (commonLen == edgeLabelLen) {
        // Recurse with remaining string
        char* remaining = binaryStr + commonLen;
        insert(child, remaining);
        return;
    }
    
    // Case 3: Need to split the edge
    // Create intermediate node
    struct CompressedTrieNode* intermediate = createNode();
    intermediate->edgeLabel = substring(edgeLabel, 0, commonLen);
    
    // Update current child's edge label to remaining part
    char* oldRemaining = substring(edgeLabel, commonLen, edgeLabelLen - commonLen);
    free(child->edgeLabel);
    child->edgeLabel = oldRemaining;
    
    // Attach old child to intermediate
    if (oldRemaining[0] == '0') {
        intermediate->left = child;
    } else {
        intermediate->right = child;
    }
    
    // Insert new string's remaining part
    if (commonLen < binaryStrLen) {
        char* newRemaining = substring(binaryStr, commonLen, binaryStrLen - commonLen);
        struct CompressedTrieNode* newNode = createNode();
        newNode->edgeLabel = newRemaining;
        newNode->isEnd = 1;
        
        if (newRemaining[0] == '0') {
            intermediate->left = newNode;
        } else {
            intermediate->right = newNode;
        }
    } else {
        intermediate->isEnd = 1;
    }
    
    // Replace child pointer with intermediate
    *childPtr = intermediate;
}

// Traverse and display all binary strings (PreOrder)
void displayAll(struct CompressedTrieNode* root, char* prefix, int level) {
    if (root == NULL)
        return;
    
    // If this is end of a string, print it
    if (root->isEnd) {
        prefix[level] = '\0';
        printf("%s\n", prefix);
    }
    
    // Traverse left (0)
    if (root->left != NULL) {
        char* edgeLabel = root->left->edgeLabel;
        int len = strlen(edgeLabel);
        
        // Copy edge label to prefix
        for (int i = 0; i < len; i++) {
            prefix[level + i] = edgeLabel[i];
        }
        
        displayAll(root->left, prefix, level + len);
    }
    
    // Traverse right (1)
    if (root->right != NULL) {
        char* edgeLabel = root->right->edgeLabel;
        int len = strlen(edgeLabel);
        
        // Copy edge label to prefix
        for (int i = 0; i < len; i++) {
            prefix[level + i] = edgeLabel[i];
        }
        
        displayAll(root->right, prefix, level + len);
    }
}

// Wrapper function for display
void traverse(struct CompressedTrieNode* root) {
    char prefix[100];
    printf("Binary strings in compressed trie:\n");
    displayAll(root, prefix, 0);
}

// Main function
int main() {
    struct CompressedTrieNode* root = createNode();
    
    // Set of binary strings
    char* binaryStrings[] = {"101", "110", "100", "111", "001"};
    int n = 5;
    
    printf("=== Compressed Binary Trie Construction ===\n\n");
    
    // Insert all strings
    printf("Inserting binary strings:\n");
    for (int i = 0; i < n; i++) {
        printf("Inserted: %s\n", binaryStrings[i]);
        insert(root, binaryStrings[i]);
    }
    
    printf("\n");
    
    // Display tree structure (shows compression)
    
    printf("\n");
    
    // Traverse and display
    printf("=== Traversing Compressed Binary Trie ===\n\n");
    traverse(root);
    
    return 0;
}