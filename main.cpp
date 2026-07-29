#include <iostream>
// #include "config.h"
#include "item.h"
#include "inventory_manager.h"
#include "cart.h"
#include "checkout.h"
#include "function.h"

using namespace std;

const float tax_rate = 0.025; // tax rate in decimal percentage.

int main()
{
  InventoryManager inventory_manager;
  Cart cart;
  Checkout checkout(tax_rate);

  inventory_manager.load_items("products.csv");

  main_menu();

#if DEBUG
  cart_menu_page();
  cart.add_item(14, 2, inventory_manager);
  cart.add_item(5, 12, inventory_manager);
  cart.add_item(12, 1, inventory_manager);
  cart.add_item(15, 8, inventory_manager);
  display_cart_items(cart.get_cart_items());

  cart.modify_quantity(14, 10);
  cart.remove_item(12);
  display_cart_items(cart.get_cart_items());
#endif

#if DEBUG
  cout << "Checkout debugging" << endl;
  float sub_total = checkout.calculate_sub_total(cart.get_cart_items());
  cout << "Sub_total = " << sub_total << endl;
  cout << "Tax = " << checkout.calculate_tax(sub_total) << endl;
#endif

#if DEBUG
  divider();
  cout << "\t\tInventory Class DEBUGGING" << endl;
  inventory_manager.update_item_quantity(10, 5);
  cout << inventory_manager.get_item_quantity(12) << endl;
  cout << inventory_manager.get_item_price(3) << endl;
  Item item = inventory_manager.get_product(2);
  cout << "Item id: " << item.ID
       << "\tName: " << item.Name
       << "\tPrice: " << item.Price
       << "\tQuantity: " << item.Quantity << endl
       << endl;
  divider();
#endif

  return 0;
}