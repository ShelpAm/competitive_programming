#include <cstdint>
#include <vector>

namespace math {
template <std::unsigned_integral Value_type> class Xor_basis {
    static constexpr auto num_bits{sizeof(Value_type) * CHAR_BIT};

  public:
    void insert(Value_type x)
    {
        for (int i{num_bits - 1}; i != -1; --i) {
            if ((x & Value_type{1} << i) == 0) {
                continue;
            }

            if (_bases.at(i) == 0) {
                _bases.at(i) = x;
                return;
            }

            x ^= _bases.at(i);
        }
    }

    [[nodiscard]] auto find(Value_type x) const -> bool
    {
        for (int i{num_bits - 1}; i != -1; i--) {
            if ((x & Value_type{1} << i) == 0) {
                continue;
            }

            if (_bases.at(i) == 0) {
                return false;
            }

            x ^= _bases.at(i);
        }

        return true;
    }

    [[nodiscard]] auto bases() const -> std::array<Value_type, num_bits> const &
    {
        return _bases;
    }

  private:
    std::array<Value_type, num_bits> _bases{};
};
} // namespace math
