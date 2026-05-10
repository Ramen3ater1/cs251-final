#ifndef DICTIONARY_PURE
#define DICTIONARY_PURE

#include <memory>
#include <string>

class Dictionary_Pure {
private:
    struct Node {
        std::string key;
        int value;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        //constructor
        Node(const std::string &k, int v,
            std::shared_ptr<Node> l = nullptr,
            std::shared_ptr<Node> r = nullptr)
            : key(k), value(v), left(l), right(r){}
    };

    std::shared_ptr<Node> root;

    explicit Dictionary_Pure(std::shared_ptr<Node> r);
    static std::shared_ptr<Node> add_node(const std::shared_ptr<Node> &node, const std::string &key, int value);
public:
    Dictionary_Pure();
    Dictionary_Pure(const Dictionary_Pure &other);
    bool contains(const std::string &key) const;
    int lookup(const std::string &key) const;
    Dictionary_Pure add(const std::string &key, int value) const;

};


#endif