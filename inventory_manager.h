#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include <string>
#include <vector>
#include "Item.h"

class InventoryManager
{
private:
  std::vector<Item> products;

public:
  // getters
  Item get_product(int item_id) const;
  int get_item_quantity(int item_id) const;
  float get_item_price(int item_id) const;
  const std::vector<Item> &get_products() const { return products; }

  void load_items(const std::string &filename);
  // modify quantity of products in stock when a user adds an item to the cart.
  bool update_item_quantity(int item_id, int quantity_taken);
};

#endif