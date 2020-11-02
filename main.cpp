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
    strcpy(msg, "Erro: indice nao inicializado.\n");
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
    strcpy(msg, "Erro: indice negativo.\n");
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
    strcpy(msg, "Erro: indice maior que arranjo.\n");
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
  BoundedArray()
  {
    for (int i = 0; i < N; i++)
    {
      verif[i] = false;
    }
  }
  void set(int index, T value)
  {
    if (index >= N)
      throw erroIndiceMaior();
    else if (index < 0)
      throw erroIndiceNegativo();
    buf[index] = value;
    verif[index] = true;
  }
  T get(int index)
  {
    if (index >= N)
      throw erroIndiceMaior();
    else if (index < 0)
      throw erroIndiceNegativo();
    if (verif[index] == false)
    {
      throw erroIndiceInicio();
      std::cout << "Erro: indice não inicializado.\n";
    }

    return buf[index];
  }

private:
  T buf[N];
  bool verif[N];
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
  }
}

int main()
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

  return 0;
}