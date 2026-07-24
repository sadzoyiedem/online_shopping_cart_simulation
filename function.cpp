#include "function.h"
#include <iostream>

using namespace std;

// helper functions

void clear_screen()
{
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void divider()
{
  cout << "--------------------------------------------------------------------------" << endl;
}