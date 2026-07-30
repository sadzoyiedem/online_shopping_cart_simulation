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

void get_item_id(int &product_id)
{
  cout << "Enter the product ID: ";
  cin >> product_id;

  while(cin.fail() || product_id < 0)
  {
    cin.ignore(1000,'\n');
    cin.clear();
    cerr << "Invalid input. Re-enter quantity: ";
    cin >> product_id;
  }
}

void get_quantity(int &quant)
{
  cout << "Enter the quantity: ";
  cin >> quant;

  while(cin.fail() || quant < 0)
  {
    cin.ignore(1000,'\n');
    cin.clear();
    cerr << "Invalid input. Re-enter quantity: ";
    cin >> quant;
  }

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

void checkout_menu_page()
{
  clear_screen();
  divider();
  cout << center_text("CHECKOUT", 90) << endl;
  divider();

  cout << "What option would you like to explore?"
       << "\n\t1. Set delivery time"
       << "\n\t2. Checkout"
       << "\n\t3. Move to cart menu"
       << "\n\t4. Go Back" << endl;

  divider();
}






