#include <stdexcept>
#include <format>
#include "FoodBag.hpp"

FoodBag::FoodBag(double maxMass) :
	maxMass{ maxMass },
	mass{ 0 },
	sumEnergy{ 0 }
{
	if (this->maxMass <= 0) {
		throw std::invalid_argument("Max mass must be positive");
	}
}


double FoodBag::getMaxMass() {
	return maxMass;
}
double FoodBag::getCurMass() {
	return mass;
}
double FoodBag::getSumEnergy() {
	return sumEnergy;
}

// Put a single product and assign a key 'label' to it
bool FoodBag::put(const std::string& label, Product&& product) {
	if (food.find(label) != food.end()) {
		throw std::invalid_argument(std::format("There is a product labeled %s in the bag already", label));
	}
	if (product.get_state() != ProductState::NORMAL) {
		throw std::invalid_argument("Product have to be in normal state to be put in the bag");
	}
	if (product.get_mass() + mass > maxMass) {
		throw std::invalid_argument(std::format("Product can't be put due to overweight: %d", maxMass - mass));
	}

	food.insert({ label, product });

	double m = product.get_mass();
	double t = product.get_temperature() + 273; // convert to Kelvin
	double c = product.get_heat_capacity();

	mass += m;

	sumEnergy += m * t * c;
	double avgEnergy = sumEnergy / food.size();

	for (auto i : food) {
		m = i.second.get_mass();
		t = i.second.get_temperature() + 273; // convert to Kelvin
		c = i.second.get_heat_capacity();
		int energy = m * t * c;

		i.second + (avgEnergy - energy); // heating/freezing the product
	}
}
// Get and remove a product with key 'label'
Product FoodBag::fetch(const std::string& label) {
	if (food.find(label) == food.end()) {
		throw std::invalid_argument(std::format("There is no product labeled %s in the bag", label));
	}

	Product product = food.at(label);
	food.erase(label);

	double m = product.get_mass();
	double t = product.get_temperature() + 273; // convert to Kelvin
	double c = product.get_heat_capacity();

	sumEnergy -= m * t * c;
	mass -= m;

	return product;
}
// Get count of products in the bag
unsigned short FoodBag::amount() {
	return food.size();
}
// Get count of spoiled products in the bag
unsigned short FoodBag::spoiled() {
	unsigned short count = 0;
	for (auto i : food) {
		if (i.second.get_state() != ProductState::NORMAL) {
			count++;
		}
	}
	return count;
}
// Get count of spoiled products in the bag if put 'products' in it
unsigned short FoodBag::spoiledIfPut(std::vector<Product>& products) {
	if (products.empty()) return 0;

	unsigned short spoiledBefore = spoiled();
	unsigned short count = 0;
	double deltaEnergy = 0;
	for (auto product : products) {
		double m = product.get_mass();
		double t = product.get_temperature() + 273; // convert to Kelvin
		double c = product.get_heat_capacity();
		
		deltaEnergy += m * t * c;
	}

	double avgEnergy = (sumEnergy + deltaEnergy) / food.size();
	
	// Count spoiled food in the bag;
	for (auto i : food) {
		double m = i.second.get_mass();
		double t = i.second.get_temperature() + 273; // convert to Kelvin
		double c = i.second.get_heat_capacity();
		double curEnergy = m * t * c;
		double newTemp = i.second.calculate_temperature_change(avgEnergy - curEnergy);
		
		if (newTemp < i.second.get_min_temperature() || newTemp > i.second.get_max_temperature()) {
			count++;
		}
	}

	// Count spoiled food in the list
	for (auto product : products ) {
		double m = product.get_mass();
		double t = product.get_temperature() + 273; // convert to Kelvin
		double c = product.get_heat_capacity();
		double curEnergy = m * t * c;
		double newTemp = product.calculate_temperature_change(avgEnergy - curEnergy);

		if (newTemp < product.get_min_temperature() || newTemp > product.get_max_temperature()) {
			count++;
		}
	}

	return count - spoiledBefore; // count only newest spoiled food
}