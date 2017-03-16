#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector< vector < vector< double > > > dataClasses;

void showData(int clas){
    for(int i = 0; i < dataClasses[clas].size(); i++){
        for(int j = 0; j < dataClasses[clas][i].size(); j++){
            cout << dataClasses[clas][i][j]<< " ";
        }
        cout << endl;
    }
}

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

    for(int i = 0; i < classes; i++ ){
        vector < vector < double > > v = vector< vector < double > >();
        dataClasses.push_back(v);
    }
    double input ;
    int clas;
    for( int i = 0; i < cases; i++){
        vector<double> v = vector<double>();
        trF >> clas;
        cout <<"\n" << clas << "? "<<i << endl;
        dataClasses[clas].push_back(v);
        for(int j = 0; j < features; j++){
            trF >> input;
            cout << j << " " << input;

            dataClasses[clas][i].push_back(input);

            cout << dataClasses[clas][i][j];
        }
    }

    showData(0);
    trF.close();

    // Time to Train.


    //showData();


    return 0;
}
