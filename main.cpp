#include <iostream>
#include <algorithm>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <chrono>

using namespace std;

vector<int> generateArray(std::mt19937 mt, int length, int maxVal) {
    //init array
    std::vector<int> arr(length);
    std:uniform_int_distribution<int> dist(0, maxVal);

    //clear after each generation
    arr.clear();

    //generate array
    for (int i = 0; i < length; i++) {
        arr.push_back(dist(mt));
    }

    return arr;
}

void printArray(std::vector<int> arr, int length) {
    for (int i = 0; i < length; i++) {
        cout << arr[i] << ", ";
    }
}

int MinDistance1(std::vector<int> A) {
    double dmin;
    int n = (sizeof(A)/sizeof(A[0]));
    dmin = std::numeric_limits<double>::infinity();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i != j) && (abs(A[i] - A[j]) < dmin)) { //Basic Operation
                dmin = abs(A[i] - A[j]);
            }
        }
    }
    return dmin;
}

int MinDistance2(std::vector<int> A) {
    double dmin;
    int n = (sizeof(A)/sizeof(A[0]));
    int temp = 0;

    dmin = std::numeric_limits<double>::infinity();
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            temp = abs(A[i] - A[j]);
            if (temp < dmin) { //Basic Operation
                dmin = temp;
            }
        }
    }
    cout << endl << "dmin: " << dmin << endl << endl;
    return dmin;
}


int main()
{
    //CONFIG
    int PERMUTATIONS = 5; //Unique permutations of randomly filled arrays.
    int GROWTH_RATE = 1; //How many times the INCREMENT_AMOUNT will be added together to form new lengths of arrays
    int LENGTH = 20; //Vector length, as well as degree that array length will grow with GROWTH_RATE
    int VALUE_MAX = 1000; //Array values will generate from 1 to VALUE_MAX

    //Prepare CSV
    ofstream myfile;
    myfile.open ("outputMain.csv");
    myfile << "Length (n)" << "," << "Basic Operations" << "," << "Theoretical Average Efficiency" << endl;

    for (int i = 0; i < PERMUTATIONS; i++) {
        //generate a new seed based on time for each array
        auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
        std::mt19937 mt(seed);

        vector<int> a = generateArray(mt, LENGTH, VALUE_MAX);
        printArray(a, LENGTH);
        MinDistance1(a);
        MinDistance2(a);
    }





}
