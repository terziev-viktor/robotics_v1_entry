#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <cstdint>
#include <bitset>
#include <EyePatterns.h>
#include "utils/Image.h"
#include "utils/FunctionTracer.h"

class EyeLocation {
public:
    size_t location;
    uint32_t type;
};

class Solution {
public:
  static void compute([[maybe_unused]]std::vector<StrideImage> &images);
};

#endif /* SOLUTION_H_ */
