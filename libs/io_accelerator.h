#include <bits/stdc++.h>

/// @brief Turns off synchronization with stdio.
class io_accelerator {
 public:
  io_accelerator()
  {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // The following line needn't to be executed because the above line actually
    // had done this. std::cout.tie(nullptr);
  }
  io_accelerator(const io_accelerator&) = delete;
  io_accelerator(io_accelerator&&) = delete;
  io_accelerator& operator=(const io_accelerator&) = delete;
  io_accelerator& operator=(io_accelerator&&) = delete;
  ~io_accelerator()
  {
    std::ios::sync_with_stdio(true);
    std::cin.tie(&std::cout);
  }
};
