#include <iostream>
#include <vector>
#include <utility>

using std::cout;
using std::endl;
using std::swap;
using std::vector;

class MinHeap {
  vector<char> heap;

  static int parent_index(int index) {
    return (index - 1) / 2;
  }

  static int left_index(int index) {
    return 2 * index + 1;
  }

  static int right_index(int index) {
    return 2 * index + 2;
  }

  bool has_children(int index) const {
    return has_left_child(index);
  }

  bool has_left_child(int index) const {
    return left_index(index) < heap.size();
  }

  bool has_right_child(int index) const {
    return right_index(index) < heap.size();
  }

  int smallest_child_index(int index) const noexcept {
    if (has_right_child(index)) {
      int l = left_index(index), r = l + 1;
      return heap[l] < heap[r] ? l : r;
    } else {  // if (has_left_child(index))
      return left_index(index);
    }
  }

public:
  void push(char c) {
    heap.push_back(c);
    // Note: We don't have to check if i != 0 because parent_index(0) == 0 and
    //   heap[0] is never less than heap[parent_index(0)]
    for (
        int i = heap.size() - 1, pi = parent_index(i);
        heap[i] < heap[pi];
        i = pi, pi = parent_index(i)) {
      swap(heap[i], heap[pi]);
    }
  }

  void pop() {
    //follow the rule, firstly swap the min node with the last node
    swap(heap.front(), heap.back());
    //then remove the min node
    heap.pop_back();

    for (
        int i = 0, sci = smallest_child_index(0);
        has_children(i) && heap[i] > heap[sci];
        i = sci, sci = smallest_child_index(i)) {
      swap(heap[i], heap[sci]);
    }
  }

  char top() const {
    return heap.front();
  }

  bool empty() const {
    return heap.empty();
  }
};

int main() {
    cout << "Priority Queues" << endl;
    MinHeap h;
  h.push('b');
  h.push('x');
  h.push('a');
  h.push('y');

  while(!h.empty()) {
    cout << h.top() << endl;
    h.pop();
  }

    return 0;
}