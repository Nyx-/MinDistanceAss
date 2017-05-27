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

int MinDistance1(std::vector<int> A, int length) {
    double dmin;
    dmin = std::numeric_limits<double>::infinity();

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if ((i != j) && (abs(A[i] - A[j]) < dmin)) {
                dmin = abs(A[i] - A[j]);
            }
        }
    }
    return dmin;
}

int MinDistance2(std::vector<int> A, int length) {
    double dmin;
    int temp = 0;
    dmin = std::numeric_limits<double>::infinity();

    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            temp = abs(A[i] - A[j]);
            if (temp < dmin) {
                dmin = temp;
            }
        }
    }
    return dmin;
}


int main() {
    //CONFIG
    int LENGTH_MIN = 1000; //Minimum vector length
    int LENGTH_MAX = 5000; //Maximum vector length
    int AVERAGE_OF = 10; //How many calculations of each length should be created
    int GROWTH_RATE = 500; //GROWTH_RATE 10 = Vector Length 10 & 20 & 30 & ... & LENGTH_MAX
    int VALUE_MAX = INT_MAX; //Array values will generate from 1 to VALUE_MAX

    //Prepare CSV
    ofstream myfile;
    myfile.open ("outputElapsed.csv");
    myfile << "Length (n)" << "," << "dmin1" << "," << "elapsed1" << "," << "dmin2" << "," << "elapsed2" << endl;


    int result1 = 0;
    int result2 = 0;

    int currentLength = LENGTH_MIN;

    while (currentLength <= LENGTH_MAX) {
        for (int i = 0; i <= AVERAGE_OF; i++) {
            //generate a new seed based on time for each array
            auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
            std::mt19937 mt(seed);

            vector<int> a = generateArray(mt, currentLength, VALUE_MAX);


            //start timer
            std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();

            //algorithm
            result1 = MinDistance1(a, currentLength);

            //stop timer
            std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
            int elapsed1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count();

            //start timer
            std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();

            //algorithm
            result2 = MinDistance2(a, currentLength);

            //stop timer
            std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
            int elapsed2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count();

            //output to file
            myfile << currentLength << "," << result1 << "," << elapsed1 << "," << result2 << "," << elapsed2 << endl;
        }

        currentLength += GROWTH_RATE;
    }

    cout << endl << "Successfully exported to outputElapsed.csv" << endl;
    myfile.close();
}
