#ifndef CYPERCEPTRON_H
#define CYPERCEPTRON_H

#include <iostream>
#include <vector>
#include <misc.h>

using namespace std;

class CyPerceptron
  {
  public:
    CyPerceptron();
    ~CyPerceptron();

    int NInp;			// Число входов (default 1)
    int Nn;			// Число нейронов (default 1)
    double ALPHA;		// Темп обучения (default 0.75)
    vector< vector<double> > W;	// Матрица связей
    vector<double>  P;		// Вектор порогов
    vector<double> *Inp;		// Входной вектор
    vector<double> *Out;		// Выходной вектор

    double CError, CTemp, CDelta;
    double CBiasNeuron;      	// Активность нейрона-порога (default 1.0)
    double CInitWeight;      	//Максимальное начальное значение случайных синаптических весов (default 5.0)
    SigmoidType SType;

    /* Инициализация нейронной сети, задание начальных случайных значений матрицы связей */
    void Init();

    /* Установка входов нейросети */
    void SetIn(vector<double> *);

    /* Установка выходов нейросети */
    void SetOut(vector<double> *);

    /* Пропускание сигнала через слой, после можно снимать выход нейросети (GetOut) */
    void ProcessLayer();

    /* Возвращает выход */
    void GetOut();

    /* Модификация связей (обучение), необходимо установить вход (SetIn) и выход (SetOut) */
    void ModifyWeights();

    /* Сохранение нейросети в файл */
    void SaveNet();

    /* Загрузка нейросети из файла */
    void LoadNet();

  };
#endif
