#include <iostream>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

using namespace std;

static double TOLERANCE = 0.000000000000000000000001;

#define k 2

class Matrix {
int x, y;
double **matrix;
public:
Matrix (int, int);
void setValue (int x, int y, double value){
	matrix[x][y] = value;
}
double getValue (int x, int y){
	return matrix[x][y];
}
double * getMatrix (){
	return *matrix;
}
};

Matrix::Matrix (int x, int y){
	matrix = new double*[x];
	for (int i = 0; i < x; i++) {
		matrix[i] = new double[y];
	}
}

double maximumValue(double array[], int n)
{
	double max = array[0];
	for(int i = 0; i < n; i++) {
		if(array[i] > max) {
			max = array[i];
		}
	}
	return max;
}

int main(int argc, char **argv) {

	if (argc != 3) {
		cerr << "Faltan parametros o hay mas parametros de lo el tamaño y densidad de la matriz!" << endl;
		exit (EXIT_FAILURE);
		return 1;
	}

	if (!(atof(argv[2]) <= 1.0)) {
		cerr << "Densidad no es un numero menor a 1. Este debe ser un numero entre 0 y 1!" << endl;
		exit (EXIT_FAILURE);
		return 1;
	}

	if (ceil((atoi(argv[1]) * atoi(argv[1])) * atof(argv[2])) < atoi(argv[1])) {
		cerr << "Densidad de la matriz debe ser mayor!" << endl;
		exit (EXIT_FAILURE);
		return 1;
	}
/*
        MPI_Init(&argc, &argv);
        int p, rank;
        MPI_Comm_size(MPI_COMM_WORLD, &p);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        int n = abs(atoi(argv[1]));
        double d = abs(atof(argv[2]));

        Matrix matrix (n,n);
        double sumarColumnas [n];
        fill(sumarColumnas, sumarColumnas + n, 0);
        double vector[n];
        fill(vector, vector + n, 0);
        double sumRowVector;
        double resultVector[n];
        fill(resultVector, resultVector + n, 0);
        double vectorParada[n];
        fill(vectorParada, vectorParada + n, 0);

        int cntNum = ceil((n * n) * d);

        const int BLOCKROWS = n/k;      //Numero de filas a descomponer
        const int BLOCKCOLS = n;        // Numero de columnas a descomponer
        Matrix subMatrizMpi(BLOCKCOLS,BLOCKROWS);

        for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                        matrix.setValue(i,j,0);
                }
                subMatrizMpi.setValue(0,i,0);
        }

        MPI_Datatype blocktype;
        MPI_Datatype blocktype2;

        MPI_Type_vector(BLOCKROWS, BLOCKCOLS, n, MPI_DOUBLE, &blocktype2);
        MPI_Type_create_resized(blocktype2, 0, sizeof(double), &blocktype);
        MPI_Type_commit(&blocktype);

        unsigned seed = static_cast<unsigned>(time(0));
        srand(seed);

        if (rank == 0){
                MPI_Send(&seed, 1, MPI_UNSIGNED, 1, 0, MPI_COMM_WORLD);

                for (int j = 0; j < n; j++) {
                        int i = 1 + (static_cast <int> (rand()) % n) - 1;
                        if (i != j) {
                                matrix.setValue(i,j,static_cast <double> (rand()) / static_cast <double> (RAND_MAX));
                                cntNum--;
                        }else {
                                j--;
                        }
                }

                for(int i = 0; i < cntNum; i++) {
                        int ri = 1 + (static_cast <int> (rand()) % n) - 1;
                        int rj = 1 + (static_cast <int> (rand()) % n) - 1;
                        if (ri == rj || matrix.getValue(ri,rj) != 0) {
                                i--;
                        } else {
                                matrix.setValue(ri,rj,static_cast <double> (rand()) / static_cast <double> (RAND_MAX));
                        }
                }

                //Sumo las columnas, la suma se divide por 1 y se agrega esto a un arreglo
                for(int i = 0; i < n; i++) {
                        for(int j = 0; j < n; j++) {
                                sumarColumnas[i] = sumarColumnas[i] + matrix.getValue(j,i);
                        }
                        sumarColumnas[i] = 1/sumarColumnas[i];
                }

                //Cada posicion de cada columna se multiplica por el numero correspondiente calculado anteriormente
                for(int i = 0; i < n; i++) {
                        for(int j = 0; j < n; j++) {
                                matrix.setValue(j,i,sumarColumnas[i] * matrix.getValue(j,i));
                        }
                }

                for(int i = 0; i < n; i++) {
                        vector[i] = (double)1 / n;
                }

        } else {
                MPI_Recv(&seed, 1, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                for (int j = 0; j < n; j++) {
                        int i = 1 + (static_cast <int> (rand()) % n) - 1;
                        if (i != j) {
                                matrix.setValue(i,j,static_cast <double> (rand()) / static_cast <double> (RAND_MAX));
                                cntNum--;
                        }else {
                                j--;
                        }
                }

                for(int i = 0; i < cntNum; i++) {
                        int ri = 1 + (static_cast <int> (rand()) % n) - 1;
                        int rj = 1 + (static_cast <int> (rand()) % n) - 1;
                        if (ri == rj || matrix.getValue(ri,rj) != 0) {
                                i--;
                        } else {
                                matrix.setValue(ri,rj,static_cast <double> (rand()) / static_cast <double> (RAND_MAX));
                        }
                }

                //Sumo las columnas, la suma se divide por 1 y se agrega esto a un arreglo
                for(int i = 0; i < n; i++) {
                        for(int j = 0; j < n; j++) {
                                sumarColumnas[i] = sumarColumnas[i] + matrix.getValue(j,i);
                        }
                        sumarColumnas[i] = 1/sumarColumnas[i];
                }

                //Cada posicion de cada columna se multiplica por el numero correspondiente calculado anteriormente
                for(int i = 0; i < n; i++) {
                        for(int j = 0; j < n; j++) {
                                matrix.setValue(j,i,sumarColumnas[i] * matrix.getValue(j,i));
                        }
                }

                for(int i = 0; i < n; i++) {
                        vector[i] = (double)1 / n;
                }

        }



        double maxValue = 1;
        int count = 0;

        int disps[k];
        int counts[k];
        //int raizK = ceil(sqrt(k));

        for (int ii=1; ii < k; ii++) {
                disps[ii] = matrix.getValue(BLOCKROWS * k,0);
                counts[ii] = 1;
        }

        while(true) {

                if (rank == 0){
                        MPI_Scatterv(matrix.getMatrix(), counts, disps, blocktype, subMatrizMpi.getMatrix(), BLOCKROWS * BLOCKCOLS, MPI_DOUBLE, 0, MPI_COMM_WORLD);

                        if (maxValue > TOLERANCE) {
                                for(int i = 0; i < BLOCKROWS; i++) {
                                        for(int j = 0; j < BLOCKCOLS; j++) {
                                                resultVector[i] += (matrix.getValue(i,j) * vector[j]);
                                        }
                                }
                        } else {
                                break;
                        }

                        for (int i = 0; i < n; i++) {
                                vectorParada[i] = abs(resultVector[i] - vector[i]);
                        }

                        maxValue = maximumValue(vectorParada, n);

                        for (int i = 0; i < n; i++) {
                                vector[i] = resultVector[i];
                        }

                        fill(resultVector, resultVector + n, 0);

                } else {

                        if (maxValue > TOLERANCE) {
                                for(int i = rank * BLOCKROWS; i < (rank * BLOCKROWS) + (BLOCKROWS - 1); i++) {
                                        for(int j = 0; j < BLOCKCOLS; j++) {
                                                resultVector[rank * BLOCKROWS] += (matrix.getValue(i,j) * vector[j]);
                                        }
                                }
                        } else {
                                break;
                        }

                        for (int i = 0; i < n; i++) {
                                vectorParada[i] = abs(resultVector[i] - vector[i]);
                        }

                        maxValue = maximumValue(vectorParada, n);

                        for (int i = 0; i < n; i++) {
                                vector[i] = resultVector[i];
                        }

                        fill(resultVector, resultVector + n, 0);

                }
        }

        MPI_Barrier(MPI_COMM_WORLD);

        MPI_Finalize();

        /*	//Se imprime la matrix
                cout << "MATRIX" << endl;
                for(int i = 0; i < n; i++) {
                        for(int j = 0; j < n; j++) {
                                cout << matrix[i][j] << ' ';
                        }
                        cout<<endl;
                }
 */

	//Se imprime el vector
	cout << "VECTOR" << endl;
	for(int i = 0; i < n; i++) {
		cout << vector[i] << ' ';
	}
	cout<<endl;

	return 0;
}
