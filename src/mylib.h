#pragma once
#include <string>
#include <memory>

/// Interface for processing operations
struct IFoo {
  virtual ~IFoo() = default;
  
  /// Performs an operation on the input value
  /// @param x Input value
  /// @return Processed result
  virtual int Do(int x) = 0;
  
  /// Outputs a string based on the input value
  /// @param in Input value
  /// @param out Output string that will be populated by this method
  virtual void Out(int in, std::string* out) = 0;
};

/// Processes values using an IFoo implementation
class Processor {
 public:
  /// Constructs a Processor with the given IFoo implementation
  /// @param foo Shared pointer to IFoo implementation
  explicit Processor(std::shared_ptr<IFoo> foo) : foo_(std::move(foo)) {}
  
  /// Processes a value through the IFoo interface
  /// @param v Input value to process
  /// @return Processed result: -1 if Do() returns negative,
  ///         doubled value if Out() contains "ok", otherwise the value from Do()
  int ProcessValue(int v);

 private:
  std::shared_ptr<IFoo> foo_;
};
