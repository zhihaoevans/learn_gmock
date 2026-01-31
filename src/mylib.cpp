#include "mylib.h"

int Processor::ProcessValue(int v) {
  int r = foo_->Do(v);
  if (r < 0) return -1;
  std::string out;
  foo_->Out(r, &out);
  if (out.find("ok") != std::string::npos) return r * 2;
  return r;
}
