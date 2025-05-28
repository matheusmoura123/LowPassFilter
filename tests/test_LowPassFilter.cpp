#include <gtest/gtest.h>
#include "LowPassFilter.h"

namespace Moura {

TEST(LowPassFilterTest, ZeroInput) {
    LowPassFilter filter(LowPassFilter::FilterType::FIR);
    EXPECT_NEAR(filter.FilterSignal(0.0), 0.0, 1e-6);
}

// TEST(LowPassFilterTest, StepInput) {
//     LowPassFilter filter(0.1);
//     double output = filter.update(1.0);
//     EXPECT_GT(output, 0.0);
//     EXPECT_LT(output, 1.0);
// }

}
