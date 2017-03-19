#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#ifndef CLASSIFIER
#define CLASSIFIER
using namespace std;

// Assume that possition 0 is empty.
vector< vector < vector< double > > > dataClasses;

int showData(int clas, vector< vector < vector< double > > > & data);

// Calcula la suma termino a termino de dos vectores. Operacion multidimensional.
vector < double > operator +(const vector<double> &p1,const vector<double> &p2);

// Calcula la diferencia de dos vectores termino a termino. Operacion multidimensional.
vector < double > operator -(const vector<double> &p1,const vector<double> &p2);

//Calcula la multiplicacion termino a termino de dos vectores. Operacion multidimensional.
vector < double > operator *(const vector<double> &p1,const vector<double> &p2);
//Calcula la multiplicacion termino a termino de dos vectores. Operacion multidimensional.
vector < double > operator *(const double &p1,const vector<double> &p2);
//Calcula la division termino a termino de los terminos del primer vector entre los del
// segundo. Operacion multidimensional.
vector < double > operator /(const vector<double> &p1,const vector<double> &p2);

vector < double > operator /(const vector<double> &p1,const double &p2);

// Calcula el resultado de dividir un vector entre una constante. Operacion multidimensional.
vector < double > norma(const vector<double> &p1,const double &p2);

// Calcula la norma de un vector. Salida unidimensional.
double scalarProduct(const vector<double> &p1,const vector<double> &p2);

class Classifier{
private:
    vector < vector < vector <double> > > data;
    vector < vector < vector <double> > > normalData;

    vector < vector < double > > classesGravityPoints;
    vector < vector < double > > normalizeClassesGravityPoints;

    vector<double> omegaValue;
    vector< vector <double> > omegaValues;

    // Centro de gravedad de la clase. Se utiliza para clasificar
    vector < double > gravityPoint(int clas);
    // Normalizamos los datos y los centros de gravedad. Se utiliza meanValue y desviationValue.
    void normalizeData();
    // La media de cada feature. Se utiliza para normalizar.
    vector < double > meanValue();

    // La desviacion tipica de cada feature. Se utiliza para normalizar.
    vector < double > desviationValue();

    // Funcion para crear la funcion discriminante con los valores ya calculados.
    void normalizeDiscriminant(int clas);


public:

    // Constructor de clase. Inicializa los clasificadores y los estandariza.
    Classifier(vector < vector < vector <double> > > & data);
    void showGravityCenter(int clas);
    void showGravityCenterStandard(int clas);
    void showWeightsStandard(int clas);
    int clasifie(vector < double > cases);
    // Funcion discriminante. La clase que maximice esta funcion, es la mas cercana.
    double discriminant (vector < double > cases , int clas);

};


vector < double > operator +(const vector<double> &p1,const vector<double> &p2){
    vector<double> result;
    for(int i = 0; i < p1.size(); i++){
        result.push_back(p1[i]+p2[i]);
    }

    return result;
}

// Calcula la diferencia de dos vectores termino a termino. Operacion multidimensional.
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
// segundo. Operacion multidimensional.
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

// Calcula el resultado de dividir un vector entre una constante. Operacion multidimensional.
vector < double > norma(const vector<double> &p1,const double &p2){
    vector<double> result;
    for(int i = 0; i < p1.size(); i++){
        result.push_back(p1[i]/p2);
    }

    return result;
}

// Calcula la norma de un vector. Salida unidimensional.
double scalarProduct(const vector<double> &p1,const vector<double> &p2){
    double result = 0;
    for(int i = 0; i < p1.size(); i++){
        result += p1[i]*p2[i];
    }
    return result;
}


vector < double > Classifier::gravityPoint(int clas){

    vector < double > meane = data[clas][0];
    for( int i = 1; i < data[clas].size(); i++){
        meane = meane + data[clas][i];
    }
    meane = (1.0/data[clas].size())*meane;
    return meane;
}

void Classifier::normalizeData(){
    vector < double > meane = meanValue(), desv = desviationValue();
    for( int i = 0; i < data.size(); i++){
        for( int j = 0; j < data[i].size(); j++){
            normalData[i][j] = (data[i][j]-meane)/desv;
        }

        this->normalizeClassesGravityPoints[i] = (this->classesGravityPoints[i] - meane)/desv;
    }
}
vector < double > Classifier::meanValue(){
    vector<double> firstMoment(this->data[0][0].size());
    int values = 0;
    for( int i = 0; i < data.size(); i++){
        values += data[i].size();
        for( int j = 0; j < data[i].size(); j++){
            firstMoment = firstMoment + data[i][j];
        }
    }
    return firstMoment/(1.0*values);
}

vector < double > Classifier::desviationValue(){
    vector<double> secondMoment(this->data[0][0].size());
    int values = 0;
    for( int i = 0; i < data.size(); i++){
        values += data[i].size();
        for( int j = 0; j < data[i].size(); j++){
            secondMoment = secondMoment + data[i][j]*data[i][j];
        }
    }
    secondMoment = secondMoment/(1.0*values);
    vector < double > meane = this->meanValue()*this->meanValue();

    vector<double> desviation = secondMoment - meane;
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
    vector < double > desv = this->desviationValue();
    vector < double > mean = this->meanValue();
    this->omegaValues[clas] = 2*normalizeClassesGravityPoints[clas]/desv;
    this->omegaValue[clas] = -2*scalarProduct(normalizeClassesGravityPoints[clas],mean/desv)-
        scalarProduct(normalizeClassesGravityPoints[clas],normalizeClassesGravityPoints[clas]);
}
// Funcion discriminante. La clase que maximice esta funcion, es la mas cercana.
double Classifier::discriminant (vector < double > cases , int clas){
    return 2*scalarProduct(omegaValues[clas],cases)+omegaValue[clas];
}


Classifier::Classifier(vector < vector < vector <double> > > & data){
    this->data = data;
    this->normalData = this->data;
    for( int i = 0; i < data.size(); i++){
        classesGravityPoints.push_back(gravityPoint(i));
    }

    this->omegaValue = vector<double>(this->data[0][0].size());
    this->omegaValues = vector< vector < double > >(this->data.size());
    this->normalizeClassesGravityPoints = vector< vector < double > >(this->data.size());
    for(int i = 0; i < this->data.size(); i++){
        this->omegaValues[i] = vector< double >(this->data[0][0].size());
        this->normalizeClassesGravityPoints[i] = vector< double >(this->data[0][0]);
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
int Classifier::clasifie(vector < double > cases){
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
void Classifier::showWeightsStandard(int clas){
    for(int i = 0; i < this->omegaValues[clas].size(); i++){
        cout << this->omegaValues[clas][i] << " ";
    }
    cout << endl;
}




#endif
