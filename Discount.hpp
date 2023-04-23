#ifndef DISCOUNT_H
#define DISCOUNT_H

#include <string>

#include "types.hpp"
#include "Product.hpp"

class DiscountForEachProduct{
public:
    virtual priceInGrosze get(const Product& product, uint32_t quantity) = 0;
    virtual std::string name() = 0;
};

class ForEachIdenticalThreeProductsTenPercentDiscount: public DiscountForEachProduct{
public:
    priceInGrosze get(const Product& product, uint32_t quantity) override;
    std::string name() override;
};

class ProductWithPriceAboveFiftyZlotyTwentyPercentDiscount: public DiscountForEachProduct{
public:
    priceInGrosze get(const Product& product, uint32_t quantity) override;
    std::string name() override;
};

class ProductWithNameStartingWithLetterATenPercentDiscount: public DiscountForEachProduct{
public:
    priceInGrosze get(const Product& product, uint32_t quantity) override;
    std::string name() override;
};

#endif
