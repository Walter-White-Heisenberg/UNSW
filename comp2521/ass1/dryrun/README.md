
# Assignment 1 Dryrun

**NOTE: The dryrun tests only test simple cases. You are expected to develop your own tests to test other cases.**

## To run each test manually
1. Copy your `textbuffer.c` into this directory.
2. Compile using the `make` command.
3. Type `./testTextbuffer <test no>...` where `<test no>...` are the tests you want to run. For example, `./testTextbuffer 1 2 3`. To test using `valgrind`, prepend `valgrind` to the command. For example, `valgrind ./testTextbuffer 1 2 3`.

## To run tests with `rundryrun`
1. Copy your `textbuffer.c` into this directory.
2. Compile using the `make` command.
3. Type `./rundryrun`. Note that `./rundryrun` does not compile, so you'll need to compile separately.
   - Using `./rundryrun` without giving it any arguments will cause it to run all tests. To run specific tests, use `./rundryrun <test no>...`.
4. The output of your program will appear in `tests/##.out`, where `##` is a test number.
5. If you get any errors from `valgrind`, they'll appear in `tests/##.err`.

