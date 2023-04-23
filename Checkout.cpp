#include <algorithm>

#include "Discount.hpp"
#include "Product.hpp"
#include "Checkout.hpp"


template <>
struct std::hash<Product> {
  std::size_t operator()(const Product& product) const{
    return std::hash<string>()(product.getName());
  }
};


Checkout::Checkout(std::vector<Product> products, std::unique_ptr<Discount> discount): products(products),
        discount(std::move(discount)){  
}

grosz Checkout::getSumWithDiscount() const{
    grosz rawSum{};
    std::for_each(products.begin(), products.end(), [&rawSum](auto product){rawSum += product.getPrice();});
    return rawSum - getDiscount();
}

std::string Checkout::getReceipt() const{
    std::string output;
    const auto productsAndQuantity = getProductsAndQuantity();
    for( const auto& [product, quantity] : productsAndQuantity)
    {
        const auto sum = quantity * product.getPrice();
        const auto name = product.getName();
        const auto calculations = std::to_string(quantity) + "x"+
                    getPriceInZloty(product.getPrice()) + " " + getPriceInZloty(sum);
        output += formatStrings(name, calculations);
        if(discount){
            if(auto discountValue = discount->getDiscount(product, quantity); discountValue > 0){
                output += formatStrings(discount->getName(),  "-"+getPriceInZloty(discountValue));
            }
        }
    }
    output += "------------------------------------------------------------\n";
    output += formatStrings("SUMA PLN", getPriceInZloty(getSumWithDiscount()));
    return output;
}

std::string Checkout::formatStrings(std::string name, std::string calculations) const{
    std::string output;
    const auto totalSigns = 70;
    const int numberOfSpaces = totalSigns - name.size() - calculations.size();
    output += name;
    for(int i=0;i<numberOfSpaces;i++){
        output += " ";
    }
    output += calculations;
    output += "\n";
    return output;
}

grosz Checkout::getDiscount() const{
    grosz discountSum{};
    if(discount){
        const auto productsAndQuantity = getProductsAndQuantity();
        for(const auto& [product, quantity] : productsAndQuantity)
        {
            discountSum += discount->getDiscount(product, quantity);
        }
    }
    return discountSum;
}

std::string Checkout::getPriceInZloty(const grosz price) const{
    return std::to_string(price/100) + "," + std::to_string(price%100);
}

std::unordered_map<Product, uint32_t> Checkout::getProductsAndQuantity() const{
    std::unordered_map<Product, uint32_t> productsAndQuantity;
    for(const auto& product:  products){
        if(productsAndQuantity.count(product) == 1){
            productsAndQuantity[product] = productsAndQuantity[product] + 1;
        }else{
            productsAndQuantity[product] = 1;
        }
    }
    return productsAndQuantity;
}
