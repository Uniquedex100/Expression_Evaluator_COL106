/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

SymbolTable::SymbolTable(){
    size = 0; //main thing is size, because otherwise we do need a root right?
    root = nullptr;
}

SymbolTable::~SymbolTable(){
    while(root!= nullptr){
        SymbolTable::remove (root->key);
    }
}

void SymbolTable::insert(string k, UnlimitedRational *v){
    SymEntry* node = new SymEntry(k,v);
    if(size == 0){
        size++;
        root = node;return;
    }
    SymEntry* current = root;
    SymEntry* parent = nullptr;// will help in shortening of the code;
    while(current != nullptr){
        if(current->key < k){
            parent = current;
            current = current->right;
        }
        else {
            parent = current;
            current = current->left;
        }
    }
    if(k < parent->key){
        parent->left = node;
        parent = parent->left;
    }
    else {
        parent->right = node;
        parent = parent->right;
    }
    size++;
}

void traverse(SymEntry* root){
    if(root == nullptr){}
    else{
        traverse(root->left);
        traverse(root->right);
    } 
}

void SymbolTable::remove(string k) {
    if (size == 0) {return;}
    SymEntry* current = root;
    SymEntry* parent = nullptr;
    while(current != nullptr) {
        if(current->key == k) {
            if(current->left == nullptr && current->right == nullptr){
                if(parent != nullptr){
                    if(parent->left == current) {parent->left = nullptr;} 
                    else{parent->right = nullptr;}
                } 
                else {root = nullptr;}
                delete current;
            } 
            else if(current->left == nullptr){
                if(parent != nullptr){
                    if(parent->left == current) {parent->left = current->right;} 
                    else{parent->right = current->right;}
                } 
                else{root = current->right;}
                delete current;
            } 
            else if (current->right == nullptr){
                if(parent != nullptr) {
                    if (parent->left == current) {parent->left = current->left;}
                    else{parent->right = current->left;}
                } 
                else{root = current->left;}
                delete current;
            } 
            else {
                SymEntry* successorParent = current;
                SymEntry* successor = current->right;
                while (successor->left != nullptr) {
                    successorParent = successor;
                    successor = successor->left;
                }
                current->key = successor->key;
                if (successorParent->left == successor) {
                    successorParent->left = successor->right;
                } else {
                    successorParent->right = successor->right;
                }
                delete successor;
            }
            size--;
            return;
        } 
        else if(k < current->key){
            parent = current;
            current = current->left;
        } 
        else{
            parent = current;
            current = current->right;
        }
    }
}

UnlimitedRational *SymbolTable::search(string k){
    if(size == 0){return new UnlimitedRational(new UnlimitedInt(1),new UnlimitedInt(1));}
    SymEntry* current = root;
    while(current != nullptr){
        // cout<<current->key<<endl;
        if(k == current->key){return current->val;}
        else if(k<current->key){
            current = current->left;
        }
        else if(k>current->key){
            current = current->right;
        }
    }
    return nullptr;
}

int SymbolTable::get_size()
{
    return size;
}

SymEntry *SymbolTable::get_root()
{
    return root;
}

// int main(){
//     SymbolTable* gojo = new SymbolTable();
//     gojo->insert("satoru",new UnlimitedRational(new UnlimitedInt(1),new UnlimitedInt(97)));
//     gojo->insert("is",new UnlimitedRational(new UnlimitedInt(2),new UnlimitedInt(97)));
//     gojo->insert("the",new UnlimitedRational(new UnlimitedInt(3),new UnlimitedInt(97)));
//     gojo->insert("peek",new UnlimitedRational(new UnlimitedInt(4),new UnlimitedInt(97)));
//     gojo->insert("alltime",new UnlimitedRational(new UnlimitedInt(5),new UnlimitedInt(97)));
//     traverse(gojo->get_root());
//     delete gojo;
// }

//       s
//    i     t
//  a   p