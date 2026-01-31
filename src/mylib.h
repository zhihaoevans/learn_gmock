#pragma once
#include <string>
#include <memory>

struct IFoo {
  virtual ~IFoo() = default;
  virtual int Do(int x) = 0;
  virtual void Out(int in, std::string* out) = 0;
};

class Processor {
 public:
  explicit Processor(std::shared_ptr<IFoo> foo) : foo_(std::move(foo)) {}
  int ProcessValue(int v);

 private:
  std::shared_ptr<IFoo> foo_;
};
