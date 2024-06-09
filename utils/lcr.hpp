#ifndef LCR_HPP
#define LCR_HPP

#include <vector>

using namespace std;

vector<int> lcr(
  const vector<int>& solution_line, 
  const vector<int>& profits, 
  const vector<int>& weights, 
  const float& alpha
);

void print_list(const vector<int> &list);

#endif /* LCR_HPP */