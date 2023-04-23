#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Checkout.cpp"

using namespace testing;


TEST(Checkout, givenCheckoutWithTwoProducts_whensumMethodIsCalled_thenExpectSumOfPrices)
{
    uint32_t desiredResult = 37;
    Product cigarettes{"malboro", 33};
    Product cola{"cola", 4};
    Checkout checkout({cigarettes, cola});

    auto result = checkout.sum();
    
    EXPECT_EQ(result, desiredResult);
}


TEST(Checkout, givenCheckoutWithOneProduct_whensumMethodIsCalled_thenExpectProductPrice)
{
    uint32_t desiredResult = 10;
    Product watermelon{"arbuz", 10};
    Checkout checkout({watermelon});

    auto result = checkout.sum();
    
    EXPECT_EQ(result, desiredResult);
}

TEST(Checkout, givenCheckoutWithThreeIdenticalProducts_whensumMethodIsCalled_thenExpectReturnSumWith10PercentOfDiscount){
    uint32_t desiredResult = 27;
    Product watermelon{"arbuz", 10};
    Checkout checkout({watermelon, watermelon, watermelon});

    auto result = checkout.sum();
    
    EXPECT_EQ(result, desiredResult);
}

TEST(Checkout, givenCheckoutWithSixIdenticalProducts_whensumMethodIsCalled_thenExpectReturnSumWith10PercentOfDiscount){
    uint32_t desiredResult = 54;
    Product watermelon{"arbuz", 10};
    Checkout checkout({watermelon, watermelon, watermelon, watermelon, watermelon, watermelon});

    auto result = checkout.sum();
    
    EXPECT_EQ(result, desiredResult);
}

TEST(Checkout, givenCheckoutWithSixIdenticalProductsInTwoCategories_whensumMethodIsCalled_thenExpectReturnSumWith10PercentOfDiscount){
    uint32_t desiredResult = 81;
    Product watermelon{"arbuz", 10};
    Product banana{"banana", 20};
    Checkout checkout({watermelon, watermelon, watermelon, banana, banana, banana});

    auto result = checkout.sum();
    
    EXPECT_EQ(result, desiredResult);
}

TEST(Checkout, giventCheckoutWithThreeIdenticalProducts_whengetReceiptMethodIsCalled_thenExpectNonEmptyOutput){
    Product watermelon{"arbuz", 10};
    Checkout checkout({watermelon, watermelon, watermelon});

    auto receipt = checkout.getReceipt();

    EXPECT_GT(receipt.size(), 0);
}
