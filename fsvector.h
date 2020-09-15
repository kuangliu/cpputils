// Fix sized vector
#pragma once

#include <vector>
#include <deque>

template <typename T>
class fsvector {
 public:
  fsvector() = default;

  virtual ~fsvector() = default;

  fsvector(const int capacity, const T& default_value) {
    capacity_ = capacity;
    data_ = std::deque<T>(capacity, default_value);
  }

  void Append(const T& x) {
    data_.push_back(x);
    while (data_.size() > capacity_) {
      data_.pop_front();
    }
  }

  void AppendVector(const std::vector<T>& v) {
    for (const auto& x : v) {
      Append(x);
    }
  }

  std::vector<T> ToVector() {
    return std::vector<T>(data_.begin(), data_.end());
  }

 private:
  size_t capacity_ = 0;
  std::deque<T> data_;
};
