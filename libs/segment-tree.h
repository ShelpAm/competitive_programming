#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace shelpam {

class Segment_tree {
  struct Lazy_tag {
    auto operator+=(Lazy_tag const &rhs) -> Lazy_tag &
    {
      addition += rhs.addition;
      return *this;
    }

    std::int_fast64_t addition{};
  };

  struct Node {
    int left_end{};
    int right_end{};
  };

  struct Info {
    auto operator+=(Info const &rhs) -> Info &
    {
      sum += rhs.sum;
      return *this;
    }

    void apply(Lazy_tag const &lazy_tag, int const segment_length)
    {
      sum += lazy_tag.addition * segment_length;
    }

    std::int_fast64_t sum{};
  };

public:
  explicit Segment_tree(int const l, int const r)
      : _nodes(4 * (r - l + 1) + 1), _info(4 * (r - l + 1) + 1),
        _lazy_tags(4 * (r - l + 1) + 1)
  {
    build_tree(l, r, 1);
  }

  void apply(int const l, int const r, Lazy_tag const &tag)
  {
    apply_impl(l, r, 1, tag);
  }

  auto query(int const l, int const r) -> Info
  {
    return query_impl(l, r, 1);
  }

private:
  // Sets up segments that nodes manage.
  void build_tree(int const l, int const r, int const u)
  {
    _nodes[u].left_end = l;
    _nodes[u].right_end = r;

    if (l != r) {
      auto const m{(l + r) / 2};
      build_tree(l, m, u * 2);
      build_tree(m + 1, r, u * 2 + 1);
    }
  }

  void do_lazy_propagation(std::size_t const u)
  {
    if (!is_leaf(u)) {
      _lazy_tags[u * 2] += _lazy_tags[u];
      _lazy_tags[u * 2 + 1] += _lazy_tags[u];
      _info[u * 2].apply(_lazy_tags[u],
                         _nodes[u * 2].right_end - _nodes[u * 2].left_end + 1);
      _info[u * 2 + 1].apply(_lazy_tags[u], _nodes[u * 2 + 1].right_end -
                                                _nodes[u * 2 + 1].left_end + 1);
    }

    _lazy_tags[u] = {};
  }

  void apply_impl(int const l, int const r, std::size_t const u,
                  Lazy_tag const &tag)
  {
    _info[u].apply(tag, r - l + 1);

    if (l <= _nodes[u].left_end && _nodes[u].right_end <= r) {
      _lazy_tags[u] += tag;
      return;
    }

    if (_nodes[u * 2].right_end >= l) {
      apply_impl(l, std::min(r, _nodes[u * 2].right_end), u * 2, tag);
    }
    if (_nodes[u * 2 + 1].left_end <= r) {
      apply_impl(std::max(_nodes[u * 2 + 1].left_end, l), r, u * 2 + 1, tag);
    }
  }

  // We assume that [l, r] contains [_nodes[u].left_end, _nodes[u].right_end].
  [[nodiscard]] auto query_impl(int const l, int const r, std::size_t const u)
      -> Info
  {
    // If [l, r] nests node u, the segment node doesn't have to be divided
    // anymore. So we direct return the info of this node.
    if (l <= _nodes[u].left_end && _nodes[u].right_end <= r) {
      return _info[u];
    }

    do_lazy_propagation(u);

    Info res;
    if (_nodes[u * 2].right_end >= l) {
      res += query_impl(l, r, u * 2);
    }
    if (_nodes[u * 2 + 1].left_end <= r) {
      res += query_impl(l, r, u * 2 + 1);
    }
    return res;
  }

  [[nodiscard]] auto is_leaf(std::size_t const u) const -> bool
  {
    return _nodes[u].left_end == _nodes[u].right_end;
  }

  std::vector<Node> _nodes;
  std::vector<Info> _info;
  std::vector<Lazy_tag> _lazy_tags;
};

} // namespace shelpam
