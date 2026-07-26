// main.cpp
#include <iostream>
#include "function.h"
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
  // Creating objects on program startup
  InventoryManager inventory_manager;
  Cart cart;

  inventory_manager.load_items("products.csv");

  main_menu();
  // display_all_products(inventory_manager.get_products());

#if DEBUG
  // Cart debugging
  cart_menu_page();
  cart.add_item(14, 2, inventory_manager);
  cart.add_item(5, 12, inventory_manager);
  cart.add_item(12, 1, inventory_manager);
  cart.add_item(15, 8, inventory_manager);
  display_cart_items(cart.get_cart_items());

  cart.modify_quantity(14, 10);

  // remove and item
  cart.remove_item(12);
  display_cart_items(cart.get_cart_items());
  // cout << cart.get_item_quantity(14) << endl;
#endif

#if DEBUG
  divider();
  // Inventory Class
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

// reduce the quantity of item in stock when user adds and item to the cart.
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

int Cart::get_item_quantity(int item_id) const
{
  for (const Item &cart_item : cart_items)
  {
    if (cart_item.ID == item_id)
      return cart_item.Quantity;
  }

  return 0;
}

bool Cart::add_item(int item_id, int quantity, InventoryManager &inventory_manager)
{
  Item product = inventory_manager.get_product(item_id);

  if (product.ID == -1)
    return false;

  if (quantity <= 0 || quantity > product.Quantity)
    return false;

  for (Item &cart_item : cart_items)
  {
    if (cart_item.ID == item_id)
    {
      cart_item.Quantity += quantity; // merge instead of duplicating
      return true;
    }
  }

  product.Quantity = quantity;
  cart_items.push_back(product);

  return true;

#if DEBUG
  cout << "Cart.add_item Debugging" << endl;
  cout << product.ID << endl
       << product.Name << endl
       << product.Price << endl
       << product.Quantity << endl;
#endif
}

bool Cart::remove_item(int item_id)
{
  for (int i = 0; i < cart_items.size(); i++)
  {
    if (cart_items[i].ID == item_id)
    {
      cart_items.erase(cart_items.begin() + i);
      return true;
    }
  }
  return false;
}

bool Cart::modify_quantity(int item_id, int new_quant)
{
  if (new_quant <= 0)
    return false;

  for (Item &cart_item : cart_items)
  {
    if (cart_item.ID == item_id)
    {
      cart_item.Quantity = new_quant;
      return true;
    }
  }
  return false; // item wasn't in the cart
} 
