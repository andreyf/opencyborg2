// misc.cpp "Вспомогательные функции"
#include "misc.h"

#include <string.h>
#include <stdlib.h>
#include <math.h>

//#include "debug.h"

void Delete2DArray(float** p,int n1)
{
  if (!p)
    return;
  for (int i=0;i<n1;++i)
    delete p[i];
  delete p;
}

float** Create2DArray(int n1,int n2)
{
  pfloat *p;
  p = new pfloat[n1];
  for (int i=0;i<n1;++i)
    p[i] = new float[n2];

  return p;
}

float Random(float min,float max)
{
  return min+((float)rand()/RAND_MAX)*(max-min);
}

#ifdef WIN32
float round (float f)
{
	return (f-(int)f>=0.5)?(int)f+1:(int)f;
}
#endif

void Normalize(vector<float> *v,int N,float length)
{ 
  int i=0;
  double s = 0;
  for (i=0;i<N;++i)
    s+= (*v)[i]*(*v)[i];
  if (s < PRECISION)
    return;
  s=sqrt(s);
  for (i=0;i<N;++i)
    (*v)[i]=(*v)[i]*length/s;
}

double Validate(double value,double minvalue,double maxvalue)
{
  return min(maxvalue,max(minvalue,value));
  return 0;
}

int Validate(int value,int minvalue,int maxvalue)
{
  return min(maxvalue,max(minvalue,value));
  return 0;
}

double ToLog(double v)
{
  return (2.00+log10(0.01+v))/2.00;
}

void CheckString(FILE *fp,char  *str)
{
  char temp[1024];
  unsigned int  length = strlen(str);
  if (fread(temp,1,length,fp)!=length)
    {
//      ERR("Файл поврежден или устарел формат данных");
      return;
    }
  temp[length] = (char)0;
  if (strcmp(str,temp))
    {
//      ERR("Файл поврежден или устарел формат данных");
      return;
    }
}

double Gaussian(double x,double T)
{
  return exp(-x*x*T);
}

float Sigmoid(float Z, SigmoidType SType)
{
    switch(SType)
    {
	case ORIGINAL: return 1.0/(1.0+exp(-Z));
	case HYPERTAN: return tanh(Z);
	default: return 0;
    }
}
