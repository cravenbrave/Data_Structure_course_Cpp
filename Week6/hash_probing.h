#ifndef HASH_TABLE_PROBING_H_
#define HASH_TABLE_PROBING_H_

#include <cstddef>
#include <exception>
#include <iostream>
#include <utility>
#include <vector>


using std::cout;
using std::endl;
using std::invalid_argument;
using std::hash;
using std::move;
using std::size_t;
using std::vector;


static const size_t bucket_sizes[] = {
    3, 7, 17, 31, 67, 127, 257, 521, 1031, 2053, 4099, 8191, 16411, 32771,
    65537, 131071, 262147, 524287, 1048583, 2097169, 4194319, 8388617,
    16777259, 33554467, 67108879, 134217757, 268435459, 536870923, 1073741827,
    2147483647, 4294967311, 8589934609, 17179869209, 34359738421, 68719476767,
    137438953481, 274877906951, 549755813911, 1099511627791, 2199023255579,
    4398046511119, 8796093022237, 17592186044423, 35184372088891,
    70368744177679, 140737488355333, 281474976710677, 562949953421381,
    1125899906842679, 2251799813685269, 4503599627370517, 9007199254740997,
    18014398509482143, 36028797018963971
};


template <typename Key, typename Value>
class ProbingHashTable {
  static constexpr double max_load_factor = 0.75;

  struct Bucket {
    Key key;
    Value value;
    bool empty;
    Bucket() : empty(true) {}
  };

  vector<Bucket> buckets;
  int size_;
  int bucket_size_index_;

  static bool _insert(
      const Key& key,
      const Value& value,
      vector<Bucket>* buckets) {
    const size_t h = hash<Key>{}(key);
    size_t bucket_index, i;
    for (
        i = 0, bucket_index = (h + probe_amount(key, i)) % buckets->size();
        !(*buckets)[bucket_index].empty;
        ++i, bucket_index = (h + probe_amount(key, i)) % buckets->size()) {
    }
    (*buckets)[bucket_index].key = key;
    (*buckets)[bucket_index].value = value;
    (*buckets)[bucket_index].empty = false;
    return true;
  }

  static size_t probe_amount(const Key& key, const size_t i) {
    return i * i;
  }

public:
  ProbingHashTable() : buckets(bucket_sizes[0]), size_(0), bucket_size_index_(0) {}

  int size() const {
    return size_;
  }

  double load_factor() const {
    return static_cast<double>(size()) / buckets.size();
  }

  void rehash(int new_num_buckets) {
    vector<Bucket> new_buckets(new_num_buckets);
    for (const Bucket& b : buckets) {
      if (!b.empty) {
        _insert(b.key, b.value, &new_buckets);
      }
    }
    buckets = move(new_buckets);
  }

  bool insert(const Key& key, const Value& value) {
    if (load_factor() >= max_load_factor) {
      ++bucket_size_index_;
      rehash(bucket_sizes[bucket_size_index_]);
    }

    bool inserted = false;
    inserted = _insert(key, value, &buckets);
    // cout << "inserted?? : " << inserted << endl;
    if (inserted) {
      ++size_;
    }
    return inserted;
  }

  bool contains(const Key& key) const {
    const size_t h = hash<Key>{}(key);
    for (
        size_t i = 0, bucket_index = (h + probe_amount(key, i)) % buckets.size();
        !buckets[bucket_index].empty;
        ++i, bucket_index = (h + probe_amount(key, i)) % buckets.size()) {
      if (buckets[bucket_index].key == key) {
        return true;
      }
    }
    return false;
  }

  const Value& get(const Key& key) const {
    const size_t h = hash<Key>{}(key);
    for (
        size_t i = 0, bucket_index = (h + probe_amount(key, i)) % buckets.size();
        !buckets[bucket_index].empty;
        ++i, bucket_index = (h + probe_amount(key, i)) % buckets.size()) {
      if (buckets[bucket_index].key == key) {
        return buckets[bucket_index].value;
      }
    }
    throw invalid_argument(
        "Called .get() with a key that is not in the table.");
  }

  void print() {
    cout << "{";
    for (const Bucket& b : buckets) {
      if (b.empty) {
        cout << "_, ";
      } else {
        cout << b.key << ", ";
      }
    }
    cout << "}" << endl;
  }
};

#endif /* HASH_TABLE_PROBING_H_ */