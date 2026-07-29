#ifndef CART_H
#define CART_H

#include <vector>
#include "Item.h"
#include "inventory_manager.h"

class Cart
{
private:
  std::vector<Item> cart_items;

public:
  // getter
  int get_item_quantity(int item_id) const;
  const std::vector<Item> &get_cart_items() const { return cart_items; }

  // class methods
  bool add_item(int item_id, int quantity, InventoryManager &inventory_manager);
  bool remove_item(int item_id);
  bool modify_quantity(int item_id, int new_quant);
};

#endif