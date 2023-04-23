#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <memory>


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

class DiscountForEachProduct{
public:
    virtual priceInGrosze get(const Product& product, uint32_t quantity) = 0;
    virtual std::string name() = 0;
};

class ForEachIdenticalThreeProductsTenPercentDiscount: public DiscountForEachProduct{
public:
    priceInGrosze get(const Product& product, uint32_t quantity) override
    {
        auto quantityQualifiedForDiscount = quantity - (quantity % 3);
        return quantityQualifiedForDiscount * product.getPrice()/10;
    }

    std::string name() override{
        return "ForEachIdenticalThreeProductsTenPercentDiscount"; 
    }
};

class ProductWithPriceAboveFiftyZlotyTwentyPercentDiscount: public DiscountForEachProduct{
public:
    priceInGrosze get(const Product& product, uint32_t quantity) override
    {
        if(product.getPrice() <= 50'00){
            return 0;
        }
        return quantity * product.getPrice()/5;
    }

    std::string name() override{
        return "ProductWithPriceAboveFiftyZlotyTwentyPercentDiscount";
    }
};


class ProductWithNameStartingWithLetterATenPercentDiscount: public DiscountForEachProduct{
public:
    priceInGrosze get(const Product& product, uint32_t quantity) override
    {
        return 40;
    }

    std::string name() override{
        return "ProductWithNameStartingWithLetterATenPercentDiscount";
    }
};


class Checkout{
public:
    Checkout(std::vector<Product> products, std::unique_ptr<DiscountForEachProduct> discountForEachProduct): products(products),
        discountForEachProduct(std::move(discountForEachProduct)){  
    }

    priceInGrosze sumWithDiscount(){
        priceInGrosze rawSum{};
        std::for_each(products.begin(), products.end(), [&rawSum](auto product){rawSum += product.getPrice();});
        return rawSum - getDiscount();
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
private:
    std::vector<Product> products;
    std::unique_ptr<DiscountForEachProduct> discountForEachProduct;

    std::string formatStrings(std::string name, std::string calculations){
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

    priceInGrosze getDiscount(){
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
};