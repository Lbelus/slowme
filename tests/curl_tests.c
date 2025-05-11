#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <criterion/criterion.h>

// Test(suite_name, test_name)
// {
//     // write test here
// }

Test(sample, test)
{
    cr_expect(strlen("Test") == 4, "Expected \"Test\" to have a length of 4.");
    cr_expect(strlen("Hello") == 4, "This will always fail, why did I add this?");
    cr_assert(strlen("") == 0);
}

// This test will fail
Test(sample, failing) {
    int *ptr = NULL;
    *ptr = 42;
}

// This test will pass
Test(oksample, passing, .signal = SIGSEGV) {
    int *ptr = NULL;
    *ptr = 42;
}
