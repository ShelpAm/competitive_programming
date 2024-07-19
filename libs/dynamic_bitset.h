#pragma once

// Author: ShelpAm
//
// DON'T use this header as it hasn't been fully implemented yet.

#include <bitset>
#include <cassert>
#include <climits>
#include <cstdint>
#include <vector>

template <typename Bits_container> class Dynamic_bitset {
  static constexpr auto num_bits_in_container{sizeof(Bits_container) *
                                              CHAR_BIT};

public:
  Dynamic_bitset(std::size_t num_bits)
      : _num_bits(num_bits),
        _bits((num_bits + num_bits_in_container - 1) / num_bits_in_container)
  {
  }

  [[nodiscard]] auto test(int index) const -> bool
  {
    assert(0 <= index && index < _num_bits);
    return _bits[index / num_bits_in_container] >>
               (index % num_bits_in_container) &
           1;
  }

  void set(int index)
  {
    assert(0 <= index && index < _num_bits);
    _bits[index / num_bits_in_container] |= Bits_container{1}
                                            << (index % num_bits_in_container);
  }

  void reset(int index)
  {
    assert(0 <= index && index < _num_bits);
    _bits[index / num_bits_in_container] &=
        ~(Bits_container{1} << (index % num_bits_in_container));
  }

  // Simulates `b |= b << shift`
  void or_shift(int shift) { throw "Unimplemented."; }

private:
  std::size_t _num_bits;
  std::vector<Bits_container> _bits;
};

using mybitset = Dynamic_bitset<std::uint_fast64_t>;
