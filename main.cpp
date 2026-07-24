#include <iostream>
#include "main.h"
#include "function.h"
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
  InventoryManager inventory_manager;
  inventory_manager.load_items("products.csv");

#if DEBUG
  divider();
  // Inventory Class
  cout << "\t\tDEBUGGING" << endl;
  inventory_manager.update_item_quantity(30, 5);
  cout << inventory_manager.get_item_quantity(23) << endl;
  cout << inventory_manager.get_item_price(23) << endl;
  Item item = inventory_manager.get_item_struct(23);
  cout << "Item id: " << item.ID
       << "\tName: " << item.Name
       << "\tPrice: " << item.Price
       << "\tQuantity: " << item.Quantity << endl;

  divider();
#endif

  return 0;
}

Item InventoryManager::get_item_struct(int item_id) const
{
  for (int i = 0; i < products.size(); i++)
  {
    if (products[i].ID == item_id)
      return products[i];
  }

  cout << "Item not found." << endl;
}

int InventoryManager::get_item_quantity(int item_id) const
{
  for (int i = 0; i < products.size(); i++)
  {
    if (products[i].ID == item_id)
      return products[i].Quantity;
  }

  return -1;
}

float InventoryManager::get_item_price(int item_id) const
{
  for (int i = 0; i < products.size(); i++)
  {
    if (products[i].ID == item_id)
      return products[i].Price;
  }

  return -1;
}

void InventoryManager::load_items(const string &filename)
{
  ifstream file(filename);
  string line;

  if (!file.is_open())
  {
    cerr << "Error: Could not open the file " << filename << endl;
    return;
  }

  while (getline(file, line))
  {
    stringstream ss(line);
    string temp_str;
    Item new_item;

    // Parse ID
    getline(ss, temp_str, ',');
    new_item.ID = stoi(temp_str);

    // Parse Name
    getline(ss, new_item.Name, ',');

    // Parse Price
    getline(ss, temp_str, ',');
    new_item.Price = stof(temp_str);

    // Parse Quantity
    getline(ss, temp_str, ',');
    new_item.Quantity = stoi(temp_str);

    products.push_back(new_item);
  }

  file.close();
#if DEBUG
  cout << "Loaded data successfully." << endl;
#endif
}

void InventoryManager::update_item_quantity(int item_id, int quantity_taken)
{
  for (int i = 0; i < products.size(); i++)
  {
    if (products[i].ID == item_id)
    {
      products[i].Quantity -= quantity_taken;
      cout << "Item " << item_id << " quantity updated. \nNew quantity: " << products[i].Quantity << endl;
      return;
    }
  }

  cout << "Item with ID " << item_id << " not found." << endl;
}

