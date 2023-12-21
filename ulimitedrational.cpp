/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"

int compared(UnlimitedInt* i1, UnlimitedInt* i2){
    if(i1->get_size() > i2->get_size()){
        if(i1->get_sign() == 1){return 1;}
        else return -1;
    }
    else if(i1->get_size() < i2->get_size()){
        if(i1->get_sign() == 1){return -1;}
        else return 1;
    }
    else{
        int n1 = i1->get_capacity();
        int n2 = i2->get_capacity();
        int s1 = i1->get_size();
        int s2 = i2->get_size();
        int* a = i1->get_array();
        int* b = i2->get_array();
        int itr1 = n1 - s1;
        int itr2 = n2 - s2;
        while(itr1 < n1 && itr2< n2){
            if(a[itr1] > b[itr2]){
                return 1;
            }
            else if(a[itr1] < b[itr2]){
                return -1;
            }
            itr1++;
            itr2++;
        }
    }
    return 0;
}
//while a%b != 0; c = max(a,b); a = max(a,b); b = min(a,b); b = a%b; a = b;
// temp = a; a = b; b = temp%b;
UnlimitedInt* calgcd(UnlimitedInt* a,UnlimitedInt* b,UnlimitedInt* zero,UnlimitedInt* one){
    if(compared(a,b)>1){return calgcd(b,a,zero,one);}
    if(compared(a,zero)==0){return b;}
    if(compared(a,one)==0){return one;}
    UnlimitedInt* toDelete = UnlimitedInt::mod(b,a);
    delete b;
    return calgcd(toDelete,a,zero,one);
}
UnlimitedInt* gcd(UnlimitedInt* a,UnlimitedInt* b){
    UnlimitedInt* zero = new UnlimitedInt(0);
    UnlimitedInt* one = new UnlimitedInt(1);
    UnlimitedInt * tempa = new UnlimitedInt(a->get_array(),a->get_capacity(),1,a->get_size());
    UnlimitedInt * tempb = new UnlimitedInt(b->get_array(),b->get_capacity(),1,b->get_size());
    UnlimitedInt* res = calgcd(tempa,tempb,zero,one);
    return res;
}

UnlimitedRational* reduce(UnlimitedRational* r){
    UnlimitedInt* a = (gcd(r->get_p(),r->get_q()));
    UnlimitedInt* newp = UnlimitedInt::div(r->get_p(),a);
    UnlimitedInt* newq = UnlimitedInt::div(r->get_q(),a);
    UnlimitedRational * res = new UnlimitedRational(newp,newq);
    delete newp;delete newq;delete a;
    return res;
}
UnlimitedRational::UnlimitedRational(){
    p = new UnlimitedInt(1);
    q = new UnlimitedInt(1);
}
UnlimitedRational::UnlimitedRational(UnlimitedInt *num, UnlimitedInt *den){
    UnlimitedInt* zero = new UnlimitedInt(0);
    if(compared(zero,den)==0){
        p = new UnlimitedInt(0);
        q = new UnlimitedInt(0);
    }
    else {
        UnlimitedInt* hcf = gcd(num,den);
        p = UnlimitedInt::div(num,hcf);
        q = UnlimitedInt::div(den,hcf);
        delete hcf;
    }
}
UnlimitedRational::~UnlimitedRational(){
    delete p;
    delete q;
}
UnlimitedInt *UnlimitedRational::get_p()
{
    return p;
}
UnlimitedInt *UnlimitedRational::get_q()
{
    return q;
}
string UnlimitedRational::get_p_str()
{
    return p->to_string();
}
string UnlimitedRational::get_q_str()
{
    return q->to_string();
}
string UnlimitedRational::get_frac_str()
{
    string a = p->to_string();
    string b = q->to_string();
    string c = a + "/";
    c = c + b;
    return c;
}
UnlimitedRational *UnlimitedRational::add(UnlimitedRational *i1, UnlimitedRational *i2){
    UnlimitedInt* toDelete1 = UnlimitedInt::mul(i1->p,i2->q);
    UnlimitedInt* toDelete2 = UnlimitedInt::mul(i2->p,i1->q);
    UnlimitedInt* p1 = UnlimitedInt::add(toDelete1,toDelete2);
    UnlimitedInt* q1 = UnlimitedInt::mul(i1->q,i2->q);
    UnlimitedRational* res = new UnlimitedRational(p1,q1);
    delete toDelete1;delete toDelete2;
    return res;
}
UnlimitedRational *UnlimitedRational::sub(UnlimitedRational *i1, UnlimitedRational *i2){
    UnlimitedInt* toDelete1 = UnlimitedInt::mul(i1->p,i2->q);
    UnlimitedInt* toDelete2 = UnlimitedInt::mul(i2->p,i1->q);
    UnlimitedInt* p1 = UnlimitedInt::sub(toDelete1,toDelete2);
    UnlimitedInt* q1 = UnlimitedInt::mul(i1->q,i2->q);
    UnlimitedRational* res = new UnlimitedRational(p1,q1);
    delete toDelete1;delete toDelete2;
    return res;
}
UnlimitedRational *UnlimitedRational::mul(UnlimitedRational *i1, UnlimitedRational *i2){
    UnlimitedInt* p1 = UnlimitedInt::mul(i1->p,i2->p);
    UnlimitedInt* q1 = UnlimitedInt::mul(i1->q,i2->q);
    UnlimitedRational* res = new UnlimitedRational(p1,q1);
    return res;
}
//HANDLE DIVISION BY ZERO...
UnlimitedRational *UnlimitedRational::div(UnlimitedRational *i1, UnlimitedRational *i2){
    UnlimitedInt* p1 = UnlimitedInt::mul(i1->p,i2->q);
    UnlimitedInt* q1 = UnlimitedInt::mul(i1->q,i2->p);
    UnlimitedRational* res = new UnlimitedRational(p1,q1);
    return res; 
}


// int main(){
//     UnlimitedRational* a = new UnlimitedRational(new UnlimitedInt("-1"),new UnlimitedInt("2"));
//     UnlimitedRational* b = new UnlimitedRational(new UnlimitedInt("-33"),new UnlimitedInt("-2"));
//     UnlimitedRational* c = new UnlimitedRational(new UnlimitedInt("288"),new UnlimitedInt("4378"));
//     UnlimitedRational* d =  UnlimitedRational::add(a,b);
//     UnlimitedRational* e = UnlimitedRational::div(a,d);
//     cout<<a->get_frac_str()<<endl;
//     cout<<b->get_frac_str()<<endl;
//     cout<<c->get_frac_str()<<endl;
//     cout<<d->get_frac_str()<<endl;
//     cout<<e->get_frac_str()<<endl;
// }