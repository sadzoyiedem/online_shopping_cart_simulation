#include "function.h" // function.h contains cart.h, iostream
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

// Column widths
static const int W_ID = 6;
static const int W_NAME = 30;
static const int W_PRICE = 16;
static const int W_QTY = 18;
static const int W_TOTAL_COST = 16;

// Helper functions
void clear_screen()
{
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void table_divider()
{
  cout << "+" << string(W_ID, '-')
       << "+" << string(W_NAME, '-')
       << "+" << string(W_PRICE, '-')
       << "+" << string(W_QTY, '-')
       << "+" << string(W_TOTAL_COST, '-')
       << "+" << endl;
}

string center_text(const string &text, int width)
{
  int total_pad = width - static_cast<int>(text.size());
  if (total_pad <= 0)
    return text;
  int left_pad = total_pad / 2;
  int right_pad = total_pad - left_pad;
  return string(left_pad, ' ') + text + string(right_pad, ' ');
}

void divider()
{
  cout << string(101, '-') << endl;
}

bool input_validation(int min, int max, int &user_opt)
{
  int option{};
  cin >> option;

  if (cin.fail() || option < min || option > max)
  {
    cin.clear();
    cin.ignore(1000, '\n');

    cout << "Invalid option entered!\nRe-enter option: ";

    return true;
  }

  user_opt = option;

  return false;
}

bool get_item_id(int &product_id)
{
  cin >> product_id;

  if (cin.fail() || product_id < 0)
  {
    cin.clear();
    cin.ignore(1000, '\n');
    cerr << "Invalid input.\t Re-enter product ID: ";
    return true;
  }

  return false;
}

bool get_quantity(int &quant)
{
  cin >> quant;

  if (cin.fail() || quant < 0)
  {
    cin.clear();
    cin.ignore(1000, '\n');
    cerr << "Invalid input. \t Re-enter quantity: ";
    return true;
  }

  return false;
}

void hold_screen()
{
  cout << "\nPress Enter to continue...";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.get();
}

bool get_delivery_time(int &delivery_op)
{
  cin >> delivery_op;

  if (cin.fail() || delivery_op <= 0 || delivery_op > 3)
  {
    cin.clear();
    cin.ignore(1000, '\n');
    cerr << "Invalid input. Re-enter delivery time: ";
    return true;
  }

  return false;
}

void exit_message()
{ 
  clear_screen();
  divider();
  cout << "Thank you for using this program.\nSee you next time." << endl;
  divider();
}