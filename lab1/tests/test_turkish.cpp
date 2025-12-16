#include <gtest/gtest.h>
#include "TurkishNumber.h"

TEST(TurkishNumberTest, SingleDigits) {
    EXPECT_EQ(number_to_turkish(0), "sıfır");
    EXPECT_EQ(number_to_turkish(1), "bir");
    EXPECT_EQ(number_to_turkish(2), "iki");
    EXPECT_EQ(number_to_turkish(3), "üç");
    EXPECT_EQ(number_to_turkish(9), "dokuz");
}

TEST(TurkishNumberTest, Tens) {
    EXPECT_EQ(number_to_turkish(10), "on");
    EXPECT_EQ(number_to_turkish(20), "yirmi");
    EXPECT_EQ(number_to_turkish(30), "otuz");
    EXPECT_EQ(number_to_turkish(40), "kırk");
    EXPECT_EQ(number_to_turkish(50), "elli");
    EXPECT_EQ(number_to_turkish(60), "altmış");
    EXPECT_EQ(number_to_turkish(70), "yetmiş");
    EXPECT_EQ(number_to_turkish(80), "seksen");
    EXPECT_EQ(number_to_turkish(90), "doksan");
}

TEST(TurkishNumberTest, ExamplesFromTask) {
    EXPECT_EQ(number_to_turkish(1),  "bir");
    EXPECT_EQ(number_to_turkish(13), "on üç");
    EXPECT_EQ(number_to_turkish(27), "yirmi yedi");
    EXPECT_EQ(number_to_turkish(38), "otuz sekiz");
    EXPECT_EQ(number_to_turkish(77), "yetmiş yedi");
    EXPECT_EQ(number_to_turkish(94), "doksan dört");
}

TEST(TurkishNumberTest, Edges) {
    EXPECT_EQ(number_to_turkish(99), "doksan dokuz");
    EXPECT_THROW(number_to_turkish(-1), std::out_of_range);
    EXPECT_THROW(number_to_turkish(100), std::out_of_range);
}
