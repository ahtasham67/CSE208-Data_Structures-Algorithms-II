#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
#include "seperateChaining.cpp"
#include "doubleHash.cpp"
#include "customProb.cpp"
using namespace std;

const long long N = 10000, T = 0.1 * N;
vector<string> randomWords;
// bool isPrime(long long n)
// {
//     if (n <= 1)
//         return false;
//     for (long long i = 2; i * i <= n; i++)
//     {
//         if (n % i == 0)
//             return false;
//     }
//     return true;
// }

string randomWordGenerator(long long n)
{
    string s;
    for (long long i = 0; i < n; i++)
    {
        s.push_back('a' + rand() % 26);
    }
    return s;
}
bool alreadyExists(string s)
{
    for (auto i : randomWords)
    {
        if (i == s)
            return true;
    }
    return false;
}

// long long nextPrime(long long n)
// {
//     for (long long i = n + 1;; i++)
//     {
//         if (isPrime(i))
//             return i;
//     }
// }
vector<long long> unqIndx;
bool isUnq(long long num)
{
    for (auto i : unqIndx)
    {
        if (i == num)
            return false;
    }
    return true;
}

void generateReport()
{
     cout << "Enter the value of maxChainLength for seperate chaining: ";
    freopen("output.txt", "w", stdout);
    srand(2105067);
    unqIndx.clear();
    long long c;
    cin >> c;
    HashMap *mp1 = new HashMap(nextPrime(5000), c);
    for (long long i = 1; i <= 10000; i++)
    {
        long long len = 5 + rand() % 6;
        string s = randomWordGenerator(len);
        if (!alreadyExists(s))
            randomWords.push_back(s);
        else
            i--;
    }
    for (long long i = 0; i < randomWords.size(); i++)
    {
        mp1->insert(randomWords[i], i);
    }
    // cout << "Collision Count: " << mp->getCollisionCount() << endl;
    long long openCount1 = mp1->getCollisionCount();

    for (long long i = 0; i < 1000; i++)
    {
        long long indx = rand() % 10000;
        if (isUnq(indx))
        {
            unqIndx.push_back(indx);
        }
        else
        {
            i--;
        }
    }
    for (auto i : unqIndx)
    {
        mp1->search(randomWords[i]);
    }
    // cout << "Probe Count: " << mp->getProbCount() << endl;
    long long openProbe1 = mp1->getProbCount();
    delete mp1;
    HashMap2 *mp2 = new HashMap2(nextPrime(5000), c);
    for (long long i = 0; i < randomWords.size(); i++)
    {
        mp2->insert(randomWords[i], i);
    }
    for (auto i : unqIndx)
    {
        mp2->search(randomWords[i]);
    }
    // cout << "Collision Count2: " << mp2->getCollisionCount() << endl;
    // cout << "Probe Count2: " << mp2->getProbCount() << endl;
    long long openCount2 = mp2->getCollisionCount();
    long long openProbe2 = mp2->getProbCount();
    // after decimal point 3 points
    double openProbe2ratio = (double)openProbe2 / 1000;
    double openProbe1ratio = (double)openProbe1 / 1000;
    delete mp2;
    /////////////////////////////////

    HashMap *mp3 = new HashMap(nextPrime(10000), c);
    for (long long i = 0; i < randomWords.size(); i++)
    {
        mp3->insert(randomWords[i], i);
    }
    // cout << "Collision Count: " << mp->getCollisionCount() << endl;
    long long openCount3 = mp3->getCollisionCount();

    for (auto i : unqIndx)
    {
        mp3->search(randomWords[i]);
    }
    // cout << "Probe Count: " << mp->getProbCount() << endl;
    long long openProbe3 = mp3->getProbCount();
    delete mp3;

    HashMap2 *mp4 = new HashMap2(nextPrime(10000), c);
    for (long long i = 0; i < randomWords.size(); i++)
    {
        mp4->insert(randomWords[i], i);
    }
    for (auto i : unqIndx)
    {
        mp4->search(randomWords[i]);
    }
    // cout << "Collision Count2: " << mp2->getCollisionCount() << endl;
    // cout << "Probe Count2: " << mp2->getProbCount() << endl;
    long long openCount4 = mp4->getCollisionCount();
    long long openProbe4 = mp4->getProbCount();
    // after decimal point 3 points
    double openProbe4ratio = (double)openProbe4 / 1000;
    double openProbe3ratio = (double)openProbe3 / 1000;
    delete mp4;

    /////////////////////////////

    HashMap *mp5 = new HashMap(nextPrime(20000), c);
    for (long long i = 0; i < randomWords.size(); i++)
    {
        mp5->insert(randomWords[i], i);
    }
    // cout << "Collision Count: " << mp->getCollisionCount() << endl;
    long long openCount5 = mp5->getCollisionCount();
    for (auto i : unqIndx)
    {
        mp5->search(randomWords[i]);
    }
    // cout << "Probe Count: " << mp->getProbCount() << endl;
    long long openProbe5 = mp5->getProbCount();
    delete mp5;
    HashMap2 *mp6 = new HashMap2(nextPrime(20000), c);
    for (long long i = 0; i < randomWords.size(); i++)
    {
        mp6->insert(randomWords[i], i);
    }
    for (auto i : unqIndx)
    {
        mp6->search(randomWords[i]);
    }
    // cout << "Collision Count2: " << mp2->getCollisionCount() << endl;
    // cout << "Probe Count2: " << mp2->getProbCount() << endl;
    long long openCount6 = mp6->getCollisionCount();
    long long openProbe6 = mp6->getProbCount();
    // after decimal point 3 points
    double openProbe6ratio = (double)openProbe6 / 1000;
    double openProbe5ratio = (double)openProbe5 / 1000;
    delete mp6;

    DoubleHash1 dh(5000);
    DoubleHash2 dh2(5000);
    for (long long i = 0; i < randomWords.size(); i++)
    {
        dh.insert(randomWords[i], i);
    }
    for (long long i = 0; i < randomWords.size(); i++)
    {
        dh2.insert(randomWords[i], i);
    }
    long long doublehashcount1 = dh.getCollisionCount();
    long long doublehashcount2 = dh2.getCollisionCount();
    for (auto i : unqIndx)
    {
        dh.search(randomWords[i]);
    }
    for (auto i : unqIndx)
    {
        dh2.search(randomWords[i]);
    }
    long long doublehashprobe1 = dh.getProbeCount();
    long long doublehashprobe2 = dh2.getProbeCount();
    double doublehashprobe1ratio = (double)doublehashprobe1 / 1000;
    double doublehashprobe2ratio = (double)doublehashprobe2 / 1000;

    DoubleHash1 dh3(10000);
    DoubleHash2 dh4(10000);
    for (long long i = 0; i < randomWords.size(); i++)
    {
        dh3.insert(randomWords[i], i);
    }
    for (long long i = 0; i < randomWords.size(); i++)
    {
        dh4.insert(randomWords[i], i);
    }
    long long doublehashcount3 = dh3.getCollisionCount();
    long long doublehashcount4 = dh4.getCollisionCount();
    for (auto i : unqIndx)
    {
        dh3.search(randomWords[i]);
    }
    for (auto i : unqIndx)
    {
        dh4.search(randomWords[i]);
    }
    long long doublehashprobe3 = dh3.getProbeCount();
    long long doublehashprobe4 = dh4.getProbeCount();
    double doublehashprobe3ratio = (double)doublehashprobe3 / 1000;
    double doublehashprobe4ratio = (double)doublehashprobe4 / 1000;

    DoubleHash1 dh5(20000);
    DoubleHash2 dh6(20000);
    for (long long i = 0; i < randomWords.size(); i++)
    {
        dh5.insert(randomWords[i], i);
    }
    for (long long i = 0; i < randomWords.size(); i++)
    {
        dh6.insert(randomWords[i], i);
    }
    long long doublehashcount5 = dh5.getCollisionCount();
    long long doublehashcount6 = dh6.getCollisionCount();
    for (auto i : unqIndx)
    {
        dh5.search(randomWords[i]);
    }
    for (auto i : unqIndx)
    {
        dh6.search(randomWords[i]);
    }
    long long doublehashprobe5 = dh5.getProbeCount();
    long long doublehashprobe6 = dh6.getProbeCount();
    double doublehashprobe5ratio = (double)doublehashprobe5 / 1000;
    double doublehashprobe6ratio = (double)doublehashprobe6 / 1000;

    CustomProb1 cp1(5000);
    CustomProb2 cp2(5000);
    for (long long i = 0; i < randomWords.size(); i++)
    {
        cp1.insert(randomWords[i], i);
    }
    for (long long i = 0; i < randomWords.size(); i++)
    {
        cp2.insert(randomWords[i], i);
    }
    long long customCount1 = cp1.getCollisionCount();
    long long customCount2 = cp2.getCollisionCount();
    for (auto i : unqIndx)
    {
        cp1.search(randomWords[i]);
    }
    for (auto i : unqIndx)
    {
        cp2.search(randomWords[i]);
    }
    long long customProbe1 = cp1.getProbeCount();
    long long customProbe2 = cp2.getProbeCount();
    double customprobcnt1ratio = (double)customProbe1 / 1000;
    double customprobcnt2ratio = (double)customProbe2 / 1000;

    CustomProb1 cp3(10000);
    CustomProb2 cp4(10000);
    for (long long i = 0; i < randomWords.size(); i++)
    {
        cp3.insert(randomWords[i], i);
    }
    for (long long i = 0; i < randomWords.size(); i++)
    {
        cp4.insert(randomWords[i], i);
    }
    long long customCount3 = cp3.getCollisionCount();
    long long customCount4 = cp4.getCollisionCount();
    for (auto i : unqIndx)
    {
        cp3.search(randomWords[i]);
    }
    for (auto i : unqIndx)
    {
        cp4.search(randomWords[i]);
    }
    long long customProbe3 = cp3.getProbeCount();
    long long customProbe4 = cp4.getProbeCount();
    double customprobcnt3ratio = (double)customProbe3 / 1000;
    double customprobcnt4ratio = (double)customProbe4 / 1000;

    CustomProb1 cp5(20000);
    CustomProb2 cp6(20000);
    for (long long i = 0; i < randomWords.size(); i++)
    {
        cp5.insert(randomWords[i], i);
    }
    for (long long i = 0; i < randomWords.size(); i++)
    {
        cp6.insert(randomWords[i], i);
    }
    long long customCount5 = cp5.getCollisionCount();
    long long customCount6 = cp6.getCollisionCount();
    for (auto i : unqIndx)
    {
        cp5.search(randomWords[i]);
    }
    for (auto i : unqIndx)
    {
        cp6.search(randomWords[i]);
    }
    long long customProbe5 = cp5.getProbeCount();
    long long customProbe6 = cp6.getProbeCount();
    double customprobcnt5ratio = (double)customProbe5 / 1000;
    double customprobcnt6ratio = (double)customProbe6 / 1000;

    double report[3][3][2][2] = {
        {{{openCount1, openProbe1ratio}, {openCount2, openProbe2ratio}},
         {{doublehashcount1, doublehashprobe1ratio}, {doublehashcount2, doublehashprobe1ratio}},
         {{customCount1, customprobcnt1ratio}, {customCount2, customprobcnt2ratio}}},
        {{{openCount3, openProbe3ratio}, {openCount4, openProbe3ratio}},
         {{doublehashcount3, doublehashprobe3ratio}, {doublehashcount4, doublehashprobe4ratio}},
         {{customCount3, customprobcnt3ratio}, {customCount4, customprobcnt4ratio}}},
        {{{openCount5, openProbe5ratio}, {openCount6, openProbe6ratio}},
         {{doublehashcount5, doublehashprobe5ratio}, {doublehashcount6, doublehashprobe6ratio}},
         {{customCount5, customprobcnt5ratio}, {customCount6, customprobcnt6ratio}}}};

    long long size[3] = {5000, 10000, 20000};
    cout << "REPORT" << endl;
    // Print report to console
    cout << setw(80) << setfill('_') << "" << endl;
    cout << setfill(' ');
    cout << "| Hash       | Collision         | Hash Function 1 | Hash Function 2 |" << endl;
    cout << "| Table Size | Resolution Method | Colls. | Probes | Colls. | Probes |" << endl;
    cout << "|" << setw(81) << setfill('_') << "|" << endl;
    cout << setfill(' ');

    for (int i = 0; i < 3; i++)
    {
        cout << "| N = " << setw(7) << left << size[i];

        for (int j = 0; j < 3; j++)
        {
            if (j == 0)
                cout << "| Separate Chaining | ";
            else if (j == 1)
                cout << "|" << setw(34) << right << "| Double Hashing    | ";
            else
                cout << "|" << setw(34) << right << "| Custom Probing    | ";

            for (int k = 0; k < 2; k++)
            {
                for (int m = 0; m < 2; m++)
                {
                    if (m == 0)
                        cout << defaultfloat << setw(5) << setprecision(5) << right << report[i][j][k][m] << "  ";
                    if (m == 1)
                        cout << fixed << setw(2) << setprecision(3) << " " << report[i][j][k][m] << "  ";
                }

                cout << "| ";
            }

            cout << endl;
        }

        cout << "|" << setw(81) << setfill('_') << "|" << endl;
        cout << setfill(' ');
    }
    unqIndx.clear();
    randomWords.clear();
}

int main()
{
    generateReport();
    return 0;
}
