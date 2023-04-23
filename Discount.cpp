#include "types.hpp"
#include "Product.hpp"
#include "Discount.hpp"

priceInGrosze ForEachIdenticalThreeProductsTenPercentDiscount::get(const Product& product, uint32_t quantity)
{
    auto quantityQualifiedForDiscount = quantity - (quantity % 3);
    return quantityQualifiedForDiscount * product.getPrice()/10;
}

std::string ForEachIdenticalThreeProductsTenPercentDiscount::name(){
    return "ForEachIdenticalThreeProductsTenPercentDiscount"; 
}


priceInGrosze ProductWithPriceAboveFiftyZlotyTwentyPercentDiscount::get(const Product& product, uint32_t quantity)
{
    if(product.getPrice() <= 50'00){
        return 0;
    }
    return quantity * product.getPrice()/5;
}

std::string ProductWithPriceAboveFiftyZlotyTwentyPercentDiscount::name(){
    return "ProductWithPriceAboveFiftyZlotyTwentyPercentDiscount";
}


priceInGrosze ProductWithNameStartingWithLetterATenPercentDiscount::get(const Product& product, uint32_t quantity)
{
    if(product.getName().size() == 0){
        return 0;
    }

    if(auto letter = product.getName()[0]; letter == 'A' or letter == 'a'){
        return quantity*product.getPrice()/10;
    }

    return 0;
}

std::string ProductWithNameStartingWithLetterATenPercentDiscount::name(){
    return "ProductWithNameStartingWithLetteraTenPercentDiscount";
}
