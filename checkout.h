#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <vector>
#include "Item.h"

class Checkout
{
private:
  float tax_rate;

public:
  Checkout(float t_r) : tax_rate(t_r) {}
  float calculate_sub_total(const std::vector<Item> &cart_items) const;
  float calculate_tax(float sub_total) const { return sub_total * tax_rate; }
  float calculate_delivery_fee(int delivery_time) const;
  float calculate_net_total(float sub_total, float tax, float delivery_fee) const { return sub_total + tax + delivery_fee; }
  void print_out_reciept(const std::vector<Item> &cart_items, float sub_total, float tax, float delivery_fee) const;
};

#endif
