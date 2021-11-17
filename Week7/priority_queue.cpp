#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <queue>

using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::priority_queue;
using std::vector;
using std::string;

typedef pair<int, string> PriorityString;

struct PriorityStringComparator {
  constexpr bool operator()(const PriorityString& lhs, const PriorityString& rhs) const {
      //left > right ==> min heap
      //right > left ==> max heap
    return lhs.first > rhs.first;
  }
};

typedef priority_queue<PriorityString, vector<PriorityString>, PriorityStringComparator>
    PriorityStringQueue;

int main() {
  PriorityStringQueue q;
  q.push(make_pair(111, "1 a"));
  q.push(make_pair(333, "3 c"));
  q.push(make_pair(222, "2 b"));
  while (!q.empty()) {
    cout << q.top().second << endl;
    q.pop();
  }
  return 0;
}
