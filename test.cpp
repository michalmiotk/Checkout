#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Checkout.hpp"
#include "Product.hpp"
#include "Discount.hpp"

using namespace testing;

class TestCheckout : public ::testing::Test
{
public:
    const Product strawberry{"strawberry", 33'00};
    const Product apple{"apple", 4'00};
    const Product watermelon{"watermelon", 10'00};
    const Product banana{"banana", 20'00};
    const Product raspberry{"raspberry", 100'00};
    const Product blueberry{"blueberry", 50'00};
    const Product ananas{"Ananas", 4'00};
    const Product avocado{"avocado", 10'00};
    const Product rice{"rice", 3};
};

TEST_F(TestCheckout, givenCheckoutWithTwoProducts_whengetSumWithDiscountMethodIsCalled_thenExpectSumOfPrices)
{
    const grosz expectedResult = 37'00;
    
    Checkout checkout({strawberry, apple});

    const auto result = checkout.getSumWithDiscount();
    
    EXPECT_EQ(result, expectedResult);
}


TEST_F(TestCheckout, givenCheckoutWithOneProduct_whengetSumWithDiscountMethodIsCalled_thenExpectProductPrice)
{
    const grosz expectedResult = 10'00;
    Checkout checkout({watermelon});

    const auto result = checkout.getSumWithDiscount();
    
    EXPECT_EQ(result, expectedResult);
}

TEST_F(TestCheckout, givenCheckoutWithTwoIdenticalProductsAndDiscountForThreeIdenticalProduct_whensumMethodIsCalled_thenExpectReturnSum){
    const grosz expectedResult = 20'00;
    Checkout checkout({watermelon, watermelon}, std::make_unique<ForEachIdenticalThreeProductsTenPercentDiscount>());

    const auto result = checkout.getSumWithDiscount();

    EXPECT_EQ(result, expectedResult);
}

TEST_F(TestCheckout, givenCheckoutWithThreeIdenticalProductsAndDiscountForEachThreeIdenticalProduct_whensumMethodIsCalled_thenExpectReturnSumWith10PercentOfDiscount){
    const grosz expectedResult = 27'00;
    Checkout checkout({watermelon, watermelon, watermelon}, std::make_unique<ForEachIdenticalThreeProductsTenPercentDiscount>());

    const auto result = checkout.getSumWithDiscount();
    
    EXPECT_EQ(result, expectedResult);
}

TEST_F(TestCheckout, givenCheckoutWithThreeIdenticalCheapProductsAndDiscountForEachThreeIdenticalProduct_whensumMethodIsCalled_thenExpectReturnSumWith10PercentOfDiscount){
    const grosz expectedResult = 8;
    Checkout checkout({rice, rice, rice}, std::make_unique<ForEachIdenticalThreeProductsTenPercentDiscount>());

    const auto result = checkout.getSumWithDiscount();
    
    EXPECT_EQ(result, expectedResult);
}

TEST_F(TestCheckout, givenCheckoutWithTwoIdenticalProductsAndOneWithDifferentPriceAndDiscountForEachThreeIdenticalProduct_whensumMethodIsCalled_thenExpectReturnSum){
    const grosz expectedResult = 21'00;
    Product cheapwatermelon("watermelon", 1'00);
    Checkout checkout({watermelon, watermelon, cheapwatermelon}, std::make_unique<ForEachIdenticalThreeProductsTenPercentDiscount>());

    const auto result = checkout.getSumWithDiscount();

    EXPECT_EQ(result, expectedResult);
}

TEST_F(TestCheckout, givenCheckoutWithSixIdenticalProductsAndDiscountForEachThreeIdenticalProduct_whensumMethodIsCalled_thenExpectReturnSumWith10PercentOfDiscount){
    const grosz expectedResult = 54'00;
    Checkout checkout({watermelon, watermelon, watermelon, watermelon, watermelon, watermelon}, std::make_unique<ForEachIdenticalThreeProductsTenPercentDiscount>());

    const auto result = checkout.getSumWithDiscount();
    
    EXPECT_EQ(result, expectedResult);
}

TEST_F(TestCheckout, givenCheckoutWithSixIdenticalProductsInTwoCategoriesAndDiscount_whensumMethodIsCalled_thenExpectReturnSumWith10PercentOfDiscount){
    const grosz expectedResult = 81'00;
    Checkout checkout({watermelon, watermelon, watermelon, banana, banana, banana}, std::make_unique<ForEachIdenticalThreeProductsTenPercentDiscount>());

    const auto result = checkout.getSumWithDiscount();
    
    EXPECT_EQ(result, expectedResult);
}

TEST_F(TestCheckout, giventCheckoutWithThreeIdenticalProductsAndDiscount_whengetReceiptMethodIsCalled_thenExpectNonEmptyOutput){
    Checkout checkout({watermelon, watermelon, watermelon}, std::make_unique<ForEachIdenticalThreeProductsTenPercentDiscount>());

    const auto receipt = checkout.getReceipt();
    std::cout<<receipt;
    EXPECT_GT(receipt.size(), 0);
}

TEST_F(TestCheckout, givenCheckoutWithProductsPriceAbove50zlotyAndDiscountForProductAbove50zloty_whensumMethodIsCalled_thenExpectReturnPriceWith20PercentOfDiscount){
    const grosz expectedResult = 80'00;
    Checkout checkout({raspberry}, std::make_unique<ProductWithPriceAboveFiftyZlotyTwentyPercentDiscount>());

    const auto result = checkout.getSumWithDiscount();
    
    EXPECT_EQ(result, expectedResult);
}

TEST_F(TestCheckout, givenCheckoutWithProductsPriceEqual50zlotyAndDiscountForProductAbove50zloty_whensumMethodIsCalled_thenExpectReturnPrice){
    const grosz expectedResult = 50'00;
    Checkout checkout({blueberry}, std::make_unique<ProductWithPriceAboveFiftyZlotyTwentyPercentDiscount>());

    const auto result = checkout.getSumWithDiscount();
    
    EXPECT_EQ(result, expectedResult);
}

TEST_F(TestCheckout, givenCheckoutWithProductStartingWithLetteraandDiscountForProductStartWithLettera_whensumMethodIsCalled_thenExpectReturnPriceWith10PercentDiscount){
    const grosz expectedResult = 3'60;
    Checkout checkout({apple}, std::make_unique<ProductWithNameStartingWithLetterATenPercentDiscount>());

    const auto result = checkout.getSumWithDiscount();

    EXPECT_EQ(result, expectedResult);
}

TEST_F(TestCheckout, givenCheckoutWithProductStartingWithLetterAandDiscountForProductStartWithLettera_whensumMethodIsCalled_thenExpectReturnPriceWith10PercentDiscount){
    const grosz expectedResult = 3'60;
    Checkout checkout({ananas}, std::make_unique<ProductWithNameStartingWithLetterATenPercentDiscount>());

    const auto result = checkout.getSumWithDiscount();

    EXPECT_EQ(result, expectedResult);
}

TEST_F(TestCheckout, givenCheckoutWithProductStartingWithLetterbandDiscountForProductStartWithLettera_whensumMethodIsCalled_thenExpectReturnPrice){
    const grosz expectedResult = 20'00;
    Checkout checkout({banana}, std::make_unique<ProductWithNameStartingWithLetterATenPercentDiscount>());

    const auto result = checkout.getSumWithDiscount();

    EXPECT_EQ(result, expectedResult);
}

TEST_F(TestCheckout, givenCheckoutWithTwoIdenticalProductsStartingWithLetteraandDiscountForProductStartWithLettera_whensumMethodIsCalled_thenExpectReturnSumWith10PercentDiscount){
    const grosz expectedResult = 18'00;
    Checkout checkout({avocado,avocado}, std::make_unique<ProductWithNameStartingWithLetterATenPercentDiscount>());

    const auto result = checkout.getSumWithDiscount();

    EXPECT_EQ(result, expectedResult);
}
