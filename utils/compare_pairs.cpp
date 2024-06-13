#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

bool compare_pairs(const pair<float, int> &a, const pair<float, int> &b) {
  return a.first > b.first; // Classifica em ordem decrescente
}