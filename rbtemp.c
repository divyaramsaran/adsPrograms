#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;         // node value
    int color;        // 1 = red, 0 = black
    struct node *left, *right, *parent;
};

struct node *root = NULL;

// --- Utility: Create new node (always red) ---
struct node* createNode(int data) {
    struct node *temp = (struct node*) malloc(sizeof(struct node));
    temp->data = data;
    temp->color = 1;   // new node is red
    temp->left = temp->right = temp->parent = NULL;
    return temp;
}

// --- Standard BST insert ---
struct node* bstInsert(struct node *trav, struct node *temp) {
    if (trav == NULL)
        return temp;
    if (temp->data < trav->data) {
        trav->left = bstInsert(trav->left, temp);
        trav->left->parent = trav;
    } else if (temp->data > trav->data) {
        trav->right = bstInsert(trav->right, temp);
        trav->right->parent = trav;
    }
    return trav;
}

// --- Left rotation ---
void leftRotate(struct node *x) {
    struct node *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// --- Right rotation ---
void rightRotate(struct node *x) {
    struct node *y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->parent = x;

    y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->right = x;
    x->parent = y;
}

// --- Fix Red-Black violations ---
void fixViolation(struct node *root, struct node *pt) {
    struct node *parent = NULL;
    struct node *grandparent = NULL;

    while ((pt != root) && (pt->color == 1) && (pt->parent->color == 1)) {
        parent = pt->parent;
        grandparent = pt->parent->parent;

        // Case A – parent is left child of grandparent
        if (parent == grandparent->left) {
            struct node *uncle = grandparent->right;

            // Case 1: Uncle is red (Recolor)
            if (uncle != NULL && uncle->color == 1) {
                grandparent->color = 1;
                parent->color = 0;
                uncle->color = 0;
                pt = grandparent;
            } else {
                // Case 2: pt is right child -> Left rotate first
                if (pt == parent->right) {
                    leftRotate(parent);
                    pt = parent;
                    parent = pt->parent;
                }
                // Case 3: pt is left child -> Right rotate
                rightRotate(grandparent);
                int tempColor = parent->color;
                parent->color = grandparent->color;
                grandparent->color = tempColor;
                pt = parent;
            }
        }

        // Case B – parent is right child of grandparent
        else {
            struct node *uncle = grandparent->left;

            // Case 1: Uncle is red (Recolor)
            if (uncle != NULL && uncle->color == 1) {
                grandparent->color = 1;
                parent->color = 0;
                uncle->color = 0;
                pt = grandparent;
            } else {
                // Case 2: pt is left child -> Right rotate first
                if (pt == parent->left) {
                    rightRotate(parent);
                    pt = parent;
                    parent = pt->parent;
                }
                // Case 3: pt is right child -> Left rotate
                leftRotate(grandparent);
                int tempColor = parent->color;
                parent->color = grandparent->color;
                grandparent->color = tempColor;
                pt = parent;
            }
        }
    }
    root->color = 0; // Root must always be black
}

// --- Inorder traversal for display ---
void inorder(struct node* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d(%s) ", root->data, (root->color == 0 ? "B" : "R"));
    inorder(root->right);
}

// --- Main Function ---
int main() {
    int arr[] = {7, 6, 5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        struct node *temp = createNode(arr[i]);
        root = bstInsert(root, temp);
        fixViolation(root, temp);
        root->color = 0; // ensure root black after each insertion
    }

    printf("Inorder traversal (value with color):
");
    inorder(root);
    printf("
");
    return 0;
}