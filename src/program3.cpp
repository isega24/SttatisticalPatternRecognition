#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Classifier.cpp"

using namespace std;

// This function returns the minimum distance from one object of the set to other object from the
// same set.

int main(int argc, char const *argv[]) {
    if(argc < 2){
        cout << "It needs at least the Train set"<<endl;
        exit(-1);
    }

    string FileName = argv[1];

    ifstream trF(FileName);
    if( !trF  ) {
        cerr << "\nCan't open file " << FileName << endl;
        exit( -1 );
    }
    int classes, features, cases;
    trF >> classes >> features >> cases;

    vector < vector < double > > data(cases);
    vector < int > dataClass(cases);

    dataClasses = vector < vector < vector < double > > >(classes);

    double input ;
    int clas;
    for( int i = 0; i < cases; i++){
        vector<double> v;
        trF >> clas;
        dataClass[i] = clas;
        for(int j = 0; j < features; j++){
            trF >> input;
            v.push_back(input);
        }
        data[i] = v;

        dataClasses[clas-1].push_back(v);
    }
    trF.close();

    // Time to Train.

    Classifier cl(dataClasses);


    cl.overlapRateCalculation();






    return 0;

}
