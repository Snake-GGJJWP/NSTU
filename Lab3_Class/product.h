#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>

enum class ProductState {
    NORMAL,
    OVERHEATED,
    FROZEN
};

class Product {
private:
    std::string name;
    double mass;
    double temperature;
    double max_temperature;
    double min_temperature;
    ProductState state;
    double heat_capacity;
    void update_state();

public:
    // Конструктор по умолчанию
    Product(const std::string& name = "Apple",
        double mass = 1.0,
        double temperature = 20.0,
        double max_temperature = 100.0,
        double min_temperature = 0.0,
        double heat_capacity = 4180.0);

    // Деструктор
    ~Product() = default;
    
    // Геттеры
    std::string get_name() const;
    double get_mass() const;
    double get_temperature() const;
    double get_max_temperature() const;
    double get_min_temperature() const;
    ProductState get_state() const;
    double get_heat_capacity() const;

    // Метод для расчета изменения температуры (без изменения состояния) и возврата результата
    double calculate_temperature_change(double energy) const;

    // Метод для вывода информации о продукте
    void print(std::ostream& os) const;

    // Дружественный оператор для вывода в поток
    friend std::ostream& operator<<(std::ostream& os, const Product& product);

    // Перегруженный оператор + для передачи тепловой энергии
    Product& operator+(double energy);

};

#endif


