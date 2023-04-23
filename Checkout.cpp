#include <algorithm>

#include "Discount.hpp"
#include "Product.hpp"
#include "Checkout.hpp"

namespace std {
template <>
struct hash<Product> {
  size_t operator()(const Product& product) const{
    return hash<string>()(product.getName());
  }
};
}


Checkout::Checkout(std::vector<Product> products, std::unique_ptr<DiscountForEachProduct> discountForEachProduct): products(products),
        discountForEachProduct(std::move(discountForEachProduct)){  
}

grosze Checkout::sumWithDiscount() const{
    grosze rawSum{};
    std::for_each(products.begin(), products.end(), [&rawSum](auto product){rawSum += product.getPrice();});
    return rawSum - getDiscount();
}

std::string Checkout::getReceipt() const{
    std::string output;
    const auto productsAndQuantity = getProductsAndQuantity();
    for( const auto& [product, quantity] : productsAndQuantity)
    {
        auto sum = quantity * product.getPrice();
        auto name = product.getName();
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

std::string Checkout::formatStrings(std::string name, std::string calculations) const{
    std::string output;
    const auto totalSigns = 60;
    const int numberOfSpaces = totalSigns - name.size() - calculations.size();
    output += name;
    for(int i=0;i<numberOfSpaces;i++){
        output += " ";
    }
    output += calculations;
    output += "\n";
    return output;
}

grosze Checkout::getDiscount() const{
    grosze discount{};
    if(discountForEachProduct){
        const auto productsAndQuantity = getProductsAndQuantity();
        for(const auto& [product, quantity] : productsAndQuantity)
        {
            discount += discountForEachProduct->get(product, quantity);
        }
    }
    return discount;
}

std::string Checkout::getPriceInZloty(const grosze price) const{
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
