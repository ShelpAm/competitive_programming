#include <array>
#include <climits>
#include <cstdint>
#include <vector>

namespace math {

using Value_type = std::uint_least64_t;
// template <std::unsigned_integral Value_type>
class Xor_linear_basis {
    static constexpr auto num_bits = sizeof(Value_type) * CHAR_BIT;

  public:
    void insert(Value_type x)
    {
        for (int i{num_bits - 1}; i != -1; --i) {
            if ((x & 1 << i) == 0) {
                continue;
            }

            if (bases_.at(i) == 0) {
                bases_.at(i) = x;
                return;
            }

            x ^= bases_.at(i);
        }
    }

    [[nodiscard]] bool find(Value_type x) const
    {
        for (int i{num_bits - 1}; i != -1; i--) {
            if ((x & Value_type{1} << i) == 0) {
                continue;
            }

            if (bases_.at(i) == 0) {
                return false;
            }

            x ^= bases_.at(i);
        }

        return true;
    }

    // Make bases_[i] the most clear (its lower bits will be eliminated.)
    [[nodiscard]] std::vector<Value_type> rebuild()
    {
        std::vector<Value_type> bases;
        for (std::size_t i{}; i != num_bits; ++i) {
            for (std::size_t j{}; j != i; ++j) {
                if (bases_.at(i) != 0 &&
                    ((bases_.at(i) & Value_type{1} << j) != 0)) {
                    bases_.at(i) ^= bases_.at(j);
                }
            }
            if (bases_.at(i) != 0) {
                bases.push_back(bases_.at(i));
            }
        }
        return bases;
    }

    [[nodiscard]] std::array<Value_type, num_bits> bases() const
    {
        return bases_;
    }

  private:
    // bases_[i] controls i-th bit.
    std::array<Value_type, num_bits> bases_{};
};

} // namespace math
