#include <iostream>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

static double TOLERANCE = 0.000000000000000000000001;

int main(int argc, char **argv) {

	if (argc != 3) {
		cerr << "Faltan parametros o hay mas parametros de lo el tamaño y densidad de la matriz!" << endl;
		return 1;
		exit (EXIT_FAILURE);
	}

	if (!(atoi(argv[2]) <= (atoi(argv[1])))) {
		cerr << "La densidad tiene que ser un entero menor que el tamaño de la matriz!" << endl;
		return 1;
		exit (EXIT_FAILURE);
	}

	int n = abs(atoi(argv[1]));
	double d = abs(atof(argv[2]));

	double matrix[n][n];
	double sumarColumnas [n];
	double vector[n];
	double sumRowVector;
	double resultVector[n];
	double oldResultVector[n];
	double vectorParada[n];

	int cantidadCerosReal = ((n * n) - (n * d));
	int cantidadCerosIngresar = 0;

	srand(static_cast<unsigned>(time(0)));

	//Lleno la matrix de numeros random y la diagonal en 0
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			matrix[i][j] = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
		}
		matrix[i][i] = 0;
	}

	cantidadCerosIngresar = cantidadCerosReal - n;

	for(int i = 0; i < cantidadCerosIngresar; ++i) {
		int randomI = 1 + (static_cast <int> (rand()) % n) - 1;
		int randomJ = 1 + (static_cast <int> (rand()) % n) - 1;
		int count = 0;
		for (int j = 0; j < n; j++) {
			if (matrix[randomI][j] == 0) {
				count++;
			}
		}
		if (count < (n - 2)) {
			matrix[randomI][randomJ] = 0;
		}else{
			i--;
		}
	}

//Sumo las columnas, la suma se divide por 1 y se agrega esto a un arreglo
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			sumarColumnas[i] = sumarColumnas[i] + matrix[j][i];
		}
		sumarColumnas[i] = 1/sumarColumnas[i];
	}

//Cada posicion de cada columna se multiplica por el numero correspondiente calculado anteriormente
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			matrix[j][i] = sumarColumnas[i] * matrix[j][i];
		}
	}

	for(int i = 0; i < n; i++) {
		vector[i] = (double)1 / n;
	}

	//Se imprime la matrix
	cout << "MATRIX" << endl;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			cout << matrix[i][j] << ' ';
		}
		cout<<endl;
	}

	double maxValue = 1;
	int count = 0;

	while(true) {

		if (maxValue > TOLERANCE) {
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < n; j++) {
					resultVector[i] += (matrix[i][j] * vector[j]);
				}
			}
		} else {
			break;
		}

		//Se imprime el vector resultado
		cout << "RESULT VECTOR" << endl;
		for(int i = 0; i < n; i++) {
			cout << resultVector[i] << ' ';
		}
		cout<<endl;

		for (int i = 0; i < n; i++) {
			vectorParada[i] = abs(resultVector[i] - vector[i]);
		}

		maxValue = *max_element(vectorParada, vectorParada + n);

		for (int i = 0; i < n; i++) {
			vector[i] = resultVector[i];
		}

		fill(resultVector, resultVector + n, 0);
	}

	//Se imprime el vector
	cout << "VECTOR" << endl;
	for(int i = 0; i < n; i++) {
		cout << vector[i] << ' ';
	}
	cout<<endl;

	return 0;
}
