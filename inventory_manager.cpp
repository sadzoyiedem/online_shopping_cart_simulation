#include "InventoryManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Item InventoryManager::get_product(int item_id) const
{
  for (int i = 0; i < products.size(); i++)
  {
    if (products[i].ID == item_id)
      return products[i];
  }

  cout << "Item not found." << endl;
  return {-1, "not found", 0.0, 0};
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
    if (line.empty())
      continue; // skip blank lines

    stringstream ss(line);
    string temp_str;
    Item new_item;

    try
    {
      getline(ss, temp_str, ',');
      new_item.ID = stoi(temp_str);

      getline(ss, new_item.Name, ',');

      getline(ss, temp_str, ',');
      new_item.Price = stof(temp_str);

      getline(ss, temp_str, ',');
      new_item.Quantity = stoi(temp_str);

      products.push_back(new_item);
    }
    catch (const exception &e)
    {
      cerr << "Skipping malformed line: " << line << endl;
      continue;
    }
  }

  file.close();
#if DEBUG
  cout << "Loaded data successfully." << endl;
#endif
}

// reduce the quantity of item in stock when user adds an item to the cart.
bool InventoryManager::update_item_quantity(int item_id, int quantity_taken)
{
  for (int i = 0; i < products.size(); i++)
  {
    if (products[i].ID == item_id)
    {
      if (quantity_taken > products[i].Quantity)
      {
        cout << "Error: not enough stock for item " << item_id << endl;
        return false;
      }
      products[i].Quantity -= quantity_taken;
      cout << "Item " << item_id << " quantity updated.\nNew quantity: " << products[i].Quantity << endl;
      return true;
    }
  }

  cout << "Item with ID " << item_id << " not found." << endl;
  return false;
}