#include <iostream>
#include <algorithm>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <chrono>

using namespace std;

int counter1 = 0;
int counter2 = 0;

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

int MinDistance1(std::vector<int> A, int length) {
    double dmin;
    dmin = std::numeric_limits<double>::infinity();

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            counter1 = counter1 + 1;
            if ((i != j) && (abs(A[i] - A[j]) < dmin)) { //Basic Operation
//                counter1 = counter1 + 1;
                dmin = abs(A[i] - A[j]);
            }
        }
    }
    printValue("     dmin1: ", dmin);
    printValue("  counter1: ", counter1);
    return dmin;
}

int MinDistance2(std::vector<int> A, int length) {
    double dmin;
    int temp = 0;
    dmin = std::numeric_limits<double>::infinity();

    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            temp = abs(A[i] - A[j]);
            counter2 = counter2 + 1;
            if (temp < dmin) { //Basic Operation
//                counter2 = counter2 + 1;
                dmin = temp;
            }
        }
    }
    printValue("     dmin2: ", dmin);
    printValue("  counter2: ", counter2);
    return dmin;
}


int main()
{
    //CONFIG
    int LENGTH_MIN = 10; //Minimum vector length
    int LENGTH_MAX = 100; //Maximum vector length
    int GROWTH_RATE = 10; //GROWTH_RATE 10 = Vector Length 10 & 20 & 30 & ... & LENGTH_MAX
    int VALUE_MAX = 100000; //Array values will generate from 1 to VALUE_MAX

    //Prepare CSV
    ofstream myfile;
    myfile.open ("outputMain.csv");
    myfile << "Length (n)" << "," << "dmin1" << "," << "Min1 BO" << "," << "dmin2" << "," << "Min2 BO" << endl;


    int result1 = 0;
    int result2 = 0;

    int currentLength = LENGTH_MIN;

    while (currentLength < LENGTH_MAX) {
        for (int i = 0; i < currentLength - 1; i++) {
            //generate a new seed based on time for each array
            auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
            std::mt19937 mt(seed);

            vector<int> a = generateArray(mt, currentLength, VALUE_MAX);
            printArray(a, currentLength);
            result1 = MinDistance1(a, currentLength);
            result2 = MinDistance2(a, currentLength);

            myfile << currentLength << "," << result1 << "," << counter1 << "," << result2 << "," << counter2 << endl;
            counter1 = 0;
            counter2 = 0;
        }

        currentLength += GROWTH_RATE;
    }
}
