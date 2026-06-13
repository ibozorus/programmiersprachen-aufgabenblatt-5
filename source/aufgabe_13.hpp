#include "list.hpp"

#include <vector>

template <typename T>
bool has_same_content(List<T> const& list, std::vector<T> const& vec) {
  if (list.size() != vec.size()) return false;

  auto list_it = list.begin();
  auto vec_it = vec.begin();
  while (list_it != list.end()) {
    if (*list_it != *vec_it) return false;
    ++list_it;
    ++vec_it;
  }
  return true;
}

