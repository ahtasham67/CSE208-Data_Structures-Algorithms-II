#include <iostream>
#include <cstring>
#include <string>
#include <bits/stdc++.h>

using namespace std;

// const long long N = 10000, T = 0.1 * N;
// vector<string> randomWords;

bool isPrime(long long n)
{
    if (n <= 1)
        return false;
    for (long long i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

// string randomWordGenerator(long long n)
// {
//     string s;
//     for (long long i = 0; i < n; i++)
//     {
//         s.push_back('a' + rand() % 26);
//     }
//     return s;
// }
// bool alreadyExists(string s)
// {
//     for (auto i : randomWords)
//     {
//         if (i == s)
//             return true;
//     }
//     return false;
// }

long long nextPrime(long long n)
{
    for (long long i = n + 1;; i++)
    {
        if (isPrime(i))
            return i;
    }
}

class Node
{
public:
    string key;
    long long value;
    Node *next;
    Node(const string &k, long long v) : key(k), value(v), next(nullptr) {}
    ~Node() {}
};

class HashMap
{
public:
    long long numOfElements, capacity, deletedNum, initcap;
    // Node **arr;
    vector<Node *> arr;
    long long probeCount, collisionCount, maxChainLength, chainLength[100000];

    // HashMap() : capacity(100), probeCount(0), collisionCount(0), numOfElements(0), arr(new Node *[capacity]()) {}
    HashMap(long long cap, long long c) : capacity(cap), probeCount(0), deletedNum(0), collisionCount(0), numOfElements(0), arr(capacity, nullptr), maxChainLength(c)
    {
        for (long long i = 0; i < cap; i++)
        {
            chainLength[i] = 0;
        }
        initcap = cap;
    }

    long long getMaxChainLength()
    {
        long long max = 0;
        for (long long i = 0; i < capacity; i++)
        {
            if (chainLength[i] > max)
            {
                max = chainLength[i];
            }
        }
        // cout << max << endl;
        return max;
    }
    ~HashMap()
    {
        for (long long i = 0; i < capacity; ++i)
        {
            Node *current = arr[i];
            while (current)
            {
                Node *next = current->next;
                delete current;
                current = next;
            }
        }
        // delete[] arr;
    }

    long long getCollisionCount()
    {
        return collisionCount;
    }
    long long getProbCount()
    {
        return probeCount;
    }
    // 37 based hash function
    long long hashFunction(const string &key)
    {
        long long hashVal = 0;

        for (long long i = 0; i < key.length(); i++)
            hashVal = 37 * hashVal + key[i];

        hashVal %= capacity;

        if (hashVal < 0)
            hashVal += capacity;

        return hashVal;
    }

    // ON AT A TIME HASH FUNCTION
    //  unsigned long long hashFunction(const std::string &key)
    //  {
    //      unsigned long long hash = 0;
    //      for (char c : key)
    //      {
    //          hash += c;
    //          hash += hash << 10;
    //          hash ^= hash >> 6;
    //      }
    //      hash += hash << 3;
    //      hash ^= hash >> 11;
    //      hash += hash << 15;
    //      hash %= capacity;
    //      return hash;
    //  }
    void insert(const string &key, long long value)
    {
        inserthelp(key, value, arr);
        // cout << getMaxChainLength() << endl;
    }

    void inserthelp(const string &key, long long value, vector<Node *> &Narr)
    {
        long long bucketIndex = hashFunction(key);
        Node *newNode = new Node(key, value);
        if (getMaxChainLength() > maxChainLength && numOfElements % 1000 == 0)
        {
            reHash();
            bucketIndex = hashFunction(key);
        }
        // cout<<getMaxChainLength()<<endl;
        if (Narr[bucketIndex] == nullptr)
        {
            Narr[bucketIndex] = newNode;
        }
        else
        {
            newNode->next = Narr[bucketIndex];
            Narr[bucketIndex] = newNode;
            collisionCount++;
            chainLength[bucketIndex]++;
            // cout << chainLength[bucketIndex] << endl;
        }
        numOfElements++;
    }

    void deleteKey(const string &key)
    {
        // cout << getMaxChainLength() << endl;
        if (deletedNum == 100 && getMaxChainLength() >= (0.8 * maxChainLength))
        {
            delReHash();
            deletedNum = 0;
            // cout << getMaxChainLength() << endl;
        }
        long long bucketIndex = hashFunction(key);
        Node *prevNode = nullptr;
        Node *currNode = arr[bucketIndex];
        while (currNode != nullptr)
        {
            if (key == currNode->key)
            {
                if (currNode == arr[bucketIndex])
                {
                    arr[bucketIndex] = currNode->next;
                }
                else
                {
                    prevNode->next = currNode->next;
                }
                delete currNode;
                // cout << "deleted" <<" "<< key << endl;
                numOfElements--;
                chainLength[bucketIndex]--;
                deletedNum++;
                // cout<<deletedNum<<endl;
                // cout<<numOfElements<<endl;
                return;
            }
            prevNode = currNode;
            currNode = currNode->next;
        }
    }
    void search(const string &key)
    {

        long long bucketIndex = hashFunction(key);
        Node *bucketHead = arr[bucketIndex];
        probeCount++;
        while (bucketHead != nullptr)
        {
            if (key == bucketHead->key)
            {
                return;
            }
            bucketHead = bucketHead->next;
            probeCount++;
        }
        // return "Oops! No data found.";
    }

    bool search1(const string &key)
    {

        long long bucketIndex = hashFunction(key);
        Node *bucketHead = arr[bucketIndex];
        probeCount++;
        while (bucketHead != nullptr)
        {
            if (key == bucketHead->key)
            {
                return true;
            }
            bucketHead = bucketHead->next;
            probeCount++;
        }
        // return "Oops! No data found.";
        false;
    }
    void reHash()
    {
        long long newCapacity = nextPrime(capacity * 2);
        vector<Node *> newArr(newCapacity, nullptr); // Initialize new array with new capacity

        if (newArr.empty())
        {
            cout << "Memory allocation failed" << endl;
            return;
        }

        // Resetting variables
        memset(chainLength, 0, sizeof(chainLength));
        // probeCount = 0;
        collisionCount = 0;

        // Moving existing elements to the new array
        for (long long i = 0; i < capacity; i++)
        {
            Node *current = arr[i];
            while (current != nullptr)
            {
                Node *nextNode = current->next;
                long long bucketIndex = hashFunction(current->key); // Re-hash the key
                if (newArr[bucketIndex] != nullptr)
                    collisionCount++;                // if (newArr[bucketIndex] != nullptr) collisionCount++;
                current->next = newArr[bucketIndex]; // Insert at the head of the new chain
                newArr[bucketIndex] = current;       // Update the head of the new chain
                chainLength[bucketIndex]++;          // Update chain length
                current = nextNode;
                numOfElements--; // Decrement numOfElements since we are moving elements
            }
        }

        // Delete the old array (do not delete nodes themselves, just the array)
        // No need to delete nodes themselves as they are now part of newArr
        // Memory for old nodes will be deallocated when newArr is destroyed
        // Also, no need to set old array elements to nullptr, as they are not used anymore
        arr.clear();            // Clear the vector, which deallocates memory
        arr = move(newArr);     // Assign newArr to arr, transferring ownership
        capacity = newCapacity; // Update capacity
        // cout << "Rehash completed. New capacity: " << newCapacity << endl;
    }

    void delReHash()
    {
        cout << "in delete Rehashing" << endl;
        if (capacity / 2 < initcap)
            return;
        long long newCapacity = nextPrime(capacity / 2);
        vector<Node *> newArr(newCapacity, nullptr); // Initialize new array with new capacity

        if (newArr.empty())
        {
            cout << "Memory allocation failed" << endl;
            return;
        }

        // Resetting variables
        memset(chainLength, 0, sizeof(chainLength));
        // probeCount = 0;
        collisionCount = 0;

        // Moving existing elements to the new array
        for (long long i = 0; i < capacity; i++)
        {
            Node *current = arr[i];
            while (current != nullptr)
            {
                Node *nextNode = current->next;
                long long bucketIndex = hashFunction(current->key); // Re-hash the key
                if (newArr[bucketIndex] != nullptr)
                    collisionCount++;
                current->next = newArr[bucketIndex]; // Insert at the head of the new chain
                newArr[bucketIndex] = current;       // Update the head of the new chain
                chainLength[bucketIndex]++;          // Update chain length
                current = nextNode;
                numOfElements--; // Decrement numOfElements since we are moving elements
            }
        }

        arr.clear();            // Clear the vector, which deallocates memory
        arr = move(newArr);     // Assign newArr to arr, transferring ownership
        capacity = newCapacity; // Update capacity
        // cout << "Rehash completed. New capacity: " << newCapacity << endl;
    }
};

class HashMap2
{
public:
    long long numOfElements, capacity, deletedNum, initcap;
    // Node **arr;
    vector<Node *> arr;
    long long probeCount, collisionCount, maxChainLength, chainLength[100000];

    // HashMap() : capacity(100), probeCount(0), collisionCount(0), numOfElements(0), arr(new Node *[capacity]()) {}
    HashMap2(long long cap, long long c) : capacity(cap), probeCount(0), deletedNum(0), collisionCount(0), numOfElements(0), arr(capacity, nullptr), maxChainLength(c)
    {
        for (long long i = 0; i < cap; i++)
        {
            chainLength[i] = 0;
        }
        initcap = cap;
    }

    long long getMaxChainLength()
    {
        long long max = 0;
        for (long long i = 0; i < capacity; i++)
        {
            if (chainLength[i] > max)
            {
                max = chainLength[i];
            }
        }
        // cout << max << endl;
        return max;
    }
    ~HashMap2()
    {
        for (long long i = 0; i < capacity; ++i)
        {
            Node *current = arr[i];
            while (current)
            {
                Node *next = current->next;
                delete current;
                current = next;
            }
        }
        // delete[] arr;
    }

    long long getCollisionCount()
    {
        return collisionCount;
    }
    long long getProbCount()
    {
        return probeCount;
    }
    // 37 based hash function
    long long hashFunction(const string &k)
    {
        // long long hashVal = 0;

        // for (long long i = 0; i < key.length(); i++)
        //     hashVal = 37 * hashVal + key[i];

        // hashVal %= capacity;

        // if (hashVal < 0)
        //     hashVal += capacity;

        // return hashVal;
        char *key = (char *)k.c_str();
        unsigned int *lkey = (unsigned int *)key;
        long long intlength = k.size() / 4;
        unsigned int sum = 0;

        for (long long i = 0; i < intlength; i++)
            sum += lkey[i];

        // Now deal with the extra chars at the end
        long long extra = k.size() - intlength * 4;
        char temp[4];
        lkey = (unsigned int *)temp;
        lkey[0] = 0;

        for (long long i = 0; i < extra; i++)
            temp[i] = key[intlength * 4 + i];

        sum += lkey[0];
        return sum % capacity;
    }

    // ON AT A TIME HASH FUNCTION
    //  unsigned long long hashFunction(const std::string &key)
    //  {
    //      unsigned long long hash = 0;
    //      for (char c : key)
    //      {
    //          hash += c;
    //          hash += hash << 10;
    //          hash ^= hash >> 6;
    //      }
    //      hash += hash << 3;
    //      hash ^= hash >> 11;
    //      hash += hash << 15;
    //      hash %= capacity;
    //      return hash;
    //  }
    void insert(const string &key, long long value)
    {
        inserthelp(key, value, arr);
        // cout << getMaxChainLength() << endl;
    }

    void inserthelp(const string &key, long long value, vector<Node *> &Narr)
    {
        long long bucketIndex = hashFunction(key);
        Node *newNode = new Node(key, value);
        if (getMaxChainLength() > maxChainLength && numOfElements % 100 == 0)
        {
            reHash();
            bucketIndex = hashFunction(key);
        }
        // cout<<getMaxChainLength()<<endl;
        if (Narr[bucketIndex] == nullptr)
        {
            Narr[bucketIndex] = newNode;
        }
        else
        {
            newNode->next = Narr[bucketIndex];
            Narr[bucketIndex] = newNode;
            collisionCount++;
            chainLength[bucketIndex]++;
            // cout << chainLength[bucketIndex] << endl;
        }
        numOfElements++;
    }

    void deleteKey(const string &key)
    {
        // cout << getMaxChainLength() << endl;
        if (deletedNum == 100 && getMaxChainLength() >= (0.8 * maxChainLength))
        {
            delReHash();
            deletedNum = 0;
            // cout << getMaxChainLength() << endl;
        }
        long long bucketIndex = hashFunction(key);
        Node *prevNode = nullptr;
        Node *currNode = arr[bucketIndex];
        while (currNode != nullptr)
        {
            if (key == currNode->key)
            {
                if (currNode == arr[bucketIndex])
                {
                    arr[bucketIndex] = currNode->next;
                }
                else
                {
                    prevNode->next = currNode->next;
                }
                delete currNode;
                // cout << "deleted" <<" "<< key << endl;
                numOfElements--;
                chainLength[bucketIndex]--;
                deletedNum++;
                // cout<<deletedNum<<endl;
                // cout<<numOfElements<<endl;
                return;
            }
            prevNode = currNode;
            currNode = currNode->next;
        }
    }
    void search(const string &key)
    {

        long long bucketIndex = hashFunction(key);
        Node *bucketHead = arr[bucketIndex];
        probeCount++;
        while (bucketHead != nullptr)
        {
            if (key == bucketHead->key)
            {
                return;
            }
            bucketHead = bucketHead->next;
            probeCount++;
        }
        // return "Oops! No data found.";
    }

    bool search1(const string &key)
    {

        long long bucketIndex = hashFunction(key);
        Node *bucketHead = arr[bucketIndex];
        probeCount++;
        while (bucketHead != nullptr)
        {
            if (key == bucketHead->key)
            {
                return true;
            }
            bucketHead = bucketHead->next;
            probeCount++;
        }
        // return "Oops! No data found.";
        false;
    }
    void reHash()
    {
        long long newCapacity = nextPrime(capacity * 2);
        vector<Node *> newArr(newCapacity, nullptr); // Initialize new array with new capacity

        if (newArr.empty())
        {
            cout << "Memory allocation failed" << endl;
            return;
        }

        // Resetting variables
        memset(chainLength, 0, sizeof(chainLength));
        // probeCount = 0;
        collisionCount = 0;

        // Moving existing elements to the new array
        for (long long i = 0; i < capacity; i++)
        {
            Node *current = arr[i];
            while (current != nullptr)
            {
                Node *nextNode = current->next;
                long long bucketIndex = hashFunction(current->key); // Re-hash the key
                if (newArr[bucketIndex] != nullptr)
                    collisionCount++;
                current->next = newArr[bucketIndex]; // Insert at the head of the new chain
                newArr[bucketIndex] = current;       // Update the head of the new chain
                chainLength[bucketIndex]++;          // Update chain length
                current = nextNode;
                numOfElements--; // Decrement numOfElements since we are moving elements
            }
        }

        arr.clear();
        arr = move(newArr);
        capacity = newCapacity; // Update capacity
        // cout << "Rehash completed. New capacity: " << newCapacity << endl;
    }

    void delReHash()
    {
        cout << "in delete Rehashing" << endl;
        if (capacity / 2 < initcap)
            return;
        long long newCapacity = nextPrime(capacity / 2);
        vector<Node *> newArr(newCapacity, nullptr); // Initialize new array with new capacity

        if (newArr.empty())
        {
            cout << "Memory allocation failed" << endl;
            return;
        }

        // Resetting variables
        memset(chainLength, 0, sizeof(chainLength));
        // probeCount = 0;
        collisionCount = 0;

        // Moving existing elements to the new array
        for (long long i = 0; i < capacity; i++)
        {
            Node *current = arr[i];
            while (current != nullptr)
            {
                Node *nextNode = current->next;
                long long bucketIndex = hashFunction(current->key); // Re-hash the key
                if (newArr[bucketIndex] != nullptr)
                    collisionCount++;
                current->next = newArr[bucketIndex]; // Insert at the head of the new chain
                newArr[bucketIndex] = current;       // Update the head of the new chain
                chainLength[bucketIndex]++;          // Update chain length
                current = nextNode;
                numOfElements--; // Decrement numOfElements since we are moving elements
            }
        }

        arr.clear();            // Clear the vector, which deallocates memory
        arr = move(newArr);     // Assign newArr to arr, transferring ownership
        capacity = newCapacity; // Update capacity
        // cout << "Rehash completed. New capacity: " << newCapacity << endl;
    }
};

// vector<long long> unqIndx;
// bool isUnq(long long num)
// {
//     for (auto i : unqIndx)
//     {
//         if (i == num)
//             return false;
//     }
//     return true;
// }

// int main()
// {
//     srand(2105067);
//     unqIndx.clear();
//     cout << "enter chainlength" << endl;
//     long long c;
//     cin >> c;
//     HashMap *mp = new HashMap(nextPrime(5000),c);
//     for (long long i = 1; i <= 10000; i++)
//     {
//         long long len = 5 + rand() % 6;
//         string s = randomWordGenerator(len);
//         if (!alreadyExists(s))
//             randomWords.push_back(s);
//         else
//             i--;
//     }
//     for (long long i = 0; i < randomWords.size(); i++)
//     {
//         mp->insert(randomWords[i], i);
//         // cout << randomWords[i] << " " << i << endl;
//     }

//     cout << "Collision Count: " << mp->getCollisionCount() << endl;

//     for (long long i = 0; i < 1000; i++)
//     {
//         long long indx = rand() % 10000;
//         if (isUnq(indx))
//         {
//             unqIndx.push_back(indx);
//         }
//         else
//         {
//             i--;
//         }
//     }
//     for (auto i : unqIndx)
//     {
//         mp->search(randomWords[i]);
//     }
//     cout << "Probe Count: " << mp->getProbCount() << endl;

//     for (int i = 0; i < 500; i++)
//     {
//         int indx = rand() % 10000;
//         mp->deleteKey(randomWords[indx]);
//     }
//     cout << "Collision Count: " << mp->getCollisionCount() << endl;
//     cout << "Probe Count: " << mp->getProbCount() << endl;
//     delete mp;

//     HashMap2 *mp2 = new HashMap2(nextPrime(5000),c);
//     for (long long i = 0; i < randomWords.size(); i++)
//     {
//         mp2->insert(randomWords[i], i);
//         // cout << randomWords[i] << " " << i << endl;
//     }
//     cout << "Collision Count: " << mp2->getCollisionCount() << endl;
//     for (auto i : unqIndx)
//     {
//         mp2->search(randomWords[i]);
//     }
//     cout << "Probe Count: " << mp2->getProbCount() << endl;
//     for (int i = 0; i < 500; i++)
//     {
//         int indx = rand() % 10000;
//         mp2->deleteKey(randomWords[indx]);
//     }
//     cout << "Collision Count: " << mp2->getCollisionCount() << endl;
//     delete mp2;
//     unqIndx.clear();
//     randomWords.clear();
//     return 0;
// }
