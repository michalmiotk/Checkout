#ifndef DISCOUNT_H
#define DISCOUNT_H

#include <string>

#include "types.hpp"
#include "Product.hpp"

class Discount{
public:
    virtual grosz getDiscount(const Product& product, uint32_t quantity) const = 0;
    virtual std::string getName() const = 0;
};

class ForEachIdenticalThreeProductsTenPercentDiscount: public Discount{
public:
    [[nodiscard]] grosz getDiscount(const Product& product, uint32_t quantity) const  override;
    std::string getName() const override;
};

class ProductWithPriceAboveFiftyZlotyTwentyPercentDiscount: public Discount{
public:
    [[nodiscard]] grosz getDiscount(const Product& product, uint32_t quantity) const override;
    std::string getName() const override;
};

class ProductWithNameStartingWithLetterATenPercentDiscount: public Discount{
public:
    [[nodiscard]] grosz getDiscount(const Product& product, uint32_t quantity) const override;
    std::string getName() const override;
};

#endif
