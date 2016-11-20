#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv) {

	if (argc != 3) {
		cerr << "Missing parameters, please check if your input is correct!" << endl;
		return 1;
		exit (EXIT_FAILURE);
	}

	int n = atoi(argv[1]);
	double d = atof(argv[2]);

	std::cout << "n = " << n << " d = " << d << '\n';

	double sumarFilas [n];
	double matrix [n][n];
	double tamanoMatrix = n*n;
	double cantidadCerosReal = tamanoMatrix * d/100;
	double cantidadCerosActual;
	double cantidadCerosIngresar;

	//Lleno la matrix de numeros random y la diagonal en 0
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			matrix[i][j] = (double)rand() / (double)RAND_MAX;
			matrix[i][i] = 0;
		}
	}

	//Sumo las filas, la suma se divide por 1 y se agrega esto a un arreglo
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			sumarFilas[i] = sumarFilas[i] + matrix[i][j];
		}
		sumarFilas[i] = 1/sumarFilas[i];
	}

	//Cada posicion de cada fila se multiplica por el numero correspondiente calculado anteriormente
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			matrix[i][j] = sumarFilas[i]*matrix[i][j];
		}
	}

	for(int i = 0 ; i < n ; i++){
			for(int j = 0 ; j < n ; j++){
					if(matrix[i][j] == 0){
						cantidadCerosActual = cantidadCerosActual + 1;
					};
			}
	}

	cantidadCerosIngresar = cantidadCerosReal - cantidadCerosActual;

	for(int i = 0 ; i < cantidadCerosIngresar; ++i){
					int randomI = rand()%((n-1)-0 + 1) + 0;
					int randomJ = rand()%((n-1)-0 + 1) + 0;
					if(matrix[randomI][randomJ] == 0){
						i = i-1;
					}else{
						matrix[randomI][randomJ] = 0;
					}
	}

	//Se imprime la matrix
	for(int i = 0 ; i < n ; i++){
			for(int j = 0 ; j < n ; j++){
					cout << matrix[i][j] << ' ';
			}
			cout<<endl;
	}

	return 0;
}
