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

// Kernel Tests
TEST_F(MovingAverageTest, SetKernelZero) {
    EXPECT_ANY_THROW(f_.SetParameter(0));
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



class ButterworthTest : public testing::Test {
protected:
    Butterworth f_;

    void SetUp() override {
        f_ = Butterworth();
    }
};

// Bandwidth Frequency Tests
TEST_F(ButterworthTest, SetBWFreqValidValue) {
    f_.SetParameter(0.1);
    EXPECT_NO_THROW(f_.FilterSignal(1.0));
}

// TEST_F(ButterworthTest, SetBWFreqInvalidZero) {
//     f2_.SetBWFreq(0.0); // Should produce error message but not crash
//     EXPECT_NO_THROW(f2_.FilterSignal(1.0));
// }

// TEST_F(MovingAverageTest, SetBWFreqInvalidAboveHalfDoesNotChangeValue) {
//     f2_.SetBWFreq(0.6);
//     EXPECT_NO_THROW(f2_.FilterSignal(1.0));
// }

// // FIR Filtering
// TEST_F(MovingAverageTest, FIRFilterHandlesFewerSamplesThanKernel) {
//     for (int i = 0; i < 5; ++i)
//         f_.FilterSignal(1.0);
//     EXPECT_NEAR(f_.FilterSignal(1.0), 6.0 / 51, 1e-6);
// }

// TEST_F(MovingAverageTest, FIRFilterHandlesExactKernelSize) {
//     for (int i = 0; i < 50; ++i)
//         f_.FilterSignal(1.0);
//     double result = f_.FilterSignal(1.0);
//     EXPECT_NEAR(result, 51.0 / 51, 1e-6);
// }

// TEST_F(MovingAverageTest, FIRFilterHandlesMoreThanKernelSize) {
//     for (int i = 0; i < 100; ++i)
//         f_.FilterSignal(1.0);
//     double result = f_.FilterSignal(1.0);
//     EXPECT_NEAR(result, 1.0, 1e-6);
// }

// // IIR Filtering
// TEST_F(MovingAverageTest, IIRFilterHandlesMultipleInputsWithCorrectCoefs) {
//     std::vector<double> inputs = {1, 2, 3, 4, 5};
//     for (double x : inputs)
//         f2_.FilterSignal(x);
//     EXPECT_NO_THROW(f2_.FilterSignal(6));
// }

// TEST_F(MovingAverageTest, IIRFilterRespectsMemoryLengthOfFive) {
//     for (int i = 0; i < 10; ++i)
//         f2_.FilterSignal(i);
//     EXPECT_NO_THROW(f2_.FilterSignal(0));
// }

// TEST_F(MovingAverageTest, IIRFilterProducesStableOutput) {
//     for (int i = 0; i < 50; ++i)
//         f2_.FilterSignal(1.0);
//     double result = f2_.FilterSignal(1.0);
//     EXPECT_GT(result, 0.0);
//     EXPECT_LT(result, 2.0);
// }

// // BW Coefficients
// TEST_F(MovingAverageTest, ComputeBWCoefSetsExpectedCoefficientRange) {
//     f2_.SetBWFreq(0.1);
//     EXPECT_NO_THROW(f2_.FilterSignal(1.0));
// }

// TEST(MovingAverageTest, StepInput) {
//     LowPassFilter filter(0.1);
//     double output = filter.update(1.0);
//     EXPECT_GT(output, 0.0);
//     EXPECT_LT(output, 1.0);
// }

