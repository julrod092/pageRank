#include <iostream>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

static double TOLERANCE = 0.000000000000000000000001;

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
		cerr << "Missing parameters, please check if your input is correct!" << endl;
		return 1;
		exit (EXIT_FAILURE);
	} else if (atoi(argv[2]) < ((atoi(argv[1]) * 100) / (atoi(argv[1]) * atoi(argv[1])))) {
		cerr << "Density must be major" << endl;
		return 1;
		exit (EXIT_FAILURE);
	}

	int n = atoi(argv[1]);
	double d = atof(argv[2]);

	double sumarColumnas [n];
	double matrix [n][n];
	double tamanoMatrix = n*n;
	double cantidadCerosReal = ceil(tamanoMatrix * d/100);
	double cantidadCerosActual;
	double cantidadCerosIngresar;
	double vector[n];
	double sumRowVector;
	double resultVector[n];
	double oldResultVector[n];
	double vectorParada[n];



	//Lleno la matrix de numeros random y la diagonal en 0
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			matrix[i][j] = (double)rand() / (double)RAND_MAX;
		}
		matrix[i][i] = 0;
	}

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(matrix[i][j] == 0) {
				cantidadCerosActual++;
			};
		}
	}

	cantidadCerosIngresar = cantidadCerosReal - cantidadCerosActual;
	cout << cantidadCerosIngresar << endl;

	for(int i = 0; i < cantidadCerosIngresar; ++i) {
		int randomI = rand() % n + 1;
		int randomJ = rand() % n + 1;
		if(matrix[randomI][randomJ] == 0) {
			i = i-1;
		}else{
			matrix[randomI][randomJ] = 0;
		}
	}

	//Sumo las filas, la suma se divide por 1 y se agrega esto a un arreglo
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			sumarColumnas[i] = sumarColumnas[i] + matrix[j][i];
		}
		sumarColumnas[i] = 1/sumarColumnas[i];
	}

	//Cada posicion de cada fila se multiplica por el numero correspondiente calculado anteriormente
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			matrix[j][i] = sumarColumnas[i] * matrix[j][i];
		}
	}

	for(int i = 0; i < n; i++) {
		vector[i] = (double)1 / n;
	}

	double maxValue = 1;
	int count = -1;

	//Se imprime la matrix
	cout << "MATRIX" << endl;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			cout << matrix[i][j] << ' ';
		}
		cout<<endl;
	}

	while(true) {

		//Se imprime el vector
		cout << "VECTOR" << endl;
		for(int i = 0; i < n; i++) {
			cout << vector[i] << ' ';
		}
		cout<<endl;

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

		cout << "PARADA VECTOR" << endl;
		for(int i = 0; i < n; i++) {
			cout << vectorParada[i] << ' ';
		}
		cout<<endl;

		maxValue = maximumValue(vectorParada, n);

		for (int i = 0; i < n; i++) {
			vector[i] = resultVector[i];
		}

		count++;
		if (count > 1) {
			break;
		}
	}

	return 0;
}
