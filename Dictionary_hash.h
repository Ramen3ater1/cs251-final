#ifndef DICTIONARY_HASH_H
#define DICTIONARY_HASH_H

#include <string>
#include <stdexcept>
#include <cstddef>

class Dictionary_Hash {
private:
    struct Entry {
        std::string key;
        int value;
        Entry *next;

        Entry(const std::string &k, int v, Entry *n = nullptr)
            : key(k), value(v), next(n) {}
    };

    Entry **buckets;
    int bucket_count;
    int item_count;

    static constexpr double MAX_LOAD_FACTOR = 0.75;

    static std::size_t hash_string(const std::string &key);

    int bucket_index(const std::string &key) const;

    static Entry *copy_chain(Entry *head);
    static void delete_chain(Entry *head);

    void copy_from(const Dictionary_Hash &other);
    void clear();

    Dictionary_Hash add_without_resize(const std::string &key, int value) const;
    Dictionary_Hash resize_and_rehash(int new_bucket_count) const;

public:
    Dictionary_Hash();
    Dictionary_Hash(const Dictionary_Hash &other);
    Dictionary_Hash &operator=(const Dictionary_Hash &other);
    ~Dictionary_Hash();

    bool contains(const std::string &key) const;
    int lookup(const std::string &key) const;
    Dictionary_Hash add(const std::string &key, int value) const;
};

#endif