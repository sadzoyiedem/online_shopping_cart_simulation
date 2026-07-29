#include "function.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Column widths
static const int W_ID = 6;
static const int W_NAME = 30;
static const int W_PRICE = 16;
static const int W_QTY = 18;

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

void main_menu()
{
  clear_screen();
  divider();
  cout << center_text("GROUP 14 Online Shopping Cart Simulation", 101) << endl;
  divider();

  cout << "Welcome!" << endl;

  cout << "What option would you like to explore:"
       << "\n\t1. View all products."
       << "\n\t2. Search for product."
       << "\n\t3. Move to cart."
       << "\n\t4. Move to checkout."
       << "\n\t5. Exit program." << endl;

  divider();
}

void cart_menu_page()
{
  clear_screen();
  divider();
  cout << center_text("CART", 90) << endl;
  divider();

  cout << "What option would you like to explore?"
       << "\n\t1. Add item"
       << "\n\t2. Remove item"
       << "\n\t3. Modify item Quantity"
       << "\n\t4. Clear cart"
       << "\n\t5. Move to checkout menu"
       << "\n\t6. Go Back" << endl;

  divider();
}

void display_all_products(const vector<Item> &products)
{
  clear_screen();

  int table_width = W_ID + W_NAME + W_PRICE + W_QTY + 5;

  cout << string(table_width, '-') << endl;
  cout << center_text("Products Catalog", table_width) << endl;

  table_divider();
  cout << "|" << center_text("ID", W_ID)
       << "|" << center_text("Product Name", W_NAME)
       << "|" << center_text("Product Price", W_PRICE)
       << "|" << center_text("Product Quantity", W_QTY)
       << "|" << endl;
  table_divider();

  cout << fixed << setprecision(2);

  for (const Item &product : products)
  {
    cout << "|" << center_text(to_string(product.ID), W_ID)
         << "|" << " " << left << setw(W_NAME - 1) << product.Name
         << "|" << " GHC" << right << setw(W_PRICE - 3) << product.Price
         << "|" << center_text(to_string(product.Quantity), W_QTY)
         << "|" << endl;
  }
  table_divider();
}

void display_cart_items(const vector<Item> &cart_items)
{
  int table_width = W_ID + W_NAME + W_PRICE + W_QTY + 5;

  cout << string(table_width, '-') << endl;
  cout << center_text("Products in Cart", table_width) << endl;

  table_divider();
  cout << "|" << center_text("ID", W_ID)
       << "|" << center_text("Product Name", W_NAME)
       << "|" << center_text("Product Price", W_PRICE)
       << "|" << center_text("Product Quantity", W_QTY)
       << "|" << endl;
  table_divider();

  cout << fixed << setprecision(2);

  for (const Item &cart_item : cart_items)
  {
    cout << "|" << center_text(to_string(cart_item.ID), W_ID)
         << "|" << " " << left << setw(W_NAME - 1) << cart_item.Name
         << "|" << " GHC" << right << setw(W_PRICE - 3) << cart_item.Price
         << "|" << center_text(to_string(cart_item.Quantity), W_QTY)
         << "|" << endl;
  }
  table_divider();
}