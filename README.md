# CGull

CGull is a minimal tool for testing embedded C code on a PC using Python and the excellent [Unity test framework](https://www.throwtheswitch.org/unity).

## Install

Clone this repository and run `pip install .` from the check-out directory.

CGull requires that you have Python and GCC installed and available in your path. It should run on Linux, Windows, and Mac.

If you are trying to compile with the `-m32` flag on Linux and receive `fatal error: sys/cdefs.h: No such file or directory`, you may need to install `libc6-dev-i386`.

## Configuration

Create a new directory to hold your CGull tests. Your CGull tests will be separate from your embedded project. In this directory, create the following structure:

```
project_test_directory/
├ helpers/    - Stub and mock source files
├ tests/      - Unity compatible test source files
└ config.toml - Control test build and run configuration
```

A simple configuration file contains:

```
target_inc = "../path/to/embedded/project/inc"
target_src = "../path/to/embedded/project/src"
gcc_flags = ["-m32"]

[test.module_abc]
depends = ["abc.c"]
helpers = ["stub_something_abc_includes.c"]

[test.module_xyz]
depends = ["xyz.c", "related.c"]
helpers = ["stub_something_xyz_includes.c"]
```

The `target_inc` and `target_src` options tell CGull where to look for the embedded code you are testing. You can pass `gcc_flags` to help make the local builds more similar to your embedded platform, but remember that these tests will not exercise processor-specific quirks.

For each module you want to test, create a section in the configuration file. CGull will automatically look for the test file based on the section name. For example, `[test.module_abc]` will look for `test_module_abc.c` in the `project_test_directory/tests/` folder. There is a 1-to-1 relationship between test files and configuration file sections.

The list of `depends` files are compiled from the `target_src` directory. This list is almost always going to start with the module you want to test. It may also include other target modules that are so tightly coupled you need to test them together.

The `helpers` list compiles in additional code from the `helpers` folder. This is typically how you would stub/mock modules that your module-under-test interacts with.

## Running

From the root of your tests directory, run `cgull` to compile and execute all tests from the configuration file.

To run only one test module, pass the `--module`/`-m` command line option with the name of the test to run:

```
cgull --module test_module_abc
```

## Test Files

CGull is a thin wrapper around gcc, so test files are just C code that use the Unity testing framework. An example test file simply includes Unity and the code to be tested:

```
#include <stdint.h>
#include "unity.h"
#include "module_under_test.c"

void test_scaling() {
  TEST_ASSERT_EQUAL_UINT32(5, module_under_test_scale(0));
  TEST_ASSERT_EQUAL_UINT32(10, module_under_test_scale(1));
  TEST_ASSERT_EQUAL_UINT32(15, module_under_test_scale(2));
}

void test_append_done() {
  char expected[16] = "okdone";
  char tmp[16] = "ok";
  module_under_test_append_done(&tmp);
  TEST_ASSERT_EQUAL_STRING(expected, tmp);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_scaling);
  RUN_TEST(test_append_done);
  UNITY_END();
  return 0;
}
```
