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

// PLACEHOLDER: replace with your actual delivery fee logic once defined
// (e.g. flat fee, or tiered by delivery_time in hours/days).
float Checkout::calculate_delivery_fee(int delivery_time) const
{
  if (delivery_time <= 0)
    return 0.0f;

  return 10.0f; // flat placeholder fee
}

// PLACEHOLDER: basic receipt printout — style/format this to match
// your table formatting from Display.cpp once you're ready.
void Checkout::print_out_reciept(const vector<Item> &cart_items, float sub_total, float tax, float delivery_fee) const
{
  cout << fixed << setprecision(2);
  cout << "----- RECEIPT -----" << endl;
  for (const Item &cart_item : cart_items)
  {
    cout << cart_item.Name << " x" << cart_item.Quantity
         << " = GHC" << (cart_item.Price * cart_item.Quantity) << endl;
  }
  cout << "Sub-total: GHC" << sub_total << endl;
  cout << "Tax: GHC" << tax << endl;
  cout << "Delivery: GHC" << delivery_fee << endl;
  cout << "Total: GHC" << calculate_net_total(sub_total, tax, delivery_fee) << endl;
  cout << "--------------------" << endl;
}