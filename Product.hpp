#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>

#include "types.hpp"

class Product{
public:
    Product(const std::string& name, const grosz price);
    grosz getPrice() const;
    std::string getName() const;
    friend bool operator==(const Product& inProduct, const Product& rhs);
private:
    const std::string name;
    const grosz price;
};

#endif
