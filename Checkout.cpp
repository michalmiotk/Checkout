#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <unordered_map>

using priceInGrosze = uint32_t;
class Product{
public:
    Product(std::string name, priceInGrosze price): name(name), price(price){
    }

    priceInGrosze getPrice() const{
        return price;
    }

    std::string getName() const{
        return name;
    }

    friend bool operator==(const Product& lhs, const Product& rhs)
    {
        return lhs.getName() == rhs.getName();
    }

private:
    std::string name;
    uint32_t price;
};

namespace std {
template <>
struct hash<Product> {
  auto operator()(const Product &record) const -> size_t {
    return hash<string>()(record.getName());
  }
};
}  

class Checkout{
public:
    Checkout(std::vector<Product> products): products(products){  
    }
    priceInGrosze sum(){
        priceInGrosze rawSum{};
        std::for_each(products.begin(), products.end(), [&rawSum](auto product){rawSum += product.getPrice();});
        return rawSum - getDiscount();
    }

    priceInGrosze getDiscount(){
        priceInGrosze discount{};
        const auto productsAndQuantity = getProductsAndQuantity();
        for( const auto& [product, quantity] : productsAndQuantity)
        {
            auto quantityQualifiedForDiscount = quantity - (quantity % 3);
            discount += quantityQualifiedForDiscount * product.getPrice()/10;
        }
        return discount;
    }

    std::string getReceipt(){
        std::string output;
        const auto productsAndQuantity = getProductsAndQuantity();
        for( const auto& [product, quantity] : productsAndQuantity)
        {
            auto sum = quantity * product.getPrice();
            auto name =  product.getName();
            auto calculations = std::to_string(quantity) + "x"+
                      getPriceInZloty(product.getPrice()) + " " + getPriceInZloty(sum);
            output += formatStrings(name, calculations);
            if(auto discount = getDiscountForEachIdenticalThreeProductsTenPercentDiscount(product, quantity); discount > 0){
                output += formatStrings("DiscountForEachIdenticalThreeProducts",  std::to_string(discount));
            }
        }
        output += "------------------------------------------------------------\n";
        output += formatStrings("SUMA PLN", getPriceInZloty(sum() - getDiscount()));
        //std::cout<<output;
        return output;
    }
private:
    std::string formatStrings(std::string name, std::string calculations){
        std::string output;
        auto total_signs = 50;
        int space_number = total_signs - name.size() - calculations.size();
        output += name;
        for(int i=0;i<space_number;i++){
            output += " ";
        }
        output += calculations;
        output += "\n";
        return output;
    }

    priceInGrosze getDiscountForEachIdenticalThreeProductsTenPercentDiscount(const Product& product, uint32_t quantity)
    {
        auto quantityQualifiedForDiscount = quantity - (quantity % 3);
        return quantityQualifiedForDiscount * product.getPrice()/10;
    }

    std::string getPriceInZloty(priceInGrosze price){
        return std::to_string(price/100) + "," + std::to_string(price%100);
    }

    std::unordered_map<Product, uint32_t> getProductsAndQuantity(){
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
    std::vector<Product> products;
};