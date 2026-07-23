#include <iostream>
#include "main.h"
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
  InventoryManager inventory_manager;
  inventory_manager.load_items("products.csv");

  return 0;
}

void InventoryManager::load_items(const string & filename)
{
  ifstream file(filename);
  string line;

  if(!file.is_open())
  {
    cerr << "Error: COuld not open the file " << filename << endl;
    return;
  }

  while(getline(file,line))
  {
    stringstream ss(line);
    string temp_str;
    Item new_item;

    //Parse ID 
    getline(ss, temp_str,',');
    new_item.ID = stoi(temp_str);
    
    //Parse Name
    getline(ss, new_item.Name, ',');
    
    // Parse Price
    getline(ss, temp_str,',');
    new_item.Price = stof(temp_str);

    //Parse Quantity
    getline(ss, temp_str,',');
    new_item.Quantity = stoi(temp_str);

    products.push_back(new_item);

  } 

  file.close();
  #if DEBUG
    cout << "Loaded data successfully." << endl;
  #endif
}