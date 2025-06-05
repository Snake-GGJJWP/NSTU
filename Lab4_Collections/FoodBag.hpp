#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include "product.h"

class FoodBag {
private:
	double maxMass;
	double mass;
	double sumEnergy;
	std::unordered_map<std::string, Product> food;
public:
	FoodBag(double maxMass = 40.0);
	
	// Getters
	double getMaxMass();
	double getCurMass();
	double getSumEnergy();

	// Put a single product and assign a key 'label' to it
	bool put(const std::string& label, Product&& product);
	// Get and remove a product with key 'label'
	Product fetch(const std::string& label);
	// Get amount of products in the bag
	unsigned short amount();
	// Get amount of spoiled products in the bag
	unsigned short spoiled();
	// Get amount of spoiled products in the bag if put 'products' in it
	unsigned short spoiledIfPut(std::vector<Product>& products);
};