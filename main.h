#ifndef MAIN_H
#define MAIN_H
#include <string>
#include <vector>

#define DEBUG 0

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
  Item get_item_struct(int item_id) const;
  int get_item_quantity(int item_id) const;
  float get_item_price(int item_id) const;
  std::vector<Item> get_products() const { return products; }

  void load_items(const std::string &filename);
  void update_item_quantity(int item_id, int quantity_taken);
};

#endif