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

  // Inline methods. 
  float calculate_tax(float sub_total) const { return sub_total * tax_rate; }
  float calculate_net_total(float sub_total, float tax, float delivery_fee) const { return sub_total + tax + delivery_fee; }
  
  float calculate_delivery_fee(int delivery_time) const; // Will implement the logic when working of the final stage. 
  float calculate_sub_total(const std::vector<Item> &cart_items) const;
  void print_out_reciept(const std::vector<Item> &cart_items, float sub_total, float tax, float delivery_fee) const;
};

#endif
