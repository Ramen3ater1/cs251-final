//
// Created by davew on 11/17/22.
//

#ifndef DICTIONARY_DICTIONARY_PURE_VIA_STD_MAP_H
#define DICTIONARY_DICTIONARY_PURE_VIA_STD_MAP_H


// Map from std::string to int; would be cooler as a template.
#include <string>
#include <map>

class Dictionary_pure_via_std_map {
public:
    // We don't need to write empty-constructor, copy-constructor, destructor, or assignment,
    //   since we're using only library types, which have those already :-)
    // We don't need an initialization constructor, since we'll build with "insert", imperative-style

    [[nodiscard]] Dictionary_pure_via_std_map add(const std::string &key, int value) const;
    [[nodiscard]] bool contains(const std::string &key) const;
    [[nodiscard]] int  lookup(const std::string &key) const;  // throws an exception if key isn't there
    // could overload [ ] FOR READING, to be cool, but not bothering.

private:
    std::map<std::string, int> contents;
};


#endif //DICTIONARY_DICTIONARY_PURE_VIA_STD_MAP_H
