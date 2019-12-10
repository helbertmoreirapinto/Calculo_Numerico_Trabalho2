#define _CRT_SECURE_NO_WARNINGS
/***************************************|
|		SME0000 - CALCULO NUMERICO		|
|				TRABALHO II				|
|	INTEGRANTES:		NUSP:			|
|	HELBERT M PINTO		10716504		|
|	MARCELO M COELHO	10716633		|
|***************************************/


//------------------------------INCLUDE------------------------------//
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>


//------------------------------DEFINES------------------------------//
#define LIMIT_INF 0
#define LIMIT_SUP 1
#define EXP_ERRO -8


//-----------------------------FUNCTIONS-----------------------------//

//Calcula valor da funcao num ponto especifico
double value_function(double);

//Calcula valor da segunda derivada da funcao num ponto especifico
double value_function_seg_der(double x);

//Calcula valor da quarta derivada da funcao num ponto especifico
double value_function_qua_der(double x);

//Metodo do trapezio, recebe o valor de n como parametro
double trapezio(int);

//Retorna o valor de n para que o metodo do trapezio convirja
// com erro menor que o estabelecido
int getN_Trapezio();

//Metodo do Simpson, recebe o valor de N como parametro
double simpson(int);

//Retorna o valor de N para que o metodo de Simpson convirja
// com erro menor que o estabelecido
int getN_Simpson();


//-------------------------------MAIN--------------------------------//
int main() {
	double value_integral;
	
	int n_trap = getN_Trapezio();
	value_integral = trapezio(n_trap);

	int n_simp = getN_Simpson();
	value_integral = simpson(n_simp);

	return 0;
}


double value_function(double x) {
	return exp(-pow(x, 2));
}


double value_function_seg_der(double x) {
	return value_function(x) * (4*pow(x,2) - 2);
}


double value_function_qua_der(double x) {
	return 4*value_function(x) * (4*pow(x,4) - 12*pow(x,2) + 3);
}


//-----------------------------TRAPEZIO------------------------------//
int getN_Trapezio() {
	double range = LIMIT_SUP - LIMIT_INF;
	double range_exp3 = pow(range, 3);
	double erro = pow(10, EXP_ERRO);
	double MAX_SEG_DER = sqrt(6) / 2.0;
	double max_func = value_function_seg_der(MAX_SEG_DER);

	double A = max_func * range_exp3;
	double B = 12.0 * erro;
	double aux = sqrt(A / B);
	int n = (aux - (int)aux) ? (int)aux + 1 : (int)aux;
	return n;
}


double trapezio(int n) {
	double h = (double)(LIMIT_SUP - LIMIT_INF) / n;
	double x, y;
	double soma = 0;
	double value_integral;

	for (int i = 0; i <= n; i++) {
		x = (h * i) + LIMIT_INF;
		y = value_function(x);
		soma += (!i || i == n) ? y : 2 * y;
	}
	value_integral = (double)soma * (h / 2);

	printf("|----- METODO TRAPEZIO -----|\n");
	printf("| n (subdiv)\t%12d|\n", n);
	printf("| h (passo)\t%.10f|\n", h);
	printf("| Valor aprox\t%.10f|\n\n", value_integral);

	return value_integral;
}


//------------------------------SIMPSON------------------------------//
int getN_Simpson() {
	double range = LIMIT_SUP - LIMIT_INF;
	double range_exp5 = pow(range, 5);
	double erro = pow(10, EXP_ERRO);
	double MAX_QUA_DER = 0.0;
	double max_func = value_function_qua_der(MAX_QUA_DER);

	double A = range_exp5 * max_func;
	double B =  pow(2, 5) * 180.0 * erro;
	double aux = pow((A / B), (1.0/4.0));
	int N = (aux - (int)aux) ? (int)aux + 1 : (int)aux;
	return N;
}


double simpson(int N) {
	int n = 2 * N;
	double h = (double)(LIMIT_SUP - LIMIT_INF) / n;
	double x, y;
	double soma = 0;
	double value_integral;

	int k = n;
	for (int i = 0; i <= k; i++) {
		x = (h * i) + LIMIT_INF;
		y = value_function(x);
		soma += (!i || i == k) ? y : (i & 1) ? 4*y : 2*y;
	}
	value_integral = (double)soma * (h / 3);

	printf("|---- METODO DE SIMPSON ----|\n");
	printf("| N (grau)\t%12d|\n", N);
	printf("| n (subdiv)\t%12d|\n", n);
	printf("| h (passo)\t%.10f|\n", h);
	printf("| Valor aprox\t%.10f|\n\n", value_integral);

	return value_integral;
}