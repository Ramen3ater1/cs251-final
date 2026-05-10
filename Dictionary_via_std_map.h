//
// Created by davew on 11/17/22.
//

#ifndef DICTIONARY_DICTIONARY_VIA_STD_MAP_H
#define DICTIONARY_DICTIONARY_VIA_STD_MAP_H


// Map from std::string to int; would be cooler as a template.
#include <string>
#include <map>

class Dictionary_via_std_map {
public:
    // We don't need to write empty-constructor, copy-constructor, destructor, or assignment,
    //   since we're using only library types, which have those already :-)
    // We don't need an initialization constructor, since we'll build with "insert", imperative-style

    void insert(const std::string &key, int value);
    [[nodiscard]] bool contains(const std::string &key) const;
    [[nodiscard]] int  lookup(const std::string &key) const;  // throws an exception if key isn't there
    // could overload [ ], to be cool, but not bothering.
    
    Dictionary_via_std_map checkpoint();
    void restore(const Dictionary_via_std_map &a_checkpoint);
private:
    std::map<std::string, int> contents;
};

typedef Dictionary_via_std_map Dictionary_via_std_map_backup;


#endif //DICTIONARY_DICTIONARY_VIA_STD_MAP_H
