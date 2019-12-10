#define _CRT_SECURE_NO_WARNINGS
/***************************************|
|		SME0000 - CALCULO NUMERICO		|
|				TRABALHO II				|
|	INTEGRANTES:		NUSP:			|
|	HELBERT M PINTO		10716504		|
|	MARCELO MAGALHAES	10xxxxxx		|
|***************************************/


//------------------------------INCLUDE------------------------------//
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

#define LIMIT_INF 0
#define LIMIT_SUP 1
#define EXP_ERRO -8
#define MAX_SEG_DER 1.224744871		//equals sqrt(6)/2



//-----------------------------FUNCTIONS-----------------------------//
//Calcula valor da funcao num ponto especifico
double value_function(double);

//Metodo do trapezio, recebe o valor de n como parametro
double trapezio(int);

//Retorna o valor de n para que o metodo do trapezio convirja
//para um valor menor que o erro estabelecido
int getN_Trapezio();

//Metodo do Simpson, recebe o valor de n como parametro
double simpson(int);

//Retorna o valor de n para que o metodo de Simpson convirja
// para um valor menor que o erro estabelecido
int getN_Simpson();

//-------------------------------MAIN--------------------------------//
int main() {
	double value_integral;
	
	int n_trap = getN_Trapezio();
	value_integral = trapezio(n_trap);
	return 0;
}

double value_function(double x) {
	return exp(-pow(x, 2));
}

//-----------------------------TRAPEZIO------------------------------//
int getN_Trapezio() {
	double range = LIMIT_SUP - LIMIT_INF;
	double range_exp3 = pow(range, 3);
	double erro = pow(10, EXP_ERRO);
	double A = MAX_SEG_DER * range_exp3;
	double B = 12 * erro;
	int n = (int) sqrt(A/B);
	return ++n;
}


double trapezio(int n) {
	double h = (double)(LIMIT_SUP - LIMIT_INF) / n;
	double x, y;
	double soma = 0;
	double value_integral;
	

	for (int i = 0; i <= n; i++) {
		x = (h * i) + LIMIT_INF;
		y = value_function(x);
		if (!i || i == n) {
			soma += y;
		} else {
			soma += 2 * y;
		}
	}
	value_integral = (double)soma * (h / 2);

	printf("METODO TRAPEZIO\n");
	printf("n (subdivisoes) = %d\n", n);
	printf("h (passo)  = %.8f\n", h);
	printf("Valor aproximado = %.8f\n", value_integral);

	return value_integral;
}


//------------------------------SIMPSON------------------------------//
int getN_Simpson() {
	return 0;
}

double simpson(int n) {
	return 0;
}