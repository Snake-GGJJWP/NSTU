#include "Smartphone.h"

Smartphone::Smartphone() : model(""), price(0) {}

Smartphone::Smartphone(string model, double price, const Specifications& specs)
    : model(model), price(price), specs(specs) {}

string Smartphone::getModel() const { return model; }
double Smartphone::getPrice() const { return price; }
const Specifications& Smartphone::getSpecs() const { return specs; }

void Smartphone::setPrice(double price) { this->price = price; }
void Smartphone::setSpecs(const Specifications& newSpecs) { specs = newSpecs; }