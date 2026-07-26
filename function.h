#ifndef FUNCTION_H
#define FUNCTION_H

#include "main.h"

// Helper functions.
void clear_screen();
void divider();
void main_menu();
void cart_menu_page();

// program functionalities
void display_all_products(const std::vector<Item> &product);
void display_cart_items(const std::vector<Item> &cart_items);

#endif