#include <cfenv>

#include "types.hpp"
#include "Product.hpp"
#include "Discount.hpp"

grosz ForEachIdenticalThreeProductsTenPercentDiscount::getDiscount(const Product& product, uint32_t quantity) const 
{
    const auto quantityQualifiedForDiscount = quantity - (quantity % 3);
    auto result = (quantityQualifiedForDiscount * product.getPrice())/10;
    const auto moduloResult = (quantityQualifiedForDiscount * product.getPrice())%10;
    if(moduloResult >= 5){
        result++;
    }
    return result;
}

std::string ForEachIdenticalThreeProductsTenPercentDiscount::getName() const {
    return "ForEachIdenticalThreeProductsTenPercentDiscount"; 
}


grosz ProductWithPriceAboveFiftyZlotyTwentyPercentDiscount::getDiscount(const Product& product, uint32_t quantity) const 
{
    if(product.getPrice() <= 50'00){
        return 0;
    }
    return quantity * product.getPrice()/5;
}

std::string ProductWithPriceAboveFiftyZlotyTwentyPercentDiscount::getName() const {
    return "ProductWithPriceAboveFiftyZlotyTwentyPercentDiscount";
}


grosz ProductWithNameStartingWithLetterATenPercentDiscount::getDiscount(const Product& product, uint32_t quantity) const 
{
    if(product.getName().size() == 0){
        return 0;
    }

    if(auto letter = product.getName()[0]; letter == 'A' or letter == 'a'){
        return quantity*product.getPrice()/10;
    }

    return 0;
}

std::string ProductWithNameStartingWithLetterATenPercentDiscount::getName() const {
    return "ProductWithNameStartingWithLetteraTenPercentDiscount";
}
