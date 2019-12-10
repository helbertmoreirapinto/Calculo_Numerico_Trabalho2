#define _CRT_SECURE_NO_WARNINGS
/***************************************|
|		SME0000 - CALCULO NUMERICO		|
|				TRABALHO II				|
|	INTEGRANTES:		NUSP:			|
|	HELBERT M PINTO		10716504		|
|	MARCELO MAGALHAES	10xxxxxx		|
|***************************************/


//-----------------------------------------------------INCLUDE------------------------------------------------------//
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

#define LIMIT_INF 0
#define LIMIT_SUP 1
#define EXP_ERRO -8
#define MAX_SEG_DER 1.224744871		//equals sqrt(6)/2



//-----------------------------------------------------FUNCTIONS----------------------------------------------------//
int trapezio(int);
int getN_Trapezio();
int simpson(int);
int getN_Simpson();


//-------------------------------------------------------MAIN-------------------------------------------------------//
int main() {
	int value_integral;
	
	int n_trap = getN_Trapezio();
	value_integral = trapezio(n_trap);
	
	int n_simp = getN_Simpson();
	value_integral = trapezio(n_simp);
	
	return 0;
}


//-----------------------------------------------------TRAPEZIO-----------------------------------------------------//
int getN_Trapezio() {
	double range = LIMIT_SUP - LIMIT_INF;
	double range_exp3 = pow(range, 3);
	double erro = pow(10, EXP_ERRO);
	double A = MAX_SEG_DER * range_exp3;
	double B = 12 * erro;
	int n = (int) sqrt(A/B);
	return ++n;
}

int trapezio(int n) {
	return 0;
}


//------------------------------------------------------SIMPSON----------------------------------------------------//
int getN_Simpson() {
	return 0;
}

int simpson(int n) {
	return 0;
}