#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Classifier.cpp"

using namespace std;

int main(int argc, char const *argv[]) {
    if(argc < 1){
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

    cout << "Gravity points of the classes without Standarization:"<< endl;
    for(int i = 0; i < classes; i++){
        cl.showGravityCenter(i);
    }
    cout << "\n\nGravity points with standarization:"<< endl <<endl;
    for(int i = 0; i < classes; i++){
        cl.showGravityCenterStandard(i);
    }
    cout << "\n\nStandard weights: "<<endl;
    for( int i = 0; i < dataClasses.size(); i++){
        cl.showWeightsStandard(i);
    }
    if(argc < 2){
        cout << "There is not a Testing set"<<endl;
        exit(-1);
    }

    FileName = argv[2];
    ifstream testF(FileName);
    if( !testF    ) {
        cerr << "\nCan't open file " << FileName << endl;
        exit( -1 );
    }
    testF    >> classes >> features >> cases;

    vector < vector < double > > trainSet;

    for( int i = 0; i < cases; i++){
        vector<double> v;

        for(int j = 0; j <= features; j++){
            testF    >> input;
            v.push_back(input);
        }

        trainSet.push_back(v);
    }
    testF.close();


    cout << "Results of test:"<<endl;
    cout << "Obj nr:    True Class      assigned Class"<<endl;
    int fails = 0;
    for(int i = 0; i < trainSet.size(); i++){
        int clasified = cl.clasifie(vector<double>(++trainSet[i].begin(), trainSet[i].end()));
        cout << i+1 << "\t\t" << trainSet[i][0] << "\t\t"<< clasified <<endl;
        if(clasified != trainSet[i][0]){
            fails++;
        }
    }
    cout << "Error rate = " << 100*fails*1.0/trainSet.size() <<"%"<<endl;






    return 0;
}
