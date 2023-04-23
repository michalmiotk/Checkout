#include "Product.hpp"

Product::Product(const std::string& name, const grosz price): name(name), price(price){}

grosz Product::getPrice() const{
    return price;
}

std::string Product::getName() const{
    return name;
}

bool operator==(const Product& lhs, const Product& rhs)
{
    return lhs.getName() == rhs.getName() and lhs.getPrice() == rhs.getPrice();
}
