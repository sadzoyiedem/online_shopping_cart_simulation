#ifndef MAIN_H
#define MAIN_H
#include <string>
#include <vector>

#define DEBUG 1

struct Item
{
  int ID;
  std::string Name;
  float Price;
  int Quantity;
};

class InventoryManager
{
private:
  std::vector<Item> products;

public:
  // getters
  Item get_product(int item_id) const;
  int get_item_quantity(int item_id) const;
  float get_item_price(int item_id) const;
  std::vector<Item> get_products() const { return products; }

  void load_items(const std::string &filename);
  // modify quantity of products in stock when a user add an item to the cart.
  bool update_item_quantity(int item_id, int quantity_taken);
};

class Cart
{
private:
  std::vector<Item> cart_items;

public:
  // getter
  int get_item_quantity(int item_id) const;
  std::vector<Item> get_cart_items() const { return cart_items; }

  // class methods
  bool add_item(int item_id, int quantity, InventoryManager &inventory_manager);
  bool remove_item(int item_id);
  bool modify_quantity(int item_id, int new_quant);
};

#endif