#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>

#include "types.hpp"

class Product{
public:
    Product(std::string name, priceInGrosze price);
    priceInGrosze getPrice() const;
    std::string getName() const;
    friend bool operator==(const Product& inProduct, const Product& rhs);
private:
    std::string name;
    uint32_t price;
};

#endif
