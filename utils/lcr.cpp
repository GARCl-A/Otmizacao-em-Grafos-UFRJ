#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

void print_list(const vector<int> &list) {
  for (size_t i = 0; i < list.size(); ++i) {
    cout << list[i];
    if (i != list.size() - 1) {
      cout << " ";
    }
  }
  cout << endl;
}

void print_pair(const pair<float, int> &pair) {
  cout << "(" << pair.first << ", " << pair.second << ")";
}

void print_list(const vector<pair<float, int>> &list) {
  for (size_t i = 0; i < list.size(); ++i) {
    print_pair(list[i]);
    if (i != list.size() - 1) {
      cout << " ";
    }
  }
  cout << endl;
}

bool compare_pairs(const pair<float, int> &a, const pair<float, int> &b) {
  return a.first > b.first; // Classifica em ordem decrescente
}

vector<int> lcr(
  const vector<int>& solution_line, 
  const vector<int>& profits, 
  const vector<int>& weights, 
  const float& alpha
) {
  cout << "solution_line" << endl;
  print_list(solution_line);

  vector<pair<float, int>> solution_line_sorted;
  cout << "solution_line_with_weights" << endl;
  print_list(solution_line_sorted);
  for (size_t i = 0; i < solution_line.size(); i++) {
    if (solution_line[i] == 1) {
      float ratio = static_cast<float>(weights[i]) / profits[i];
      solution_line_sorted.push_back({ratio, i});
    }
  }
  cout << "solution_line_with_weights" << endl;
  print_list(solution_line_sorted);

  // Ordena solution_line_sorted em ordem decrescente
  sort(solution_line_sorted.begin(), solution_line_sorted.end(), compare_pairs);
  print_list(solution_line_sorted);

  // Seleciona min e max
  float min = solution_line_sorted.back().first;
  float max = solution_line_sorted.front().first;
  cout << "min: " << min << " | max: " << max << endl;

  vector<int> lcr;
  // Para cada elemento em solution_line_sorted
  for (size_t i = 0; i < solution_line_sorted.size(); i++) {
    float current_ratio = solution_line_sorted[i].first;
    int current_index = solution_line_sorted[i].second;
    // Se min <= s_line_sorted[i] <= max + alpha, adiciona o elemento na lcr
    if (min <= current_ratio && current_ratio <= (max + alpha * (min - max))) {
      lcr.push_back(current_index);
    }
  }

  print_list(lcr);
  return lcr;
}

