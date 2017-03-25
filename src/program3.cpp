#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Classifier.cpp"

using namespace std;

// This function returns the minimum distance from one object of the set to other object from the
// same set.

double minDistToSameClassObject(int idObject,vector < vector < double > > & set){
    double minDist = distance(set[idObject], set[(idObject+1)%set.size()]);
    double dist;
    for( int i = 0; i < set.size(); i++){
        dist = distance(set[idObject],set[i]);
        if( dist < minDist and idObject != i){
            minDist = dist;
        }
    }
    return minDist;
}



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

    // Classifier cl(dataClasses);

    // OverLaping set calculation.
    vector < double > minDistance(classes,0);
    for( int i = 0; i < classes; i++){
        // For each class:
        minDistance[i] = minDistToSameClassObject(0,dataClasses[i]);
        double dist = minDistance[i];
        for(int j = 0; j < dataClasses[i].size();j++){
            dist = minDistToSameClassObject(j,dataClasses[i]);
            if(dist > minDistance[i]){
                minDistance[i] = dist;
            }

        }
    }

    // Sets of overlapping calculated. Point a is in the class i if:
    //                          distance(a,'anypoint from class i') < minDistance[i]

    cout << "Object   class   ";
    for(int i = 0; i < dataClasses.size(); i++){
        cout << "A"<<i+1<< "  ";
    }
    cout << endl;
    for(int i = 0; i < data.size(); i++){

        vector < bool > overlaped(dataClasses.size(),false);
        for( int j = 0; j < dataClasses.size() ; j++){
            for( int k = 0; k < dataClasses[j].size() and not overlaped[j] ;k++){
                if(distance(data[i], dataClasses[j][k])< minDistance[j] or dataClass[i] == j){
                    overlaped[j] = true;
                }
            }
        }
        cout << "  " << i+1 << "  "<< dataClass[i] << "\t\t";
        for(int j = 0; j < dataClasses.size(); j++){
            if(overlaped[j]){
                cout << "1 ";
            }
            else{
                cout << "0 ";
            }
        }
        cout << endl;

    }





    return 0;

}
