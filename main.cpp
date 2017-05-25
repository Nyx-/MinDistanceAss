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
    if (length == 0) {
        cout << endl << "EMPTY ARRAY";
    }

    for (int i = 0; i < length; i++) {
        if (i % 20 == 0 ) {
            cout << endl;
        }
        cout << arr[i] << " ";
    }
    cout << endl;
}

int MinDistance1(std::vector<int> A, int length) {
    double dmin;
    dmin = std::numeric_limits<double>::infinity();

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            counter1 = counter1 + 1;
            if ((i != j) && (abs(A[i] - A[j]) < dmin)) { //Basic Operation
                dmin = abs(A[i] - A[j]);
            }
        }
    }
//    printValue("     dmin1: ", dmin);
//    printValue("  counter1: ", counter1);
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
                dmin = temp;
            }
        }
    }
//    printValue("     dmin2: ", dmin);
//    printValue("  counter2: ", counter2);
    return dmin;
}

void testArray(string testName, std::vector<int> testVector, string expectedValue) {
    cout << endl << "Test Name: " <<  testName;
    printArray(testVector, testVector.size());
    cout << endl << "Expected Value: " << expectedValue;
    printValue("dmin1: ", MinDistance1(testVector, testVector.size()));
    printValue("dmin2: ", MinDistance2(testVector, testVector.size()));
    cout << endl;
}

void testMinDistance() {
    int length = 10;

    vector<int> a = { }; //INFINITY AKA INT_MAX
    vector<int> b = { 1 }; //INFINITY AKA INT_MAX
    vector<int> c = { 1, 8, 17, 23, 36, 49, 60, 77, 85, 94 }; //6
    vector<int> d = { 86, 12, 60, 46, 26, 38, 10, 5, 82, 95 }; //2
    vector<int> e = { 12, 12, 12, 12, 16, 19, 19, 19, 34, 36 }; //0
    vector<int> f = { -17, -90, -7, -42, -4, -58, -50, -33, -46, -100 }; //3
    vector<int> g = { -69, 56, 98, 65, -30, 47, 93, -21, -40, 71 }; //5
    vector<int> h = { 2, -2, 9, -9, 39, -39, 94, -94, 44, -44 }; //4

    cout << endl << "-----------------------Start Tests------------------------";

    testArray("Empty", a, "Infinity");
    testArray("Single Item", b, "Infinity");
    testArray("Sorted", c, "6");
    testArray("Random", d, "2");
    testArray("Duplicates", e, "0");
    testArray("Negative Only", f, "3");
    testArray("Negative & Positive", g, "5");
    testArray("Negative & Positive Duplicates", h, "4");

    cout << endl << "------------------------End Tests-------------------------";
    cout << endl << endl;
}

int main()
{
    //CONFIG
    int LENGTH_MIN = 10; //Minimum vector length
    int LENGTH_MAX = 50; //Maximum vector length
    int AVERAGE_OF = 20; //AVERAGE_OF
    int GROWTH_RATE = 10; //GROWTH_RATE 10 = Vector Length 10 & 20 & 30 & ... & LENGTH_MAX
    int VALUE_MAX = 10000; //Array values will generate from 1 to VALUE_MAX

    //Prepare CSV
    ofstream myfile;
    myfile.open ("outputMain.csv");
    myfile << "Length (n)" << "," << "dmin1" << "," << "Min1 BO" << "," << "dmin2" << "," << "Min2 BO" << endl;

    testMinDistance();

    int result1 = 0;
    int result2 = 0;

    int currentLength = LENGTH_MIN;

    while (currentLength <= LENGTH_MAX) {
        for (int i = 0; i <= AVERAGE_OF; i++) {
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

    cout << endl << "Successfully exported to output.csv" << endl;
    myfile.close();
}
