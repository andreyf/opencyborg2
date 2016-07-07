#include <iostream>
#include <cyperceptron.h>
#include <misc.h>

using namespace std;

int main ( int argc, char* argv [] )
{

  CyPerceptron *perc = new CyPerceptron();
  perc->NInp = 10; //1 - нейрон, 10 - входов
  perc->Init();
  
#ifdef WIN32
  perc->SType = SigmoidType::HYPERTAN;
#else
  perc->SType = HYPERTAN;
#endif

  cout << "Начальная матрица связей" << endl;
  for (int i=0; i<perc->NInp;i++ )
    cout << perc->W[i][0] << endl;

  vector <double> in(perc->NInp);
  vector <double> out(perc->Nn);
  for (int n = 0; n <10000; n++)
    {
      int num = 0;
      for (int i = 0; i <perc->NInp; i++)
        {
          /* Случайно 0 или 1 */
          //in[i] = (int)Random(-1,1); //RANDOM( 2 );
			if (Random(-1,1)>0) in[i]=1; else in[i]=-1;
		  //cout << in[i] << endl;
          /* Подсчет единиц */
          if (in[i] > 0)
            num = num + 1;
          /* Выход равен единице, если в данном входном векторе
                   		число единиц больше числа нулей */
          if (num > (perc->NInp-num))
            out[0] = 1;
          else
            out[0] = -1;
        }
      perc->SetIn(&in);
      perc->SetOut(&out);
      perc->ModifyWeights();
    }

  perc->SaveNet();
  delete perc;
  perc = new CyPerceptron();
#ifdef WIN32
  perc->SType = SigmoidType::HYPERTAN;
#else
  perc->SType = HYPERTAN;
#endif
  perc->LoadNet();
  perc->SetOut(&out);

  cout << "Конечная матрица связей" << endl;
  for (int i=0; i<perc->NInp;i++ )
    cout << perc->W[i][0] << endl;
  cout << "Порог нейрона" << endl;
  cout << perc->P[0] << endl;

  cout << "               CYPERCEPTRON_TEST                 " << endl;
  cout << "-------------------------------------------------" << endl;
  cout << "Нейронной сети предъявляется вектор состоящий из" << endl;
  cout << "10 компонент, каждая из которых может быть 1" << endl;
  cout << "или -1. Сеть должна научиться определять, " << endl;
  cout << "чего больше - 1 или -1." << endl;
  cout << "-------------------------------------------------" << endl;
  cout << " ВОПРОС                 ВЕРНЫЙ ОТВЕТ    ОТВЕТ    " << endl;
  cout << "-------------------------------------------------" << endl;

  for (int n = 0; n <25; n++)
    {
      int num = 0;
      for (int i = 0; i <perc->NInp; i++)
        {
          /* Случайно 0 или 1 */
          //in[i] = (int)Random(-1,1); //RANDOM( 2 );
		  if (Random(-1,1)>0) in[i]=1; else in[i]=-1;
          /* Подсчет единиц */
          if (in[i] > 0)
            num = num + 1;
          /* Выход равен единице, если в данном входном векторе
                   		число единиц больше числа нулей */
          if (num > (perc->NInp-num))
            out[0] = 1;
          else
            out[0] = -1;
          cout << in[i] << " ";
        }
      cout << "         " << out[0];
      perc->SetIn(&in);
      perc->ProcessLayer();
      printf("    %.4f \n",out[0]);
    }

  delete perc;
  return 0;
}
