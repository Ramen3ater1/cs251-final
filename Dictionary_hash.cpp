#include "Dictionary_hash.h"

Dictionary_Hash::Dictionary_Hash()
    : bucket_count(8), item_count(0) {
    buckets = new Entry *[bucket_count];

    for (int i = 0; i < bucket_count; i++) {
        buckets[i] = nullptr;
    }
}

Dictionary_Hash::Dictionary_Hash(const Dictionary_Hash &other) {
    copy_from(other);
}

Dictionary_Hash &Dictionary_Hash::operator=(const Dictionary_Hash &other) {
    if (this != &other) {
        clear();
        copy_from(other);
    }

    return *this;
}

Dictionary_Hash::~Dictionary_Hash() {
    clear();
}

void Dictionary_Hash::copy_from(const Dictionary_Hash &other) {
    bucket_count = other.bucket_count;
    item_count = other.item_count;

    buckets = new Entry *[bucket_count];

    for (int i = 0; i < bucket_count; i++) {
        buckets[i] = copy_chain(other.buckets[i]);
    }
}

void Dictionary_Hash::clear() {
    for (int i = 0; i < bucket_count; i++) {
        delete_chain(buckets[i]);
    }

    delete[] buckets;
    buckets = nullptr;
    bucket_count = 0;
    item_count = 0;
}

Dictionary_Hash::Entry *Dictionary_Hash::copy_chain(Entry *head) {
    if (head == nullptr) {
        return nullptr;
    }

    Entry *new_head = new Entry(head->key, head->value);
    Entry *old_current = head->next;
    Entry *new_current = new_head;

    while (old_current != nullptr) {
        new_current->next = new Entry(old_current->key, old_current->value);
        new_current = new_current->next;
        old_current = old_current->next;
    }

    return new_head;
}

void Dictionary_Hash::delete_chain(Entry *head) {
    Entry *current = head;

    while (current != nullptr) {
        Entry *next = current->next;
        delete current;
        current = next;
    }
}

std::size_t Dictionary_Hash::hash_string(const std::string &key) {
    std::size_t hash = 1469598103934665603ULL;

    for (char c : key) {
        hash ^= static_cast<unsigned char>(c);
        hash *= 1099511628211ULL;
    }

    return hash;
}

int Dictionary_Hash::bucket_index(const std::string &key) const {
    return static_cast<int>(hash_string(key) % bucket_count);
}

bool Dictionary_Hash::contains(const std::string &key) const {
    int index = bucket_index(key);

    Entry *current = buckets[index];

    while (current != nullptr) {
        if (current->key == key) {
            return true;
        }

        current = current->next;
    }

    return false;
}

int Dictionary_Hash::lookup(const std::string &key) const {
    int index = bucket_index(key);

    Entry *current = buckets[index];

    while (current != nullptr) {
        if (current->key == key) {
            return current->value;
        }

        current = current->next;
    }

    throw std::runtime_error("key not found");
}

Dictionary_Hash Dictionary_Hash::add(const std::string &key, int value) const {
    Dictionary_Hash result = add_without_resize(key, value);

    double load_factor =
        static_cast<double>(result.item_count) / result.bucket_count;

    if (load_factor > MAX_LOAD_FACTOR) {
        return result.resize_and_rehash(result.bucket_count * 2);
    }

    return result;
}

Dictionary_Hash Dictionary_Hash::add_without_resize(
    const std::string &key,
    int value
) const {
    Dictionary_Hash result;

    result.clear();

    result.bucket_count = bucket_count;
    result.item_count = item_count;
    result.buckets = new Entry *[result.bucket_count];

    for (int i = 0; i < result.bucket_count; i++) {
        result.buckets[i] = copy_chain(buckets[i]);
    }

    int index = result.bucket_index(key);

    Entry *current = result.buckets[index];

    while (current != nullptr) {
        if (current->key == key) {
            current->value = value;
            return result;
        }

        current = current->next;
    }

    result.buckets[index] = new Entry(key, value, result.buckets[index]);
    result.item_count++;

    return result;
}

Dictionary_Hash Dictionary_Hash::resize_and_rehash(
    int new_bucket_count
) const {
    Dictionary_Hash result;

    result.clear();

    result.bucket_count = new_bucket_count;
    result.item_count = 0;
    result.buckets = new Entry *[result.bucket_count];

    for (int i = 0; i < result.bucket_count; i++) {
        result.buckets[i] = nullptr;
    }

    for (int i = 0; i < bucket_count; i++) {
        Entry *current = buckets[i];

        while (current != nullptr) {
            int new_index =
                static_cast<int>(hash_string(current->key) % result.bucket_count);

            result.buckets[new_index] =
                new Entry(current->key, current->value, result.buckets[new_index]);

            result.item_count++;

            current = current->next;
        }
    }

    return result;
}