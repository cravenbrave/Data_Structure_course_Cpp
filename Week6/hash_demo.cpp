#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <utility>

using namespace std;


unsigned int name_hash(const string& name) {
  return hash<string>{}(name);
}

// We assume no name is empty! (In other words, "" is not a valid name)
class NamesHashSet {
  static constexpr double max_load_factor = 1.0;

  vector<set<string> > names;
  int size_;

public:
  NamesHashSet() : size_(0) {
    names.resize(1);
  }

  int size() {
    return size_;
  }

  bool contains(const string& name) {
    const set<string>& subset = names[name_hash(name) % names.size()];
    return subset.find(name) != subset.end();
  }

  bool insert(const string& name) {
    ++size_;
    if (size_ > names.size() * max_load_factor) {
      rehash(2 * names.size());
    }
    return names[name_hash(name) % names.size()].insert(name).second;
  }

  void rehash(int new_num_buckets) {
    vector<set<string> > new_names;
    new_names.resize(new_num_buckets);
    for (const set<string>& bucket : names) {
      for (const string& name : bucket) {
          //tip: resize and mod new_names.size!! not names.size
        new_names[name_hash(name) % new_names.size()].insert(name);
      }
    }
    names = move(new_names);
  }

  void print() {
    cout << '(';
    for (const auto& bucket : names) {
      cout << '[';
      for (const string& name : bucket) {
        cout << name << ", ";
      }
      cout << "], ";
    }
    cout << ')' << endl;;
  }
};



int main() {
  vector<string> names_vec = {"Alice", "Brock", "Mikel", "Maya", "Nana"};
    NamesHashSet names;
  for (const string& name : names_vec) {
    cout << "Inserting " << name << " with hash " << name_hash(name) << ":" << endl;
    names.insert(name);
    names.print();
  }
  for (const string& name : names_vec) {
    cout << "names.contains(\"" << name << "\") == " << names.contains(name) << endl;
  }
  for (const string& name : {"Not a name", "Coconuts"}) {
    cout << "names.contains(\"" << name << "\") == " << names.contains(name) << endl;
  }

  return 0;
}