#include "unity.h"

// Forward declaration of test functions
void test_hello_world(void);

int main(void) {
    UNITY_BEGIN();

    // Run test functions
    RUN_TEST(test_hello_world);

    return UNITY_END();
}