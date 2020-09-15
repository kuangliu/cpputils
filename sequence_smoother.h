#pragma once

#include <deque>
#include <algorithm>

class SequenceSmoother {
 public:
  SequenceSmoother() = default;

  SequenceSmoother(const size_t cache_size) : cache_size_(cache_size) {}

  virtual ~SequenceSmoother() = default;

  void Add(const int x) {
    cache_.push_back(x);
    while (cache_.size() > cache_size_) {
      cache_.pop_front();
    }
  }

  bool AllOf(const int value) {
    return std::all_of(cache_.begin(), cache_.end(),
                       [&](int x) { return x == value; });
  }

  bool AnyOf(const int value) {
    return std::any_of(cache_.begin(), cache_.end(),
                       [&](int x) { return x == value; });
  }

  bool AnyOfConsectiveN(const int value, const size_t window_size) {
    if (window_size > cache_.size()) {
      return false;
    }

    std::vector<int> sum(cache_.size(), 0);
    sum[0] = cache_[0];
    for (size_t i = 1; i < window_size; ++i) {
      sum[i] = cache_[i] + sum[i - 1];
    }

    for (size_t i = window_size; i < cache_.size(); ++i) {
      sum[i] = cache_[i] + sum[i - 1] - cache_[i - window_size];
    }

    return std::any_of(sum.begin(), sum.end(), [&](int x) {
      return x == static_cast<int>(window_size);
    });
  }

  std::string ToString() {
    std::vector<char> v;
    std::transform(cache_.begin(), cache_.end(), std::back_inserter(v),
                   [](int x) -> char { return x + '0'; });
    return std::string(v.begin(), v.end());
  }

 private:
  size_t cache_size_;
  std::deque<int> cache_;
};
