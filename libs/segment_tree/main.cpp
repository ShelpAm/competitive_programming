#include <bits/stdc++.h>
using namespace std;

using i64 = ::std::int_fast64_t;
using u64 = ::std::uint_fast64_t;
template<typename T> [[maybe_unused]] constexpr T inf
    = std::numeric_limits<T>::max() >> 2;
template<> [[maybe_unused]] constexpr double inf<double>
    = std::numeric_limits<double>::max() / 4;
[[maybe_unused]] constexpr double eps = 1e-6;
[[maybe_unused]] constexpr u64 msb(u64 const i)
{
  assert(i != 0);
  return sizeof(u64) * CHAR_BIT - 1 - __builtin_clzll(i | 1);
}

template<typename info_type, typename tag_type> class segment_tree {
 public:
  segment_tree(u64 n);
  // The input array should start from the index 0.
  segment_tree(std::vector<i64> const& raw);

  [[deprecated("unimplemented")]] void modify_range(u64 a, u64 b, u64 x)
  {
    modify_range_impl(1, 0, n_, a, b, x);
  }
  void apply_range(u64 a, u64 b, tag_type const& tag)
  {
    apply_range_impl(1, 0, n_, a, b, tag);
  }
  info_type query_range(u64 a, u64 b)
  {
    return query_range_impl(1, 0, n_, a, b);
  }
 private:
  // pull info from subtree(s)
  void pull(u64 p);

  // push tag into subtree(s)
  void push(u64 p, u64 l, u64 r);

  // apply tag on node `p`
  void apply(u64 p, tag_type const& tag);

  void modify_range_impl(u64 p, u64 l, u64 r, u64 a, u64 b, i64 x);
  void apply_range_impl(u64 p, u64 l, u64 r, u64 a, u64 b, tag_type const& tag);
  info_type query_range_impl(u64 p, u64 l, u64 r, u64 a, u64 b);

  [[deprecated]] void add_on_segment_impl(u64 a, u64 b, i64 d, u64 l, u64 r,
                                          u64 x)
  {
    if (a <= l && r <= b) {
      info_[x].tag += d;
      return;
    }

    push(l, r, x);
    u64 const mid = (l + r) / 2;
    if (a <= mid) {
      add_on_segment_impl(a, b, d, l, mid, x * 2);
    }
    if (mid < b) {
      add_on_segment_impl(a, b, d, mid + 1, r, x * 2 + 1);
    }
    pull(x);
  }

  u64 n_;
  std::vector<info_type> info_;
  std::vector<tag_type> tags_;
};
template<typename info_type, typename tag_type>
segment_tree<info_type, tag_type>::segment_tree(u64 const n)
    : n_(n), info_(4ULL << msb(n_), info_type{0, 0, 0, 0}),
      tags_(4ULL << msb(n_))
{}
template<typename info_type, typename tag_type>
segment_tree<info_type, tag_type>::segment_tree(std::vector<i64> const& raw)
    : segment_tree(raw.size())
{
  auto build = [this, &raw](auto build, u64 p, u64 l, u64 r) {
    // if we don't change the structure of the tree, we won't save info of
    // internal nodes, since it can be calculated at runtime.
    if (r - l == 1) {
      info_[p] = raw[l];
      return;
    }

    u64 const m = (l + r) / 2;
    build(build, p * 2, l, m);
    build(build, p * 2 + 1, m, r);
    pull(p);
  };
  build(build, 1, n_, 1);
}
template<typename info_type, typename tag_type>
void segment_tree<info_type, tag_type>::pull(u64 p)
{
  info_[p] = info_[p * 2] + info_[p * 2 + 1];
}
template<typename info_type, typename tag_type>
void segment_tree<info_type, tag_type>::push(u64 p, u64 l, u64 r)
{
  if (r - l == 1) {
    return;
  }

  apply(p * 2, tags_[p]);
  apply(p * 2 + 1, tags_[p]);
  tags_[p] = tag_type{};
}
template<typename info_type, typename tag_type>
void segment_tree<info_type, tag_type>::apply(u64 p, tag_type const& tag)
{
  info_[p].apply(tag);
  tags_[p].apply(tag);
}
template<typename info_type, typename tag_type> void
segment_tree<info_type, tag_type>::modify_range_impl([[maybe_unused]] u64 p,
                                                     u64 l, u64 r, u64 a, u64 b,
                                                     [[maybe_unused]] i64 x)
{
  // ranges not intersecting
  if (b <= l || r <= a) {
    return;
  }
}
template<typename info_type, typename tag_type>
void segment_tree<info_type, tag_type>::apply_range_impl(u64 p, u64 l, u64 r,
                                                         u64 a, u64 b,
                                                         tag_type const& tag)
{
  // ranges not intersecting
  if (b <= l || r <= a) {
    return;
  }

  // range fully included in [a, b)
  if (a <= l && r <= b) {
    apply(p, tag);
    return;
  }

  push(p, l, r);
  u64 const m = (l + r) / 2;
  apply_range_impl(p * 2, l, m, a, b, tag);
  apply_range_impl(p * 2 + 1, m, r, a, b, tag);
  pull(p);
}
template<typename info_type, typename tag_type>
info_type segment_tree<info_type, tag_type>::query_range_impl(u64 p, u64 l,
                                                              u64 r, u64 a,
                                                              u64 b)
{
  // ranges not intersecting
  if (b <= l || r <= a) {
    return info_type{};
  }

  // range fully included in [a, b)
  if (a <= l && r <= b) {
    return info_[p];
  }

  push(l, r, p);
  u64 const m = (l + r) / 2;
  return query_range_impl(p * 2, l, m, a, b)
         + query_range_impl(p * 2 + 1, m, r, a, b);
}

struct tag {
  void apply(tag const& tag) { add += tag.add; }
  i64 add;
};
struct info {
  info operator+(info const& rhs) const
  {
    return info{.min = ::min(this->min, rhs.min),
                .max = ::max(this->max, rhs.max),
                .sum = this->sum + rhs.sum,
                .act = this->act + rhs.act};
  }
  void apply(tag const& tag)
  {
    min += tag.add;
    max += tag.add;
    sum += act * tag.add;
  }
  i64 min = inf<i64>;
  i64 max = -inf<i64>;
  i64 sum = 0;
  i64 act = 0;
};
using segtree = segment_tree<info, tag>;
