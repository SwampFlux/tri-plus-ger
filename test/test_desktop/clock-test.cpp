#include <unity.h>
#include "../src/clock.h"

Clock clock;

const int example = 1;

void test_equality(void) {
  TEST_ASSERT_EQUAL_INT(2, example);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_equality);
    UNITY_END();
    
    return 0;
}