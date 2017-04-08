#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Classifier.cpp"

using namespace std;

// This function returns the minimum distance from one object of the set to other object from the
// same set.

int main(int argc, char const *argv[]) {
    if(argc < 4){
        cout << "It needs a Train set, a name for the Output set and a name for a Information."<<endl;
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

    ofstream outSet(argv[2]);


    Classifier cl(dataClasses);

    vector < pair < vector < double >, int > > finalSet = cl.reduceHartModification(argv[3]);
    outSet << classes << " " << features  << " "<< finalSet.size() << endl;
    for( int i = 0; i < finalSet.size(); i++){
        outSet << finalSet[i].second << " ";
        for( int j = 0; j < finalSet[i].first.size(); j++){
            outSet << finalSet[i].first[j]<< " ";
        }
        outSet << endl;
    }






    return 0;

}
