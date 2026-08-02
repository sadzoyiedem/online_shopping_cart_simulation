#include "Checkout.h"
#include "function.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

// Column widths
static const int W_ID = 6;
static const int W_NAME = 30;
static const int W_PRICE = 16;
static const int W_QTY = 18;
static const int W_TOTAL_COST = 16;

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

void Checkout::order_summary(const std::vector<Item> &cart_items,
                             float sub_total,
                             float tax,
                             float delivery_fee,
                             Checkout &checkout) const
{
  clear_screen();
  divider();
  cout << center_text("ORDER SUMMARY", 90) << endl;
  divider();

  // Displaying item details
  int table_width = W_ID + W_NAME + W_PRICE + W_QTY + W_TOTAL_COST + 6;

  cout << string(table_width, '-') << endl;
  cout << center_text("Items in Cart", table_width) << endl;

  table_divider();
  cout << "|" << center_text("ID", W_ID)
       << "|" << center_text("Name", W_NAME)
       << "|" << center_text("Price", W_PRICE)
       << "|" << center_text("Quantity", W_QTY)
       << "|" << center_text("Total Cost", W_TOTAL_COST)
       << "|" << endl;
  table_divider();

  cout << fixed << setprecision(2);

  for (const Item &cart_item : cart_items)
  {
    cout << "|" << center_text(to_string(cart_item.ID), W_ID)
         << "|" << " " << left << setw(W_NAME - 1) << cart_item.Name
         << "|" << " GHC" << right << setw(W_PRICE - 3) << cart_item.Price
         << "|" << center_text(to_string(cart_item.Quantity), W_QTY)
         << "|" << " GHC" << right << setw(W_TOTAL_COST - 3) << cart_item.Price * cart_item.Quantity
         << "|" << endl;
  }
  table_divider();
  cout << endl;

  // Displaying calculations (sub total, tax, total cost)
  float net_total = checkout.calculate_net_total(sub_total, tax, delivery_fee);

  cout << "Sub Total: GHC " << sub_total << endl;
  cout << "Tax : GHC " << tax << endl;
  cout << "Delivery fee : GHC " << delivery_fee << endl;
  cout << "Total Cost: GHC " << net_total << endl;

  divider();

  char choice;
  cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover input
  cout << "Place order? \t[Y] Yes\t[N] No" << endl;
  cin >> choice;

  if (choice == 'Y' || choice == 'y')
  {
    divider();
    cout << "Order placed succesffully!" << endl;
    divider();
    hold_screen();
    main_menu(); // todo: never reaches this point of code must check it.
  }
  else 
  {
    checkout_menu_page();
  }
}

void checkout_menu_page()
{
  clear_screen();
  divider();
  cout << center_text("CHECKOUT", 90) << endl;
  divider();

  cout << "What option would you like to explore?"
       << "\n\t1. Set delivery time"
       << "\n\t2. Checkout"
       << "\n\t3. Move to cart menu"
       << "\n\t4. Go Back" << endl;

  divider();
}

bool checkout_menu_page_flow(Cart &cart, InventoryManager &inventory_manager, Checkout &checkout)
{
  int choice;
  int delivery_time_op{};

  cout << "Enter option: ";
  while (input_validation(1, 4, choice))
    ;

  switch (choice)
  {
  case 1: // set delivery time
    display_delivery_time();

    cout << "Enter the delivery time: ";
    while (get_delivery_time(delivery_time_op))
      ;
    checkout.set_del_op(delivery_time_op);
    break;
  case 2: // checkout
  {
    if (checkout.get_deliv_time_op() == 0)
    {
      divider();
      cout << "Set delivery fee before you proceed to checkout." << endl;
      hold_screen();
      return true;
    }

    float sub_total = checkout.calculate_sub_total(cart.get_cart_items());
    float tax = checkout.calculate_tax(sub_total);

    // Delivery fee calulations
    float delivery_fee{};
    if (checkout.get_deliv_time_op() == 1)
      delivery_fee = 15;
    else if (checkout.get_deliv_time_op() == 2)
      delivery_fee = 10;
    else if (checkout.get_deliv_time_op() == 3)
      delivery_fee = 5;

    checkout.order_summary(cart.get_cart_items(), sub_total, tax, delivery_fee, checkout);
    break;
  }
  case 3: // move to cart page
  {
    bool is_running = true;
    while (is_running)
    {
      cart_menu_page();
      is_running = cart_menu_page_flow(cart, inventory_manager, checkout);
    }
    break;
  }
  case 4: // go back to main menu
    main_menu();
    return false;
  }

  return true;
}

void display_delivery_time()
{
  clear_screen();
  divider();
  cout << center_text("DELIVERY TIME AND PRICE", 90) << endl;
  divider();

  cout << "Set delivery time."
       << "\n\t1. 3 days\t- GHC 15.00"
       << "\n\t2. 7 days\t- GHC 10.00"
       << "\n\t3. 14 days\t- GHC 5.00" << endl;

  divider();
}
