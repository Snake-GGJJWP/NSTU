#include "product.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>

Product::Product(const std::string& name, double mass, double temperature, double max_temperature, double min_temperature, double heat_capacity) :
    name(name),
    mass(mass),
    temperature(temperature),
    max_temperature(max_temperature),
    min_temperature(min_temperature),
    heat_capacity(heat_capacity),
    state(ProductState::NORMAL)
{
    if (mass <= 0) {
        throw std::invalid_argument("Mass must be positive.");
    }
    if (heat_capacity <= 0) {
        throw std::invalid_argument("Heat capacity must be positive.");
    }
    if (min_temperature > max_temperature) {
        throw std::invalid_argument ("Min temperature cannot be greater than max temperature.");
    }

    if (temperature < min_temperature || temperature > max_temperature) {
        throw std::invalid_argument ("Initial temperature is out of range.");
    }

  

    update_state();
}

std::string Product::get_name() const {
    return name;
}

double Product::get_mass() const {
    return mass;
}

double Product::get_temperature() const {
    return temperature;
}

double Product::get_max_temperature() const {
    return max_temperature;
}

double Product::get_min_temperature() const {
    return min_temperature;
}

ProductState Product::get_state() const {
    return state;
}

double Product::get_heat_capacity() const {
    return heat_capacity;
}

double Product::calculate_temperature_change(double energy) const {
    double new_temperature = temperature + energy / (mass * heat_capacity);
    return new_temperature;
}

void Product::update_state() {
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

void Product::print(std::ostream& os) const {
    os << std::fixed << std::setprecision(2);
    os << "Name: " << name << std::endl;
    os << "Mass: " << mass << " kg" << std::endl;
    os << "Temperature: " << temperature << " C" << std::endl;
    os << "Max Temperature: " << max_temperature << " C" << std::endl;
    os << "Min Temperature: " << min_temperature << " C" << std::endl;
    os << "Heat Capacity: " << heat_capacity << " J/(kg*C)" << std::endl;

    os << "State: ";
    switch (state) {
    case ProductState::NORMAL:
        os << "Normal";
        break;
    case ProductState::OVERHEATED:
        os << "Overheated";
        break;
    case ProductState::FROZEN:
        os << "Frozen";
        break;
    }
    os << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Product& product) {
    product.print(os);
    return os;
}

Product& Product::operator+(double energy) {
    if (state != ProductState::NORMAL) {
        return *this; // Нельзя изменять температуру замороженного или перегретого продукта
    }

    temperature += energy / (mass * heat_capacity);

    update_state();
    return *this;
}
