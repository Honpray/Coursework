#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using std::vector;

struct Segment {
  int start, end;
};

bool sort_segments(const Segment &a, const Segment &b) {
  return (a.end < b.end);
}

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;
  // write your code here
  std::sort(segments.begin(), segments.end(), sort_segments);
  int current_point = segments[0].end;
  points.push_back(current_point);
  for (size_t i = 0; i < segments.size(); ++i) {
    if (current_point < segments[i].start || current_point > segments[i].end) {
      current_point = segments[i].end;
      points.push_back(current_point);
    }
  }
  return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
