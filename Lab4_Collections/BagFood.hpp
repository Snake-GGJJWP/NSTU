#pragma once
#include "product.h"

class BagFood : public Product {
    BagFood(const std::string& name = "Apple",
        double mass = 1.0,
        double temperature = 20.0,
        double max_temperature = 100.0,
        double min_temperature = 0.0,
        double heat_capacity = 4180.0);

    BagFood& operator+(double energy);
};