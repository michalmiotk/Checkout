#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Checkout.cpp"

using namespace testing;

class TestCheckout : public ::testing::Test
{
public:
    Product strawberry{"strawberry", 33'00};
    Product apple{"apple", 4'00};
    Product watermelon{"watermelon", 10'00};
    Product banana{"banana", 20'00};
    Product raspberry{"raspberry", 100'00};
    Product blueberry{"blueberry", 50'00};
};

TEST_F(TestCheckout, givenCheckoutWithTwoProducts_whensumMethodIsCalled_thenExpectSumOfPrices)
{
    uint32_t desiredResult = 37'00;
    
    Checkout checkout({strawberry, apple}, {});

    auto result = checkout.sumWithDiscount();
    
    EXPECT_EQ(result, desiredResult);
}


TEST_F(TestCheckout, givenCheckoutWithOneProduct_whensumMethodIsCalled_thenExpectProductPrice)
{
    uint32_t desiredResult = 10'00;
    Checkout checkout({watermelon}, {});

    auto result = checkout.sumWithDiscount();
    
    EXPECT_EQ(result, desiredResult);
}

TEST_F(TestCheckout, givenCheckoutWithTwoIdenticalProductsAndDiscountForThreeIdenticalProduct_whensumMethodIsCalled_thenExpectReturnSum){
    uint32_t desiredResult = 20'00;
    Checkout checkout({watermelon, watermelon}, std::make_unique<ForEachIdenticalThreeProductsTenPercentDiscount>());

    auto result = checkout.sumWithDiscount();
    
    EXPECT_EQ(result, desiredResult);
}

TEST_F(TestCheckout, givenCheckoutWithThreeIdenticalProductsAndDiscountForEachThreeIdenticalProduct_whensumMethodIsCalled_thenExpectReturnSumWith10PercentOfDiscount){
    uint32_t desiredResult = 27'00;
    Checkout checkout({watermelon, watermelon, watermelon}, std::make_unique<ForEachIdenticalThreeProductsTenPercentDiscount>());

    auto result = checkout.sumWithDiscount();
    
    EXPECT_EQ(result, desiredResult);
}

TEST_F(TestCheckout, givenCheckoutWithSixIdenticalProductsAndDiscountForEachThreeIdenticalProduct_whensumMethodIsCalled_thenExpectReturnSumWith10PercentOfDiscount){
    uint32_t desiredResult = 54'00;
    Checkout checkout({watermelon, watermelon, watermelon, watermelon, watermelon, watermelon}, std::make_unique<ForEachIdenticalThreeProductsTenPercentDiscount>());

    auto result = checkout.sumWithDiscount();
    
    EXPECT_EQ(result, desiredResult);
}

TEST_F(TestCheckout, givenCheckoutWithSixIdenticalProductsInTwoCategoriesAndDiscount_whensumMethodIsCalled_thenExpectReturnSumWith10PercentOfDiscount){
    uint32_t desiredResult = 81'00;
    Checkout checkout({watermelon, watermelon, watermelon, banana, banana, banana}, std::make_unique<ForEachIdenticalThreeProductsTenPercentDiscount>());

    auto result = checkout.sumWithDiscount();
    
    EXPECT_EQ(result, desiredResult);
}

TEST_F(TestCheckout, giventCheckoutWithThreeIdenticalProductsAndDiscount_whengetReceiptMethodIsCalled_thenExpectNonEmptyOutput){
    Checkout checkout({watermelon, watermelon, watermelon}, std::make_unique<ForEachIdenticalThreeProductsTenPercentDiscount>());

    auto receipt = checkout.getReceipt();
    std::cout<<receipt;
    EXPECT_GT(receipt.size(), 0);
}

TEST_F(TestCheckout, givenCheckoutWithProductsPriceAbove50zlotyAndDiscountForProductAbove50zloty_whensumMethodIsCalled_thenExpectReturnPriceWith20PercentOfDiscount){
    uint32_t desiredResult = 80'00;
    Checkout checkout({raspberry}, std::make_unique<ProductWithPriceAboveFiftyZlotyTwentyPercentDiscount>());

    auto result = checkout.sumWithDiscount();
    
    EXPECT_EQ(result, desiredResult);
}

TEST_F(TestCheckout, givenCheckoutWithProductsPriceEqual50zlotyAndDiscountForProductAbove50zloty_whensumMethodIsCalled_thenExpectReturnPrice){
    uint32_t desiredResult = 50'00;
    Checkout checkout({blueberry}, std::make_unique<ProductWithPriceAboveFiftyZlotyTwentyPercentDiscount>());

    auto result = checkout.sumWithDiscount();
    
    EXPECT_EQ(result, desiredResult);
}

TEST_F(TestCheckout, givenCheckoutWithProductStartingWithLetteraAndDiscountForProductStartWithLettera_whensumMethodIsCalled_thenExpectReturnPriceWith10PercentDiscount){
    priceInGrosze expectedResult = 3'60;
    Checkout checkout({apple}, std::make_unique<ProductWithNameStartingWithLetterATenPercentDiscount>());

    auto result = checkout.sumWithDiscount();

    EXPECT_EQ(result, expectedResult);
}