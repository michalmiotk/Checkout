#include "Product.hpp"

Product::Product(const std::string& name, const grosze price): name(name), price(price){}

grosze Product::getPrice() const{
    return price;
}

std::string Product::getName() const{
    return name;
}

bool operator==(const Product& lhs, const Product& rhs)
{
    return lhs.name == rhs.name and lhs.price == rhs.price;
}
