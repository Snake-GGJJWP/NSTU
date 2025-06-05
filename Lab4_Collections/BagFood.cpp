#include "BagFood.hpp"

BagFood::BagFood(const std::string& name = "Apple",
    double mass = 1.0,
    double temperature = 20.0,
    double max_temperature = 100.0,
    double min_temperature = 0.0,
    double heat_capacity = 4180.0) :
    Product(name, mass, temperature, max_temperature, min_temperature, heat_capacity)
{}

BagFood::update_state() {
    double temperature = get_temperature();
    double max_temperature = get_max_temperature();
    double min_temperature = get_min_temperature();
    ProductState state = get_state();

    if (temperature > max_temperature) {
        state = ProductState::OVERHEATED;
    }
    else if (temperature < min_temperature) {
        state = ProductState::FROZEN;
    }
    else {
        state = ProductState::NORMAL;
    }
}

BagFood& BagFood::operator+(double energy) {
    if (state != ProductState::NORMAL) {
        return *this; // „N„u„|„Ž„x„‘ „y„x„}„u„~„‘„„„Ž „„„u„}„„u„‚„p„„„…„‚„… „x„p„}„€„‚„€„w„u„~„~„€„s„€ „y„|„y „„u„‚„u„s„‚„u„„„€„s„€ „„‚„€„t„…„{„„„p
    }

    temperature += energy / (mass * heat_capacity);

    if (state != ProductState::NORMAL) {
        update_state();
    }
    return *this;
}