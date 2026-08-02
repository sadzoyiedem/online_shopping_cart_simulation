#include "function.h"
#include "checkout.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Column widths
static const int W_ID = 6;
static const int W_NAME = 30;
static const int W_PRICE = 16;
static const int W_QTY = 18;

void display_cart_items(const vector<Item> &cart_items)
{
  clear_screen();

  if (cart_items.empty())
  {
    divider();
    cout << "Sorry, cart is empty." << endl;
    divider();
    return;
  }

  int table_width = W_ID + W_NAME + W_PRICE + W_QTY + 5;

  cout << string(table_width, '-') << endl;
  cout << center_text("Products in Cart", table_width) << endl;

  table_divider();
  cout << "|" << center_text("ID", W_ID)
       << "|" << center_text("Product Name", W_NAME)
       << "|" << center_text("Product Price", W_PRICE)
       << "|" << center_text("Product Quantity", W_QTY)
       << "|" << endl;
  table_divider();

  cout << fixed << setprecision(2);

  for (const Item &cart_item : cart_items)
  {
    cout << "|" << center_text(to_string(cart_item.ID), W_ID)
         << "|" << " " << left << setw(W_NAME - 1) << cart_item.Name
         << "|" << " GHC" << right << setw(W_PRICE - 3) << cart_item.Price
         << "|" << center_text(to_string(cart_item.Quantity), W_QTY)
         << "|" << endl;
  }
  table_divider();
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

void cart_menu_page()
{
  clear_screen();
  divider();
  cout << center_text("CART", 90) << endl;
  divider();

  cout << "What option would you like to explore?"
       << "\n\t1. Add item"
       << "\n\t2. Remove item"
       << "\n\t3. Modify item quantity"
       << "\n\t4. Display cart items"
       << "\n\t5. Clear cart"
       << "\n\t6. Move to checkout menu"
       << "\n\t7. Go Back" << endl;

  divider();
}

bool cart_menu_page_flow(Cart &cart, InventoryManager &inventory_manager, Checkout &checkout)
{
  int choice;

  cout << "Enter option: ";
  while (input_validation(1, 7, choice))
    ;

  switch (choice)
  {
  case 1: // add item
  {
    display_all_products(inventory_manager.get_products());

    int product_id{}, quantity{};
    cout << "Enter the product ID: ";
    while (get_item_id(product_id))
      ;

    if (inventory_manager.get_item_quantity(product_id) == -1)
    {
      cerr << "Item ID not found." << endl;
      hold_screen();
      break;
    }

    cout << "Enter the quantity: ";
    while (get_quantity(quantity))
      ;

    while (quantity > inventory_manager.get_item_quantity(product_id))
    {
      cout << "Quantity in stock is less than the quantity you need. " << endl;
      cout << "Quantity in stock: " << inventory_manager.get_item_quantity(product_id) << endl;
      cout << "Re-enter quantity: ";
      get_quantity(quantity);
    }

    if (cart.add_item(product_id, quantity, inventory_manager))
    {
      cout << "Added " << inventory_manager.get_product(product_id).Name << " to cart." << endl;
      inventory_manager.decrease_item_quantity(product_id, quantity);
    }
    else
      cerr << "Error!, couldn't add product to cart. Try again" << endl;

    hold_screen();
    break;
  }

  case 2: // remove item
  {
    clear_screen();
    if (cart.get_cart_items().empty())
    {
      cout << "Cart is empty." << endl;
      break;
    }

    int product_id{};
    cout << "Enter product ID:";
    while (get_item_id(product_id))
      ;

    int quantity = cart.get_item_quantity(product_id); // get item to be removed quantity from cart database.

    if (cart.remove_item(product_id))
    {
      inventory_manager.increase_item_quantity(product_id, quantity);
      cout << "Removed " << inventory_manager.get_product(product_id).Name << " from cart." << endl;
    }
    else
      cerr << "Error!, couldn't remove product from cart. Try again" << endl;

    hold_screen();
    break;
  }

  case 3: // modify item quantity
  {
    clear_screen();

    int product_id{}, new_quantity{};

    cout << "Enter product ID: ";
    while (get_item_id(product_id))
      ;

    if (inventory_manager.get_item_quantity(product_id) == -1)
    {
      cerr << "Item ID not found." << endl;
      hold_screen();
      break;
    }

    int old_quantity = cart.get_item_quantity(product_id);
    cout << "Enter new quantity: ";
    while (get_quantity(new_quantity))
      ;

    while (new_quantity > inventory_manager.get_item_quantity(product_id) + old_quantity)
    {
      cout << "Quantity in stock is less than the quantity you need. " << endl;
      cout << "Quantity available: " << inventory_manager.get_item_quantity(product_id) + old_quantity << endl;
      get_quantity(new_quantity);
    }

    if (!cart.modify_quantity(product_id, new_quantity))
      cerr << "Error! Couldn't modify item quantity." << endl;
    else
    {
      if (old_quantity > new_quantity)
        inventory_manager.increase_item_quantity(product_id, old_quantity - new_quantity);
      else if (old_quantity < new_quantity)
        inventory_manager.decrease_item_quantity(product_id, new_quantity - old_quantity);

      cout << "Item quantity modified." << endl;
      cout << "Product " << product_id << " new quantity: " << cart.get_item_quantity(product_id) << endl;
    }

    hold_screen();
    break;
  }

  case 4: // view cart
  {
    clear_screen();
    display_cart_items(cart.get_cart_items());

    hold_screen();
    break;
  }

  case 5: // clear cart
  {
    clear_screen();

    for (const Item &cart_item : cart.get_cart_items())
    {
      inventory_manager.increase_item_quantity(cart_item.ID, cart_item.Quantity);
    }
    cart.clear_cart();

    cout << "Cart cleared." << endl;
    hold_screen();
    break;
  }

  case 6: // move to checkout
  {
    clear_screen();

    if (cart.get_cart_items().empty())
    {
      divider();
      cout << "Cart is empty." << endl;
      divider();
      hold_screen();
    }
    else
    {
      bool is_running = true;
      while (is_running)
      {
        checkout_menu_page();
        is_running = checkout_menu_page_flow(cart, inventory_manager, checkout);
      }
    }
    break;
  }

  case 7: // go back
  {
    main_menu();
    return false;
  }
  }

  return true;
}
