#pragma once
#include <stdexcept>
#include <map>
#include <string>

class Price {
private:
    double amount;
    static const std::map<std::string, double> exchangeRates;

    void validatePrice(double price) {
        if (price < 0) {
            throw std::invalid_argument("Price can't be neggative");
        }
    }

public:
    Price(double usdAmount = 0) {
        validatePrice(usdAmount);
        this->amount = usdAmount;
    }

    double getAmount(const std::string& currency = "USD") const {
        if (currency == "USD") {
            return amount;
        }
        auto it = exchangeRates.find(currency);
        if (it == exchangeRates.end()) {
            throw std::invalid_argument("Invalid currency");
        }
        return amount * it->second;
    }

    void setAmount(double usdAmount) {
        validatePrice(usdAmount);
        this->amount = usdAmount;
    }

    std::string toString(const std::string& currency = "USD") const {
        if (currency == "USD") {
            return std::to_string(amount) + "  USD";
        }
        double converted = getAmount(currency);
        if (currency == "EUR") {
            return std::to_string(converted) + "  EUR";
        }
        else if (currency == "RUB") {
            return std::to_string(converted) + "  RUB";
        }
        return std::to_string(converted) + " " + currency;
    }
};
