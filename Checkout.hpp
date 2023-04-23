#ifndef CHECKOUT_HPP
#define CHECKOUT_HPP

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>

#include "Product.hpp"
#include "types.hpp"
#include "Discount.hpp"

class Checkout{
public:
    Checkout(std::vector<Product> products, std::unique_ptr<DiscountForEachProduct> discountForEachProduct={});

    priceInGrosze sumWithDiscount();

    std::string getReceipt();
private:
    std::vector<Product> products;
    std::unique_ptr<DiscountForEachProduct> discountForEachProduct;
    std::string formatStrings(std::string name, std::string calculations);
    priceInGrosze getDiscount();
    std::string getPriceInZloty(priceInGrosze price);
    std::unordered_map<Product, uint32_t> getProductsAndQuantity();
};

#endif
