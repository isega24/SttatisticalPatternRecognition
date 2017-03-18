#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Classifier.cpp"

using namespace std;

int main(int argc, char const *argv[]) {

    string FileName = argv[1];

    ifstream trF(FileName);
    if( !trF  ) {
        cerr << "\nCan't open file " << FileName << endl;
        exit( -1 );
    }
    int classes, features, cases;
    trF >> classes >> features >> cases;

    cout << "\nNumber of classes: " << classes << "\nNumber of features: "<< features << "\nNumber of cases: "<<cases << endl;

    dataClasses = vector < vector < vector < double > > >(classes);

    double input ;
    int clas;
    for( int i = 0; i < cases; i++){
        vector<double> v;
        trF >> clas;

        for(int j = 0; j < features; j++){
            trF >> input;
            v.push_back(input);
        }

        dataClasses[clas-1].push_back(v);
    }
    trF.close();

    // Time to Train.
    
    Classifier cl(dataClasses);

    cout << "Gravity points of the classes without Standarization:"<<endl<< endl;
    for(int i = 0; i < classes; i++){
        cl.showGravityCenter(i);
    }
    cout << "\n\nGravity points with standarization:"<< endl <<endl;
    for(int i = 0; i < classes; i++){
        cl.showGravityCenterStandard(i);
    }





    return 0;
}
