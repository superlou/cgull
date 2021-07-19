#include "unity.h"
#include "debouncer.h"

void test_basic_debouncing(void) {
  Debouncer debouncer;
  debouncer_new(&debouncer, 5);

  uint32_t in = 0xffffffff;

  TEST_ASSERT_EQUAL_UINT32(0x00000000, debouncer_update(&debouncer, in));
  TEST_ASSERT_EQUAL_UINT32(0x00000000, debouncer_update(&debouncer, in));
  TEST_ASSERT_EQUAL_UINT32(0x00000000, debouncer_update(&debouncer, in));
  TEST_ASSERT_EQUAL_UINT32(0x00000000, debouncer_update(&debouncer, in));
  TEST_ASSERT_EQUAL_UINT32(0xffffffff, debouncer_update(&debouncer, in));
}

void test_debouncing_of_some_inputs(void) {
  Debouncer debouncer;
  debouncer_new(&debouncer, 5);

  uint32_t in = 0xAAAA5555;

  TEST_ASSERT_EQUAL_UINT32(0x00000000, debouncer_update(&debouncer, in));
  TEST_ASSERT_EQUAL_UINT32(0x00000000, debouncer_update(&debouncer, in));
  TEST_ASSERT_EQUAL_UINT32(0x00000000, debouncer_update(&debouncer, in));
  TEST_ASSERT_EQUAL_UINT32(0x00000000, debouncer_update(&debouncer, in));
  TEST_ASSERT_EQUAL_UINT32(0xAAAA5555, debouncer_update(&debouncer, in));
}

void test_debouncing_on_and_off(void) {
  Debouncer debouncer;
  debouncer_new(&debouncer, 5);

  uint32_t in = 0xffffffff;

  TEST_ASSERT_EQUAL_UINT32(0x00000000, debouncer_update(&debouncer, in));
  TEST_ASSERT_EQUAL_UINT32(0x00000000, debouncer_update(&debouncer, in));
  TEST_ASSERT_EQUAL_UINT32(0x00000000, debouncer_update(&debouncer, in));
  TEST_ASSERT_EQUAL_UINT32(0x00000000, debouncer_update(&debouncer, in));
  TEST_ASSERT_EQUAL_UINT32(0xffffffff, debouncer_update(&debouncer, in));
  TEST_ASSERT_EQUAL_UINT32(0xffffffff, debouncer_update(&debouncer, 0));
  TEST_ASSERT_EQUAL_UINT32(0xffffffff, debouncer_update(&debouncer, 0));
  TEST_ASSERT_EQUAL_UINT32(0xffffffff, debouncer_update(&debouncer, 0));
  TEST_ASSERT_EQUAL_UINT32(0xffffffff, debouncer_update(&debouncer, 0));
  TEST_ASSERT_EQUAL_UINT32(0x00000000, debouncer_update(&debouncer, 0));
}

void test_debouncing_for_a_while(void) {
  Debouncer debouncer;
  debouncer_new(&debouncer, 5);

  uint32_t in = 0xffffffff;

  TEST_ASSERT_EQUAL_UINT32(0x00000000, debouncer_update(&debouncer, in));
  TEST_ASSERT_EQUAL_UINT32(0x00000000, debouncer_update(&debouncer, in));
  TEST_ASSERT_EQUAL_UINT32(0x00000000, debouncer_update(&debouncer, in));
  TEST_ASSERT_EQUAL_UINT32(0x00000000, debouncer_update(&debouncer, in));

  for (uint64_t i = 0; i < 10000; i++) {
    TEST_ASSERT_EQUAL_UINT32(0xffffffff, debouncer_update(&debouncer, in));
  }

  TEST_ASSERT_EQUAL_UINT32(0xffffffff, debouncer_update(&debouncer, 0));
  TEST_ASSERT_EQUAL_UINT32(0xffffffff, debouncer_update(&debouncer, 0));
  TEST_ASSERT_EQUAL_UINT32(0xffffffff, debouncer_update(&debouncer, 0));
  TEST_ASSERT_EQUAL_UINT32(0xffffffff, debouncer_update(&debouncer, 0));

  for (uint64_t i = 0; i < 10000; i++) {
    TEST_ASSERT_EQUAL_UINT32(0x00000000, debouncer_update(&debouncer, 0));
  }
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_basic_debouncing);
  RUN_TEST(test_debouncing_of_some_inputs);
  RUN_TEST(test_debouncing_on_and_off);
  RUN_TEST(test_debouncing_for_a_while);
  UNITY_END();
  return 0;
}
