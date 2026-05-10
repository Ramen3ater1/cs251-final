//
// Created by davew on 11/17/22.
//

#ifndef A_CS250_STARTER_DICTIONARY_H
#define A_CS250_STARTER_DICTIONARY_H

// Re-define _either_ the two Dictionary_Imp types or the one Dictionary_Pure type, below:

#include "Dictionary_via_std_map.h"
typedef Dictionary_via_std_map Dictionary_Imp;  // delete this line or change to be your Dictionary_Imp
typedef Dictionary_via_std_map_backup Dictionary_Imp_backup;


#include "Dictionary_pure_via_std_map.h"
typedef Dictionary_pure_via_std_map Dictionary_Pure;



void dict_exammple_imp();
void dict_example_pure();
void dict_examples_interactive();


#endif //A_CS250_STARTER_DICTIONARY_H
