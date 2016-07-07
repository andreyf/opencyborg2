#ifndef CYKOHONEN_H
#define CYKOHONEN_H

#include <iostream>
#include <vector>

using namespace std;

class CyKohonen
  {
  public:
    CyKohonen();
    ~CyKohonen();

    int NInp;			// Число входов (default 1)
//    int NOut;			// Число выходов
    int Nn;			// Число нейронов (default 1)
    float ALPHA;		// Темп обучения (default 0.75)
    float DALPHA;
    float ALPHA2;		// Радиус действия латеральных связей (default 0.001)
    float DALPHA2;
    vector< vector<float> > W;	// Матрица связей
    vector<float>  P;		// Вектор порогов
    vector<float> *Inp;		// Входной вектор
    vector<float> *Out;		// Выходной вектор
    int win;

    float CError, CTemp, CDelta;
//    float CBiasNeuron;      	// Активность нейрона-порога (default 1.0)
    float CInitWeight;      	//Максимальное начальное значение случайных синаптических весов (default 5.0)

    /* Инициализация нейронной сети, задание начальных случайных значений матрицы связей */
    void Init();

    /* Установка входов нейросети */
    void SetIn(vector<float> *);

    /* Установка выходов нейросети */
    void SetOut(vector<float> *);

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

  private:
    // Вычисление веса латеральной связи
    float Lateral(float);

  };
#endif
