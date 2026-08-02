#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <vector>
#include "Item.h"

// forward declarations
class Cart;             
class InventoryManager; 

class Checkout
{
private:
  float tax_rate;
  int delivery_time_op;

public:
  Checkout(float t_r) : tax_rate(t_r) {}

  void set_del_op(int d_o) { delivery_time_op = d_o; }
  int get_deliv_time_op() { return delivery_time_op; }

  float calculate_tax(float sub_total) const { return sub_total * tax_rate; }
  float calculate_net_total(float sub_total, float tax, float delivery_fee) const { return sub_total + tax + delivery_fee; }

  float calculate_sub_total(const std::vector<Item> &cart_items) const;
  void order_summary(const std::vector<Item> &cart_items, float sub_total, float tax, float delivery_fee, Checkout &checkout) const;
};

void checkout_menu_page();
bool checkout_menu_page_flow(Cart &cart, InventoryManager &inventory_manager, Checkout &checkout);
void display_delivery_time();

#endif