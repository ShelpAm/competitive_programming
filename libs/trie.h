#pragma once

#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

template <std::ranges::range T> class Trie {
    struct Node {
        using Value_type = std::ranges::range_value_t<T>;
        std::unordered_map<Value_type, std::size_t> children;
        bool is_terminal{};
        std::size_t terminal_count{};
    };

  public:
    static constexpr std::size_t npos{-1UZ};

    Trie() : nodes_(1) {}

    void insert(T const &range)
    {
        std::size_t x{0}; // root
        for (auto ch : range) {
            if (!nodes_[x].children.contains(ch)) {
                nodes_[x].children.insert({ch, nodes_.size()});
                nodes_.push_back({});
            }
            x = nodes_[x].children[ch];
        }
        nodes_[x].is_terminal = true;
        ++nodes_[x].terminal_count;
    }

    [[nodiscard]] bool find(T const &range) const
    {
        auto i = find_terminal(0, range);
        return i != npos && nodes_[i].is_terminal;
    }

    void remove(T const &range)
    {
        if (auto i = find_terminal(0, range); i != npos) {
            if (--nodes_[i].terminal_count == 0) {
                nodes_[i].is_terminal = false;
            }
        }
    }

  private:
    std::vector<Node> nodes_;

    // Returns npos if not found
    [[nodiscard]] std::size_t find_terminal(std::size_t root,
                                            T const &range) const
    {
        auto x = root; // root
        for (auto ch : range) {
            if (!nodes_[x].children.contains(ch)) {
                return npos;
            }
            x = nodes_[x].children.at(ch);
        }
        return x;
    }
};
