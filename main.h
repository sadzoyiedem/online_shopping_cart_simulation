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
  void load_items(const std::string &filename);

};

#endif