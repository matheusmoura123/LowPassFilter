#include <gtest/gtest.h>
#include "MovingAverage.h"
#include "Butterworth.h"

using namespace Moura;

class MovingAverageTest : public testing::Test {
protected:
    MovingAverage f_;

    void SetUp() override {
        f_ = MovingAverage();
    }
};

TEST_F(MovingAverageTest, SetKernelZero) {
    EXPECT_ANY_THROW(f_.SetParameter(0));
}

TEST_F(MovingAverageTest, SetKernelDouble) {
    EXPECT_ANY_THROW(f_.SetParameter(1.5));
}

TEST_F(MovingAverageTest, SetKernelOdd) {
    f_.SetParameter(7);
    EXPECT_NEAR(f_.FilterSignal(7.0), 7.0 / 7, 1e-6) << f_.FilterSignal(7.0);
}

TEST_F(MovingAverageTest, SetKernelEven) {
    f_.SetParameter(6);
    EXPECT_NEAR(f_.FilterSignal(7.0), 7.0 / 7, 1e-6) << f_.FilterSignal(7.0);
}

TEST_F(MovingAverageTest, ZeroInput) {
    EXPECT_NEAR(f_.FilterSignal(0.0), 0.0, 1e-6);
}

TEST_F(MovingAverageTest, FewerSamplesThanKernel) {
    for (int i = 0; i < 5; ++i)
        f_.FilterSignal(1.0);
    EXPECT_NEAR(f_.FilterSignal(1.0), 6.0 / 51, 1e-6);
}

TEST_F(MovingAverageTest, ExactSamplesKernelSize) {
    for (int i = 0; i < 50; ++i)
        f_.FilterSignal(1.0);
    EXPECT_NEAR(f_.FilterSignal(1.0), 51.0 / 51, 1e-6);
}

TEST_F(MovingAverageTest, MoreSamplesThanKernelSize) {
    for (int i = 0; i < 100; ++i)
        f_.FilterSignal(1.0);
    EXPECT_NEAR(f_.FilterSignal(1.0), 1.0, 1e-6);
}



class ButterworthTest : public testing::Test {
protected:
    Butterworth f_;

    void SetUp() override {
        f_ = Butterworth();
    }
};

TEST_F(ButterworthTest, SetBWFreqInt) {
    EXPECT_ANY_THROW(f_.SetParameter(1));
}

TEST_F(ButterworthTest, SetBWFreqSEqZero) {
    EXPECT_ANY_THROW(f_.SetParameter(0));
}

TEST_F(ButterworthTest, SetBWFreqBEqHalf) {
    EXPECT_ANY_THROW(f_.SetParameter(0.7));
}

TEST_F(ButterworthTest, SetBWFreqValidValue) {
    EXPECT_NO_THROW(f_.SetParameter(0.1));
}

TEST_F(ButterworthTest, StableOutput) {
    for (int i = 0; i < 50; ++i)
        f_.FilterSignal(1.0);
    double result = f_.FilterSignal(1.0);
    EXPECT_GT(result, 0.0);
    EXPECT_LT(result, 2.0);
}



