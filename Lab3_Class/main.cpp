#include "product.h"
#include <iostream>

int main() {

    try {

        // ������������� ������� 
        Product apple("Apple", 0.2, 20.0, 30.0, 5.0, 3.85);

        // ����� ��������� ���������� 
        std::cout << "Initial Apple:" << std::endl;
        std::cout << apple << std::endl;

        // ����������
        apple + 100;
        std::cout << "Apple after heating:" << std::endl;
        std::cout << apple << std::endl;

        // ����������
        apple + (-5);
        std::cout << "Apple after cooling:" << std::endl;
        std::cout << apple << std::endl;

        // ������ ��������� ����������� 
        double energy = -5;
        double new_temperature = apple.calculate_temperature_change(energy);

        std::cout << "Calculated temperature change after adding " << energy << " J: " << new_temperature << " C" << std::endl;

    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Initialisation error: " << e.what() << std::endl;
    }
    return 0;
}

