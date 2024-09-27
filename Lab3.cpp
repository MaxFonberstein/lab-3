// Max Fonberstein
// Lab 3
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>

// InventoryItem class to represent each car
class InventoryItem {
public:
    int carID;
    std::string model;
    std::string manufacturer;
    int quantity;
    double price;

    // Constructor
    InventoryItem(int id, std::string mod, std::string man, int qty, double prc)
        : carID(id), model(mod), manufacturer(man), quantity(qty), price(prc) {}

    // Display method
    void display() const {
        std::cout << "ID: " << carID 
                  << ", Model: " << model 
                  << ", Manufacturer: " << manufacturer 
                  << ", Quantity: " << quantity 
                  << ", Price: $" << price << std::endl;
    }
};

// Function to convert a string to lowercase for case-insensitive comparison
std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Function to check if a string contains another string (case-insensitive)
bool containsIgnoreCase(const std::string& data, const std::string& search) {
    return toLower(data).find(toLower(search)) != std::string::npos;
}

// Search function to find cars by model or manufacturer (partial, case-insensitive)
void searchByModelOrManufacturer(const std::vector<InventoryItem>& items, const std::string& query) {
    bool found = false;
    for (const auto& item : items) {
        if (containsIgnoreCase(item.model, query) || containsIgnoreCase(item.manufacturer, query)) {
            item.display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No matching cars found for the search query: " << query << std::endl;
    }
}

// Search function to find cars within a price range (±15% of the target price)
void searchByPriceRange(const std::vector<InventoryItem>& items, double targetPrice) {
    double lowerLimit = targetPrice * 0.85;
    double upperLimit = targetPrice * 1.15;
    std::cout << "Searching for cars with prices between $" << lowerLimit << " and $" << upperLimit << std::endl;
    
    bool found = false;
    for (const auto& item : items) {
        if (item.price >= lowerLimit && item.price <= upperLimit) {
            item.display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No cars found in the price range." << std::endl;
    }
}

// Enum class to define sorting keys
enum class SortKey { ID, Model, Manufacturer, Price };

// Bubble sort function to sort cars by the specified field
void sortCars(std::vector<InventoryItem>& items, SortKey key) {
    bool swapped;
    for (size_t i = 0; i < items.size() - 1; i++) {
        swapped = false;
        for (size_t j = 0; j < items.size() - i - 1; j++) {
            bool condition = false;
            switch (key) {
                case SortKey::ID:
                    condition = items[j].carID > items[j + 1].carID;
                    break;
                case SortKey::Model:
                    condition = items[j].model > items[j + 1].model;
                    break;
                case SortKey::Manufacturer:
                    condition = items[j].manufacturer > items[j + 1].manufacturer;
                    break;
                case SortKey::Price:
                    condition = items[j].price > items[j + 1].price;
                    break;
            }
            if (condition) {
                std::swap(items[j], items[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

// Enum for the main menu options
enum class MenuOption { Search = 1, Sort, Exit };

// Enum for the sort menu options
enum class SortOption { ID = 1, Model, Manufacturer, Price };

// Function to display the main menu
void displayMenu() {
    std::cout << "1. Search Cars\n2. Sort Cars\n3. Exit\nChoose an option: ";
}

// Function to display the sort menu
void displaySortMenu() {
    std::cout << "1. Sort by ID\n2. Sort by Model\n3. Sort by Manufacturer\n4. Sort by Price\nChoose a sort key: ";
}

// Function to handle the main menu
void handleMenu(std::vector<InventoryItem>& items) {
    int choice;
    MenuOption option;
    
    do {
        displayMenu();
        std::cin >> choice;
        option = static_cast<MenuOption>(choice);

        switch (option) {
            case MenuOption::Search: {
                int searchChoice;
                std::cout << "1. Search by model/manufacturer\n2. Search by price range\nChoose an option: ";
                std::cin >> searchChoice;
                if (searchChoice == 1) {
                    std::string query;
                    std::cout << "Enter a model or manufacturer to search: ";
                    std::cin >> query;
                    searchByModelOrManufacturer(items, query);
                } else if (searchChoice == 2) {
                    double targetPrice;
                    std::cout << "Enter target price: ";
                    std::cin >> targetPrice;
                    searchByPriceRange(items, targetPrice);
                }
                break;
            }
            case MenuOption::Sort: {
                displaySortMenu();
                std::cin >> choice;
                sortCars(items, static_cast<SortKey>(choice - 1));
                std::cout << "Cars sorted successfully. Displaying sorted list:\n";
                for (const auto& car : items) {
                    car.display();
                }
                break;
            }
            case MenuOption::Exit:
                std::cout << "Exiting...\n";
                break;
        }
    } while (option != MenuOption::Exit);
}

// Main function
int main() {
    std::vector<InventoryItem> cars = {
        {1, "Stroller", "StrollCo", 10, 50000},
        {2, "Rolls", "Rolls Inc", 5, 55000},
        {3, "Camry", "Toyota", 20, 30000},
        {4, "Accord", "Honda", 15, 28000}
    };

    handleMenu(cars);

    return 0;
}
/*
Test runs
1.Enter a model or manufacturer to search: roll
ID: 1, Model: Stroller, Manufacturer: StrollCo, Quantity: 10, Price: $50000
ID: 2, Model: Rolls, Manufacturer: Rolls Inc, Quantity: 5, Price: $55000

2.Enter target price: 50000
Searching for cars with prices between $42500 and $57500
ID: 1, Model: Stroller, Manufacturer: StrollCo, Quantity: 10, Price: $50000
ID: 2, Model: Rolls, Manufacturer: Rolls Inc, Quantity: 5, Price: $55000

3.Enter a model or manufacturer to search: tesla
No matching cars found for the search query: tesla

4.Cars sorted successfully. Displaying sorted list:
ID: 4, Model: Accord, Manufacturer: Honda, Quantity: 15, Price: $28000
ID: 3, Model: Camry, Manufacturer: Toyota, Quantity: 20, Price: $30000
ID: 2, Model: Rolls, Manufacturer: Rolls Inc, Quantity: 5, Price: $55000
ID: 1, Model: Stroller, Manufacturer: StrollCo, Quantity: 10, Price: $50000

5.Cars sorted successfully. Displaying sorted list:
ID: 4, Model: Accord, Manufacturer: Honda, Quantity: 15, Price: $28000
ID: 3, Model: Camry, Manufacturer: Toyota, Quantity: 20, Price: $30000
ID: 1, Model: Stroller, Manufacturer: StrollCo, Quantity: 10, Price: $50000
ID: 2, Model: Rolls, Manufacturer: Rolls Inc, Quantity: 5, Price: $55000

6.Exiting...

*/
