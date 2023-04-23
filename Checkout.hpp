#ifndef CHECKOUT_HPP
#define CHECKOUT_HPP

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>

#include "types.hpp"

class Discount;
class Product;


class Checkout{
public:
    Checkout(std::vector<Product> products, std::unique_ptr<Discount> discountForEachProduct={});
    [[nodiscard]] grosz getSumWithDiscount() const;
    [[nodiscard]] std::string getReceipt() const;
private:
    const std::vector<Product> products;
    const std::unique_ptr<Discount> discount;
    std::string formatStrings(std::string name, std::string calculations) const;
    grosz getDiscount() const;
    std::string getPriceInZloty(const grosz price) const;
    std::unordered_map<Product, uint32_t> getProductsAndQuantity() const;
};



#endif
