#include <iostream>
#include <math.h>
#include <stdlib.h>


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

int MinDistance1() {
    int A[] = {1,21,6,12,9,3};
    //double dmin;
    int dmin;
    int n = (sizeof(A)/sizeof(A[0]));

    dmin = INFINITY;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i != j) && (abs(A[i] - A[j]) < dmin)) { //Basic Operation
                dmin = abs(A[i] - A[j]);
            }
        }
    }
    return dmin;
}

int MinDistance2() {
    int A[] = {1,21,6,12,9,3};
    //double dmin;
    int dmin;
    int n = (sizeof(A)/sizeof(A[0]));
    int temp = 0;

    dmin = INFINITY;
    //dmin = INT_MAX;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            temp = abs(A[i] - A[j]);
            if (temp < dmin) { //Basic Operation
                dmin = temp;
            }
        }
    }
    return dmin;
}


int main()
{
    //CONFIG
    int PERMUTATIONS = 1; //Unique permutations of randomly filled arrays.
    int GROWTH_RATE = 1; //How many times the INCREMENT_AMOUNT will be added together to form new lengths of arrays
    int LENGTH = 20; //Vector length, as well as degree that array length will grow with GROWTH_RATE
    int VALUE_MAX = 1000000; //Array values will generate from 1 to VALUE_MAX
    int MT_SEED = 100; //Mersenne Twister engine seed

    //Prepare CSV
    ofstream myfile;
    myfile.open ("outputMain.csv");
    myfile << "Length (n)" << "," << "Basic Operations" << "," << "Theoretical Average Efficiency" << endl;

    //set seed
    std::mt19937 mt(MT_SEED);

    //Comment this to skip tests
//    testImplementationValidity();
//    cout << endl << "****************************************" << endl;




}
