#include "Cart.h"
#include <iostream>

using namespace std;

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

#if DEBUG
  cout << "Cart.add_item Debugging" << endl;
  cout << product.ID << endl
       << product.Name << endl
       << product.Price << endl
       << product.Quantity << endl;
#endif

  return true;
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