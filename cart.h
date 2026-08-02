#ifndef CART_H
#define CART_H

#include <vector>
#include <iostream>
#include "Item.h"
#include "inventory_manager.h"

class Checkout; // forward declaration — no full include needed here

class Cart
{
private:
  std::vector<Item> cart_items;

public:
  int get_item_quantity(int item_id) const;
  const std::vector<Item> &get_cart_items() const { return cart_items; }

  bool add_item(int item_id, int quantity, InventoryManager &inventory_manager);
  bool remove_item(int item_id);
  bool modify_quantity(int item_id, int new_quant);
  void clear_cart()
  {
    cart_items.clear();
    std::cout << "Cleared cart items" << std::endl;
  }
};

// functions
void cart_menu_page();
void display_cart_items(const std::vector<Item> &cart_items);
bool cart_menu_page_flow(Cart &cart, InventoryManager &inventory_manager, Checkout &checkout);

#endif