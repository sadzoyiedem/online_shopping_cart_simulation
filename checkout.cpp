#include "Checkout.h"
#include <iostream>
#include <iomanip>

using namespace std;

float Checkout::calculate_sub_total(const vector<Item> &cart_items) const
{
  if (cart_items.empty())
    return 0.0f;

  float sub_total{};
  for (const Item &cart_item : cart_items)
  {
    sub_total += (cart_item.Quantity * cart_item.Price);
  }

  return sub_total;
}



