#include "unity.h"

// Include the header file for the code being tested
#include "../src/hello_world.h"

// Declare the test function
void test_hello_world()
{
    // Test case 1: Verify the output of the hello_world function
    TEST_ASSERT_EQUAL_STRING("Hello, World!", hello_world());
}

// Run the test function
int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_hello_world);
    return UNITY_END();
}