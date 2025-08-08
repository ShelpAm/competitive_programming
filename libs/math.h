#include <bits/stdc++.h>

namespace math {

constexpr double eps{1e-8};

template <typename T> class Matrix {
  public:
    // Matrix() : mat_() {}
    Matrix(std::size_t n, std::size_t m, T val) : n_(n), m_(m)
    {
        assert(n == m && "Matrix must be square to use scalar constructor");

        for (std::size_t i{}; i != n; ++i) {
            get(i, i) = val;
        }
    }
    Matrix(std::vector<std::vector<T>> mat)
        : mat_(mat), n_{mat.size()}, m_{mat[0].size()}
    {
    }

    std::vector<T> &operator[](std::size_t i)
    {
        return mat_[i];
    }

    std::vector<T> const &operator[](std::size_t i) const
    {
        return mat_[i];
    }

    [[nodiscard]] T &get(std::size_t i, std::size_t j)
    {
        return mat_.at(i).at(j);
    }

    [[nodiscard]] T get(std::size_t i, std::size_t j) const
    {
        return mat_.at(i).at(j);
    }

    [[nodiscard]] std::size_t n() const
    {
        return n_;
    }

    [[nodiscard]] std::size_t m() const
    {
        return m_;
    }

  private:
    std::vector<std::vector<T>> mat_;
    std::size_t n_;
    std::size_t m_;
};

template <typename T>
[[nodiscard]] Matrix<T> operator*(Matrix<T> const &lhs, Matrix<T> const &rhs)
{
    assert(lhs.m() == rhs.n());

    auto const n = lhs.n();
    auto const m = lhs.m();
    auto const p = rhs.m();

    Matrix<T> res{};
    for (std::size_t i{}; i != n; ++i) {
        for (std::size_t j{}; j != p; ++j) {
            for (std::size_t k{}; k != m; ++k) {
                res.get(i, j) += lhs.get(i, k) * rhs.get(k, j);
            }
        }
    }
    return res;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, Matrix<T> const &mat)
{
    for (std::size_t i{}; i != mat.n(); ++i) {
        for (std::size_t j{}; j != mat.m(); ++j) {
            os << mat.get(i, j) << ' ';
        }
        os << '\n';
    }
}

// template<>

enum class Solution_kind {
    infinite,
    only_one,
    DNE // Does not exist
};

template <typename Matrix> struct Gauss_elimination_result {
    Solution_kind solution_kind{};
    Matrix eliminated_matrix;
    std::vector<int> pivot_row;
};

template <typename Matrix>
Gauss_elimination_result<Matrix> gauss_elimination(Matrix a, int n, int m,
                                                   int p)
    requires requires(int i, int j) {
        a[i][j];
        std::abs(a[i][j]);
    }
{
    // The row that i-th column pivot resides in. -1 represents this column
    // doesn't contain a pivot.
    std::vector<int> pivot_row(m, -1);
    int row{};
    for (int j{}; j != m; ++j) {

        // Find the row with max a[`row`][j], and swap it to the top(`row`)
        int max_row{row};
        for (int i{row + 1}; i != n; ++i) {
            if (std::abs(a[i][j]) > std::abs(a[max_row][j])) {
                max_row = i;
            }
        }
        if (std::abs(a[max_row][j]) < eps) {
            continue;
        }
        pivot_row[j] = row;
        std::swap(a[row], a[max_row]);

        // 向下消去
        for (int i{row + 1}; i != n; ++i) {
            if (a[i][j]) {
                a[i] ^= a[row];
            }
        }
        ++row;
        if (row == n) {
            break;
        }
    }

    // 向上消去
    for (int j{m - 1}; j != -1; --j) {
        if (pivot_row[j] == -1) {
            continue;
        }

        for (int i{}; i != pivot_row[j]; ++i) {
            if (a[i][j]) {
                a[i] ^= a[pivot_row[j]];
            }
        }
    }

    // Identify DNE situations
    for (int j{m}; j != m + p; ++j) {
        for (int i{row}; i != n; ++i) {
            if (a[i][j] > eps) {
                // No solution
                return {.solution_kind = Solution_kind::DNE,
                        .eliminated_matrix = a,
                        .pivot_row = pivot_row};
            }
        }
    }

    auto const num_pivots = n - std::ranges::count(pivot_row, -1); // 主元个数
    if (num_pivots < m) {
        // Many solutions
        return {.solution_kind = Solution_kind::infinite,
                .eliminated_matrix = a,
                .pivot_row = pivot_row};
    }

    // Only one solution
    return {.solution_kind = Solution_kind::only_one,
            .eliminated_matrix = a,
            .pivot_row = pivot_row};
};

} // namespace math
