#include <iostream>
#include <cyperceptron.h>
#include <misc.h>

using namespace std;

int main ( int argc, char* argv [] )
{
  CyPerceptron *perc = new CyPerceptron();
  perc->NInp = 10; //1 - нейрон, 10 - входов
  perc->Init();

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
          in[i] = (int)Random(0,2); //RANDOM( 2 );
          /* Подсчет единиц */
          if (in[i] > 0)
            num = num + 1;
          /* Выход равен единице, если в данном входном векторе
                   		число единиц больше числа нулей */
          if (num > (perc->NInp-num))
            out[0] = 1;
          else
            out[0] = 0;
        }
      perc->SetIn(&in);
      perc->SetOut(&out);
      perc->ModifyWeights();
    }

  perc->SaveNet();
  delete perc;
  perc = new CyPerceptron();
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
  cout << "10 компонент, каждая из которых может быть нулем" << endl;
  cout << "или единицей. Сеть должна научиться определять, " << endl;
  cout << "чего больше - нулей или единиц." << endl;
  cout << "-------------------------------------------------" << endl;
  cout << " ВОПРОС                 ВЕРНЫЙ ОТВЕТ    ОТВЕТ    " << endl;
  cout << "-------------------------------------------------" << endl;

  for (int n = 0; n <25; n++)
    {
      int num = 0;
      for (int i = 0; i <perc->NInp; i++)
        {
          /* Случайно 0 или 1 */
          in[i] = (int)Random(0,2); //RANDOM( 2 );
          /* Подсчет единиц */
          if (in[i] > 0)
            num = num + 1;
          /* Выход равен единице, если в данном входном векторе
                   		число единиц больше числа нулей */
          if (num > (perc->NInp-num))
            out[0] = 1;
          else
            out[0] = 0;
          cout << in[i] << " ";
        }
      cout << "          " << out[0];
      perc->SetIn(&in);
      perc->ProcessLayer();
      printf("         %.4f \n",out[0]);
    }

  delete perc;
  return 0;
}
