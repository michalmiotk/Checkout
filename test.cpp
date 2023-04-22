#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Receipt.cpp"

using namespace testing;


TEST(Receipt, givenReceiptWithTwoProducts_whensumMethodIsCalled_thenExpectSumOfPrices)
{
    uint32_t desiredResult = 37;
    Product cigarettes{"malboro", 33};
    Product cola{"cola", 4};
    Receipt receipt;
    receipt.addProduct(cigarettes);
    receipt.addProduct(cola);

    auto result = receipt.sum();
    
    EXPECT_EQ(result, desiredResult);
}


TEST(Receipt, givenReceiptWithOneProduct_whensumMethodIsCalled_thenExpectProductPrice)
{
    uint32_t desiredResult = 10;
    Product watermelon{"arbuz", 10};
    Receipt receipt;
    receipt.addProduct(watermelon);

    auto result = receipt.sum();
    
    EXPECT_EQ(result, desiredResult);
}

TEST(Receipt, givenReceiptWithThreeIdenticalProducts_whensumMethodIsCalled_thenExpectReturnSumWith10PercentOfDiscount){
    uint32_t desiredResult = 27;
    Product watermelon{"arbuz", 10};
    Receipt receipt;
    receipt.addProduct(watermelon);
    receipt.addProduct(watermelon);
    receipt.addProduct(watermelon);

    auto result = receipt.sum();
    
    EXPECT_EQ(result, desiredResult);
}

TEST(Receipt, givenReceiptWithSixIdenticalProducts_whensumMethodIsCalled_thenExpectReturnSumWith10PercentOfDiscount){
    uint32_t desiredResult = 54;
    Product watermelon{"arbuz", 10};
    Receipt receipt;
    receipt.addProduct(watermelon);
    receipt.addProduct(watermelon);
    receipt.addProduct(watermelon);
    receipt.addProduct(watermelon);
    receipt.addProduct(watermelon);
    receipt.addProduct(watermelon);

    auto result = receipt.sum();
    
    EXPECT_EQ(result, desiredResult);
}

TEST(Receipt, givenReceiptWithSixIdenticalProductsInTwoCategories_whensumMethodIsCalled_thenExpectReturnSumWith10PercentOfDiscount){
    uint32_t desiredResult = 81;
    Product watermelon{"arbuz", 10};
    Product banana{"banana", 20};
    Receipt receipt;
    receipt.addProduct(watermelon);
    receipt.addProduct(watermelon);
    receipt.addProduct(watermelon);
    
    receipt.addProduct(banana);
    receipt.addProduct(banana);
    receipt.addProduct(banana);

    auto result = receipt.sum();
    
    EXPECT_EQ(result, desiredResult);
}
