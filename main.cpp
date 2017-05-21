#include <iostream>
#include <algorithm>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <chrono>

using namespace std;

int counter1;
int counter2;

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

void printValue(string valueName, int value) {
    cout << endl << valueName << value;
}

void printArray(std::vector<int> arr, int length) {
    cout << endl << endl;
    for (int i = 0; i < length; i++) {
        if (i % 20 == 0 ) {
            cout << endl;
        }
        cout << arr[i] << ", ";
    }
}

int MinDistance1(std::vector<int> A) {
    double dmin1;
    int n = (sizeof(A)/sizeof(A[0]));
    dmin1 = std::numeric_limits<double>::infinity();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            counter1 = counter1 + 1;
            if ((i != j) && (abs(A[i] - A[j]) < dmin1)) { //Basic Operation
                dmin1 = abs(A[i] - A[j]);
            }
        }
    }
    printValue("dmin1: ", dmin1);
    printValue("counter1: ", counter1);
    return dmin1;
}

int MinDistance2(std::vector<int> A) {
    double dmin2;
    int n = (sizeof(A)/sizeof(A[0]));
    int temp = 0;

    dmin2 = std::numeric_limits<double>::infinity();
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            temp = abs(A[i] - A[j]);
            counter2 = counter2 + 1;
            if (temp < dmin2) { //Basic Operation
                dmin2 = temp;
            }
        }
    }
    printValue("dmin2: ", dmin2);
    printValue("counter2: ", counter2);
    return dmin2;
}


int main()
{
    //CONFIG
    int LENGTH_MIN = 10; //Minimum vector length
    int LENGTH_MAX = 50; //Maximum vector length
    int GROWTH_RATE = 10; //GROWTH_RATE 10 = Vector Length 10 & 20 & 30 & ... & LENGTH_MAX
    int VALUE_MAX = 1000; //Array values will generate from 1 to VALUE_MAX

    int result1 = 0;
    int result2 = 0;

    //Prepare CSV
    ofstream myfile;
    myfile.open ("outputMain.csv");
    myfile << "Length (n)" << "," << "MinDistance1" << "," << "Min1 BO" << "," << "MinDistance2" << "," << "Min2 BO" << endl;

    int currentLength = LENGTH_MIN;

    while (currentLength < LENGTH_MAX) {
        for (int i = 0; i < currentLength - 1; i++) {
            counter1 = 0;
            counter2 = 0;
            //generate a new seed based on time for each array
            auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
            std::mt19937 mt(seed);

            vector<int> a = generateArray(mt, currentLength, VALUE_MAX);
            printArray(a, currentLength);
            result1 = MinDistance1(a);
            result2 = MinDistance2(a);
            myfile << currentLength << "," << result1 << "," << counter1 << "," << result2 << "," << counter2 << endl;
        }

        currentLength += GROWTH_RATE;
    }
}
