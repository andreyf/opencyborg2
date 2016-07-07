#include "cykohonen.h"
#include <math.h>
#include <misc.h>

CyKohonen::CyKohonen()
{
  //Значения по умолчанию
  NInp = 1;			// Число входов
  Nn = 1;			// Число нейронов
  ALPHA = 0.75;			// Темп обучения
  DALPHA =  0.01;
  ALPHA2 = 0.001;		// Радиус действия латеральных связей
  DALPHA2 = 0.001;
//  CBiasNeuron = 1.0;      	// Активность нейрона-порога
  CInitWeight = 1.0;      	// Максимальное начальное значение случайных синаптических весов
}

CyKohonen::~CyKohonen()
{}

void CyKohonen::Init()
{
  W.assign(NInp,vector<float>(Nn));
  for (int i=0; i<NInp; i++)
    for (int j=0; j<Nn; j++)
      W[i][j] = CInitWeight*Random(0,1);
//  P.assign(Nn,0);
//  for (int j=0; j<Nn; j++)
//    P[j] = CInitWeight*Random(0,1);
}

void CyKohonen::SetIn(vector<float> *in)
{
  Inp=in;

}

void CyKohonen::SetOut(vector<float> *out)
{
  Out=out;
}

void CyKohonen::ProcessLayer()
{
  float s, max_a=0;
  int max_n=0;
  // Для всех нейронов
  for (int j=0;j<Nn;j++)
    {
      // Вычисление суммарного входа нейрона
      s=0.0;
      for (int i=0;i<NInp;i++)
        s+=(*Inp)[i]*W[i][j];

      // Прохождение через нейрон
      (*Out)[j] = Validate(s,0.0,10.0);

      // Если слой типа "выиигрывает один", то определяем max активный нейрон
      if ((*Out)[j]>max_a)
        {
          max_a = (*Out)[j];
          max_n = j;
        }
    }

  // Моделируем слой "побеждает один"
  for (int j=0;j<Nn;j++)
    {
      if (j==max_n) (*Out)[j]=1.0;
        else (*Out)[j]=0.0;
    }
    win = max_n;

}

void CyKohonen::GetOut()
{}

void CyKohonen::ModifyWeights() //i-j
{

  float s, max_a=0;
  int max_n=0;
  // Для всех нейронов
  for (int j=0;j<Nn;j++)
    {
      // Вычисление суммарного входа нейрона
      s=0.0;
      for (int i=0;i<NInp;i++)
        s+=(*Inp)[i]*W[i][j];

      // Прохождение через нейрон
      (*Out)[j] = Validate(s,0.0,10.0);

      // Если слой типа "выиигрывает один", то определяем max активный нейрон
      if ((*Out)[j]>max_a)
        {
          max_a = (*Out)[j];
          max_n = j;
        }
    }

  // Моделируем слой "побеждает один"
  for (int j=0;j<Nn;j++)
    {
      (*Out)[j]=Lateral(j-max_n);
    }
    win = max_n;


  float newW;
  // Для всех нейронов
  for (int j=0;j<Nn;++j)
    {
      // для всех связей
      for (int i=0;i<NInp;++i)
        {
          newW=W[i][j];
          // Стремление весов активного нейрона к входному вектору
          newW+=((*Inp)[i]-W[i][j])*(*Out)[j]*ALPHA;
          W[i][j] = newW;
        }
//      Normalize(&W[j],NInp,1.0);
    }

  ALPHA-=ALPHA*DALPHA;
  ALPHA2-=ALPHA2*DALPHA2;
}

void CyKohonen::SaveNet()
{
  FILE *CFile;
  if ( (CFile = fopen( "ckohonen.net","w+b")) == NULL)    {
//	ERR("Ошибка создания файла cyperceptron.net");
	return;
    }
  fwrite(&NInp, 1, sizeof(int), CFile);	// Число входов
  fwrite(&Nn, 1, sizeof(int), CFile);	// Число нейронов
  for (int i=0; i<NInp; i++)
    for (int j=0; j<Nn; j++)
      fwrite(&W[i][j], 1, sizeof(float), CFile); // Матрица связей      
  fclose(CFile);
}

void CyKohonen::LoadNet()
{
  FILE *CFile;
  if ( (CFile = fopen( "ckohonen.net","r+b")) == NULL)    {
//	ERR("Ошибка создания файла cyperceptron.net");
	return;
    }
  fread(&NInp, 1, sizeof(int), CFile);	// Число входов
  fread(&Nn, 1, sizeof(int), CFile);	// Число нейронов
  W.assign(NInp,vector<float>(Nn));
  P.assign(Nn,0);
  for (int i=0; i<NInp; i++)
    for (int j=0; j<Nn; j++)
      fread(&W[i][j], 1, sizeof(float), CFile); // Матрица связей      
  fclose(CFile);
}

float CyKohonen::Lateral(float di)
{
  // Латеральные связи по экспоненциальному закону
  float T = ALPHA2*Nn+0.01;
  return exp(-di*di/(T*T));
}
