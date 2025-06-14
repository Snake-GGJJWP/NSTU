#ifndef DISHWASHER_H
#define DISHWASHER_H

#include <string>
#include <stdexcept>
#include <iostream>

class Dishwasher {
private:
    std::string model;
    double water_consumption;
    double price;

    void init(const std::string& mdl, double wc, double pr);

public:
    // �K���~���������{��������
    Dishwasher(const std::string& mdl = "LG", double wc = 10.0, double pr = 30000.0);
    Dishwasher(const Dishwasher& other);

    // �M�u�����t��
    void print() const;
    void rename(const std::string& new_model);
    void setWaterConsumption(double new_consumption);
    void setPrice(double new_price);
    void interactivelyEditField();
};

// �U���~�{���y�� �����x�t�p�~�y�� ���q���u�{���p
Dishwasher* createDishwasher();

#endif
