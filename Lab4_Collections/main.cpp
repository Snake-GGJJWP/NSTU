#include <iostream>
#include <memory>
#include "FoodBag.hpp"

int main() {
	try {
		std::unique_ptr<FoodBag> bag(new FoodBag(40));
		bag->put("Annie", Product{ "Apple", 0.2, 20.0, 30.0, 5.0, 4200 });
		bag->put("Max", Product{ "Cucumber", 0.4, 20.0, 30.0, 5.0, 4200 });
		bag->put("Alice", Product{ "Tomato", 0.2, 10.0, 30.0, 5.0, 4200 });
		bag->put("Bob", Product{ "Eggplant", 0.2, 25.0, 30.0, 5.0, 4200 });

		std::cout << "Current Mass: " << bag->getCurMass() << std::endl;
		std::cout << "Max Mass: " << bag->getMaxMass() << std::endl;
		std::cout << "Current Energy: " << bag->getSumEnergy() << std::endl;

		std::cout << "Products in the bag: " << bag->amount() << std::endl;
		std::cout << "Products spoiled: " << bag->spoiled() << std::endl;

		std::vector<Product> list;
		list.push_back(Product{"Sun", 1, 4000, 4000, 5, 3.85});
		std::cout << "Number of spoiled, if put >4000C: " << bag->spoiledIfPut(list) << std::endl;
		list.erase(list.begin());
		
		list.push_back(Product{ "Water", 1, 22, 30, -4546, 4200 }); // owo
		std::cout << "Number of spoiled if also put <-4000C: " << bag->spoiledIfPut(list) << std::endl;

		std::cout << "Fetch Annie: " << bag->fetch("Annie");
		std::cout << "Products in the bag: " << bag->amount() << std::endl;
		std::cout << "Products spoiled: " << bag->spoiled() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error occured: " << e.what() << std::endl;
	}

	return 0;
}