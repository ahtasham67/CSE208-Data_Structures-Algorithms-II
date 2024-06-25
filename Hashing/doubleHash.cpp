#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

// const long long N = 10000, T = 0.1 * N;
// vector<string> randomWords;

bool isPrime1(long long n)
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

long long nextPrime1(long long n)
{
    for (long long i = n + 1;; i++)
    {
        if (isPrime1(i))
            return i;
    }
}
long long lastPrime(long long n)
{
    for (long long i = n - 1;; i--)
    {
        if (isPrime1(i))
            return i;
    }
}

// class Node
// {
// public:
//     string key;
//     long long value;
//     Node() : key(""), value(0) {}
//     Node(string key, long long value) : key(key), value(value) {}
// };

class DoubleHash1
{
    long long TABLE_SIZE, keysPresent, PRIME, collisionCount, probeCount;
    Node **hashTable;
    Node *dummy = new Node("dummy", -2);

    long long hash1(string key)
    {
        long long hashVal = 0;
        for (long long i = 0; i < key.length(); i++)
            hashVal = 37 * hashVal + key[i];
        hashVal %= TABLE_SIZE;
        if (hashVal < 0)
            hashVal += TABLE_SIZE;
        return hashVal;
    }

    long long hash2(string key)
    {
        return PRIME - (hash1(key) % PRIME);
    }

    bool isFull()
    {
        return (TABLE_SIZE == keysPresent);
    }

public:
    DoubleHash1(long long n) : keysPresent(0)
    {
        // cout<<"in the constructor"<<endl;
        TABLE_SIZE = nextPrime1(n);
        PRIME = lastPrime(TABLE_SIZE);
        hashTable = new Node *[TABLE_SIZE];
        for (long long i = 0; i < TABLE_SIZE; i++)
            hashTable[i] = nullptr;
        probeCount = 0;
        collisionCount = 0;
    }

    void insert(string key, long long value)
    {
        if (isFull())
        {
            // cout << "Hash table is full. Unable to insert more elements.\n";
            collisionCount++;
            return;
        }
        long long probe = hash1(key), offset = hash2(key), i = 1, temp = hash1(key);
        if (hashTable[probe] != nullptr)
            collisionCount++;
        while (hashTable[probe] != nullptr || hashTable[probe] == dummy)
        {
            if (hashTable[probe]->key == key)
            {
                // Key already exists, no need to insert, just return
                return;
            }
            probe = (temp + i * offset) % TABLE_SIZE;
            i++;
        }

        // Insert the new node since no existing key was found
        hashTable[probe] = new Node(key, value);
        // cout << hashTable[probe]->key << endl;
        keysPresent += 1;
    }

    bool search(string key)
    {
        long long probe = hash1(key), offset = hash2(key), initialPos = probe;
        long long i = 0;
        probeCount++;
        while (true)
        {
            if (hashTable[probe] == nullptr)
                break;
            else if (hashTable[probe] != dummy && probe == initialPos && i != 0)
            {
                return false;
            }
            else if (hashTable[probe]->key == key)
            {
                if (hashTable[probe] != dummy)
                    return true; // Key found
                else
                    return false; // Key was deleted
            }
            probeCount++;
            probe = (initialPos + i * offset) % TABLE_SIZE;
            i++;
        }
        return false; // Key not found
    }

    void deletekey(string key)
    {
        if (!search(key))
        {
            cout << "Key not found" << endl;
            return;
        }
        long long probe = hash1(key), offset = hash2(key), initialPos = probe, temp = hash1(key);
        bool firstItr = true;
        long long i = 0;
        while (true)
        {
            if (hashTable[probe] == nullptr)
                break;
            else if (probe == initialPos && !firstItr)
            {
                break;
            }
            else if (hashTable[probe]->key == key)
            {
                hashTable[probe] = dummy;
                keysPresent--;
                return;
            }
            probeCount++;
            probe = (temp + (i * offset)) % TABLE_SIZE;
            i++;
            firstItr = false;
        }
    }

    long long getKeysPresent()
    {
        return keysPresent;
    }
    long long getTableSize()
    {
        return TABLE_SIZE;
    }
    long long getProbeCount()
    {
        return probeCount;
    }
    long long getCollisionCount()
    {
        return collisionCount;
    }
    long long getPrime() { return PRIME; }
    ~DoubleHash1()
    {
        for (long long i = 0; i < TABLE_SIZE; ++i)
        {
            delete hashTable[i];
        }
        delete[] hashTable;
    }

    void printHashTable()
    {
        for (long long i = 0; i < TABLE_SIZE; ++i)
        {
            if (hashTable[i] != nullptr)
            {
                if (hashTable[i] == dummy)
                {
                    cout << "Slot " << i << ": dummy" << endl;
                }
                else
                {
                    cout << "Slot " << i << ": " << hashTable[i]->key << endl;
                }
            }
            else
            {
                cout << "Slot " << i << ": nullptr" << endl;
            }
        }
    }
};

class DoubleHash2
{
    long long TABLE_SIZE, keysPresent, PRIME, collisionCount, probeCount;
    Node **hashTable;
    Node *dummy = new Node("dummy", -2);

    long long hash1(string k)
    {
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
        return sum % TABLE_SIZE;
    }

    long long hash2(string key)
    {
        return PRIME - (hash1(key) % PRIME);
    }

    bool isFull()
    {
        return (TABLE_SIZE == keysPresent);
    }

public:
    DoubleHash2(long long n) : keysPresent(0)
    {
        // cout<<"in the constructor"<<endl;
        TABLE_SIZE = nextPrime1(n);
        PRIME = lastPrime(TABLE_SIZE);
        hashTable = new Node *[TABLE_SIZE];
        for (long long i = 0; i < TABLE_SIZE; i++)
            hashTable[i] = nullptr;
        probeCount = 0;
        collisionCount = 0;
    }

    void insert(string key, long long value)
    {
        if (isFull())
        {
            // cout << "Hash table is full. Unable to insert more elements.\n";
            collisionCount++;
            return;
        }
        long long probe = hash1(key), offset = hash2(key), i = 1, temp = hash1(key);
        if (hashTable[probe] != nullptr)
            collisionCount++;
        while (hashTable[probe] != nullptr || hashTable[probe] == dummy)
        {
            if (hashTable[probe]->key == key)
            {
                // Key already exists, no need to insert, just return
                return;
            }
            probe = (temp + i * offset) % TABLE_SIZE;
            i++;
        }

        // Insert the new node since no existing key was found
        hashTable[probe] = new Node(key, value);
        // cout << hashTable[probe]->key << endl;
        keysPresent += 1;
    }

    bool search(string key)
    {
        long long probe = hash1(key), offset = hash2(key), initialPos = probe;
        long long i = 0;
        probeCount++;
        while (true)
        {
            if (hashTable[probe] == nullptr)
                break;
            else if (hashTable[probe] != dummy && probe == initialPos && i != 0)
            {
                return false;
            }
            else if (hashTable[probe]->key == key)
            {
                if (hashTable[probe] != dummy)
                    return true; // Key found
                else
                    return false; // Key was deleted
            }
            probeCount++;
            probe = (initialPos + i * offset) % TABLE_SIZE;
            i++;
        }
        return false; // Key not found
    }

    void deletekey(string key)
    {
        if (!search(key))
        {
            cout << "Key not found" << endl;
            return;
        }
        long long probe = hash1(key), offset = hash2(key), initialPos = probe, temp = hash1(key);
        bool firstItr = true;
        long long i = 0;
        while (true)
        {
            if (hashTable[probe] == nullptr)
                break;
            else if (probe == initialPos && !firstItr)
            {
                break;
            }
            else if (hashTable[probe]->key == key)
            {
                hashTable[probe] = dummy;
                keysPresent--;
                return;
            }
            probeCount++;
            probe = (temp + (i * offset)) % TABLE_SIZE;
            i++;
            firstItr = false;
        }
    }

    long long getKeysPresent()
    {
        return keysPresent;
    }
    long long getTableSize()
    {
        return TABLE_SIZE;
    }
    long long getProbeCount()
    {
        return probeCount;
    }
    long long getCollisionCount()
    {
        return collisionCount;
    }
    long long getPrime() { return PRIME; }
    ~DoubleHash2()
    {
        for (long long i = 0; i < TABLE_SIZE; ++i)
        {
            delete hashTable[i];
        }
        delete[] hashTable;
    }

    void printHashTable()
    {
        for (long long i = 0; i < TABLE_SIZE; ++i)
        {
            if (hashTable[i] != nullptr)
            {
                if (hashTable[i] == dummy)
                {
                    cout << "Slot " << i << ": dummy" << endl;
                }
                else
                {
                    cout << "Slot " << i << ": " << hashTable[i]->key << endl;
                }
            }
            else
            {
                cout << "Slot " << i << ": nullptr" << endl;
            }
        }
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
//     // freopen("output.txt", "w", stdout);
//     srand(2105067);

//     DoubleHash1 dh1(10000);
//     // cout << dh.getTableSize() << endl;
//     // cout << dh.getKeysPresent() << endl;
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
//         // cout<<"inserting "<<i<<endl;
//         dh1.insert(randomWords[i], i);
//     }
//     cout << "Collision Count:hash2 " << dh1.getCollisionCount() << endl;

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
//         dh1.search(randomWords[i]);
//     }
//     cout << "Probe Count: hash2 " << dh1.getProbeCount() << endl;

//     // dh2.printHashTable();
//     if (dh1.search("cdsuhvbtsl"))
//         cout << "found" << endl;
//     else
//         cout << "not found" << endl;
//     dh1.deletekey("cdsuhvbtsl");
//     if (dh1.search("cdsuhvbtsl"))
//         cout << "found" << endl;
//     else
//         cout << "not found" << endl;

//     DoubleHash2 dh2(10000);
//     for (long long i = 0; i < randomWords.size(); i++)
//     {
//         // cout<<"inserting "<<i<<endl;
//         dh2.insert(randomWords[i], i);
//     }
//     cout << "Collision Count:hash2 " << dh2.getCollisionCount() << endl;

//     for (auto i : unqIndx)
//     {
//         dh2.search(randomWords[i]);
//     }
//     cout << "Probe Count: hash2 " << dh2.getProbeCount() << endl;

//     // dh2.printHashTable();
//     if (dh2.search("cdsuhvbtsl"))
//         cout << "found" << endl;
//     else
//         cout << "not found" << endl;
//     dh2.deletekey("cdsuhvbtsl");
//     if (dh2.search("cdsuhvbtsl"))
//         cout << "found" << endl;
//     else
//         cout << "not found" << endl;
//     return 0;
// }
