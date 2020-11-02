#include <iostream>
#include <exception>
#include <string.h>
using namespace std;
class erroIndiceInicio : public exception
{
protected:
  char msg[100];

public:
  erroIndiceInicio()
  {
    strcpy(msg, "Erro: indice nao inicializado.");
  }
  virtual const char *what()
  {
    return msg;
  }
};
class erroIndiceNegativo : public exception
{
protected:
  char msg[100];

public:
  erroIndiceNegativo()
  {
    strcpy(msg, "Erro: indice negativo.");
  }
  virtual const char *what()
  {
    return msg;
  }
};
class erroIndiceMaior : public exception
{
protected:
  char msg[100];

public:
  erroIndiceMaior()
  {
    strcpy(msg, "Erro: indice maior que arranjo.");
  }
  virtual const char *what()
  {
    return msg;
  }
};
template <class T, int N>
class BoundedArray
{
public:
  void set(int index, T value)
  {
    if (index < 0)
      throw erroIndiceNegativo();
    buf[index] = value;
  }
  T get(int index)
  {
    if (index >= N)
      throw erroIndiceMaior();
    else if (index < 0)
      throw erroIndiceNegativo();
    return buf[index];
  }

private:
  T buf[N];
};

template <class T>
void testArray()
{
  BoundedArray<T, 8> a;
  char action;
  while (std::cin >> action)
  {
    int index;
    std::cin >> index;
    try
    {
      if (action == 's')
      {
        T value;
        std::cin >> value;
        a.set(index, value);
      }
      else if (action == 'g')
      {
        std::cout << a.get(index) << std::endl;
      }
    }
    catch (...)
    {
      std::cerr << "Erro desconhecido." << std::endl;
    }
  }
}

int main()
{
  try
  {
    char type;
    std::cin >> type;
    switch (type)
    {
    case 'd':
      testArray<double>();
      break;
    case 'i':
      testArray<int>();
      break;
    case 's':
      testArray<std::string>();
      break;
    }
  }
  catch (erroIndiceInicio e)
  {
    cerr << e.what();
  }
  catch (erroIndiceNegativo e)
  {
    cerr << e.what();
  }
  catch (erroIndiceMaior e)
  {
    cerr << e.what();
  }
  catch (...)
  {
    cerr << "Erro inesperado!";
  }

  return 0;
}