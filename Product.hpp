#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>

#include "types.hpp"

class Product{
public:
    Product(const std::string& name, const grosz price);
    grosz getPrice() const;
    [[nodiscard]] std::string getName() const;
private:
    const std::string name;
    const grosz price;
};

bool operator==(const Product& lhs, const Product& rhs);
#endif
