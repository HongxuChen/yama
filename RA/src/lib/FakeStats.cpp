//
// Created by hongxu on 6/11/16.
//

#include <iostream>
#include "FakeStats.h"

std::ostream &operator<<(std::ostream &ostream, FakeStats const &stats) {
  ostream << stats.msg_ << ": " << stats.value_;
  return ostream;
}
