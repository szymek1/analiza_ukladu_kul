#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "rk4.h"

double l;//dlugosc wahadla
double m;//masa kulki
double k1;//stala sprezystosci sprezyny 1
double k2;//stala sprezystosci sprezyny 2

void fun(double t, double* X, double* F);
double Energy(double* X);

int main()
{
	FILE* wynik = fopen("wynik.txt", "w");
	FILE* energia = fopen("energia.txt", "w");
	double w0 = 0.5;// [rad/s] predkosc katowa
	double a0 = 0.2;// [rad] kat wychylenia
	double tk = 10;
	double h = 1e-4;

	int n = 2;
	double* X, * X1r;
	X = (double*)malloc(n * sizeof(double));
	X1r = (double*)malloc(n * sizeof(double));
	X[0] = w0;
	X[1] = a0;

	printf("Podaj dlugosc wahadla[m] i mase kulki[kg]: ");
	scanf("%lf %lf", &l, &m);
	printf("Podaj stala sprezystosci sprezyny 1 i sprezyny 2: ");
	scanf("%lf %lf", &k1, &k2);

	//printf("t\tw\ta\n");
	fprintf(wynik,"t\tw\ta\n");
	fprintf(energia, "Energia dla m= %lf, L= %lf, k1= %lf, k2= %lf\n", m, l, k1, k2);
	for (double t = 0; t <= tk; t += h)
	{
		vrk4(t, X, h, n, fun, X1r);
		//printf("%lf\t%lf\t%lf\n", t, X[0], X[1]);
		fprintf(wynik,"%lf\t%lf\t%lf\n", t, X[0], X[1]);
		fprintf(energia, "%lf\n", Energy(X));
		X[0] = X1r[0];
		X[1] = X1r[1];
	}


	free(X);
	free(X1r);
	fclose(wynik);
	fclose(energia);
	return 0;
}

void fun(double t, double* X, double* F)
{
	double g = 9.81;
	F[0] = ((-1) * g * sin(X[1]) / l) - ((k1 + k2) * sin(X[1]) * cos(X[1]) / m);
	F[1] = X[0];
}
double Energy(double* X)
{
	double g = 9.81;
	return (m * pow(l, 2) * pow(X[0], 2) / 2) + m * g * l * (1 - cos(X[1]));
}
