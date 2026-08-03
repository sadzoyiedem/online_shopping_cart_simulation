#include "inventory_manager.h"
#include "function.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// Column widths
static const int W_ID = 6;
static const int W_NAME = 30;
static const int W_PRICE = 16;
static const int W_QTY = 18;

void display_all_products(const vector<Item> &products)
{
  clear_screen();

  int table_width = W_ID + W_NAME + W_PRICE + W_QTY + 5;

  cout << string(table_width, '-') << endl;
  cout << center_text("Products Catalog", table_width) << endl;

  table_divider();
  cout << "|" << center_text("ID", W_ID)
       << "|" << center_text("Product Name", W_NAME)
       << "|" << center_text("Product Price", W_PRICE)
       << "|" << center_text("Product Quantity", W_QTY)
       << "|" << endl;
  table_divider();

  cout << fixed << setprecision(2);

  for (const Item &product : products)
  {
    cout << "|" << center_text(to_string(product.ID), W_ID)
         << "|" << " " << left << setw(W_NAME - 1) << product.Name
         << "|" << " GHC" << right << setw(W_PRICE - 3) << product.Price
         << "|" << center_text(to_string(product.Quantity), W_QTY)
         << "|" << endl;
  }
  table_divider();
}

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
bool InventoryManager::decrease_item_quantity(int item_id, int quantity_taken)
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
#if DEBUG
      cout << "Item " << item_id << " quantity updated.\nNew quantity: " << products[i].Quantity << endl;
#endif

      return true;
    }
  }

  cout << "Item with ID " << item_id << " not found." << endl;
  return false;
}
bool InventoryManager::increase_item_quantity(int item_id, int quantity_added)
{
  for (int i = 0; i < products.size(); i++)
  {
    if (products[i].ID == item_id)
    {
      products[i].Quantity += quantity_added;
#if DEBUG
      cout << "Item " << item_id << " quantity updated.\nNew quantity: " << products[i].Quantity << endl;
#endif

      return true;
    }
  }

  cout << "Item with ID " << item_id << " not found." << endl;
  return false;
}