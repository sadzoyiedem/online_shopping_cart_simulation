#include "Checkout.h"
#include "function.h"
#include <iostream>
#include <iomanip>

using namespace std;

float Checkout::calculate_sub_total(const vector<Item> &cart_items) const
{
  if (cart_items.empty())
    return 0.0f;

  float sub_total{};
  for (const Item &cart_item : cart_items)
  {
    sub_total += (cart_item.Quantity * cart_item.Price);
  }

  return sub_total;
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

bool checkout_menu_page_flow(Cart &cart, InventoryManager &inventory_manager)
{
  int choice;
  int delivery_time_op{};

  cout << "Enter option: ";
  while (input_validation(1, 4, choice))
    ;

  switch (choice)
  {
  case 1:
    display_delivery_time();
    get_delivery_time(delivery_time_op);
    
    break;
  
  default:
    break;
  }
}

void display_delivery_time()
{
  clear_screen();
  divider();
  cout << center_text("DELIVERY TIME AND PRICE", 90) << endl;
  divider();

  cout << "Set delivery time."
       << "\n\t1. 3 days\t- GHC 15.00"
       << "\n\t2. 7 days\t- GHC 10.00"
       << "\n\t3. 14 days\t- GHC 5.00"<< endl;

  divider();
}

