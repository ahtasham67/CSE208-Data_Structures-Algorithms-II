#include <cmath>
#include <cstdlib>
#include <iostream>
#include <unordered_set>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

ofstream outputFile("out.txt");
class node
{
public:
    node *parent;
    node *child;
    node *left;
    node *right;
    int key;
    int value;
    int degree;
    bool mark;
};

class fiboHeap
{
    node *maxH;
    int nH;
    // node* arr[1000];
    unordered_map<int, node *> arr;

public:
    fiboHeap()
    {
        maxH = NULL;
        nH = 0;
    }
    node *makeHeap()
    {
        node *np;
        np = NULL;
        return np;
    }
    bool isEmpty()
    {
        return maxH == NULL;
    }

    void insert(fiboHeap *f, int key, int val)
    {
        node *newNode = new node();

        // Initialize a new node
        newNode->key = key;
        newNode->value = val;
        newNode->degree = 0;
        newNode->mark = false;
        newNode->parent = NULL;
        newNode->child = NULL;

        f->arr[key] = newNode;

        // Initialize the circular doubly linked list for the new node
        newNode->left = newNode;
        newNode->right = newNode;

        if (f->maxH != NULL)
        {
            // Link the new node into the root list
            (f->maxH->left)->right = newNode;
            newNode->right = f->maxH;
            newNode->left = f->maxH->left;
            f->maxH->left = newNode;

            // Update the maxH pointer if the new node has a greater key
            if (newNode->key > f->maxH->key)
                f->maxH = newNode;
        }
        else
            f->maxH = newNode; // If the heap is empty, set the new node as the only node in the heap
        f->nH++;
    }

    // Linking the heap nodes in parent child relationship
    void Fibonnaci_link(fiboHeap *h, node *ptr2, node *ptr1)
    {
        // Remove ptr2 from its circular doubly linked list
        (ptr2->left)->right = ptr2->right;
        (ptr2->right)->left = ptr2->left;

        // Update maxH pointer if ptr1's child list is circular and only contains ptr2
        if (ptr1->right == ptr1)
            h->maxH = ptr1;

        // Initialize ptr2 as a singleton circular doubly linked list
        ptr2->left = ptr2;
        ptr2->right = ptr2;

        // Set ptr2 as the child of ptr1
        ptr2->parent = ptr1;
        if (ptr1->child == NULL)
            ptr1->child = ptr2;

        // Insert ptr2 into ptr1's child list
        ptr2->right = ptr1->child;
        ptr2->left = (ptr1->child)->left;
        ((ptr1->child)->left)->right = ptr2;
        (ptr1->child)->left = ptr2;

        // Update ptr1's child list if ptr2 has a smaller key
        if (ptr2->key < (ptr1->child)->key)
            ptr1->child = ptr2;

        ptr1->degree++;
    }

    void Consolidate(fiboHeap *h)
    {
        int temp1;

        // Calculate the maximum degree possible based on the number of nodes in the heap
        float temp2 = (log(h->nH)) / (log(2));
        int temp3 = temp2;

        // Initialize an array to store trees of different degrees
        node *arr[temp3 + 1];
        for (int i = 0; i <= temp3; i++)
            arr[i] = NULL;

        node *ptr1 = h->maxH;
        node *ptr2;
        node *ptr3;

        do
        {
            temp1 = ptr1->degree;

            while (arr[temp1] != NULL)
            {
                ptr2 = arr[temp1];

                // Swap ptr1 and ptr2 if necessary
                if (ptr1->key < ptr2->key)
                {
                    ptr3 = ptr1;
                    ptr1 = ptr2;
                    ptr2 = ptr3;
                }

                // Update maxH if ptr2 is the current maxH
                if (ptr2 == h->maxH)
                    h->maxH = ptr1;

                // Link ptr2 as a child to ptr1 and remove ptr2 from the array
                Fibonnaci_link(h, ptr2, ptr1);
                arr[temp1] = NULL;
                temp1++;
            }

            // Store ptr1 in the array
            arr[temp1] = ptr1;
            ptr1 = ptr1->right;

        } while (ptr1 != h->maxH);

        // Reset maxH to NULL
        h->maxH = NULL;

        // Combine trees of the same degree to form a new root list
        for (int j = 0; j <= temp3; j++)
        {
            if (arr[j] != NULL)
            {
                arr[j]->left = arr[j];
                arr[j]->right = arr[j];

                if (h->maxH != NULL)
                {
                    // Link the tree into the root list
                    (h->maxH->left)->right = arr[j];
                    arr[j]->right = h->maxH;
                    arr[j]->left = h->maxH->left;
                    h->maxH->left = arr[j];

                    // Update maxH if the current tree has a greater key
                    if (arr[j]->key > h->maxH->key)
                        h->maxH = arr[j];
                }
                else
                {
                    h->maxH = arr[j];
                }

                // Update maxH again in case it is NULL
                if (h->maxH == NULL)
                    h->maxH = arr[j];
                else if (arr[j]->key > h->maxH->key)
                    h->maxH = arr[j];
            }
        }
    }

    node *ExtractMax(fiboHeap *h)
    {
        // Check if the heap is empty
        if (h->maxH == NULL)
        {
            outputFile << "The heap is empty" << endl;
            return NULL;
        }
        else
        {
            // Save the maximum node
            node *temp = h->maxH;
            node *temp2 = h->maxH;
            node *pntr;

            // Pointer to iterate through the children of the maximum node
            pntr = temp;
            node *x = NULL;

            // If the maximum node has children, move them to the root list
            if (temp->child != NULL)
            {
                x = temp->child;
                do
                {
                    pntr = x->right;

                    // Insert child node x into the root list
                    (h->maxH->left)->right = x;
                    x->right = h->maxH;
                    x->left = h->maxH->left;
                    h->maxH->left = x;

                    // Update maxH if the child has a greater key
                    if (x->key > h->maxH->key)
                        h->maxH = x;

                    x->parent = NULL;
                    x = pntr;

                } while (pntr != temp->child);
            }

            // Remove the maximum node from the root list
            (temp->left)->right = temp->right;
            (temp->right)->left = temp->left;

            // Update maxH based on the next node in the root list
            h->maxH = temp->right;

            // If there is only one node and it has no children, set maxH to NULL
            if (temp == temp->right && temp->child == NULL)
                h->maxH = NULL;
            else
            {
                // Perform consolidation on the root list
                h->maxH = temp->right;
                Consolidate(h);
            }
            h->nH--;
            // Remove the maximum node from the mapping array
            h->arr[temp2->key] = NULL;
            return temp2;
        }
    }

    // Cutting a node in the heap to be placed in the root list
    void Cut(fiboHeap *h, node *found, node *temp)
    {
        // If the node is the only child, set the parent's child pointer to NULL
        if (found == found->right)
            temp->child = NULL;

        // Remove the node from its sibling list
        (found->left)->right = found->right;
        (found->right)->left = found->left;

        // Update the parent's child pointer if necessary
        if (found == temp->child)
            temp->child = found->right;

        // Decrease the degree of the parent
        temp->degree = temp->degree - 1;
        // Initialize the node as a singleton circular doubly linked list
        found->right = found;
        found->left = found;

        // Insert the node into the root list
        (h->maxH->left)->right = found;
        found->right = h->maxH;
        found->left = h->maxH->left;
        h->maxH->left = found;

        // Reset the parent and mark properties of the node
        found->parent = NULL;
        found->mark = true;
    }

    // Recursive cascade cutting function
    void CascadeCut(fiboHeap *h, node *temp)
    {
        // Get the parent of the current node
        node *par = temp->parent;

        // Check if the node has a parent
        if (par != NULL)
        {
            // If the node is unmarked, mark it
            if (temp->mark == false)
            {
                temp->mark = true;
            }
            else
            {
                // If the node is marked, perform a cut operation and recursively cascade cut its parent
                Cut(h, temp, par);
                CascadeCut(h, par);
            }
        }
    }

    // Function to decrease the value of a node in the heap
    void increaseHelp(fiboHeap *h, node *found, int key)
    {
        if (h->maxH == NULL)
        {
            outputFile << "The Heap is Empty" << endl;
            return;
        }
        found->key = key;
        node *temp = found->parent;

        // If the found node has a parent and its key is greater than the parent's key
        if (temp != NULL && found->key > temp->key)
        {
            Cut(h, found, temp); // Perform a cut operation to detach the found node from its parent
            CascadeCut(h, temp); // Recursively cascade cut the parent node
        }

        // Update maxH if the found node has a greater key
        if (found->key > h->maxH->key)
            h->maxH = found;
    }

    // Function to increaseKey the given node
    void increaseKey(fiboHeap *h, int value, int new_key)
    {
        // need to return the pointer if a specific node having the given value
        int targetValue = value;
        node *foundNode = nullptr;
        for (auto &pair : h->arr)
        {
            if (pair.second != nullptr && pair.second->value == targetValue)
            {
                foundNode = pair.second;
                break;
            }
        }
        // outputFile << "foundNode: " << foundNode->key << " " << foundNode->value << endl;
        if (foundNode != nullptr)
            increaseHelp(h, foundNode, new_key);
        else
            return;
        //  increaseHelp(h, foundNode, new_key);
    }
    node *findmax(fiboHeap *h)
    {
        return h->maxH;
    }
    int numNode()
    {
        return nH;
    }
    // Deleting a node from the heap
    void Deletion(fiboHeap *h, int val)
    {
        if (h->maxH == NULL)
            outputFile << "The heap is empty" << endl;
        else
        {

            increaseKey(h, val, INT_MAX);
            ExtractMax(h);
            outputFile << "Key Deleted" << endl;
        }
    }

    fiboHeap *meld(fiboHeap *h1, fiboHeap *h2)
    {
        fiboHeap *h = new fiboHeap();
        // Case 1: If h1 is empty, set h as a copy of h2
        if (h1->maxH == nullptr)
        {
            h->maxH = h2->maxH;
            h->arr.insert(h2->arr.begin(), h2->arr.end());
        }
        // Case 2: If h2 is empty, set h as a copy of h1
        else if (h2->maxH == nullptr)
        {
            h->maxH = h1->maxH;
            h2->arr.insert(h1->arr.begin(), h1->arr.end());
        }
        // Case 3: Both h1 and h2 are non-empty, merge them
        else
        {
            // Connect the root lists of h1 and h2
            node *temp1 = h1->maxH->right;
            h1->maxH->right = h2->maxH->right;
            (h2->maxH->right)->left = h1->maxH;
            h2->maxH->right = temp1;
            temp1->left = h2->maxH;

            if (h1->maxH->key > h2->maxH->key)
            {
                h->maxH = h1->maxH;
            }
            else
            {
                h->maxH = h2->maxH;
            }

            // Copy the mapping arrays of h1 and h2 to h
            h->arr.insert(h1->arr.begin(), h1->arr.end());
            h->arr.insert(h2->arr.begin(), h2->arr.end());
        }
        h->nH = h1->nH + h2->nH;
        return h;
    }

    queue<node *> q;
    void printHelp(node *root)
    {
        if (root->degree == 0)
        {
            outputFile << endl;
            return;
        }
        outputFile << " -> ";
        node *temp = root->child;
        for (int i = 0; i < root->degree; i++)
        {
            if (temp->degree > 0)
            {
                q.push(temp);
            }
            outputFile << "(" << temp->key << "," << temp->value << ")";
            if (i != root->degree - 1)
            {
                outputFile << ",";
            }
            temp = temp->right;
        }
        outputFile << endl;
    }
    void print()
    {
        int k = 0;
        node *temp = maxH;
        do
        {
            outputFile << "Tree " << ++k << ":";
            // q.clear();
            q.push(temp);
            while (!q.empty())
            {
                node *temp2 = q.front();
                q.pop();
                outputFile << "(" << temp2->key << "," << temp2->value << ")";
                printHelp(temp2);
            }
            temp = temp->right;
        } while (temp != maxH);
        outputFile << endl;
    }
};

void test()
{
    fiboHeap f;
    fiboHeap f1;
    fiboHeap *test = new fiboHeap();
    // checking if the heap is empty
    if (f.isEmpty())
        outputFile << "Heap is empty" << endl;
    else
        outputFile << "Heap is not empty" << endl;
    // inserting 10 nodes in the heap
    outputFile << "inserting 1-10 nodes in the heap" << endl;
    for (int i = 1; i <= 10; i++)
    {
        f.insert(&f, i, i + 100);
    }
    f.print();
    if (f.isEmpty())
        outputFile << "Heap is empty" << endl;
    else
        outputFile << "Heap is not empty" << endl;
    node *extracted = f.ExtractMax(&f);
    if (extracted != NULL)
        outputFile << "Extracted Max " << extracted->key << endl;
    f.print();
    outputFile << "increase value of 8 to 11" << endl;
    f.increaseKey(&f, 108, 11);
    f.print();
    // deleting 9
    outputFile << "deleltion of 9" << endl;
    f.Deletion(&f, 109);
    f.print();
    outputFile << "inserting 20-30 nodes in the heap" << endl;
    for (int i = 20; i <= 30; i++)
    {
        f1.insert(&f1, i, i + 100);
    }
    extracted = f1.ExtractMax(&f1);
    if (extracted != NULL)
        outputFile << "Extracted Max " << extracted->key << endl;
    f1.print();
    test = test->meld(&f, &f1);
    outputFile << "After melding" << endl;
    test->print();
    outputFile << "After extarcting max from meld" << endl;
    extracted = test->ExtractMax(test);
    if (extracted != NULL)
        outputFile << "Extracted Max " << extracted->key << endl;
    test->print();
    outputFile << "AFter second extarcting max" << endl;
    extracted = test->ExtractMax(test);
    if (extracted != NULL)
        outputFile << "Extracted Max " << extracted->key << endl;
    test->print();
    outputFile << "deleltion of 21" << endl;
    test->Deletion(test, 121);
    test->print();
    outputFile << "incraese key of 22 to 50" << endl;
    test->increaseKey(test, 122, 50);
    test->print();
    outputFile << "max of meld " << test->findmax(test)->key << endl;
    if (test->isEmpty())
        outputFile << "Heap is empty" << endl;
    else
        outputFile << "Heap is not empty" << endl;
}

bool areFilesEqual(const string &filePath1, const string &filePath2)
{
    ifstream file1(filePath1, ios::binary | ios::ate);
    ifstream file2(filePath2, ios::binary | ios::ate);

    if (!file1.is_open() || !file2.is_open())
    {
        cerr << "Error opening files." << endl;
        return false;
    }

    file1.seekg(0, ios::beg);
    file2.seekg(0, ios::beg);

    char ch1, ch2;

    while (file1.get(ch1) && file2.get(ch2))
    {
        if (ch1 != ch2)
        {
            file1.close();
            file2.close();
            return false; // Files have different content
        }
    }

    file1.close();
    file2.close();
    return true; // Files are identical
}

// Driver code
int main()
{
    // freopen("out.txt", "w", stdout);
    test();
    if (areFilesEqual("test.txt", "out.txt"))
    {
        cout << "passed" << endl;
    }
    else
    {
        cout << "not passed" << endl;
    }
}