#include "Product.hpp"

Product::Product(std::string name, priceInGrosze price): name(name), price(price){}

priceInGrosze Product::getPrice() const{
    return price;
}

std::string Product::getName() const{
    return name;
}

bool operator==(const Product& lhs, const Product& rhs)
{
    return lhs.getName() == rhs.getName();
}
