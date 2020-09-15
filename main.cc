#include <iostream>
#include <vector>

#include "fsvector.h"
#include "sequence_smoother.h"

int main() {
  std::cout << "Testing fsvector: " << std::endl;
  fsvector<int> a(10, 0);
  for (int i = 0; i < 20; ++i) {
    a.Append(i);
  }
  std::vector<int> b = a.ToVector();
  for (int x : b) {
    std::cout << x << std::endl;
  }

  std::cout << "Testing sequence_smoother: " << std::endl;
  SequenceSmoother sm(5);
  sm.Add(0);
  sm.Add(0);
  sm.Add(1);
  sm.Add(1);
  sm.Add(1);
  std::cout << sm.AnyOf(1) << std::endl;
  std::cout << sm.AllOf(1) << std::endl;
  std::cout << sm.AnyOfConsectiveN(1, 3) << std::endl;
  std::cout << sm.ToString() << std::endl;

  return 0;
}
