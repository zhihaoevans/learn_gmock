# learn_gmock

一个 C++17 的 Google Test / Google Mock 最小示例：通过 `IFoo` 接口注入依赖，用 mock 验证 `Processor` 的成功路径与错误路径。

## 可以学习什么

- 使用 `MOCK_METHOD` 替代接口实现。
- 使用 `EXPECT_CALL`、`Return` 设置并检查调用行为。
- 使用 `DoAll` 与 `SetArgPointee` 模拟输出参数。
- 使用 CMake、CTest 与 GitHub Actions 组织测试及覆盖率报告。

## 目录导航

| 文件 | 内容 |
| --- | --- |
| [src/mylib.h](src/mylib.h) · [src/mylib.cpp](src/mylib.cpp) | 接口与被测试实现 |
| [test/sample_test.cpp](test/sample_test.cpp) | 两个 `ProcessorTest` 测试用例 |
| [CMakeLists.txt](CMakeLists.txt) | C++17 构建、FetchContent 与覆盖率开关 |
| [CI 工作流](.github/workflows/ci.yml) | 构建、测试、覆盖率报告上传 |

## 快速开始

需要 CMake 3.14+、支持 C++17 的编译器及 Git。首次配置通过 FetchContent 下载 GoogleTest `v1.14.0`，需要网络访问。

```bash
git clone https://github.com/zhihaoevans/learn_gmock.git
cd learn_gmock
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

测试目标是 `sample_test`。成功时 CTest 应报告该测试目标通过；具体断言见测试源码。

## 本地覆盖率

使用 GCC/Clang，并安装 `lcov`（包含 `genhtml`）。配置时开启 `ENABLE_COVERAGE`：

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON
cmake --build build
lcov --directory build --zerocounters
ctest --test-dir build --output-on-failure
lcov --directory build --capture --output-file coverage.info
lcov --remove coverage.info '/usr/*' '*/_deps/*' '*/googletest/*' '*/gmock/*' --output-file coverage.filtered.info
genhtml coverage.filtered.info --output-directory coverage-report
```

打开 `coverage-report/index.html` 查看结果。清零计数必须在运行测试**之前**；现有 CI 将清零放在测试之后，解读其覆盖率报告时需注意这个顺序问题。

## CI 与扩展

CI 在 `main` 的 push / pull request 上运行，并上传 `coverage-report` artifact。工作流还包含 Codecov 上传步骤；私有仓库需要在对应步骤启用 `CODECOV_TOKEN` 配置。

可以从新增一个失败场景或 mock 调用期望开始扩展，测试与实现分别放在 `test/` 和 `src/`。
