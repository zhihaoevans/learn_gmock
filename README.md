# MyGMockTests - Example

This repository demonstrates:
- A small library (`mylib`) that depends on an interface `IFoo`.
- Unit tests using Google Test / Google Mock.
- GitHub Actions workflow that builds, runs tests and collects coverage (lcov + genhtml).
- CMake-based build using FetchContent to bring googletest/gmock.

How to build and run locally:

1. Build:
   mkdir build && cd build
   cmake -S .. -B . -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON
   cmake --build .

2. Run tests:
   ctest --output-on-failure

3. Generate coverage locally:
   sudo apt-get install -y lcov
   lcov --directory . --capture --output-file coverage.info
   lcov --remove coverage.info "/usr/*" "*/_deps/*" "*/googletest/*" --output-file coverage.filtered.info
   genhtml coverage.filtered.info --output-directory coverage-report

To enable Codecov upload on CI, add a repository secret named `CODECOV_TOKEN`.
