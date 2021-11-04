#ifndef HASH_TABLE_PROBING_H_
#define HASH_TABLE_PROBING_H_

//for size_t
#include <cstddef>
#include <exception>
#include <iostream>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::hash;
using std::invalid_argument;
using std::move;
using std::size_t;
using std::vector;
using std::exception;

template <typename Key, typename Value>
class ProbingHashTable
{
    static constexpr double max_load_factor = 0.5;
    struct Bucket
    {
        Key key;
        Value value;
        bool empty;
        Bucket() : empty(true) {}
    };
    vector<Bucket> buckets;
    int size_;

    static bool _insert(const Key &key, const Value &value, vector<Bucket> *buckets)
    {
        size_t bucket_index;
        for (bucket_index = hash<Key>{}(key) % buckets->size();
             !(*buckets)[bucket_index].empty;
             //bucket_index = (bucket_index + 1) % buckets->size()
             bucket_index++)
        {
            if ((*buckets)[bucket_index].key == key)
            {
                return false;
            }
        }
        (*buckets)[bucket_index].key = key;
        (*buckets)[bucket_index].value = value;
        (*buckets)[bucket_index].empty = false;
        // ++size_;
        return true;
    }

public:
    ProbingHashTable() : buckets(10), size_(0) {}

    int size() const
    {
        return size_;
    }

    double load_factor() const
    {
        return static_cast<double>(size()) / buckets.size();
    }
    void rehash(int new_num_buckets)
    {
        vector<Bucket> new_buckets(new_num_buckets);
        for (const Bucket &b : buckets)
        {
            if (!b.empty)
            {
                _insert(b.key, b.value, &new_buckets);
            }
        }
        buckets = move(new_buckets);
    }

    bool insert(const Key &key, const Value &value)
    {
        //resize
        if (load_factor() > max_load_factor)
        {
            rehash(2 * buckets.size());
        }

        bool is_inserted = _insert(key, value, &buckets);
        if (is_inserted)
        {
            size_++;
        }
        return is_inserted;
    }

    const Value& get(const Key &key) const
    {
        for (size_t bucket_index = hash<Key>{}(key) % buckets.size();
             !buckets[bucket_index].empty;
             bucket_index = (bucket_index + 1) % buckets.size()
             )
        {
            if (buckets[bucket_index].key == key)
            {
                return buckets[bucket_index].value;
            }
        }
        throw invalid_argument("Don\'t have such key.");
    }

    bool contains(const Key &key) const
    {
        for (size_t bucket_index = hash<Key>{}(key) % buckets.size();
             !buckets[bucket_index].empty;
             bucket_index = (bucket_index + 1) % buckets.size()
             )
        {
            if (buckets[bucket_index].key == key)
            {
                return true;
            }
        }
        return false;
    }

    void print()
    {
        cout << "{";
        for (const Bucket &b : buckets)
        {
            if (b.empty)
            {
                cout << "_, ";
            }
            else
            {
                // cout << b.key << ": " << b.value << ", ";
                cout << b.key << ", ";
            }
        }
        cout << "}" << endl;
    }
};

#endif