/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"

SymEntry::SymEntry(){
    key = "";
    val = new UnlimitedRational(new UnlimitedInt(1), new UnlimitedInt(1));
    left = nullptr;
    right = nullptr;
}

SymEntry::SymEntry(string k, UnlimitedRational *v){
    key = k;
    val = new UnlimitedRational(v->get_p(),v->get_q());
    left = nullptr;
    right = nullptr;
}

SymEntry::~SymEntry(){
    if(val != nullptr){delete val;}
}
