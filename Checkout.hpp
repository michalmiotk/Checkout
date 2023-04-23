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
    grosz sumWithDiscount() const;
    std::string getReceipt() const;
private:
    const std::vector<Product> products;
    const std::unique_ptr<DiscountForEachProduct> discountForEachProduct;
    std::string formatStrings(std::string name, std::string calculations) const;
    grosz getDiscount() const;
    std::string getPriceInZloty(const grosz price) const;
    std::unordered_map<Product, uint32_t> getProductsAndQuantity() const;
};

#endif
