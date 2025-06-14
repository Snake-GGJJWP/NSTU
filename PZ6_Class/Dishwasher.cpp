#include "Dishwasher.hpp"
#include <iostream>
#include <limits>

void Dishwasher::init(const std::string& mdl, double wc, double pr) {
    if (mdl.empty()) {
        throw std::invalid_argument("Model name cannot be empty");
    }
    if (wc <= 0 || wc > 100.0) {
        throw std::invalid_argument("Water consumption must be between 0 and 100 liters");
    }
    if (pr <= 0) {
        throw std::invalid_argument("Price must be positive");
    }

}

Dishwasher::Dishwasher(const std::string& mdl, double wc, double pr) {
    init(mdl, wc, pr);
    model = mdl;
    water_consumption = wc;
    price = pr;
}

Dishwasher::Dishwasher(const Dishwasher& other)
    : model(other.model),
    water_consumption(other.water_consumption),
    price(other.price) {}

void Dishwasher::print() const {
    std::cout << "Dishwasher Model: " << model << std::endl;
    std::cout << "Water Consumption: " << water_consumption << " liters" << std::endl;
    std::cout << "Price: " << price << " rubles" << std::endl;
}

void Dishwasher::rename(const std::string& new_model) {
    init(new_model, water_consumption, price); // „P„‚„€„r„u„‚„{„p „‰„u„‚„u„x init
    model = new_model;
}

void Dishwasher::setWaterConsumption(double new_consumption) {
    init(model, new_consumption, price); // „P„‚„€„r„u„‚„{„p „‰„u„‚„u„x init
    water_consumption = new_consumption;
}

void Dishwasher::setPrice(double new_price) {
    init(model, water_consumption, new_price); // „P„‚„€„r„u„‚„{„p „‰„u„‚„u„x init
    price = new_price;
}

void Dishwasher::interactivelyEditField() {
    int choice;

    while (true) {
        std::cout << "\nCurrent characteristics (dishwasher 1):\n";
        print();

        std::cout << "\nSelect the field to edit:\n"
            << "1. model\n"
            << "2. water_consumption\n"
            << "3. Price\n"
            << "0. Exit\n"
            << "Your choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input error. Please enter the number.\n";
            continue;
        }
        std::cin.ignore();

        try {
            switch (choice) {
            case 1: {
                std::string new_model;
                std::cout << "Enter a new model: ";
                std::getline(std::cin, new_model);
                rename(new_model);
                break;
            }
            case 2: {
                double new_wc;
                std::cout << "Enter a new water consumption: ";
                std::cin >> new_wc;
                setWaterConsumption(new_wc);
                break;
            }
            case 3: {
                double new_price;
                std::cout << "Enter a new price: ";
                std::cin >> new_price;
                setPrice(new_price);
                break;
            }
            case 0:
                return;
            default:
                std::cout << "Invalid menu option.\n";
                continue;
            }

        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\nTry again\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
Dishwasher* createDishwasher() {
    std::string model;
    double wc, pr;
    std::string input;

    while (true) {
        std::cout << "\nEnter dishwasher details (or 'exit' to to cancel the creation of an object):" << std::endl;

        // „B„r„€„t „}„€„t„u„|„y
        std::cout << "Model: ";
        while (true) {
            std::getline(std::cin, model);

            if (model == "exit") {
                return nullptr;
            }

            if (model.empty()) {
                std::cout << "Invalid input. Please enter non-empty value: ";
                continue;  // „P„‚„€„„…„ƒ„{„p„u„} „€„ƒ„„„p„r„Š„…„„ƒ„‘ „‰„p„ƒ„„„Ž „ˆ„y„{„|„p „y „x„p„„‚„p„Š„y„r„p„u„} „r„r„€„t „ƒ„~„€„r„p
            }

            break;  // „E„ƒ„|„y „t„€„Š„|„y „ƒ„„t„p, „x„~„p„‰„y„„ „r„r„€„t „{„€„‚„‚„u„{„„„u„~ - „r„„‡„€„t„y„} „y„x „ˆ„y„{„|„p
        }

        // „B„r„€„t „‚„p„ƒ„‡„€„t„p „r„€„t„
        std::cout << "Water consumption (1-100 liters): ";
        while (true) {
            std::getline(std::cin, input);
            if (input == "exit") {
                return nullptr;
            }

            try {
                wc = std::stod(input);
                if (wc > 0 && wc <= 100.0) break;
                std::cout << "Invalid input. Please enter value between 0 and 100: ";
            }
            catch (...) {
                std::cout << "Invalid input. Please enter a valid number: ";
            }
        }

        // „B„r„€„t „ˆ„u„~„
        std::cout << "Price: ";
        while (true) {
            std::getline(std::cin, input);
            if (input == "exit") {
                return nullptr;
            }

            try {
                pr = std::stod(input);
                if (pr > 0) break;
                std::cout << "Invalid input. Please enter a positive value ";
            }
            catch (...) {
                std::cout << "Invalid input. Please enter a valid number: ";
            }
        }

        // „P„€„„„„„{„p „ƒ„€„x„t„p„~„y„‘ „€„q„Œ„u„{„„„p
        try {
            return new Dishwasher(model, wc, pr);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            std::cout << "Please try again." << std::endl;
        }
    }
}
