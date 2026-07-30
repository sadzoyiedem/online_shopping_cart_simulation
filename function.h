#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <string>
#include "Item.h"
#include "cart.h"
#include "inventory_manager.h"

// Helper functions.
void clear_screen();
void divider();
std::string center_text(const std::string &text, int width);
void table_divider();
bool input_validation(int min, int max, int &user_opt);
void get_item_id(int &product_id);
void get_quantity(int &quant);
void hold_screen();

// menu screens
void main_menu();

void checkout_menu_page();

// program functionalities

#endif
