#include <algorithm>
#include <concepts>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <numeric>
#include <ranges>
#include <type_traits>
#include <vector>

auto copy_except(
  const std::ranges::random_access_range auto& items,
  std::integral auto index
) {
  auto result = typename std::remove_reference<decltype(items)>::type();
  result.reserve(items.size() - 1);
  std::copy(items.begin(), items.begin() + index, std::back_inserter(result));
  std::copy(items.begin() + index + 1, items.end(), std::back_inserter(result));
  return result;
}

auto write_items(
  std::ostream& out, const std::ranges::range auto& items, auto sep
) -> std::ostream& {
  for (const auto& item: items | std::ranges::views::take(1)) {
    out << item;
  }
  for (const auto& item: items | std::ranges::views::drop(1)) {
    out << sep << item;
  }
  return out;
}

using Index = std::ptrdiff_t;

// Dense only, not sparse.
template<typename Val>
struct Tensor {
  Tensor() {
    //
  }

  Tensor(std::initializer_list<Val> row) {
    sizes_ = {Index(row.size())};
    init();
    *vals_ = row;
  }

  Tensor(std::initializer_list<std::initializer_list<Val>> rows) {
    sizes_ = {
      Index(rows.size()), rows.size() ? Index(rows.begin()->size()) : 0,
    };
    init();
    for (auto& row: rows) {
      auto begin = vals_->begin() + sizes_[1] * (&row - rows.begin());
      std::copy(row.begin(), row.end(), begin);
    }
  }

  static auto zeros(const std::vector<Index>& shape) -> Tensor<Val> {
    auto result = Tensor<Val>{};
    result.sizes_ = shape;
    result.init();
    return result;
  }

  struct Iterator {
    using difference_type = Index;

    const Tensor* tensor = nullptr;
    Index index = 0;

    auto operator++() -> Iterator& {
      index += 1;
      return *this;
    }

    auto operator++(int) -> Iterator {
      auto result = {tensor, index};
      index += 1;
      return result;
    }

    auto operator*() -> Tensor {
      return tensor->at_by_dim(index);
    }

    // auto operator!=(Iterator other) -> bool {
    //   return !(*this == other);
    // }

    // auto operator==(Iterator other) -> bool {
    //   return tensor == other.tensor && index == other.index;
    // }

    friend auto operator<=>(const Iterator&, const Iterator&) = default;

    auto operator-(const Iterator& other) -> Index {
      // TODO Fail if tensors differ.
      return index - other.index;
    }
  };

  auto at_by_dim(Index index, Index dim = 0) const -> const Tensor<Val> {
    auto result = Tensor<Val>{};
    result.offset_ = offset_ + index * strides_.at(dim);
    result.sizes_ = copy_except(sizes_, dim);
    result.strides_ = copy_except(strides_, dim);
    result.vals_ = vals_;
    return result;
  }

  auto begin() const -> const Iterator {
    return {this, 0};
  }

  auto end() const -> const Iterator {
    return {this, ndim()};
  }

  auto ndim() const -> Index {return sizes_.size();}

  auto offset() const -> Index {return offset_;}

  auto operator[](std::initializer_list<Index> coord) const -> Val {
    // std::cout << "index: " << index(coord) << std::endl;
    return vals_->at(index(coord));
  }

  auto operator()(std::convertible_to<Index> auto... coord) const -> Val {
    return (*this)[{Index(coord)...}];
  }

  auto sizes() const -> const std::vector<Index>& {return sizes_;}

  auto strides() const -> const std::vector<Index>& {return strides_;}

  auto vals() const -> const std::vector<Val>& {return *vals_;}

private:
  Index offset_ = 0;
  std::vector<Index> sizes_;
  std::vector<Index> strides_;
  std::shared_ptr<std::vector<Val>> vals_;

  auto index(std::initializer_list<Index> coord) const -> Index {
    return std::transform_reduce(
      coord.begin(), coord.end(), strides_.cbegin(), offset_
    );
  }

  auto init() -> void {
    strides_.resize(sizes_.size());
    // Calculate strides in row majorish order back to front.
    // Imperative seems easier here at the moment and good enough.
    auto stride = 1;
    for (auto i = sizes_.size(); i; i -= 1) {
      strides_[i - 1] = stride;
      stride *= sizes_[i - 1];
    }
    // Final "stride" is for the whole array size.
    vals_ = std::make_shared<std::vector<Val>>(stride);
  }
};

template<typename Val>
auto operator<<(std::ostream& out, const std::vector<Val>& a) -> std::ostream& {
  return write_items(out, a, ' ');
}

template<typename Val>
auto operator<<(std::ostream& out, const Tensor<Val>& a) -> std::ostream& {
  switch (a.ndim()) {
    case 0: {
      out << a(0);
      break;
    }
    case 1: {
      write_items(out, a, ' ');
      break;
    }
    case 2: {
      write_items(out, a, '\n');
      break;
    }
    default: {
      out << "big ol' tensor";
      break;
    }
  }
  return out;
}

// template<typename Val>
// auto mean(const Tensor<Val>& a, Index axis) -> Tensor<Val> {
//   return {};
// }

auto main() -> int {
  auto a = Tensor<double>::zeros({2, 3});
  std::cout << a[{0, 0}] << std::endl;
  std::cout << a[{1, 0}] << std::endl;
  std::cout << a[{1, 2}] << std::endl;
  // auto b = Tensor<double>{{1, 2, 3}, {4, 5, 6}};
  auto b = Tensor{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
  std::cout << b[{0, 0}] << std::endl;
  std::cout << b[{1, 0}] << std::endl;
  std::cout << b[{1, 2}] << std::endl;
  std::cout << b(1, 2) << std::endl;
  // auto m = mean(b, 0);
  std::cout << b.sizes() << std::endl;
  std::cout << b.strides() << std::endl;
  auto row = b.at_by_dim(1, 0);
  std::cout << row.offset() << std::endl;
  std::cout << row.sizes() << std::endl;
  std::cout << row.strides() << std::endl;
  std::cout << row << std::endl;
  // std::cout << std::is_constructible<decltype(row.begin())>::value << std::endl;
  // std::input_or_output_iterator auto r = row.begin();
  // std::ranges::end(row);
  // std::ranges::range auto& r = row;
  // std::cout << (row.begin() != row.end()) << std::endl;
}
