/**************
*
*   TRABAJO PRACTICO NRO 1
*
*	Descripcion: Calculadora de Funciones
*
*   Autores: Nicolás Giudice, Luis Gimenez.
*
*	Fecha de Entrega: 1 julio 2019
*
***************/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define MAX_GRADO   15
#define MAX_ELEM    50

struct sPoli {
    float x;
    int   n;
    double vCoef [MAX_GRADO];
};

struct sCalcPoli {
    float x;
    int   n;
    double vCoef [MAX_GRADO];
    float res;
};

bool LeerPoli (ifstream &aPolinomios, sPoli &rPolinomio);

//Funciones de procesamiento de datos.
void ProcDatosEnTbl(sCalcPoli &vrPolinomio, sPoli rPolinomio, int &cantPoli);
float exponencial (float num, int exp);
float CalcPolis (sPoli rPolinomio);

// Funciones de ordenamiento.
void OrdxBur(sCalcPoli vrPolinomios [], int cantPoli);
void OrdxBur(int cantPoli, sCalcPoli vrPolinomios []);
void swapDatos (sCalcPoli vrPolinomios [], int i, int j);


void ListadoPoli (sCalcPoli vrPolinomios[], int cantPoli);


int main (void) {
    sCalcPoli vrPolinomios [MAX_ELEM];
    sPoli rPolinomio;
    int cantPoli = 0;

    // Abrimos el archivo de texto:
    ifstream aPolinomios ("Polinomios.txt");

    // dentro del argumento del while tengo que poner lo que esta al principio del proceso interno.
    while (LeerPoli (aPolinomios, rPolinomio))
        ProcDatosEnTbl (vrPolinomios[cantPoli], rPolinomio, cantPoli);

    OrdxBur (vrPolinomios, cantPoli); //ord. creciente por resultado del polinomio.
    ListadoPoli(vrPolinomios,cantPoli);
    OrdxBur(cantPoli, vrPolinomios); //ord. decreciente por grado del polinomio.
    ListadoPoli(vrPolinomios,cantPoli);
    aPolinomios.close ();

    return 0;
}

bool LeerPoli (ifstream &aPolinomios, sPoli &rPolinomio) {
    int i;

    aPolinomios >> rPolinomio.x >> rPolinomio.n;

    for (i=0; i < rPolinomio.n; i++)
        aPolinomios >> rPolinomio.vCoef[i];

    return aPolinomios.good();
}

// Las siguientes funciones sonn de procesamiento de datos.
void ProcDatosEnTbl(sCalcPoli &vrPolinomio, sPoli rPolinomio, int &cantPoli) {
    int i;

    //Pasamos los valores del registro a la tabla.
    vrPolinomio.x = rPolinomio.x;
    vrPolinomio.n = rPolinomio.n;

    for (i=0; i < rPolinomio.n; i++)
        vrPolinomio.vCoef[i] = rPolinomio.vCoef[i];

    //Calculamos y agregramos el resultado a la tabla.
    vrPolinomio.res =  CalcPolis (rPolinomio);
    cantPoli++;

    return;
}

float CalcPolis (sPoli rPolinomio) {
    float valorPoli=0;
    int i;

    for (i=0; i < rPolinomio.n ;i++)
        valorPoli += rPolinomio.vCoef[i] * exponencial (rPolinomio.x,i);

    return valorPoli;
}

float exponencial (float num, int exp) {
    float resul=1;
    int i;

    for (i=0; i<exp; i++)
        resul *= num;

    return resul;
}

// Funciones de ordenamiento e impresion de listado
void OrdxBur(sCalcPoli vrPolinomios [], int cantPoli) {
    int i, j;

    for (i=0; i < cantPoli-1; i++)
        for (j = i+1 ; j < cantPoli; j++)
            if (vrPolinomios[i].res > vrPolinomios[j].res)
                swapDatos (vrPolinomios, i, j);
}

void OrdxBur(int cantPoli, sCalcPoli vrPolinomios []) {
    int i, j;

    for (i=0; i < cantPoli-1; i++)
        for (j = i+1 ; j < cantPoli; j++)
            if (vrPolinomios[i].n < vrPolinomios[j].n)
                swapDatos (vrPolinomios, i, j);
}

void swapDatos (sCalcPoli vrPolinomios [], int i, int j) {
    sCalcPoli rAux;
    int k;

    // Guardo el contenido del primer elemento en un registro auxiliar.
    rAux.x = vrPolinomios[i].x;
    rAux.n = vrPolinomios[i].n;
    rAux.res = vrPolinomios[i].res;

    for (k=0; k < MAX_GRADO; k++)
        rAux.vCoef[k] = vrPolinomios[i].vCoef[k];

    // Copiamos el contenido del segundo registro en el primero.
    vrPolinomios[i].x = vrPolinomios[j].x;
    vrPolinomios[i].n = vrPolinomios[j].n;
    vrPolinomios[i].res = vrPolinomios[j].res;

    for (k=0; k < MAX_GRADO; k++)
        vrPolinomios[i].vCoef[k] = vrPolinomios[j].vCoef[k];

    // Copiamos lo guardado en el registro auxiliar en el segundo registro.
    vrPolinomios[j].x = rAux.x;
    vrPolinomios[j].n = rAux.n;
    vrPolinomios[j].res = rAux.res;

    for (k=0; k < MAX_GRADO; k++)
        vrPolinomios[j].vCoef[k] = rAux.vCoef[k];
}

void ListadoPoli (sCalcPoli vrPolinomios[], int cantPoli) {
    static int pos = 0;
	int i,j;

	freopen ("ListadoPoli.txt","a",stdout);

    if (pos == 0)
    {
        cout << "Listado Polinomios ordenado por Resultado creciente." << endl << endl;
        pos = 1;
    }
    else
        cout << "Listado Polinomios ordenado por Grado decreciente." << endl << endl;

	cout<<right<<setw(8)<<"#Ord"<<setw(14)<<"Valor de x"<<setw(10)<<"Grado n"<<setw(20)<<"Resultado"<<endl;

	for(j=0;j<cantPoli;j++)
    {
		cout<<right<<setw(8)<<j+1<<setw(14)<<vrPolinomios[j].x<<setw(10)<<vrPolinomios[j].n<<setw(20);
		cout<<setprecision(3)<<fixed<<vrPolinomios[j].res<<endl;
    }

    cout << endl;
    freopen ("CON","a",stdout);
}
