#include "cyperceptron.h"
#include <misc.h>
#include <string.h>
#include <errno.h>
#ifdef WIN32
#include <stdio.h>
#endif

CyPerceptron::CyPerceptron()
{
  //Значения по умолчанию
  NInp = 1;			// Число входов
  Nn = 1;			// Число нейронов
  ALPHA = 0.75;			// Темп обучения
  CBiasNeuron = 1.0;      	// Активность нейрона-порога
  CInitWeight = 1.0;      	// Максимальное начальное значение случайных синаптических весов
#ifdef WIN32
  SType = SigmoidType::ORIGINAL;
#else
  SType = ORIGINAL;
#endif
}

CyPerceptron::~CyPerceptron()
{}

void CyPerceptron::Init()
{
  W.assign(NInp,vector<double>(Nn));
  for (int i=0; i<NInp; i++)
    for (int j=0; j<Nn; j++)
      W[i][j] = CInitWeight*Random(-1,1);
  P.assign(Nn,0);
  for (int j=0; j<Nn; j++)
    P[j] = CInitWeight*Random(-1,1);
}

void CyPerceptron::SetIn(vector<double> *in)
{
  Inp=in;
}

void CyPerceptron::SetOut(vector<double> *out)
{
  Out=out;
}

void CyPerceptron::ProcessLayer()
{
  for (int j=0; j<Nn; j++)
    {
      CTemp = CBiasNeuron*P[j];
      for (int i=0; i<NInp; i++)
        CTemp = CTemp + (*Inp)[i]*W[i][j];

      (*Out)[j] = Sigmoid( CTemp, SType );
    }
}

void CyPerceptron::GetOut()
{}

void CyPerceptron::ModifyWeights()
{
  CError = 0;
  /* Цикл по нейронам. При аппаратной реализации
                   будет выполняться параллельно !!! */
  for (int j=0; j<Nn; j++)
    {
      /* Состояние очередного нейрона */
      CTemp = CBiasNeuron*P[j];
      for (int i=0; i<NInp; i++)
        CTemp = CTemp +(*Inp)[i]*W[i][j];

      /* Накопление ошибки */
      CDelta = (*Out)[j]-Sigmoid( CTemp, SType );

      (*Out)[j] = Sigmoid( CTemp, SType ); // sigmoid

      CError = CError + 0.5*CDelta*CDelta;

      /* Обучение по дельта-правилу Розенблатта */
      P[j] = P[j] + ALPHA*CBiasNeuron*CDelta;
      for (int i=0; i<NInp; i++)
        W[i][j] = W[i][j] + ALPHA*(*Inp)[i]*CDelta;
    }

}

void CyPerceptron::SaveNet()
{
  FILE *CFile;
  if ( (CFile = fopen( "cyperceptron.net","w+b")) == NULL)    {
	cout << "Error in CyPerceptron::SaveNet(). Error message: " << strerror(errno) << endl;
	return;
    }
  fwrite(&NInp, 1, sizeof(int), CFile);	// Число входов
  fwrite(&Nn, 1, sizeof(int), CFile);	// Число нейронов
  for (int i=0; i<NInp; i++)
    for (int j=0; j<Nn; j++)
      fwrite(&W[i][j], 1, sizeof(double), CFile); // Матрица связей      
  for (int j=0; j<Nn; j++)
      fwrite(&P[j], 1, sizeof(double), CFile); // Вектор порогов
  fclose(CFile);
}

void CyPerceptron::LoadNet()
{
  FILE *CFile;
  if ( (CFile = fopen( "cyperceptron.net","r+b")) == NULL)    {
	cout << "Error in CyPerceptron::LoadNet(). Error message: " << strerror(errno) << endl;
	return;
    }
  fread(&NInp, 1, sizeof(int), CFile);	// Число входов
  fread(&Nn, 1, sizeof(int), CFile);	// Число нейронов
  W.assign(NInp,vector<double>(Nn));
  P.assign(Nn,0);
  for (int i=0; i<NInp; i++)
    for (int j=0; j<Nn; j++)
      fread(&W[i][j], 1, sizeof(double), CFile); // Матрица связей      
  for (int j=0; j<Nn; j++)
      fread(&P[j], 1, sizeof(double), CFile); // Вектор порогов
  fclose(CFile);
}
