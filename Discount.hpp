#ifndef DISCOUNT_H
#define DISCOUNT_H

#include <string>

#include "types.hpp"
#include "Product.hpp"

class DiscountForEachProduct{
public:
    virtual grosze get(const Product& product, uint32_t quantity) const = 0;
    virtual std::string name() const = 0;
};

class ForEachIdenticalThreeProductsTenPercentDiscount: public DiscountForEachProduct{
public:
    grosze get(const Product& product, uint32_t quantity) const  override;
    std::string name() const override;
};

class ProductWithPriceAboveFiftyZlotyTwentyPercentDiscount: public DiscountForEachProduct{
public:
    grosze get(const Product& product, uint32_t quantity) const override;
    std::string name() const override;
};

class ProductWithNameStartingWithLetterATenPercentDiscount: public DiscountForEachProduct{
public:
    grosze get(const Product& product, uint32_t quantity) const override;
    std::string name() const override;
};

#endif
