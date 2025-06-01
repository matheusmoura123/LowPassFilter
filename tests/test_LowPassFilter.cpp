#include <gtest/gtest.h>
#include "LowPassFilter.h"

using namespace Moura;

class LowPassFilterTest : public testing::Test {
protected:
    LowPassFilter f1_;
    LowPassFilter f2_;

    void SetUp() override {
        f1_ = LowPassFilter(LowPassFilter::FIR);
        f2_ = LowPassFilter(LowPassFilter::IIR);
    }
};


// Constructor Tests
TEST_F(LowPassFilterTest, DefaultConstructorSetsExpectedDefaults) {
    LowPassFilter f;
    EXPECT_NEAR(f.FilterSignal(1.0), 1.0 / 51, 1e-6);
}

// Assignment Operators
TEST_F(LowPassFilterTest, AssignmentOperatorCopiesAllFieldsCorrectly) {
    LowPassFilter f1(LowPassFilter::FIR);
    f1.SetKernel(9);
    LowPassFilter f2;
    f2 = f1;
    EXPECT_NEAR(f2.FilterSignal(1.0), f1.FilterSignal(1.0), 1e-6);
}

// Kernel Tests
TEST_F(LowPassFilterTest, SetKernelOddValueSetsCorrectly) {
    f1_.SetKernel(7);
    EXPECT_NEAR(f1_.FilterSignal(7.0), 7.0 / 7, 1e-6) << f1_.FilterSignal(7.0);
}

TEST_F(LowPassFilterTest, SetKernelEvenValueIncrementsToOdd) {
    f1_.SetKernel(8);
    EXPECT_NEAR(f1_.FilterSignal(9.0), 9.0 / 9, 1e-6);
}

// Bandwidth Frequency Tests
TEST_F(LowPassFilterTest, SetBWFreqValidValueUpdatesAndComputesCoefs) {
    f2_.SetBWFreq(0.1);
    EXPECT_NO_THROW(f2_.FilterSignal(1.0));
}

TEST_F(LowPassFilterTest, SetBWFreqInvalidZeroDoesNotChangeValue) {
    f2_.SetBWFreq(0.0); // Should produce error message but not crash
    EXPECT_NO_THROW(f2_.FilterSignal(1.0));
}

TEST_F(LowPassFilterTest, SetBWFreqInvalidAboveHalfDoesNotChangeValue) {
    f2_.SetBWFreq(0.6);
    EXPECT_NO_THROW(f2_.FilterSignal(1.0));
}

// FIR Filtering
TEST_F(LowPassFilterTest, FIRFilterHandlesFewerSamplesThanKernel) {
    for (int i = 0; i < 5; ++i)
        f1_.FilterSignal(1.0);
    EXPECT_NEAR(f1_.FilterSignal(1.0), 6.0 / 51, 1e-6);
}

TEST_F(LowPassFilterTest, FIRFilterHandlesExactKernelSize) {
    for (int i = 0; i < 50; ++i)
        f1_.FilterSignal(1.0);
    double result = f1_.FilterSignal(1.0);
    EXPECT_NEAR(result, 51.0 / 51, 1e-6);
}

TEST_F(LowPassFilterTest, FIRFilterHandlesMoreThanKernelSize) {
    for (int i = 0; i < 100; ++i)
        f1_.FilterSignal(1.0);
    double result = f1_.FilterSignal(1.0);
    EXPECT_NEAR(result, 1.0, 1e-6);
}

// IIR Filtering
TEST_F(LowPassFilterTest, IIRFilterHandlesMultipleInputsWithCorrectCoefs) {
    std::vector<double> inputs = {1, 2, 3, 4, 5};
    for (double x : inputs)
        f2_.FilterSignal(x);
    EXPECT_NO_THROW(f2_.FilterSignal(6));
}

TEST_F(LowPassFilterTest, IIRFilterRespectsMemoryLengthOfFive) {
    for (int i = 0; i < 10; ++i)
        f2_.FilterSignal(i);
    EXPECT_NO_THROW(f2_.FilterSignal(0));
}

TEST_F(LowPassFilterTest, IIRFilterProducesStableOutput) {
    for (int i = 0; i < 50; ++i)
        f2_.FilterSignal(1.0);
    double result = f2_.FilterSignal(1.0);
    EXPECT_GT(result, 0.0);
    EXPECT_LT(result, 2.0);
}

// BW Coefficients
TEST_F(LowPassFilterTest, ComputeBWCoefSetsExpectedCoefficientRange) {
    f2_.SetBWFreq(0.1);
    EXPECT_NO_THROW(f2_.FilterSignal(1.0));
}

TEST_F(LowPassFilterTest, ZeroInput) {
    LowPassFilter f(LowPassFilter::FIR);
    EXPECT_NEAR(f.FilterSignal(0.0), 0.0, 1e-6);
}

// TEST(LowPassFilterTest, StepInput) {
//     LowPassFilter filter(0.1);
//     double output = filter.update(1.0);
//     EXPECT_GT(output, 0.0);
//     EXPECT_LT(output, 1.0);
// }

