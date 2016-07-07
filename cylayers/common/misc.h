// misc.h "Вспомогательные функции"
#ifndef MISC_H
#define MISC_H

#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

#define PRECISION 0.001     // точность вычислений

enum SigmoidType {ORIGINAL=0,HYPERTAN=1};

typedef float* pfloat;

// Создание и удаление двумерного массива float
float** Create2DArray(int n1,int n2);
void Delete2DArray(float** p,int n1);

// Получение случ. числа float в диапазоне
float Random(float min,float max);

#ifdef WIN32
// Округление до целого
float round (float f);
#endif

// Нормализация вектора на length
void Normalize(vector<float> *v,int N,float length);

// Ограничение данных диапазоном min..max
double Validate(double value,double min,double max);
int Validate(int value,int min,int max);

// Перевод в логарифмический масштаб
double ToLog(double v);

// Проверка присутствия строки str в файле fp
void CheckString(FILE *fp,char *str);

// Распределение Гаусса
double Gaussian(double x,double T);

// Сигмоидальная передаточная функция нейрона
float Sigmoid(float, SigmoidType);

#endif
