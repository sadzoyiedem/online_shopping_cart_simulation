#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <string>
#include "Item.h"

// Helper functions.
void clear_screen();
void divider();
std::string center_text(const std::string &text, int width);
void table_divider();

// menu screens
void main_menu();
void cart_menu_page();

// program functionalities
void display_all_products(const std::vector<Item> &products);
void display_cart_items(const std::vector<Item> &cart_items);

#endif
