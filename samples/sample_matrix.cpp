// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

void main()
{
  setlocale(LC_ALL, "Russian");
  int sz;
  cout << "Введите размер матриц: ";
  cin >> sz;

  TDynamicMatrix<int> a(sz), b(sz);
  cout << "Введите первую матрицу:\n";
  cin >> a;
  cout << "Введите вторую матрицу:\n";
  cin >> b;

  char op;
  cout << "Введите операцию, производимую над матрицами (1 символ +,-,*): ";
  cin >> op;

  TDynamicMatrix<int> c;
  switch (op)
  {
  case '+':
	  c = a + b;
	  cout << "Сумма введенных матриц:";
	  cout << endl << c << endl;
	  break;
  case '*':
	  c = a * b;
	  cout << "Произведение введенных матриц:";
	  cout << endl << c << endl;
	  break;
  case '-':
	  c = a - b;
	  cout << "Разность матриц a и b:";
	  cout << endl << c << endl;
	  break;
  default:
	  break;
  }
}
//---------------------------------------------------------------------------
