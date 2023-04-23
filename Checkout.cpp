#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <memory>

#include "Discount.hpp"
#include "Product.hpp"
#include "Checkout.hpp"

namespace std {
template <>
struct hash<Product> {
  auto operator()(const Product &record) const -> size_t {
    return hash<string>()(record.getName());
  }
};
}


Checkout::Checkout(std::vector<Product> products, std::unique_ptr<DiscountForEachProduct> discountForEachProduct): products(products),
        discountForEachProduct(std::move(discountForEachProduct)){  
}

priceInGrosze Checkout::sumWithDiscount(){
    priceInGrosze rawSum{};
    std::for_each(products.begin(), products.end(), [&rawSum](auto product){rawSum += product.getPrice();});
    return rawSum - getDiscount();
}

std::string Checkout::getReceipt(){
    std::string output;
    const auto productsAndQuantity = getProductsAndQuantity();
    for( const auto& [product, quantity] : productsAndQuantity)
    {
        auto sum = quantity * product.getPrice();
        auto name =  product.getName();
        auto calculations = std::to_string(quantity) + "x"+
                    getPriceInZloty(product.getPrice()) + " " + getPriceInZloty(sum);
        output += formatStrings(name, calculations);
        if(discountForEachProduct){
            if(auto discount = discountForEachProduct->get(product, quantity); discount > 0){
                output += formatStrings(discountForEachProduct->name(),  getPriceInZloty(discount));
            }
        }
    }
    output += "------------------------------------------------------------\n";
    output += formatStrings("SUMA PLN", getPriceInZloty(sumWithDiscount()));
    return output;
}

std::string Checkout::formatStrings(std::string name, std::string calculations){
    std::string output;
    auto total_signs = 60;
    int space_number = total_signs - name.size() - calculations.size();
    output += name;
    for(int i=0;i<space_number;i++){
        output += " ";
    }
    output += calculations;
    output += "\n";
    return output;
}

priceInGrosze Checkout::getDiscount(){
    priceInGrosze discount{};
    const auto productsAndQuantity = getProductsAndQuantity();
    if(discountForEachProduct){
        for( const auto& [product, quantity] : productsAndQuantity)
        {
            discount += discountForEachProduct->get(product, quantity);
        }
    }
    return discount;
}

std::string Checkout::getPriceInZloty(priceInGrosze price){
    return std::to_string(price/100) + "," + std::to_string(price%100);
}

std::unordered_map<Product, uint32_t> Checkout::getProductsAndQuantity(){
    std::unordered_map<Product, uint32_t> productsAndQuantity;
    for(auto product:  products){
        if(productsAndQuantity.count(product) == 1){
            productsAndQuantity[product] = productsAndQuantity[product] + 1;
        }else{
            productsAndQuantity[product] = 1;
        }
    }
    return productsAndQuantity;
}
