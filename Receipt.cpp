#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <unordered_map>



class Product{
public:
    Product(std::string name, uint32_t price): name(name), price(price){
    }

    uint32_t getPrice() const{
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

class Receipt{
public:    
    uint32_t sum(){
        uint32_t rawSum{};
        std::for_each(products.begin(), products.end(), [&rawSum](auto product){rawSum += product.getPrice();});
        return rawSum - getDiscount();
    }

    uint32_t getDiscount(){
        std::unordered_map<Product, uint32_t> productsAndQuantity;
        uint32_t discount{};
        for(auto product:  products){
            if(productsAndQuantity.count(product) == 1){
                productsAndQuantity[product] = productsAndQuantity[product] + 1;
            }else{
                productsAndQuantity[product] = 1;
            }
            
        }

        for( const auto& [key, value] : productsAndQuantity)
        {
            auto discountProductQuantity = value - (value % 3);
            discount += discountProductQuantity * key.getPrice()/10;
        }
        return discount;
    }

    void addProduct(const Product& product){
        products.push_back(product);
    }
private:
    std::vector<Product> products;
};