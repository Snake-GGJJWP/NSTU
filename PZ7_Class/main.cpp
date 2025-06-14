#include "Smartphone.hpp"
#include "Catalog.hpp"
#include <iostream>
using namespace std;

Catalog InitializeCatalog() {
    Catalog catalog;

    catalog.addSmartphone("iPhone 12 Pro", -100100, "Apple", "White",
        "6", "3", "64", "Apple", "iOS",
        2020, 3, "2815 mAh", true);

    catalog.addSmartphone("Valid Phone", 1000, "Samsung", "Black",
        "6.2", "8", "128", "Exynos", "Android",
        2023, 3, "4000 mAh", true);

    return catalog;
}

int main() {
    Catalog catalog = InitializeCatalog();

    Smartphone searchTemplate("iPhone 12 Pro", 100, "", "", "", "", "", "", "", 0, 0, "", false);
    Smartphone found = catalog.search(searchTemplate);

    if (found.getModel().empty()) {
        cout << "Sorry, we have nothing for you." << endl;
    }
    else {
        found.print();
    }

    return 0;
}
