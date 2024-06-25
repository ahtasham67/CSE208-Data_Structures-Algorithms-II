#include <iostream>
#include "color.hpp"
#include <bits/stdc++.h>
using namespace std;

struct Node
{
  int data;
  string str;
  Node *parent;
  Node *left;
  Node *right;
  int color;
};


class RedBlackTree
{
private:
  Node* root;
  Node* dummy;
  int cnt;

  Node* searchTreeHelper(Node* node, int key)
  {
    if (node == dummy || key == node->data)
    {
      return node;
    }

    if (key < node->data)
    {
      return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
  }


  void deleteFix(Node* x)
{
    Node* s;
    //until the current node is not the root and has a black color
    while (x != root && x->color == 0)
    {
        // Case 1: Current node is the left child of its parent
        if (x == x->parent->left)
        {
            // Sibling of x
            s = x->parent->right;

            // Case 1.1: Sibling is red
            if (s->color == 1)
            {
                // Make sibling black, parent red, left rotate on parent
                s->color = 0;
                x->parent->color = 1;
                leftRotate(x->parent);
                s = x->parent->right; // Update sibling after rotation
            }

            // Case 1.2: Both children of the sibling are black
            if (s->left->color == 0 && s->right->color == 0)
            {
                // Make sibling red, move up to the parent
                s->color = 1;
                x = x->parent;
            }
            else
            {
                // Case 1.3: Right child of the sibling is black
                if (s->right->color == 0)
                {
                    // Make left child of the sibling black, make sibling red, right rotate on sibling
                    s->left->color = 0;
                    s->color = 1;
                    rightRotate(s);
                    s = x->parent->right; // Update sibling after rotation
                }

                // Case 1.4: Right child of the sibling is red
                s->color = x->parent->color;
                x->parent->color = 0;
                s->right->color = 0;
                leftRotate(x->parent);
                x = root; // Move to the root to exit the loop
            }
        }
        else
        {
            // Case 2: Current node is the right child of its parent (symmetric to Case 1)
            s = x->parent->left;

            if (s->color == 1)
            {
                s->color = 0;
                x->parent->color = 1;
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if (s->right->color == 0 && s->left->color == 0)
            {
                s->color = 1;
                x = x->parent;
            }
            else
            {
                if (s->left->color == 0)
                {
                    s->right->color = 0;
                    s->color = 1;
                    leftRotate(s);
                    s = x->parent->left;
                }

                s->color = x->parent->color;
                x->parent->color = 0;
                s->left->color = 0;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = 0; // Ensuring the root is black after fixing
}


  void rbTransplant(Node* u, Node* v)
{
    // Case 1: If the parent of u is nullptr, u is the root of the tree
    if (u->parent == nullptr)
    {
        // Set the root of the tree to be v
        root = v;
    }
    else if (u == u->parent->left)
    {
        // Case 2: If u is the left child of its parent Set the left child of u's parent to be v
        u->parent->left = v;
    }
    else
    {
        // Case 3: If u is the right child of its parent Set the right child of u's parent to be v
        u->parent->right = v;
    }

    // Set the parent of v to be the parent of u, regardless of the cases
    v->parent = u->parent;
}


void deleteNodeHelper(Node* node, int key)
{
    Node* z = dummy;
    Node* x;
    Node* y;
    // Find the node to be deleted
    while (node != dummy)
    {
        if (node->data == key)
        {
            z = node; // Node to be deleted found
        }

        if (node->data <= key)
        {
            node = node->right;
        }
        else
        {
            node = node->left;
        }
    }

    // If the node to be deleted is not found, return
    if (z == dummy)
    {
        // cout << "Key not found in the tree" << endl;
        return;
    }

    y = z; // y is a pointer to the node to be deleted
    int y_original_color = y->color;

    // Case 1: Node to be deleted has no left child
    if (z->left == dummy)
    {
        x = z->right;
        rbTransplant(z, z->right); // Transplant z with its right child
    }
    // Case 2: Node to be deleted has no right child
    else if (z->right == dummy)
    {
        x = z->left;
        rbTransplant(z, z->left); // Transplant z with its left child
    }
    // Case 3: Node to be deleted has both left and right children
    else
    {
        y = predecessor(z);
        y_original_color = y->color;
        x = y->left; // x is the left child of y

        // Case 3.1: If y is the direct left child of z
        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            // Case 3.2: If y is not the direct left child of z
            rbTransplant(y, y->left);
            y->left = z->left;
            y->left->parent = y;
        }

        // Transplant z with y
        rbTransplant(z, y);
        y->right = z->right;
        y->right->parent = y;
        y->color = z->color; // Copy the color of z to y
    }

    delete z; // Delete the node to be deleted
    // If the original color of y was black, fix the tree
    if (y_original_color == 0)
    {
        deleteFix(x);
    }

    cnt--;
}


  // For balancing the tree after insertion
  void insertFix(Node* k)
{
    Node* u;
    // until the parent of k is black (0)
    while (k->parent->color == 1)
    {
        // Case 1: Parent of k is the right child of its grandparent
        if (k->parent == k->parent->parent->right)
        {
            // Uncle of k (sibling of the parent)
            u = k->parent->parent->left;

            // Case 1.1: Uncle is red
            if (u->color == 1)
            {
                // Make uncle black, parent black, grandparent red, move up to the grandparent
                u->color = 0;
                k->parent->color = 0;
                k->parent->parent->color = 1;
                k = k->parent->parent;
            }
            else
            {
                // Case 1.2: Uncle is black, and k is the left child
                if (k == k->parent->left)
                {
                    // Move up to the parent, perform right rotation on the parent
                    k = k->parent;
                    rightRotate(k);
                }

                // Case 1.3: Uncle is black, k is the right child
                k->parent->color = 0; // Make parent black
                k->parent->parent->color = 1; // Make grandparent red
                leftRotate(k->parent->parent); // Perform left rotation on the grandparent
            }
        }
        else
        {
            // Case 2: Parent of k is the left child of its grandparent (symmetric to Case 1)
            u = k->parent->parent->right;

            // Case 2.1: Uncle is red
            if (u->color == 1)
            {
                // Make uncle black, parent black, grandparent red, move up to the grandparent
                u->color = 0;
                k->parent->color = 0;
                k->parent->parent->color = 1;
                k = k->parent->parent;
            }
            else
            {
                // Case 2.2: Uncle is black, and k is the right child
                if (k == k->parent->right)
                {
                    // Move up to the parent, perform left rotation on the parent
                    k = k->parent;
                    leftRotate(k);
                }

                // Case 2.3: Uncle is black, k is the left child
                k->parent->color = 0; // Make parent black
                k->parent->parent->color = 1; // Make grandparent red
                rightRotate(k->parent->parent); //right rotation on the grandparent
            }
        }

        // Check if the current node is the root to exit the loop
        if (k == root)
        {
            break;
        }
    }
    root->color = 0; //root is black after fixing
}

public:
  RedBlackTree()
  {
    dummy = new Node;
    dummy->color = 0;
    dummy->left = nullptr;
    dummy->right = nullptr;
    root = dummy;
    cnt = 0;
  }


  Node* searchTree(int k)
  {
    return searchTreeHelper(this->root, k);
  }


  Node* maximum(Node* node)
  {
    while (node->right != dummy)
    {
      node = node->right;
    }
    return node;
  }

  Node* predecessor(Node* x)
  {
    if (x->left != dummy)
    {
      return maximum(x->left);
    }

    Node* y = x->parent;
    while (y != dummy && x == y->left)
    {
      x = y;
      y = y->parent;
    }

    return y;
  }

  void leftRotate(Node* x)
  {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != dummy)
    {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr)
    {
      this->root = y;
    }
    else if (x == x->parent->left)
    {
      x->parent->left = y;
    }
    else
    {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void rightRotate(Node* x)
  {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != dummy)
    {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr)
    {
      this->root = y;
    }
    else if (x == x->parent->right)
    {
      x->parent->right = y;
    }
    else
    {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

  // Inserting a node
  void insert(int key, string s)
  {
    cnt++;
    Node* node = new Node;
    node->parent = nullptr;
    node->data = key;
    node->str = s;
    node->left = dummy;
    node->right = dummy;
    node->color = 1;

    Node* y = nullptr;
    Node* x = this->root;

    while (x != dummy)
    {
      y = x;
      if (node->data < x->data)
      {
        x = x->left;
      }
      else
      {
        x = x->right;
      }
    }

    node->parent = y;
    if (y == nullptr)
    {
      root = node;
    }
    else if (node->data < y->data)
    {
      y->left = node;
    }
    else
    {
      y->right = node;
    }

    if (node->parent == nullptr)
    {
      node->color = 0;
      return;
    }

    if (node->parent->parent == nullptr)
    {
      return;
    }

    insertFix(node);
  }

  Node* getRoot()
  {
    return this->root;
  }

  void deleteNode(int data)
  {
    deleteNodeHelper(this->root, data);
  }

  void print(Node *curr)
  {
    if (curr == dummy)
      return;
    if (curr->color == 0)
      cout << curr->data << "_" << curr->str;
    else
      cout << hue::red << curr->data << "_" << curr->str << hue::reset;

    if (curr->left != dummy || curr->right != dummy)
    {
      cout << "(";
      print(curr->left);
      cout << ",";
      print(curr->right);
      cout << ")";
    }
  }
  void printTree()
  {
    if (root == dummy)
      cout << "Tree is empty" << endl;
    else
      print(root);
    cout << endl;
  }
  int size()
  {
    return cnt;
  }
  void deleteTreeRecur(Node *root)
  {
    if (root == dummy)
    {
      return;
    }
    deleteTreeRecur(root->left);
    deleteTreeRecur(root->right);
    delete root;
  }
  void deleteTree()
  {
    cnt = 0;
    deleteTreeRecur(root);
    root = dummy;
  }
  bool isEmpty()
  {
    return cnt == 0;
  }
  void inorder(Node *x)
  {
    if (x == dummy)
      return;
    inorder(x->left);
    if (x->color == 0)
      cout << x->data << " ⇒ " << x->str << endl;
    else
      cout << hue::red << x->data << " ⇒ " << x->str << hue::reset << endl;
    inorder(x->right);
  }
  void printInOrder()
  {
    // cout << "Inorder: " << endl;
    if (root == dummy){}
      //cout << "Tree is empty" << endl;
    else
      inorder(root);
    // cout << endl;
  }

  bool search1(Node *current, int val)
  {
    // base cases
    if (current == nullptr)
      return false;
    if (current->data == val)
      return true;

    // search in the right subtree
    if (val > current->data)
    {
      return search1(current->right, val);
    }
    else if (val < current->data)
    {
      return search1(current->left, val);
    }
    return false;
  }
  bool find(int val)
  {
    return search1(root, val);
  }
};
