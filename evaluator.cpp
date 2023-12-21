/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

Evaluator::Evaluator(){
    symtable = new SymbolTable;
}

Evaluator::~Evaluator(){
    delete symtable;
}

// ( means insert a node and move to that node, we need to insert another node, so push it to parent.
// +,- means edit the current node
// 78 means insert a node and dont move to it, as well do not push to parent.
// // if moved it to rhs node, go to parent.
// ) means move to parent node.
void Evaluator::parse(vector<string> code){
    ExprTreeNode* root = new ExprTreeNode("UltimateEqual",new UnlimitedRational());
    expr_trees.push_back(root);
    ExprTreeNode* fleft = new ExprTreeNode("VAR",new UnlimitedRational());
    fleft->id = code[0];
    root->left = fleft;
    vector<ExprTreeNode*> parent;
    parent.push_back(root);
    ExprTreeNode* current = root;
    for(int i = 2;i<int(code.size());i++){
        if(code[i] == "("){
            ExprTreeNode* temp = new ExprTreeNode();
            if(current->left == nullptr || current->type == "equal"){
                current->left = temp;
                current = current->left;
                // cout<<"went left"<<code[i]<<endl;
            }
            else {
                current->right = temp;
                current = current->right;
                // cout<<"went right"<<code[i]<<endl;
            }
            parent.push_back(current);
        }
        else if(code[i] == ")"){
            // cout<<current->type<<endl;
            parent.pop_back();
            current = parent[int(parent.size())-1];
            // cout<<"went up"<<code[i]<<endl;
            // cout<<current->type<<endl;
        }
        else if(code[i] == "+"){
            current->type = "ADD";
            // cout<<"added add"<<code[i]<<endl;
        }
        else if(code[i] == "-"){
            current->type = "SUB";
            // cout<<"added sub"<<code[i]<<endl;
        }
        else if(code[i] == "*"){
            current->type = "MUL";
            // cout<<"added mul"<<code[i]<<endl;
        }
        else if(code[i] == "/"){
            current->type = "DIV";
            // cout<<"added div"<<code[i]<<endl;
        }
        else if(int(code[i][0])=='-'){
            UnlimitedRational* toDelete = new UnlimitedRational(new UnlimitedInt(code[i]),new UnlimitedInt(1));
            ExprTreeNode* node = new ExprTreeNode("VAL",toDelete);
            if(current->left == nullptr){
                current->left = node;
            }
            else {
                current->right = node;
            }
            delete toDelete;
        }
        else if(int(code[i][0])<=57 && int(code[i][0]>=48)){
            UnlimitedRational* toDelete = new UnlimitedRational(new UnlimitedInt(code[i]),new UnlimitedInt(1));
            ExprTreeNode* node = new ExprTreeNode("VAL",toDelete);
            if(current->left == nullptr){
                current->left = node;
            }
            else {
                current->right = node;
            }
            delete toDelete;
        }
        else {
            UnlimitedRational* toDelete = new UnlimitedRational(new UnlimitedInt(1),new UnlimitedInt(1));
            ExprTreeNode* node = new ExprTreeNode("VAR",toDelete);
            node->id = code[i];
            if(current->left == nullptr){
                current->left = node;
            }
            else current->right = node;
            delete toDelete;
        }
    }
}

void Evaluator::eval(){
    // postorder traversal of the root
    ExprTreeNode* root = expr_trees[int(expr_trees.size())-1];
    ExprTreeNode* current = root->right;
    if(root == nullptr){
        return;
    }
    vector<ExprTreeNode* > stk;
    vector<ExprTreeNode* > p;
    stk.push_back(current);
    while(!stk.empty()){
        current = stk[int(stk.size())-1];
        stk.pop_back();
        p.push_back(current);
        if(current->left != nullptr) stk.push_back(current->left);
        if(current->right != nullptr) stk.push_back(current->right);
    }
    while(!p.empty()){
        current = p[int(p.size())-1];
        if(current->type == "ADD"){
            current->evaluated_value = UnlimitedRational::add(current->left->evaluated_value,current->right->evaluated_value);
            // cout<<"assigned value "<<current->evaluated_value->get_frac_str()<<endl;
        }
        else if(current->type == "SUB"){
            current->evaluated_value = UnlimitedRational::sub(current->left->evaluated_value,current->right->evaluated_value);
            // cout<<"assigned value "<<current->evaluated_value->get_frac_str()<<endl;
        }
        else if(current->type == "MUL"){
            current->evaluated_value = UnlimitedRational::mul(current->left->evaluated_value,current->right->evaluated_value);
            // cout<<"assigned value "<<current->evaluated_value->get_frac_str()<<endl;
        }
        else if(current->type == "DIV"){
            current->evaluated_value = UnlimitedRational::div(current->left->evaluated_value,current->right->evaluated_value);
            // cout<<"assigned value "<<current->evaluated_value->get_frac_str()<<endl;
        }
        else if(current->type == "VAL"){
            // cout<<"assigned value "<<current->evaluated_value->get_frac_str()<<endl;
        }
        else if(current->type == "VAR"){
            current->evaluated_value = symtable->search(current->id);
        }
        p.pop_back();
    }
    root = expr_trees.back();
    root->left->evaluated_value = root->right->evaluated_value;
    symtable->insert(root->left->id,root->right->evaluated_value);
}

void traverse(ExprTreeNode* root){
    if(root == nullptr){}
    else{
        traverse(root->left);
        traverse(root->right); 
    } 
}

// #include<iostream>
// using namespace std;
// void evaluateAndPrint(ExprTreeNode* node) {
//     if (node == nullptr) {
//         return;
//     }
//     evaluateAndPrint(node->left);
//     evaluateAndPrint(node->right);
//     if (node->evaluated_value != nullptr) {
//         cout << "Node ID: " << node->id << ", Evaluated Value: " << node->evaluated_value->get_frac_str() << endl;
//     } else {
//         cout << "Node ID: " << node->id << " has no evaluated value." << endl;
//     }
// }

// int main() {
//     Evaluator evaluator;
//     cout<<"FOR FIRST PARSE TREE: "<<endl;
//     cout<<endl;
//     vector<string> code;
//     code.push_back("a");
//     code.push_back(":=");
//     code.push_back("-4373");
//     evaluator.parse(code);
//     evaluator.eval();
//     evaluateAndPrint(evaluator.expr_trees[0]);

//     cout<<endl;
//     cout<<"FOR SECOND PARSE TREE: "<<endl;
//     cout<<endl;

//     vector<string> code2;
//     code2.push_back("b");
//     code2.push_back(":=");
//     code2.push_back("(");
//     code2.push_back("(");
//     code2.push_back("a");
//     code2.push_back("+");
//     code2.push_back("4373");
//     code2.push_back(")");
//     code2.push_back("*");
//     code2.push_back("2267373");
//     code2.push_back(")");
//     evaluator.parse(code2);
//     evaluator.eval();
//     evaluateAndPrint(evaluator.expr_trees[1]);

//     cout<<endl;
//     cout<<"FOR THIRD PARSE TREE : "<<endl;
//     cout<<endl;
//     vector<string> code3;
//     code3.push_back("c");
//     code3.push_back(":=");
//     code3.push_back("(");
//     code3.push_back("(");
//     code3.push_back("(");
//     code3.push_back("a");
//     code3.push_back("+");
//     code3.push_back("b");
//     code3.push_back(")");
//     code3.push_back("*");
//     code3.push_back("-32627");
//     code3.push_back(")");
//     code3.push_back("-");
//     code3.push_back("703938");
//     code3.push_back(")");
//     evaluator.parse(code3);
//     evaluator.eval();
//     evaluateAndPrint(evaluator.expr_trees[2]);

//     cout<<endl;
//     cout<<"FOR FOURTH PARSE TREE : "<<endl;
//     cout<<endl;

//     vector<string> code4;
//     code4.push_back("d");
//     code4.push_back(":=");
//     code4.push_back("(");
//     code4.push_back("(");
//     code4.push_back("a");
//     code4.push_back("/");
//     code4.push_back("628265876");
//     code4.push_back(")");
//     code4.push_back("*");
//     code4.push_back("(");
//     code4.push_back("b");
//     code4.push_back("/");
//     code4.push_back("c");
//     code4.push_back(")");
//     code4.push_back(")");
//     evaluator.parse(code4);
//     evaluator.eval();
//     evaluateAndPrint(evaluator.expr_trees[3]);

//     cout<<endl;
//     cout<<"FOR FIFTH PARSE TREE : "<<endl;
//     cout<<endl;

//     vector<string> code5;
//     code5.push_back("e");
//     code5.push_back(":=");
//     code5.push_back("d");
//     evaluator.parse(code5);
//     evaluator.eval();
//     evaluateAndPrint(evaluator.expr_trees[4]);

//     cout<<endl;
//     cout<<"FOR SIXTH PARSE TREE : "<<endl;
//     cout<<endl;

//     vector<string> code6;
//     code6.push_back("f");
//     code6.push_back(":=");
//     code6.push_back("(");
//     code6.push_back("e");
//     code6.push_back("/");
//     code6.push_back("-58373822900038939928302283293");
//     code6.push_back(")");
//     evaluator.parse(code6);
//     evaluator.eval();
//     evaluateAndPrint(evaluator.expr_trees[5]);

//     return 0;
// }
