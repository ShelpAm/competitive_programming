#pragma once

#include "../templates/main.cpp"

namespace shelpam {

// note: zero-indexed
template <std::size_t Base> class Hash {
public:
  template <typename R>
  constexpr Hash(R const &range)
      : _hash_value(range.size() + 1), _pow_base(range.size() + 1)
  {
    for (std::size_t i{1}; i != _hash_value.size(); ++i) {
      _hash_value[i] = _hash_value[i - 1] * Base + range[i - 1];
    }

    _pow_base[0] = 1;
    for (std::size_t i{1}; i != _pow_base.size(); ++i) {
      _pow_base[i] = _pow_base[i - 1] * Base;
    }
  }

  [[nodiscard]] auto query(std::size_t l, std::size_t r) const -> std::size_t
  {
    return _hash_value[r + 1] - (_hash_value[l] * _pow_base[r - l + 1]);
  }

private:
  std::vector<std::size_t> _hash_value;
  std::vector<std::size_t> _pow_base;
};

} // namespace shelpam
