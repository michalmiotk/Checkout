#include <iostream>

#include "Checkout.hpp"
#include "Discount.hpp"

int main(){
    Checkout checkout({{"water", 3'00}, {"butter", 21'00}, 
    {"cigarettes", 210'00}}, std::make_unique<ProductWithPriceAboveFiftyZlotyTwentyPercentDiscount>());
    std::cout<<checkout.getReceipt()<<std::endl;
    return 0;
}