#include "Dishwasher.hpp"
#include <iostream>

int main() {

    // 1. „R„€„x„t„p„~„y„u „€„q„Œ„u„{„„„€„r „~„p „ƒ„„„u„{„u
    Dishwasher dw1;  // „x„~„p„‰„u„~„y„‘ „„€ „…„}„€„|„‰„p„~„y„
    Dishwasher dw2("Bosch SMV", 12.5, 45000.0);

    // 2. „P„u„‰„p„„„ „y„~„†„€„‚„}„p„ˆ„y„y
    std::cout << "\n=== Initial Dishwashers ===" << std::endl;
    std::cout << "Dishwasher 1 (default):" << std::endl;
    dw1.print();
    std::cout << "Dishwasher 2 (custom):" << std::endl;
    dw2.print();

    // 3. „R„€„x„t„p„~„y„u „{„€„„y„y
    Dishwasher dw3(dw2);
    std::cout << "\n=== Copied Dishwasher ===" << std::endl;
    std::cout << "Dishwasher 3 (copy of 2):" << std::endl;
    dw3.print();

    // 4. „I„x„}„u„~„u„~„y„u „„€„|„‘
    std::cout << "\n=== Changing the class field ===";
    dw1.interactivelyEditField();
    std::cout << "\nChanged characteristics:\n";
    dw1.print();

    // 5. „R„€„x„t„p„~„y„u „€„q„Œ„u„{„„„€„r „r „t„y„~„p„}„y„‰„u„ƒ„{„€„z „„p„}„‘„„„y
    std::cout << "\n=== Creating Dynamic Dishwashers ===";
    Dishwasher* dw4 = createDishwasher();
    Dishwasher* dw5 = createDishwasher();

    // 6. „P„u„‰„p„„„ „y„~„†„€„‚„}„p„ˆ„y„y „€„q „„„„y„‡ „€„q„Œ„u„{„„„p„‡
    std::cout << "\n=== Dynamic Dishwashers ===" << std::endl;
    if (dw4) {
        std::cout << "Dishwasher 4:" << std::endl;
        dw4->print();
        delete dw4;
    }
    else {
        std::cout << "Dishwasher 4 creation canceled." << std::endl;
    }

    if (dw5) {
        std::cout << "Dishwasher 5:" << std::endl;
        dw5->print();
        delete dw5;
    }
    else {
        std::cout << "Dishwasher 5 creation canceled." << std::endl;
    }

    return 0;
}
