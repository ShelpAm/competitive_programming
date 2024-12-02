#pragma once

#include "../templates/main.cpp"

namespace sparse_table {
// Note: 0-indexed
template <typename T, typename F> class Sparse_table {
  public:
    constexpr Sparse_table(std::vector<T> table)
        : _table(msb(table.size()) + 1, std::move(table))
    {
        for (std::size_t i{1}; i != _table.size(); ++i) {
            for (std::size_t j{}; j != _table[0].size(); ++j) {
                _table[i][j] =
                    _f(_table[i - 1][j], _table[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    [[nodiscard]] constexpr auto query(std::size_t l, std::size_t r) const
        -> decltype(F{}(T{}, T{}))
    {
        assert(r >= l);
        auto const k{msb(r - l + 1)};
        return _f(_table[k][l], _table[k][r - (1 << k) + 1]);
    }

  private:
    std::vector<std::vector<T>> _table;
    F _f;
};

namespace details {
template <typename T> struct Min {
    constexpr auto operator()(T const &lhs, T const &rhs) const -> T const &
    {
        return std::min(lhs, rhs);
    }
};
template <typename T> struct Max {
    constexpr auto operator()(T const &lhs, T const &rhs) const -> T const &
    {
        return std::max(lhs, rhs);
    }
};
} // namespace details

template <typename T> class Min_st : public Sparse_table<T, details::Min<T>> {
  public:
    using Sparse_table<T, details::Min<T>>::Sparse_table;
};
template <typename T> Min_st(std::vector<T>) -> Min_st<T>;
template <typename T> class Max_st : public Sparse_table<T, details::Max<T>> {
  public:
    using Sparse_table<T, details::Max<T>>::Sparse_table;
};
template <typename T> Max_st(std::vector<T>) -> Max_st<T>;
} // namespace sparse_table
