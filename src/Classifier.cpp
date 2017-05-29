#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#ifndef CLASSIFIER
#define CLASSIFIER
using namespace std;

vector< vector < vector< double > > > dataClasses;
int showData(int clas, vector< vector < vector< double > > > & data);
vector < double > operator +(const vector<double> &p1,const vector<double> &p2);
vector < double > operator -(const vector<double> &p1,const vector<double> &p2);
vector < double > operator *(const vector<double> &p1,const vector<double> &p2);
vector < double > operator *(const double &p1,const vector<double> &p2);
vector < double > operator /(const vector<double> &p1,const vector<double> &p2);
vector < double > operator /(const vector<double> &p1,const double &p2);
double scalarProduct(const vector<double> &p1,const vector<double> &p2);
double discriminantKNN(const vector < double > & cases, const vector < double > &trainPoint);
double distance(vector < double > a, vector < double > b);
class Classifier{
private:
    vector < vector < vector <double> > > data;
    vector < vector < vector <double> > > normalData;
    vector < vector < double > > classesGravityPoints;
    vector < vector < double > > normalizeClassesGravityPoints;
    vector< double > omegaValue;
    vector< vector < double > > omegaValues;
    vector<double> omegaValueStandard;
    vector< vector <double> > omegaValuesStandard;
    vector < double > maxMinValues;
    vector < double > gravityPoint(int clas)const;
    void normalizeData();
    int nClasses, nFeatures;
    vector < double > meanValues()const;
    vector < double > desviationValues()const;
    void normalizeDiscriminant(int clas);
    double minDistToSameClassObject(int idObject, int idClass);
    double minDistToOtherClass(int idObject, int idClass);
    void setMaxMinDist();
    pair< vector < double >, int > minDistFromSet(pair < vector < double >, int> element,vector < pair < vector < double >, int> > SET);
    pair< vector < double >, pair <int, int >  >minDistFromSet(pair < vector < double >, pair < int, int> > element,vector < pair < vector < double >, pair<int, int> > > SET);

    int calcNP(int idClass, int idObject);
public:
    Classifier(const vector < vector < vector <double> > > & data);
    void showGravityCenter(int clas)const;
    void showGravityCenterStandard(int clas)const;
    void showWeights(int clas)const;
    void showWeightsStandard(int clas)const;
    int clasifie(vector < double > cases)const;
    double discriminant (vector < double > cases , int clas)const;
    int clasifieKNN(int k, const vector<double> cases)const;
    double overlapRateCalculation()const;
    vector < pair < vector < double >, int > >reduceHart(const char * v);
    vector < pair < vector < double >, int > >reduceHartModification(const char * v);

};


vector < double > operator +(const vector<double> &p1,const vector<double> &p2){
    vector<double> result;
    for(int i = 0; i < p1.size(); i++){
        result.push_back(p1[i]+p2[i]);
    }

    return result;
}

vector < double > operator -(const vector<double> &p1,const vector<double> &p2)
{
    vector<double> result;
    for(int i = 0; i < p1.size(); i++){
        result.push_back(p1[i]-p2[i]);
    }

    return result;
}

//Calcula la multiplicacion termino a termino de dos vectores. Operacion multidimensional.
vector < double > operator *(const vector<double> &p1,const vector<double> &p2){
    vector<double> result;
    for(int i = 0; i < p1.size(); i++){
        result.push_back(p1[i]*p2[i]);
    }

    return result;
}
//Calcula la multiplicacion termino a termino de dos vectores. Operacion multidimensional.
vector < double > operator *(const double &p1,const vector<double> &p2){
    vector<double> result;
    for(int i = 0; i < p2.size(); i++){
        result.push_back(p1*p2[i]);
    }

    return result;
}
//Calcula la division termino a termino de los terminos del primer vector entre los del
vector < double > operator /(const vector<double> &p1,const vector<double> &p2){
    vector<double> result;
    for(int i = 0; i < p1.size(); i++){
        result.push_back(p1[i]/p2[i]);
    }
    return result;
}

vector < double > operator /(const vector<double> &p1,const double &p2){
    vector<double> result;
    for(int i = 0; i < p1.size(); i++){
        result.push_back(p1[i]/p2);
    }

    return result;
}

double scalarProduct(const vector<double> &p1,const vector<double> &p2){
    double result = 0;
    for(int i = 0; i < p1.size(); i++){
        result += p1[i]*p2[i];
    }
    return result;
}

double distance(vector < double > a, vector < double > b){

    vector< double > dist = a-b;

    return sqrt(scalarProduct(dist,dist));
}


vector < double > Classifier::gravityPoint(int clas)const{

    vector < double > meane = data[clas][0];
    for( int i = 1; i < data[clas].size(); i++){
        meane = meane + data[clas][i];
    }
    meane = (1.0/data[clas].size())*meane;
    return meane;
}

void Classifier::normalizeData(){
    vector < double > meane = meanValues(), desv = desviationValues();
    for( int i = 0; i < data.size(); i++){
        for( int j = 0; j < data[i].size(); j++){
            normalData[i][j] = (data[i][j]-meane)/desv;
        }
        this->normalizeClassesGravityPoints[i] = (this->classesGravityPoints[i] - meane)/desv;
        this->omegaValues[i] =2*this->normalizeClassesGravityPoints[i];
        this->omegaValue[i] = -scalarProduct(this->normalizeClassesGravityPoints[i],this->normalizeClassesGravityPoints[i]);
    }
    for(int i= 0; i < data.size(); i++) this->normalizeDiscriminant(i);
}
vector < double > Classifier::meanValues()const{
    vector<double> firstMoment(this->nFeatures);
    int values = 0;
    for( int i = 0; i < data.size(); i++){
        values += data[i].size();
        for( int j = 0; j < data[i].size(); j++){
            firstMoment = firstMoment + data[i][j];
        }
    }
    return firstMoment/(1.0*values);
}

vector < double > Classifier::desviationValues()const{
    vector<double> secondMoment(this->nFeatures);
    int values = 0;
    for( int i = 0; i < data.size(); i++){
        values += data[i].size();
        for( int j = 0; j < data[i].size(); j++){
            secondMoment = secondMoment + data[i][j]*data[i][j];
        }
    }
    secondMoment = secondMoment/(1.0*values);
    vector < double > meanValus = this->meanValues();
    vector < double > meane = meanValus*meanValus;

    vector<double> desviation = secondMoment - meane;
    for(int i = 0; i < desviation.size(); i++){
        desviation[i] = sqrt(desviation[i]);
    }
    return desviation;
}

void Classifier::normalizeDiscriminant(int clas){
    vector < double > desv = this->desviationValues();
    vector < double > mean = this->meanValues();
    this->omegaValuesStandard[clas] = 2*normalizeClassesGravityPoints[clas]/desv;
    this->omegaValueStandard[clas] = -2*scalarProduct(normalizeClassesGravityPoints[clas],mean/desv)-
        scalarProduct(normalizeClassesGravityPoints[clas],normalizeClassesGravityPoints[clas]);
}
double Classifier::discriminant (vector < double > cases , int clas)const{
    return scalarProduct(omegaValuesStandard[clas],cases)+omegaValueStandard[clas];
}


Classifier::Classifier(const vector < vector < vector <double> > > & data){
    this->normalData = this->data = data;
    this->nClasses = this->data.size();
    this->nFeatures = this->data[0][0].size();
    for( int i = 0; i < data.size(); i++){
        vector < double > gPoint = this->gravityPoint(i);
        this->classesGravityPoints.push_back(gPoint);
    }

    this->omegaValue = vector<double>(this->nFeatures);
    this->omegaValues = vector< vector < double > >( this->nClasses);
    this->omegaValueStandard = vector<double>(this->nFeatures);
    this->omegaValuesStandard = vector< vector < double > >(nClasses);
    this->normalizeClassesGravityPoints = vector< vector < double > >(nClasses);
    for(int i = 0; i < nClasses; i++){
        this->omegaValues[i] = vector < double >(this->nFeatures,0);
        this->omegaValuesStandard[i] = vector< double >(this->nFeatures,0);
        this->normalizeClassesGravityPoints[i] = vector< double >(this->data[0][0]);
    }
    this->normalizeData();
    this->setMaxMinDist();

}
void Classifier::showGravityCenter(int clas)const{
    for(int i = 0; i < dataClasses[0][0].size(); i++){
        cout << classesGravityPoints[clas][i] << " ";
    }
    cout << endl;
}
void Classifier::showGravityCenterStandard(int clas)const{
    for(int i = 0; i < dataClasses[0][0].size(); i++){
        cout << normalizeClassesGravityPoints[clas][i] << " ";
    }
    cout << endl;
}
int Classifier::clasifie(vector < double > cases)const{
    int max = 0;
    double maxValue = discriminant(cases,0);
    double value = maxValue;
    for(int i = 1; i < data.size(); i++){
        value = discriminant(cases,i);
        if(maxValue < value){
            max = i;
            maxValue = value;
        }
    }
    return max+1;
}

int showData(int clas, vector< vector < vector< double > > > & data){

    if( clas > data.size()){
        cout << "There is no clas " << clas + 1 << endl;
        return -1;
    }
    for(int i = 0; i < data[clas].size(); i++){
        for(int j = 0; j < data[clas][i].size(); j++){
            cout << data[clas][i][j]<< " ";
        }
        cout << endl;
    }
    return 0;
}
void Classifier::showWeights(int clas)const{
    for(int i = 0; i < this->omegaValuesStandard[clas].size(); i++){
        cout << this->omegaValues[clas][i] << " ";
    }
    cout << endl;
}

void Classifier::showWeightsStandard(int clas)const{
    for(int i = 0; i < this->omegaValuesStandard[clas].size(); i++){
        cout << this->omegaValuesStandard[clas][i] << " ";
    }
    cout << endl;
}

int Classifier::clasifieKNN(int k, const vector<double> cases)const{
    vector < double > casesNormalize = (cases - this->meanValues())/this->desviationValues();
    vector < pair< vector < double >, int > > data;
    for( int i = 0; i < normalData.size(); i++){
        for(int j = 0; j < normalData[i].size(); j++){
            data.push_back(pair< vector < double >, int>(normalData[i][j],i) );
        }
    }
    sort(data.begin(), data.end(),
        [casesNormalize]( pair < vector< double >, int > a, pair < vector<double>, int > b) {
            return discriminantKNN(casesNormalize,a.first) > discriminantKNN(casesNormalize,b.first);
        }
    );
    vector < int > selected(normalData.size(),0);

    for(int i = 0; i < k; i++){
        selected[data[i].second]++;
    }
    int max = 0;
    int maxValue = selected[0];
    for( int i = 1; i < selected.size(); i++){
        if(selected[i] > maxValue){
            max = i;
            maxValue = selected[i];
        }
    }
    return max+1;

}
double discriminantKNN(const vector < double > & cases, const vector < double > &trainPoint){
    return 2*scalarProduct(cases,trainPoint) - scalarProduct(trainPoint,trainPoint);
}

double Classifier::minDistToSameClassObject(int idObject,int idClass){
    double maxDist = distance(normalData[idClass][idObject], normalData[idClass][(idObject+1)%normalData[idClass].size()]);
    double dist;
    for( int i = 0; i < normalData[idClass].size(); i++){
        dist = distance(normalData[idClass][idObject],normalData[idClass][i]);
        if( dist < maxDist and idObject != i){
            maxDist = dist;
        }
    }
    return maxDist;
}
void Classifier::setMaxMinDist(){
    this->maxMinValues = vector < double >(this->normalData.size(),0);
    for( int idClass = 0; idClass < this->normalData.size(); idClass++){
        double dist;
        for(int idObject = 0; idObject < this->normalData[idClass].size();idObject++){
            dist = this->minDistToSameClassObject(idObject,idClass);
            if(dist > this->maxMinValues[idClass]){
                this->maxMinValues[idClass] = dist;
            }
        }
    }
}
double Classifier::overlapRateCalculation()const{
    cout << "Object   class   ";
    for(int i = 0; i < this->normalData.size(); i++){
        cout << "A"<<i+1<< "  ";
    }
    cout << endl;

    vector < bool > overlaped;
    int overlapRate = 0;
    int object = 1;
    for(int i = 0; i < this->normalData.size(); i++){
        for(int j = 0; j < this->normalData[i].size(); j++){
            overlaped = vector < bool > (normalData.size(),false);
            for(int clas = 0; clas < this->normalData.size();clas++){
                for(int idObject = 0; idObject < this->normalData[clas].size() and not overlaped[clas];idObject++){
                    if( distance(normalData[i][j], normalData[clas][idObject]) < this->maxMinValues[clas] or
                        i == clas){
                        overlaped[clas] = true;
                    }
                }
            }
            cout << "  " << object <<"  "<< i+1 << "\t\t";
            int count = 0;
            for(int k = 0; k < normalData.size(); k++){
                if(overlaped[k]){
                    cout << "1 ";
                    count++;
                    if(count == 2){
                        overlapRate++;
                    }
                }
                else{
                    cout << "0 ";
                }
            }
            cout << endl;
            object++;

        }
    }
    cout << "Overlaping Rate: "<< overlapRate*1.0/(object-1) <<endl;
    return overlapRate*1.0/(object-1);
}

pair< vector < double >, int > Classifier::minDistFromSet(pair < vector < double >, int> element,vector < pair < vector < double >, int> > SET){
    int id = 0;
    double minDistance = distance(element.first,SET[0].first);
    double dist;
    for(int i = 0; i < SET.size(); i++){
        dist = distance(element.first, SET[i].first);
        if(dist < minDistance){
            minDistance = dist;
            id = i;
        }
    }
    return SET[id];
}
pair< vector < double >, pair <int, int >  > Classifier::minDistFromSet(pair < vector < double >, pair < int, int> > element,vector < pair < vector < double >, pair<int, int> > > SET){
    int id = 0;
    double minDistance = distance(element.first,SET[0].first);
    double dist;
    for(int i = 0; i < SET.size(); i++){
        dist = distance(element.first, SET[i].first);
        if(dist < minDistance){
            minDistance = dist;
            id = i;
        }
    }
    return SET[id];
}

vector < pair < vector < double >, int > > Classifier::reduceHart(const char * v){
    vector < pair< vector < double >, int > > orderedData;
    for( int i = 0; i < normalData.size(); i++){
        for(int j = 0; j < normalData[i].size(); j++){
            orderedData.push_back(pair< vector < double >, int>(normalData[i][j],i) );
        }
    }
    vector < double > zero(orderedData[0].first.size(),0);
    sort(orderedData.begin(), orderedData.end(),
        [zero]( pair < vector< double >, int > a, pair < vector<double>, int > b) {
            return distance(zero,a.first) < distance(zero,b.first);
        }
    );

    vector < pair < vector < double >, int> > SET;
    SET.push_back(orderedData[0]);

    bool adding = true;
    int iterations = 1;

    ofstream out(v);

    while( adding){
        adding = false;
        vector < pair < vector < double >, int> >::iterator iter;

        for( iter = orderedData.begin(); iter != orderedData.end(); ++iter){
            pair < vector < double >, int > p = this->minDistFromSet(*iter,SET);
            if(p.second != (*iter).second){
                SET.push_back(*iter);
                orderedData.erase(iter);
                adding = true;
            }
        }
        out << "Set size after "<< iterations <<" iterations: " << SET.size()<< endl;
        iterations++;

    }
    return SET;

}

double Classifier::minDistToOtherClass(int idObject, int idClass){
    double dist = numeric_limits<double>::max();
    for(int clas = 0; clas < normalData.size(); ++clas){
        if(idClass != clas){

            for(int object = 0; object < normalData[clas].size(); object++){
                double newDist = distance(normalData[clas][object],normalData[idClass][idObject]);
                if(newDist < dist){
                    dist = newDist;
                }
            }
        }
    }
    return dist;
}

int Classifier::calcNP(int idClass, int idObject){
    double distanceToClass = this->minDistToOtherClass(idObject, idClass);
    int np = 0;

    for(int j = 0; j < normalData[idClass].size(); j++){
        if( distance(normalData[idClass][j],normalData[idClass][idObject]) < distanceToClass){
            np++;
        }
    }

    return np;
}
vector < pair < vector < double >, int > > Classifier::reduceHartModification(const char * v){
    vector < pair< vector < double >, pair < int, int > > > orderedData;
    for( int i = 0; i < normalData.size(); i++){
        for(int j = 0; j < normalData[i].size(); j++){
            orderedData.push_back(pair< vector < double >, pair <int, int> >(normalData[i][j],pair<int,int>(i,this->calcNP(i,j)) ));
        }
    }
    sort(orderedData.begin(), orderedData.end(),
        []( const pair < vector< double >, pair < int, int > > &a, const pair < vector<double>, pair < int, int > > &b) {
            return a.second.second < b.second.second;
        }
    );

    vector < pair < vector < double >, pair < int , int > > > SET;
    SET.push_back(orderedData[0]);

    bool adding = true;
    int iterations = 1;

    ofstream out(v);

    while( adding){
        adding = false;
        vector < pair < vector < double >, pair < int, int> > >::iterator iter;

        for( iter = orderedData.begin(); iter != orderedData.end(); ++iter){
            pair < vector < double >, pair < int ,int > > p(this->minDistFromSet(*iter,SET));
            if(p.second.first != (*iter).second.first){
                SET.push_back(*iter);
                orderedData.erase(iter);
                adding = true;
            }
        }
        out << "Set size after "<< iterations <<" iterations: " << SET.size()<< endl;
        iterations++;

    }
    vector < pair < vector < double >, int > > realSet;
    vector < pair < vector <double >, pair < int, int > > >::iterator iter;
    for(iter = SET.begin(); iter != SET.end(); ++iter){
        pair < vector < double >, int > realObject((*iter).first,(*iter).second.first);
        realSet.push_back(realObject);
    }
    return realSet;
}


#endif
