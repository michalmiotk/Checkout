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
};

TEST_F(TestCheckout, givenCheckoutWithTwoProducts_whensumMethodIsCalled_thenExpectSumOfPrices)
{
    const uint32_t desiredResult = 37'00;
    
    Checkout checkout({strawberry, apple});

    const auto result = checkout.sumWithDiscount();
    
    EXPECT_EQ(result, desiredResult);
}


TEST_F(TestCheckout, givenCheckoutWithOneProduct_whensumMethodIsCalled_thenExpectProductPrice)
{
    const uint32_t desiredResult = 10'00;
    Checkout checkout({watermelon});

    const auto result = checkout.sumWithDiscount();
    
    EXPECT_EQ(result, desiredResult);
}

TEST_F(TestCheckout, givenCheckoutWithTwoIdenticalProductsAndDiscountForThreeIdenticalProduct_whensumMethodIsCalled_thenExpectReturnSum){
    uint32_t desiredResult = 20'00;
    Checkout checkout({watermelon, watermelon}, std::make_unique<ForEachIdenticalThreeProductsTenPercentDiscount>());

    const auto result = checkout.sumWithDiscount();
    
    EXPECT_EQ(result, desiredResult);
}

TEST_F(TestCheckout, givenCheckoutWithThreeIdenticalProductsAndDiscountForEachThreeIdenticalProduct_whensumMethodIsCalled_thenExpectReturnSumWith10PercentOfDiscount){
    uint32_t desiredResult = 27'00;
    Checkout checkout({watermelon, watermelon, watermelon}, std::make_unique<ForEachIdenticalThreeProductsTenPercentDiscount>());

    const auto result = checkout.sumWithDiscount();
    
    EXPECT_EQ(result, desiredResult);
}

TEST_F(TestCheckout, givenCheckoutWithSixIdenticalProductsAndDiscountForEachThreeIdenticalProduct_whensumMethodIsCalled_thenExpectReturnSumWith10PercentOfDiscount){
    uint32_t desiredResult = 54'00;
    Checkout checkout({watermelon, watermelon, watermelon, watermelon, watermelon, watermelon}, std::make_unique<ForEachIdenticalThreeProductsTenPercentDiscount>());

    const auto result = checkout.sumWithDiscount();
    
    EXPECT_EQ(result, desiredResult);
}

TEST_F(TestCheckout, givenCheckoutWithSixIdenticalProductsInTwoCategoriesAndDiscount_whensumMethodIsCalled_thenExpectReturnSumWith10PercentOfDiscount){
    uint32_t desiredResult = 81'00;
    Checkout checkout({watermelon, watermelon, watermelon, banana, banana, banana}, std::make_unique<ForEachIdenticalThreeProductsTenPercentDiscount>());

    const auto result = checkout.sumWithDiscount();
    
    EXPECT_EQ(result, desiredResult);
}

TEST_F(TestCheckout, giventCheckoutWithThreeIdenticalProductsAndDiscount_whengetReceiptMethodIsCalled_thenExpectNonEmptyOutput){
    Checkout checkout({watermelon, watermelon, watermelon}, std::make_unique<ForEachIdenticalThreeProductsTenPercentDiscount>());

    const auto receipt = checkout.getReceipt();
    std::cout<<receipt;
    EXPECT_GT(receipt.size(), 0);
}

TEST_F(TestCheckout, givenCheckoutWithProductsPriceAbove50zlotyAndDiscountForProductAbove50zloty_whensumMethodIsCalled_thenExpectReturnPriceWith20PercentOfDiscount){
    uint32_t desiredResult = 80'00;
    Checkout checkout({raspberry}, std::make_unique<ProductWithPriceAboveFiftyZlotyTwentyPercentDiscount>());

    const auto result = checkout.sumWithDiscount();
    
    EXPECT_EQ(result, desiredResult);
}

TEST_F(TestCheckout, givenCheckoutWithProductsPriceEqual50zlotyAndDiscountForProductAbove50zloty_whensumMethodIsCalled_thenExpectReturnPrice){
    uint32_t desiredResult = 50'00;
    Checkout checkout({blueberry}, std::make_unique<ProductWithPriceAboveFiftyZlotyTwentyPercentDiscount>());

    const auto result = checkout.sumWithDiscount();
    
    EXPECT_EQ(result, desiredResult);
}

TEST_F(TestCheckout, givenCheckoutWithProductStartingWithLetteraandDiscountForProductStartWithLettera_whensumMethodIsCalled_thenExpectReturnPriceWith10PercentDiscount){
    grosze expectedResult = 3'60;
    Checkout checkout({apple}, std::make_unique<ProductWithNameStartingWithLetterATenPercentDiscount>());

    const auto result = checkout.sumWithDiscount();

    EXPECT_EQ(result, expectedResult);
}

TEST_F(TestCheckout, givenCheckoutWithProductStartingWithLetterAandDiscountForProductStartWithLettera_whensumMethodIsCalled_thenExpectReturnPriceWith10PercentDiscount){
    grosze expectedResult = 3'60;
    Checkout checkout({ananas}, std::make_unique<ProductWithNameStartingWithLetterATenPercentDiscount>());

    const auto result = checkout.sumWithDiscount();

    EXPECT_EQ(result, expectedResult);
}

TEST_F(TestCheckout, givenCheckoutWithProductStartingWithLetterbandDiscountForProductStartWithLettera_whensumMethodIsCalled_thenExpectReturnPrice){
    grosze expectedResult = 20'00;
    Checkout checkout({banana}, std::make_unique<ProductWithNameStartingWithLetterATenPercentDiscount>());

    const auto result = checkout.sumWithDiscount();

    EXPECT_EQ(result, expectedResult);
}

TEST_F(TestCheckout, givenCheckoutWithTwoIdenticalProductsStartingWithLetteraandDiscountForProductStartWithLettera_whensumMethodIsCalled_thenExpectReturnSumWith10PercentDiscount){
    grosze expectedResult = 18'00;
    Checkout checkout({avocado,avocado}, std::make_unique<ProductWithNameStartingWithLetterATenPercentDiscount>());

    const auto result = checkout.sumWithDiscount();

    EXPECT_EQ(result, expectedResult);
}
