/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode(){
    type = "equal";
    val = nullptr;
    evaluated_value = nullptr;
    left = nullptr;
    right = nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt *v){
    type = t;
    UnlimitedInt* one = new UnlimitedInt(1);
    val = new UnlimitedRational(new UnlimitedInt(v->get_array(),v->get_capacity(),v->get_sign(),v->get_size()),new UnlimitedInt(1));
    evaluated_value = new UnlimitedRational(v,one);
    left = nullptr;
    right = nullptr;
    delete one;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational *v){
    type = t;
    val = new UnlimitedRational(v->get_p(),v->get_q());
    evaluated_value = new UnlimitedRational(v->get_p(),v->get_q());
    left = nullptr;
    right = nullptr;
}

ExprTreeNode::~ExprTreeNode(){
    if(val != nullptr) delete val;
    if(evaluated_value!=nullptr) delete evaluated_value;
    if(left!=nullptr) delete left;
    if(right!=nullptr) delete right;
}
