#define _CRT_SECURE_NO_WARNINGS
/***************************************|
|		SME0602 - CALCULO NUMERICO		|
|				TRABALHO II				|
|	INTEGRANTES:		NUSP:			|
|	HELBERT M PINTO		10716504		|
|	MARCELO M COELHO	10716633		|
|***************************************/


//-----------------------------INCLUDES------------------------------//
#include<stdlib.h>
#include<stdio.h>
#include<math.h>


//------------------------------DEFINES------------------------------//
#define LIMIT_INF 0
#define LIMIT_SUP 1
#define EXP_ERRO -8


//-----------------------------FUNCTIONS-----------------------------//

// Calcula valor da funcao num ponto especifico
double value_function(double);

// Calcula valor da segunda derivada da funcao num ponto especifico
double value_function_seg_der(double x);

// Calcula valor da quarta derivada da funcao num ponto especifico
double value_function_qua_der(double x);

// Metodo do trapezio, recebe o valor de n como parametro
double trapezio(int);

// Retorna o valor de n para que o metodo do trapezio convirja
// com erro menor que o estabelecido
int getN_Trapezio();

// Metodo do Simpson, recebe o valor de N como parametro
double simpson(int);

// Retorna o valor de N para que o metodo de Simpson convirja
// com erro menor que o estabelecido
int getN_Simpson();


//-------------------------------MAIN--------------------------------//
int main() {
	double value_integral;
	
	int n_trap = getN_Trapezio();
	value_integral = trapezio(n_trap);

	int N_simp = getN_Simpson();
	value_integral = simpson(N_simp);

	return 0;
}


//-----------------------------FUNCTIONS-----------------------------//
double value_function(double x) {
	return exp(-pow(x, 2));
}


double value_function_seg_der(double x) {
	return 2*value_function(x) * (2*pow(x,2) - 1);
}


double value_function_qua_der(double x) {
	return 4*value_function(x) * (4*pow(x,4) - 12*pow(x,2) + 3);
}


//-----------------------------TRAPEZIO------------------------------//
int getN_Trapezio() {
	double range = LIMIT_SUP - LIMIT_INF;		// B - A
	double range_exp3 = pow(range, 3);			// (B - A)^3
	double erro = pow(10, EXP_ERRO);			// 10^(EXP_ERRO)
	double MAX_SEG_DER = 0.0;									// A <= x <= B
	double max_func = fabs(value_function_seg_der(MAX_SEG_DER));// MAX|f''(x)|

	double A = max_func * range_exp3;
	double B = 12.0 * erro;
	double aux = sqrt(A / B);
	int n = (aux - (int)aux) ? (int)aux + 1 : (int)aux;	// n = sqrt(A/B) se der valor exato
	return n;											// senao o prox inteiro
}


double trapezio(int n) {
	double h = (double)(LIMIT_SUP - LIMIT_INF) / n;	// (B - A)/n
	double x, y;
	double soma = 0;
	double value_integral;

	for (int i = 0; i <= n; i++) {
		x = (h * i) + LIMIT_INF;			// x = (i * passo) + A
		y = value_function(x);				// y = f(x)
		soma += (!i || i == n) ? y : 2 * y;	// i(extremos)	-> soma +y
	}										// senao i		-> soma +2y
	value_integral = (soma * h) / 2.0;		// (h / 2) * soma

	printf("|------- METODO TRAPEZIO -------|\n");
	printf("| n (subdiv)\t%16d|\n", n);
	printf("| h (passo)\t%.14f|\n", h);
	printf("| Valor aprox\t%.14f|\n\n", value_integral);

	return value_integral;
}


//------------------------------SIMPSON------------------------------//
int getN_Simpson() {
	double range = LIMIT_SUP - LIMIT_INF;		// B - A
	double range_exp5 = pow(range, 5);			// (B - A)^5
	double erro = pow(10, EXP_ERRO);			// 10^(EXP_ERRO)
	double MAX_QUA_DER = 0.0;									// A <= x <= B
	double max_func = fabs(value_function_qua_der(MAX_QUA_DER));// MAX|f''''(x)|

	double A = range_exp5 * max_func;
	double B =  pow(2, 5) * 180.0 * erro;
	double aux = pow((A / B), (1.0/4.0));				// n = raiz a quarta de (A/B) se der valor exato
	int N = (aux - (int)aux) ? (int)aux + 1 : (int)aux;	// senao o prox inteiro
	return N;
}


double simpson(int N) {
	int n = 2*N;									// n = 2 * N 
	double h = (double)(LIMIT_SUP - LIMIT_INF) / n;	// (B - A) / n <==> (B - A) / 2N
	double x, y;
	double soma = 0;
	double value_integral;

	for (int i = 0; i <= n; i++) {
		x = (h * i) + LIMIT_INF;
		y = value_function(x);								// i(extremos)	-> soma +y
		soma += (!i || i == n) ? y : (i & 1) ? 4*y : 2*y;	// i(impar)		-> soma +4y
	}														// i(par)		-> soma +2y
	value_integral = (soma * h) / 3.0;						// (h/3)*soma

	printf("|------ METODO DE SIMPSON ------|\n");
	printf("| N (grau)\t%16d|\n", N);
	printf("| n (subdiv)\t%16d|\n", n);
	printf("| h (passo)\t%.14f|\n", h);
	printf("| Valor aprox\t%.14f|\n\n", value_integral);

	return value_integral;
}