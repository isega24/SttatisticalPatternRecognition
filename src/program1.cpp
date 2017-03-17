#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


// Assume that possition 0 is empty.
vector< vector < vector< double > > > dataClasses;

// Calcula la suma termino a termino de dos vectores. Operacion multidimensional.
vector < double > operator +(const vector<double> &p1,const vector<double> &p2){
    vector<double> result(dataClasses[0][0].size());
    for(int i = 0; i < p1.size(); i++){
        result.push_back(p1[i]+p2[i]);
    }

    return result;
}

// Calcula la diferencia de dos vectores termino a termino. Operacion multidimensional.
vector < double > operator -(const vector<double> &p1,const vector<double> &p2)
{
    vector<double> result(dataClasses[0][0].size());
    for(int i = 0; i < p1.size(); i++){
        result.push_back(p1[i]-p2[i]);
    }

    return result;
}

//Calcula la multiplicacion termino a termino de dos vectores. Operacion multidimensional.
vector < double > operator *(const vector<double> &p1,const vector<double> &p2){
    vector<double> result(dataClasses[0][0].size());
    for(int i = 0; i < p1.size(); i++){
        result.push_back(p1[i]*p2[i]);
    }

    return result;
}
//Calcula la multiplicacion termino a termino de dos vectores. Operacion multidimensional.
vector < double > operator *(const double &p1,const vector<double> &p2){
    vector<double> result(dataClasses[0][0].size());
    for(int i = 0; i < p2.size(); i++){
        result.push_back(p1*p2[i]);
    }

    return result;
}
//Calcula la division termino a termino de los terminos del primer vector entre los del
// segundo. Operacion multidimensional.
vector < double > operator /(const vector<double> &p1,const vector<double> &p2){
    vector<double> result(dataClasses[0][0].size());
    for(int i = 0; i < p1.size(); i++){
        result.push_back(p1[i]/p2[i]);
    }

    return result;
}

vector < double > operator /(const vector<double> &p1,const double &p2){
    vector<double> result(dataClasses[0][0].size());
    for(int i = 0; i < p1.size(); i++){
        result.push_back(p1[i]/p2);
    }

    return result;
}

// Calcula el resultado de dividir un vector entre una constante. Operacion multidimensional.
vector < double > norma(const vector<double> &p1,const double &p2){
    vector<double> result(dataClasses[0][0].size());
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



class Classifier{
private:
    vector < vector < vector <double> > > data;
    vector < vector < vector <double> > > normalData;

    vector < vector < double > > classesGravityPoints;
    vector < vector < double > > normalizeClassesGravityPoints;

    vector<double> omegaValue;
    vector< vector <double> > omegaValues;

    // Centro de gravedad de la clase. Se utiliza para clasificar
    vector < double > gravityPoint(int clas){

        vector < double > meane = data[clas][0];
        for( int i = 0; i < data[clas].size(); i++){
            meane = meane + data[clas][i];
        }
        meane = (1.0/data[clas].size())*meane;
        return meane;


    }
    // Normalizamos los datos y los centros de gravedad. Se utiliza meanValue y desviationValue.
    void normalizeData(){
        vector < double > meane = meanValue(), desv = desviationValue();
        for( int i = 0; i < data.size(); i++){
            for( int j = 0; j < data[i].size(); j++){
                normalData[i][j] = (data[i][j]-meane)/desv;
            }

            this->normalizeClassesGravityPoints.at(i) = (this->classesGravityPoints.at(i) - meane)/desv;
        }
    }
    // La media de cada feature. Se utiliza para normalizar.
    vector < double > meanValue(){
        vector<double> firstMoment(data[0][0].size());
        int values = 0;
        for( int i = 0; i < data.size(); i++){
            values += data[i].size();
            for( int j = 0; j < data[i].size(); j++){
                firstMoment = firstMoment + data[i][j];
            }
        }
        return firstMoment/(1.0*values);
    }

    // La desviacion tipica de cada feature. Se utiliza para normalizar.
    vector < double > desviationValue(){
        vector<double> secondMoment;
        double values = 0;
        for( int i = 0; i < data.size(); i++){
            values += data[i].size();
            for( int j = 0; j < data[i].size(); j++){
                secondMoment = secondMoment + data[i][j]*data[i][j];
            }
        }
        return secondMoment/values;
    }

    // Funcion para crear la funcion discriminante con los valores ya calculados.
    void normalizeDiscriminant(int clas){
        this->omegaValues[clas] = normalizeClassesGravityPoints[clas]/desviationValue();
        this->omegaValue[clas] = -2*scalarProduct(normalizeClassesGravityPoints[clas],meanValue()/desviationValue())-
            scalarProduct(normalizeClassesGravityPoints[clas],normalizeClassesGravityPoints[clas]);
    }
    // Funcion discriminante. La clase que maximice esta funcion, es la mas cercana.
    double discriminant (vector < double > cases , int clas){
        return 2*scalarProduct(omegaValues[clas],cases)+omegaValue[clas];
    }

public:

    // Constructor de clase. Inicializa los clasificadores y los estandariza.
    Classifier(vector < vector < vector <double> > > & data){
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

    }
    int clasifie(vector < double > cases){
        int max = 1;
        double maxValue = discriminant(cases,1);
        double value = maxValue;
        for(int i = 1; i < data.size(); i++){
            if(maxValue < value){
                max = i;
                maxValue = value;
            }
        }
        return max+1;
    }

};

void showData(int clas, vector< vector < vector< double > > > & data){
    for(int i = 0; i < data[clas].size(); i++){
        for(int j = 0; j < data[clas][i].size(); j++){
            cout << data[clas][i][j]<< " ";
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
        vector < vector < double > > v;
        dataClasses.push_back(v);
    }
    double input ;
    int clas;
    for( int i = 0; i < cases; i++){
        vector<double> v = vector<double>(features);
        trF >> clas;
        dataClasses[clas-1].push_back(v);
        for(int j = 0; j < features; j++){
            trF >> input;
            dataClasses[clas-1][(dataClasses[clas-1].size()-1)][j] = input;
        }
    }
    // showData(3, dataClasses);
    trF.close();

    Classifier cl(dataClasses);
    vector< double > caso;

    for(int i = 0; i < 10; i++) caso.push_back(0);
    cout << "This element  " << 1+ cl.clasifie(caso) << endl;

    // Time to Train.


    //showData();


    return 0;
}
