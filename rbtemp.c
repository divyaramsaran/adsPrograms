#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int color;   // 1 = RED, 0 = BLACK
    struct Node *left, *right, *parent;
};

struct Node *root = NULL;

/* Create a new RB node (always RED initially) */
struct Node* newNode(int data) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->data = data;
    n->color = 1;   // RED = 1
    n->left = n->right = n->parent = NULL;
    return n;
}

/* LEFT ROTATE */
void leftRotate(struct Node* x) {
    struct Node* y = x->right;
    if (!y) return;

    x->right = y->left;
    if (y->left != NULL) y->left->parent = x;

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

/* RIGHT ROTATE */
void rightRotate(struct Node* x) {
    struct Node* y = x->left;
    if (!y) return;

    x->left = y->right;
    if (y->right) y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

/* FIX VIOLATIONS */
void fixViolation(struct Node* pt) {
    while (pt != root && pt->parent->color == 1) {  // parent red = 1
        struct Node *parent = pt->parent;
        struct Node *grandParent = parent->parent;

        if (parent == grandParent->left) {
            struct Node* uncle = grandParent->right;

            if (uncle != NULL && uncle->color == 1) {
                parent->color = 0;
                uncle->color = 0;
                grandParent->color = 1;
                pt = grandParent;
            }
            else {
                if (pt == parent->right) {
                    leftRotate(parent);
                    pt = parent;
                    parent = pt->parent;
                }
                parent->color = 0;
                grandParent->color = 1;
                rightRotate(grandParent);
            }
        }
        else {
            struct Node* uncle = grandParent->left;

            if (uncle != NULL && uncle->color == 1) {
                parent->color = 0;
                uncle->color = 0;
                grandParent->color = 1;
                pt = grandParent;
            }
            else {
                if (pt == parent->left) {
                    rightRotate(parent);
                    pt = parent;
                    parent = pt->parent;
                }
                parent->color = 0;
                grandParent->color = 1;
                leftRotate(grandParent);
            }
        }
    }

    root->color = 0;   // BLACK = 0
}

/* RECURSIVE BST INSERT */
struct Node* bstInsert(struct Node* node, struct Node* pt) {
    if (node == NULL)
        return pt;

    if (pt->data < node->data) {
        node->left = bstInsert(node->left, pt);
        node->left->parent = node;
    }
    else if (pt->data > node->data) {
        node->right = bstInsert(node->right, pt);
        node->right->parent = node;
    }
    else
        return node; // duplicate ignored

    return node;
}

/* INSERT: recursive BST + fix */
void insert(int data) {
    struct Node* pt = newNode(data);

    root = bstInsert(root, pt);

    fixViolation(pt);
}

/* Inorder traversal */
void inorder(struct Node* n) {
    if (!n) return;
    inorder(n->left);
    printf("%d(%c) ", n->data, n->color == 1 ? 'R' : 'B');
    inorder(n->right);
}

int main() {
    int count;
    printf("Enter number of elements to add");
    scanf("%d", &count);

    int arr[count];
    printf("Enter elements");

    for(int i = 0; i < count; i++) {
        int value;
        scanf("%d", &value);
        arr[i] = value;
    }

    for (int i = 0; i < count; i++)
        insert(arr[i]);

    inorder(root);
    return 0;
}