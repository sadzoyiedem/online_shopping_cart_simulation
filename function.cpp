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

// Program functions
void main_menu()
{
  clear_screen();
  divider();
  cout << center_text("GROUP 14 Online Shopping Cart Simulation", 101) << endl;
  divider();

  cout << "Welcome!" << endl;

  cout << "What option would you like to explore:"
       << "\n\t1. View all products."
       << "\n\t2. Move to cart."
       << "\n\t3. Move to checkout."
       << "\n\t4. Exit program." << endl;

  divider();
}

void get_delivery_time(int &delivery_op)
{
  cout << "Enter the quantity: ";
  cin >> delivery_op;

  while (cin.fail() || delivery_op <= 0 || delivery_op > 3)
  {
    cin.ignore(1000, '\n');
    cin.clear();
    cerr << "Invalid input. Re-enter quantity: ";
    cin >> delivery_op;
  }
}
