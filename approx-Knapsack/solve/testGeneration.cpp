#include <iostream>
#include <fstream>
#include <random>
using namespace std;
int main() {
    int n = 50; // Number of items
    int W = 1000; // Maximum weight capacity

    random_device rd;
    mt19937 gen(rd());

    // Value range and weight range
    uniform_int_distribution<int> val_dist(1200,1400);
    uniform_int_distribution<int> weight_dist(12,31);

    ofstream outFile("output.txt");
    if (!outFile.is_open()) {
        cerr << "Unable to create file!" << endl;
        return 1;
    }

    // Write n and W to file
    outFile << n << endl;
    outFile << W << endl;

    // Generate and write n lines with random vi and wi values
    for (int i = 0; i < n; ++i) {
        int vi = val_dist(gen);
        int wi = weight_dist(gen);
        outFile << vi << " " << wi << endl;
    }

    outFile.close();
    cout << "Test case generated and saved to test_case.txt" << endl;

    return 0;
}