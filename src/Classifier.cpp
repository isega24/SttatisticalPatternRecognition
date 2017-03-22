#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#ifndef CLASSIFIER
#define CLASSIFIER
using namespace std;

// Assume that possition 0 is empty.
vector< vector < vector< float > > > dataClasses;

int showData(int clas, vector< vector < vector< float > > > & data);

// Calcula la suma termino a termino de dos vectores. Operacion multidimensional.
vector < float > operator +(const vector<float> &p1,const vector<float> &p2);

// Calcula la diferencia de dos vectores termino a termino. Operacion multidimensional.
vector < float > operator -(const vector<float> &p1,const vector<float> &p2);

//Calcula la multiplicacion termino a termino de dos vectores. Operacion multidimensional.
vector < float > operator *(const vector<float> &p1,const vector<float> &p2);
//Calcula la multiplicacion termino a termino de dos vectores. Operacion multidimensional.
vector < float > operator *(const float &p1,const vector<float> &p2);
//Calcula la division termino a termino de los terminos del primer vector entre los del
// segundo. Operacion multidimensional.
vector < float > operator /(const vector<float> &p1,const vector<float> &p2);

vector < float > operator /(const vector<float> &p1,const float &p2);

// Calcula el resultado de dividir un vector entre una constante. Operacion multidimensional.
vector < float > norma(const vector<float> &p1,const float &p2);

// Calcula la norma de un vector. Salida unidimensional.
float scalarProduct(const vector<float> &p1,const vector<float> &p2);

class Classifier{
private:
    vector < vector < vector <float> > > data;
    vector < vector < vector <float> > > normalData;

    vector < vector < float > > classesGravityPoints;
    vector < vector < float > > normalizeClassesGravityPoints;

    vector< float > omegaValue;
    vector< vector < float > > omegaValues;
    vector<float> omegaValueStandard;
    vector< vector <float> > omegaValuesStandard;

    // Centro de gravedad de la clase. Se utiliza para clasificar
    vector < float > gravityPoint(int clas);
    // Normalizamos los datos y los centros de gravedad. Se utiliza meanValue y desviationValue.
    void normalizeData();
    // La media de cada feature. Se utiliza para normalizar.
    vector < float > meanValue();

    // La desviacion tipica de cada feature. Se utiliza para normalizar.
    vector < float > desviationValue();

    // Funcion para crear la funcion discriminante con los valores ya calculados.
    void normalizeDiscriminant(int clas);


public:

    // Constructor de clase. Inicializa los clasificadores y los estandariza.
    Classifier(vector < vector < vector <float> > > & data);
    void showGravityCenter(int clas);
    void showGravityCenterStandard(int clas);
    void showWeights(int clas);
    void showWeightsStandard(int clas);
    int clasifie(vector < float > cases);
    // Funcion discriminante. La clase que maximice esta funcion, es la mas cercana.
    float discriminant (vector < float > cases , int clas);

};


vector < float > operator +(const vector<float> &p1,const vector<float> &p2){
    vector<float> result;
    for(int i = 0; i < p1.size(); i++){
        result.push_back(p1[i]+p2[i]);
    }

    return result;
}

// Calcula la diferencia de dos vectores termino a termino. Operacion multidimensional.
vector < float > operator -(const vector<float> &p1,const vector<float> &p2)
{
    vector<float> result;
    for(int i = 0; i < p1.size(); i++){
        result.push_back(p1[i]-p2[i]);
    }

    return result;
}

//Calcula la multiplicacion termino a termino de dos vectores. Operacion multidimensional.
vector < float > operator *(const vector<float> &p1,const vector<float> &p2){
    vector<float> result;
    for(int i = 0; i < p1.size(); i++){
        result.push_back(p1[i]*p2[i]);
    }

    return result;
}
//Calcula la multiplicacion termino a termino de dos vectores. Operacion multidimensional.
vector < float > operator *(const float &p1,const vector<float> &p2){
    vector<float> result;
    for(int i = 0; i < p2.size(); i++){
        result.push_back(p1*p2[i]);
    }

    return result;
}
//Calcula la division termino a termino de los terminos del primer vector entre los del
// segundo. Operacion multidimensional.
vector < float > operator /(const vector<float> &p1,const vector<float> &p2){
    vector<float> result;
    for(int i = 0; i < p1.size(); i++){
        result.push_back(p1[i]/p2[i]);
    }
    return result;
}

vector < float > operator /(const vector<float> &p1,const float &p2){
    vector<float> result;
    for(int i = 0; i < p1.size(); i++){
        result.push_back(p1[i]/p2);
    }

    return result;
}

// Calcula el resultado de dividir un vector entre una constante. Operacion multidimensional.
vector < float > norma(const vector<float> &p1,const float &p2){
    vector<float> result;
    for(int i = 0; i < p1.size(); i++){
        result.push_back(p1[i]/p2);
    }

    return result;
}

// Calcula la norma de un vector. Salida unidimensional.
float scalarProduct(const vector<float> &p1,const vector<float> &p2){
    float result = 0;
    for(int i = 0; i < p1.size(); i++){
        result += p1[i]*p2[i];
    }
    return result;
}


vector < float > Classifier::gravityPoint(int clas){

    vector < float > meane = data[clas][0];
    for( int i = 1; i < data[clas].size(); i++){
        meane = meane + data[clas][i];
    }
    meane = (1.0/data[clas].size())*meane;
    return meane;
}

void Classifier::normalizeData(){
    vector < float > meane = meanValue(), desv = desviationValue();
    for( int i = 0; i < data.size(); i++){
        for( int j = 0; j < data[i].size(); j++){
            normalData[i][j] = (data[i][j]-meane)/desv;
        }
        this->normalizeClassesGravityPoints[i] = (this->classesGravityPoints[i] - meane)/desv;
        this->omegaValues[i] =2*this->normalizeClassesGravityPoints[i];
        this->omegaValue[i] = -scalarProduct(this->normalizeClassesGravityPoints[i],this->normalizeClassesGravityPoints[i]);
    }
}
vector < float > Classifier::meanValue(){
    vector<float> firstMoment(this->data[0][0].size());
    int values = 0;
    for( int i = 0; i < data.size(); i++){
        values += data[i].size();
        for( int j = 0; j < data[i].size(); j++){
            firstMoment = firstMoment + data[i][j];
        }
    }
    return firstMoment/(1.0*values);
}

vector < float > Classifier::desviationValue(){
    vector<float> secondMoment(this->data[0][0].size());
    int values = 0;
    for( int i = 0; i < data.size(); i++){
        values += data[i].size();
        for( int j = 0; j < data[i].size(); j++){
            secondMoment = secondMoment + data[i][j]*data[i][j];
        }
    }
    secondMoment = secondMoment/(1.0*values);
    vector < float > meane = this->meanValue()*this->meanValue();

    vector<float> desviation = secondMoment - meane;
    for(int i = 0; i < desviation.size(); i++){
        if(desviation[i] < 0){
            desviation[i] = 0;
        }
        else{
            desviation[i] = sqrt(desviation[i]);
        }
    }
    return desviation;
}

// Funcion para crear la funcion discriminante con los valores ya calculados.
void Classifier::normalizeDiscriminant(int clas){
    vector < float > desv = this->desviationValue();
    vector < float > mean = this->meanValue();
    this->omegaValuesStandard[clas] = 2*normalizeClassesGravityPoints[clas]/desv;
    this->omegaValueStandard[clas] = -2*scalarProduct(normalizeClassesGravityPoints[clas],mean/desv)-
        scalarProduct(normalizeClassesGravityPoints[clas],normalizeClassesGravityPoints[clas]);
}
// Funcion discriminante. La clase que maximice esta funcion, es la mas cercana.
float Classifier::discriminant (vector < float > cases , int clas){
    return scalarProduct(omegaValuesStandard[clas],cases)+omegaValueStandard[clas];
}


Classifier::Classifier(vector < vector < vector <float> > > & data){
    this->data = data;
    this->normalData = this->data;
    for( int i = 0; i < data.size(); i++){
        vector < float > gPoint = this->gravityPoint(i);
        this->classesGravityPoints.push_back(gPoint);
    }

    this->omegaValue = vector<float>(this->data[0][0].size());
    this->omegaValues = vector< vector < float > >( this->data[0][0].size());
    this->omegaValueStandard = vector<float>(this->data[0][0].size());
    this->omegaValuesStandard = vector< vector < float > >(this->data.size());
    this->normalizeClassesGravityPoints = vector< vector < float > >(this->data.size());
    for(int i = 0; i < this->data.size(); i++){
        this->omegaValues[i] = vector < float >(this->data[0][0].size());
        this->omegaValuesStandard[i] = vector< float >(this->data[0][0].size());
        this->normalizeClassesGravityPoints[i] = vector< float >(this->data[0][0]);
    }
    this->normalizeData();
    for(int i= 0; i < data.size(); i++) this->normalizeDiscriminant(i);

}
void Classifier::showGravityCenter(int clas){
    for(int i = 0; i < dataClasses[0][0].size(); i++){
        cout << classesGravityPoints[clas][i] << " ";
    }
    cout << endl;
}
void Classifier::showGravityCenterStandard(int clas){
    for(int i = 0; i < dataClasses[0][0].size(); i++){
        cout << normalizeClassesGravityPoints[clas][i] << " ";
    }
    cout << endl;
}
int Classifier::clasifie(vector < float > cases){
    int max = 0;
    float maxValue = discriminant(cases,0);
    float value = maxValue;
    for(int i = 1; i < data.size(); i++){
        value = discriminant(cases,i);
        if(maxValue < value){
            max = i;
            maxValue = value;
        }
    }
    return max+1;
}

int showData(int clas, vector< vector < vector< float > > > & data){

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
void Classifier::showWeights(int clas){
    for(int i = 0; i < this->omegaValuesStandard[clas].size(); i++){
        cout << this->omegaValues[clas][i] << " ";
    }
    cout << endl;
}

void Classifier::showWeightsStandard(int clas){
    for(int i = 0; i < this->omegaValuesStandard[clas].size(); i++){
        cout << this->omegaValuesStandard[clas][i] << " ";
    }
    cout << endl;
}




#endif
