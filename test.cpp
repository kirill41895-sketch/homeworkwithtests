#include "delivery.hpp"
#include <gtest/gtest.h>
#include <string>

using namespace demo;

class LocalShipmentTest : public ::testing::Test {
protected:
    DeliveryPolicy policy;
    Shipment shipment{100000, 1000, Zone::Local};
    void SetUp() override { shipment.grams = 1000; }
};

struct FeeCase {
    const char* name;
    Shipment shipment;
    Cents expected;
};

class FeeMatrixTest : public ::testing::TestWithParam<FeeCase> {};

TEST_P(FeeMatrixTest, FollowsTariff) {
    const auto& p = GetParam();
    DeliveryPolicy policy;
    EXPECT_EQ(policy.quote(p.shipment), p.expected);
}

const FeeCase fee_cases[] = {
    {"LocalBelow", {499999, 1000, Zone::Local}, 30000},
    {"LocalAt", {500000, 1000, Zone::Local}, 0},
    {"LocalAbove", {500001, 1000, Zone::Local}, 0},
    {"RemoteBelow", {499999, 1000, Zone::Remote}, 70000},
    {"RemoteAt", {500000, 1000, Zone::Remote}, 70000},
    {"RemoteAbove", {500001, 1000, Zone::Remote}, 70000}
};

INSTANTIATE_TEST_SUITE_P(Tariffs, FeeMatrixTest,
    ::testing::ValuesIn(fee_cases),
    [](const ::testing::TestParamInfo<FeeCase>& info) {
        return std::string(info.param.name);
    }
);

class AcceptedWeightTest : public ::testing::TestWithParam<int> {};

TEST_P(AcceptedWeightTest, KeepsBaseFee) {
    DeliveryPolicy policy;
    EXPECT_EQ(policy.quote(Shipment{100000, GetParam(), Zone::Local}), 30000);
}

INSTANTIATE_TEST_SUITE_P(Boundaries, AcceptedWeightTest, ::testing::Values(1, 1000, 20000));

TEST_F(LocalShipmentTest, LocalOrderHasBaseFee) {
    EXPECT_EQ(policy.quote(shipment), 30000);
}

TEST_F(LocalShipmentTest, NegativeSubtotalIsRejected) {
    shipment.subtotal = -1;
    EXPECT_THROW(policy.quote(shipment), std::invalid_argument);
}

TEST_F(LocalShipmentTest, ZeroWeightIsRejected) {
    shipment.grams = 0;
    EXPECT_THROW(policy.quote(shipment), std::invalid_argument);
}

TEST_F(LocalShipmentTest, RemoteZoneHasHigherFee) {
    shipment.zone = Zone::Remote;
    EXPECT_EQ(policy.quote(shipment), 70000);
}

TEST_F(LocalShipmentTest, LargeSubtotalHasFreeShipping) {
    shipment.subtotal = 500000;
    EXPECT_EQ(policy.quote(shipment), 0);
}

TEST_F(LocalShipmentTest, RegularCustomerGetsLowerThreshold) {
    shipment.is_regular_customer = true;
    shipment.subtotal = 300000;
    EXPECT_EQ(policy.quote(shipment), 0);
}

TEST_F(LocalShipmentTest, RegularCustomerRemoteFee) {
    shipment.is_regular_customer = true;
    shipment.zone = Zone::Remote;
    EXPECT_EQ(policy.quote(shipment), 50000);
}

TEST_F(LocalShipmentTest, RegularCustomerRemoteVsNormal) {
    shipment.is_regular_customer = false;
    shipment.zone = Zone::Remote;
    EXPECT_EQ(policy.quote(shipment), 70000);
}

TEST_F(LocalShipmentTest, LocalOverweightBlock) {
    shipment.grams = 24000; 
    EXPECT_EQ(policy.quote(shipment), 130000); 
}

TEST_F(LocalShipmentTest, LocalOverweightTwoBlocks) {
    shipment.grams = 29000;
    EXPECT_EQ(policy.quote(shipment), 230000);
}

TEST_F(LocalShipmentTest, RemoteOverweight) {
    shipment.zone = Zone::Remote;
    shipment.grams = 22000;
    EXPECT_EQ(policy.quote(shipment), 130000);
}

TEST_F(LocalShipmentTest, MaxWeightIsNow50Kg) {
    shipment.grams = 50000;
    EXPECT_EQ(policy.quote(shipment), 630000);
}

TEST_F(LocalShipmentTest, OverweightAbove50KgIsRejected) {
    shipment.grams = 50001;
    EXPECT_THROW(policy.quote(shipment), std::invalid_argument);
}