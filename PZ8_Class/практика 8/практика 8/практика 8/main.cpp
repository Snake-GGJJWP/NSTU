#include"Smartphone.h"
#include"Catalog.h"
#include<iostream>
using namespace std;
Catalog InitializeCatalog() {
    Catalog catalog;
    catalog.addSmartphone("iPhone 12 Pro", 100, Manufacturer::APPLE,
        Color::WHITE, 6, 3, 64, CPU::APPLE, OS::IOS);
    catalog.addSmartphone("iPhone 12 Pro", 102, Manufacturer::APPLE,
        Color::WHITE, 6, 3, 128, CPU::APPLE, OS::IOS);
    catalog.addSmartphone("iPhone 12 Pro", 98, Manufacturer::APPLE,
        Color::BLUE, 6, 3, 64, CPU::APPLE, OS::IOS);
    return catalog;
}
int main(int argc, char* argv[]) {
    Catalog catalog = InitializeCatalog();
    Smartphone whatBuyerLikes{ "iphone 12 pro", 0, Manufacturer::APPLE,
    Color::WHITE, 0 , 0, 0, CPU::UNDEFINED, OS::UNDEFINED };
    vector<Smartphone> results = catalog.search(whatBuyerLikes);
    if (!results.empty()) {
        cout << "You might like this:" << endl;
        for (Smartphone s : results) {
            cout << s.getModel() << endl;
            cout << "Price: " << s.getPrice() << endl;
            cout << "Display: " << s.getDisplay() << endl;
            cout << s.getRAM() << "Gb RAM, " << s.getStorage() << " GB storage"
                << endl << endl;
        }
    }
    else cout << "Sorry, we have nothing for you.";
    return 0;
}