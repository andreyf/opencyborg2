#include <iostream>
#include <cykohonen.h>
#include <misc.h>

using namespace std;

int main ( int argc, char* argv [] )
{
  CyKohonen *koh = new CyKohonen();
  koh->NInp = 3; //3 - нейрона, 3 - входа
  koh->Nn = 3;
  koh->Init();

//  DBG("Начальная матрица связей");
//  for (int i=0; i<koh->NInp;i++ )
//    DBG("%f ", koh->W[i][0]);

  vector <float> in(koh->NInp);
  vector <float> out(koh->Nn);
  koh->SetOut(&out);
  for (int n = 0; n <10000; n++)
    {
      int num = 0;
      for (int i = 0; i <koh->NInp; i++)
          /* Случайно 0 или 1 */
          in[i] = (int)Random(0,2); //RANDOM( 2 );
      koh->SetIn(&in);      
      koh->ModifyWeights();
    }

  koh->SaveNet();
  delete koh;
  koh = new CyKohonen();
  koh->LoadNet();
  koh->SetOut(&out);

//  DBG("Конечная матрица связей");
//  for (int i=0; i<koh->NInp;i++ )
//    DBG("%f ", koh->W[i][0]);

  cout << "               CYKOHONEN_TEST               " << endl;
  cout << "-------------------------------------------------" << endl;
  cout << "Нейронной сети предъявляется вектор состоящий из" << endl;
  cout << "3 компонент, каждая из которых может быть нулем" << endl;
  cout << "или единицей. Сеть должна научиться разделять " << endl;
  cout << "на 3 класса входящие вектора." << endl;
  cout << "-------------------------------------------------" << endl;
  cout << " ВОПРОС                  ОТВЕТ    " << endl;
  cout << "-------------------------------------------------" << endl;

  for (int n = 0; n <25; n++)
    {
      int num = 0;
      for (int i = 0; i <koh->NInp; i++)
      {
          in[i] = (int)Random(0,2); //RANDOM( 2 );
	  cout << in[i] << " ";
      }
	  

      koh->SetIn(&in);
      koh->ProcessLayer();
      printf("            %.4f %.4f %.4f \n",out[0], out[1], out[2]);
    }
  
  delete koh;
  return 0;
}
