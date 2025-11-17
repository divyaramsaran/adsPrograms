#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    struct node *left, *right;
    int isLeaf;   // 1 = leaf node with key, 0 = internal node
};

struct node* createNode(int key, int isLeaf) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    newNode->isLeaf = isLeaf;
    return newNode;
}

struct node* insert(struct node* root, int key) {
    int bit;

    // If tree empty → create leaf node
    if (root == NULL)
        return createNode(key, 1);

    struct node* curr = root;

    // Traverse bits from MSB to LSB
    for (int i = 31; i >= 0; i--) {
        bit = (key >> i) & 1;

        if (bit == 0) {
            if (curr->left == NULL)
                curr->left = createNode(key, (i == 0));
            curr = curr->left;
        } else {
            if (curr->right == NULL)
                curr->right = createNode(key, (i == 0));
            curr = curr->right;
        }
    }

    curr->key = key; // ensure leaf stores the key
    curr->isLeaf = 1;

    return root;
}

void preorder(struct node* root) {
    if (root == NULL) return;

    if (root->isLeaf)
        printf("%d ", root->key);

    preorder(root->left);
    preorder(root->right);
}

int main() {
    struct node* root = NULL;
    int choice, key;

    while (1) {
        printf("\n--- Digital Search Tree Menu ---\n");
        printf("1. Insert\n");
        printf("2. Preorder Display (show keys only)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter number to insert: ");
            scanf("%d", &key);
            root = insert(root, key);
            break;

        case 2:
            printf("Preorder Traversal: ");
            preorder(root);
            printf("\n");
            break;

        case 3:
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }
}