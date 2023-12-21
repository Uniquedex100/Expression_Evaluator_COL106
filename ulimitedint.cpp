/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#define defSize 100
#include "ulimitedint.h"

#define positifyZero(result) int sgn = result->sign;result->sign = 1;for(int i = 0;i<result->capacity;i++){if(result->unlimited_int[i] != 0){result->sign = sgn;}};

int comparemod(UnlimitedInt* i1, UnlimitedInt* i2){
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
int log10(int a){
    int res = 0;
    while(a>=10){
        a/=10;
        res++;
    }
    return res;
}
UnlimitedInt::UnlimitedInt(){
    unlimited_int = new int[defSize];
    for(int i = 0;i<defSize;i++){unlimited_int[i] = 0;}
    unlimited_int[defSize-1] = 1;///////
    size = 1;
    capacity = defSize;
    sign = 1;
}
UnlimitedInt::UnlimitedInt(string s){
    if(s[0] == '-'){
        int n = s.size()-1;
        unlimited_int = new int[n];
        for(int i = 0;i<n;i++){
            unlimited_int[i] = s[i+1] - '0';
        }
        size = n;
        capacity = n;
        sign = -1;
    }
    else {
        int n = s.size();
        unlimited_int = new int[n];
        for(int i = 0;i<n;i++){
            unlimited_int[i] = s[i] - '0';
        }
        size = n;
        capacity = n;
        sign = 1;
    }
}
UnlimitedInt::UnlimitedInt(int i){
    if(i < 0){sign = -1;}
    else if(i==0){sign = 1;}
    else{sign = 1;}
    i = abs(i);
    int n = log10(i) + 1;//log10 is also giving problems now...
    unlimited_int = new int[n];
    for(int j = n-1;j>=0;j--){
        unlimited_int[j] = (i - (i/10)*10);
        i = i/10;
    }
    size = n;
    capacity = n;
}
//Assume array given to be perfect... capaciity denotes full size and sz denotes size of digits that matter.
UnlimitedInt::UnlimitedInt(int *ulimited_int, int cap, int sgn, int sz){
    unlimited_int = new int[cap];
    capacity = cap;
    size = sz;
    sign = sgn;
    for(int i = 0;i<cap;i++){
        unlimited_int[i] = ulimited_int[i];
    }
}
UnlimitedInt::~UnlimitedInt(){
    delete [] unlimited_int;
}
int UnlimitedInt::get_size(){
    return size;
}
int *UnlimitedInt::get_array(){
    return unlimited_int;
}
int UnlimitedInt::get_sign(){
    return sign;
}
int UnlimitedInt::get_capacity(){
    return capacity;
}

UnlimitedInt *UnlimitedInt::add(UnlimitedInt *ii1, UnlimitedInt *ii2){//adjust the size for performance purposes.
    UnlimitedInt* i1 = new UnlimitedInt(ii1->get_array(),ii1->get_capacity(),ii1->get_sign(),ii1->get_size()); 
    UnlimitedInt* i2 = new UnlimitedInt(ii2->get_array(),ii2->get_capacity(),ii2->get_sign(),ii2->get_size()); 
    int cap = max(i1->size,i2->size)+1;
    int zero[cap] = {0};
    UnlimitedInt * result = new UnlimitedInt(zero,cap,1,1);
    result->capacity = cap;
    int c1 = i1->capacity;int c2 = i2->capacity;
    int s1 = i1->size;int s2 = i2->size;
    int itr1 = i1->capacity - 1;
    int itr2 = i2->capacity - 1;
    int itr = cap - 1;
    if(i1->sign == 1 && i2->sign == 1){
        result->sign = 1;
    }
    else if(i1->sign == -1 && i2->sign == -1){
        result->sign = -1;
    }
    else if(i1->sign == -1 && i2->sign == 1){
        result->unlimited_int = i1->unlimited_int;
        result->capacity = i1->capacity;
        result->size = i1->size;
        result->sign = 1;
        UnlimitedInt* toDelete = result;
        result = sub(i2,result);
        delete toDelete;
        positifyZero(result);
        delete i1;delete i2;
        return result;
    }
    else if(i1->sign == 1 && i2->sign == -1){
        result->unlimited_int = i2->unlimited_int;
        result->capacity = i2->capacity;
        result->size = i2->size;
        result->sign = 1;
        UnlimitedInt* toDelete = result;
        result = sub(i1,result);
        delete toDelete;
        positifyZero(result);
        delete i1;delete i2;
        return result;
    }
    int carryin = 0;
    while(itr1>=c1-s1 && itr2>=c2-s2){
        result->unlimited_int[itr] = (i1->unlimited_int[itr1] + i2->unlimited_int[itr2] + carryin );
        if(result->unlimited_int[itr] >= 10){carryin = 1;}
        else{carryin = 0;}
        result->unlimited_int[itr] = result->unlimited_int[itr]%10;
        itr1--;itr2--;itr--;
    }
    while(itr1>=c1-s1){
        result->unlimited_int[itr] = (i1->unlimited_int[itr1] + carryin );
        if(result->unlimited_int[itr] >= 10){carryin = 1;}
        else{carryin = 0;}
        result->unlimited_int[itr] = result->unlimited_int[itr]%10;
        itr1--;itr--;
    }
    while(itr2>=c2-s2){
        result->unlimited_int[itr] = (i2->unlimited_int[itr2] + carryin );
        if(result->unlimited_int[itr] >= 10){carryin = 1;}
        else{carryin = 0;}
        result->unlimited_int[itr] = result->unlimited_int[itr]%10;
        itr2--;itr--;
    }
    if(carryin == 1){result->unlimited_int[itr] = carryin;}
    // Adjusting size : 
    for(int i = 0;i<cap;i++){
        if(result->unlimited_int[i] != 0){
            result->size = result->capacity-i;
            break;
        }
    }
    //To handle negative zeros...
    positifyZero(result);
    delete i1;delete i2;
    return result;
}

UnlimitedInt *UnlimitedInt::sub(UnlimitedInt *ii1, UnlimitedInt *ii2){
    UnlimitedInt* i1 = new UnlimitedInt(ii1->get_array(),ii1->get_capacity(),ii1->get_sign(),ii1->get_size()); 
    UnlimitedInt* i2 = new UnlimitedInt(ii2->get_array(),ii2->get_capacity(),ii2->get_sign(),ii2->get_size()); 
    int cap = max(i1->size,i2->size) + 1;
    int zero[cap] = {0};
    UnlimitedInt * result = new UnlimitedInt(zero,cap,1,1);
    result->capacity = cap;
    if(i1->sign == -1 && i2->sign == 1){
        result->unlimited_int = i1->unlimited_int;
        result->capacity = i1->capacity;
        result->size = i1->size;
        result->sign = 1;
        UnlimitedInt* toDelete = result;
        result = add(i2,result);
        result->sign = -1;
        delete toDelete;
        positifyZero(result);
        delete i1;delete i2;
        return result;
    }
    else if(i1->sign == 1 && i2->sign == -1){
        result->unlimited_int = i2->unlimited_int;
        result->capacity = i2->capacity;
        result->size = i2->size;
        result->sign = 1;
        UnlimitedInt* toDelete = result;
        result = add(i1,result);
        delete toDelete;
        positifyZero(result);
        delete i1;delete i2;
        return result;
    }
    else if(i1->sign == -1 && i2->sign == -1){
        UnlimitedInt* toDelete = result;
        i1->sign = 1;
        i2->sign = 1;
        result = sub(i1,i2);
        i1->sign = -1;
        i2->sign = -1;
        result->sign = -1*result->sign;
        delete toDelete;
        positifyZero(result);
        delete i1;delete i2;
        return result;
    }
    ///////////////////
    int didiinvert = 1;
    if(comparemod(i1,i2)==-1){ //To handle when i1<i2 and still i need to subtract.//Only positive case...
        didiinvert = -1;
        UnlimitedInt* temp = i1;
        i1 = i2;
        i2 = temp;
    }
    ////////////////////
    int c1 = i1->capacity;int c2 = i2->capacity;
    int s1 = i1->size;int s2 = i2->size;
    int itr1 = i1->capacity - 1;
    int itr2 = i2->capacity - 1;
    int itr = cap - 1;
    int carryout = 0;
    while(itr1>=c1-s1 && itr2>=c2-s2){
        result->unlimited_int[itr] = ((i1->unlimited_int[itr1] - i2->unlimited_int[itr2]) - carryout);
        if(result->unlimited_int[itr] < 0){carryout = 1;}
        else{carryout = 0;}
        result->unlimited_int[itr] = (10+result->unlimited_int[itr])%10;
        itr1--;itr2--;itr--;
    }
    while(itr1>=c1-s1){
        result->unlimited_int[itr] = ((i1->unlimited_int[itr1]) - carryout);
        if(result->unlimited_int[itr] < 0){carryout = 1;}
        else{carryout = 0;}
        result->unlimited_int[itr] = (10+result->unlimited_int[itr])%10;
        itr1--;itr--;
    }
    //Obviously itr2 case will not be present in this circumstance because i used didiinvert.
    //To rehabilitate i1 and i2...
    if(didiinvert == -1){
        UnlimitedInt* temp = i1;i1 = i2;i2 = temp;
        result->sign = result->sign * didiinvert;
    }
    //To handle size issues...
    for(int i = 0;i<cap;i++){
        if(result->unlimited_int[i] != 0){
            result->size = result->capacity-i;
            break;
        }
    }
    //To handle negative zeros...
    positifyZero(result);
    delete i1;delete i2;
    return result;
}

UnlimitedInt *UnlimitedInt::mul(UnlimitedInt *i1, UnlimitedInt *i2){
    int cap = i1->size + i2->size + 1;
    int n = cap;
    int zero[n] = {0};
    UnlimitedInt * result = new UnlimitedInt(zero,cap,1,1);
    int n1 = i1->capacity;int n2 = i2->capacity;
    int s1 = i1->size;int s2 = i2->size;
    int itr1 = n1-1; int itr2 = n2-1;int itr = n-1;
    while(itr1 >= n1-s1){
        int buffer = n1-1-itr1;
        int carryup = 0;
        itr = n-1;
        itr2 = n2-1;
        while(itr2>=n2-s2){
            result->unlimited_int[itr-buffer] = result->unlimited_int[itr-buffer] + i1->unlimited_int[itr1] * i2->unlimited_int[itr2] + carryup;
            if(result->unlimited_int[itr-buffer] >= 10){carryup = result->unlimited_int[itr-buffer]/10;}
            else{carryup = 0;}
            result->unlimited_int[itr-buffer] = result->unlimited_int[itr-buffer]%10;
            itr--;itr2--;
        }
        if(carryup){result->unlimited_int[itr-buffer] = carryup;}
        itr1--;
    }
    result->sign = i1->sign * i2->sign;
    for(int i = 0;i<cap;i++){
        if(result->unlimited_int[i] != 0){
            result->size = result->capacity-i;
            break;
        }
    }
    return result;
}

// a compare_array function : 
int ca(int a[],int p1,int p2,int b[],int q1,int q2){
    int itr1 = p2;int itr2 = q2;
    int res = 0;
    while(itr1>=p1 && itr2>=q1){
        if(a[itr1] > b[itr2]){res = 1;}
        if(a[itr1] < b[itr2]){res = -1;}
        itr1--;itr2--;
    }
    while(itr1>=p1){
        if(a[itr1]>0){res = 1;}
        itr1--;
    }
    while(itr2>=q1){
        if(b[itr2]>0){res = -1;}
        itr2--;
    }
    return res;
}

UnlimitedInt *UnlimitedInt::div(UnlimitedInt *i1, UnlimitedInt *i2){
    //Checking for zero division
    UnlimitedInt* one = new UnlimitedInt(1);
    UnlimitedInt* zeros = new UnlimitedInt(0);
    if(comparemod(zeros,i2) == 0){
        delete one;
        delete zeros;
        return new UnlimitedInt(0);
    }
    int sign1 = i1->sign;
    int sign2 = i2->sign;
    int n = i1->size + 1;
    int zero[n] = {0};
    zero[n-1] = 1;
    int a[i1->capacity];
    int b[i2->capacity];
    int n1 = i1->capacity;int n2 = i2->capacity;
    int s1 = i1->size;int s2 = i2->size;
    for(int i = 0;i<n1;i++){a[i] = i1->unlimited_int[i];}
    for(int i = 0;i<n2;i++){b[i] = i2->unlimited_int[i];}
    int p1 = n1-s1;int p2 = n1-s1+s2-1;
    int res[n1];for(int i = 0;i<n1;i++){res[i] = 0;}
    int resitr = 0;int ressize = 0;
    while(p2<=n1-1){
        if(ca(a,p1,p2,b,n2-s2,n2-1) >= 0){//b<a; b divides a
            int digit = 0;
            int limit = 20;
            while(ca(a,p1,p2,b,n2-s2,n2-1)>=0 && limit--){
                int carryout = 0;
                int i = n2-1;
                for(;i>=n2-s2;i--){
                    a[p2+i-n2+1] = a[p2+i-n2+1] - b[i] - carryout;
                    if(a[p2+i-n2+1]<0){
                        carryout = 1;a[p2+i-n2+1] = (a[p2+i-n2+1] + 10)%10;
                    }
                    else{carryout = 0;}
                }
                if(carryout == 1){a[p2+i-n2+1]--;}
                digit++;
                while(p1<p2){if(a[p1]==0) p1++;else break;}
                ////////////////////////////////////////////
            }
            res[resitr] = digit;
            resitr++;
            ressize++;
            p2++;
            while(p1<p2){if(a[p1]==0) p1++;else break;}
        }
        else { // b>a
            p2++;
            while(p1<p2){if(a[p1]==0) p1++;else break;}
            res[resitr] = 0;
            resitr++;
            ressize ++;
        }
    }
    // Check for remainder to handle sign problems
    int rem = 0;
    if(p1!=p2){
        rem = 1;
    }
    // Reframe res;
    for(int i = n-1;i>=0;i--){
        if(i<n-ressize){res[i] = 0;}
        else{res[i] = res[i-n+ressize];}
    }
    UnlimitedInt* result = new UnlimitedInt(res,n,1,ressize);
    for(int i = 0;i<n;i++){
        result->unlimited_int[i] = res[i];
    }
    //Handle negative signs...
    if(sign1*sign2 == -1){
        if(rem == 1){
            UnlimitedInt* toDelete = result;
            result = add(result,one);
            delete toDelete;
        }
        result->sign = -1;
    }
    positifyZero(result);
    delete one;
    delete zeros;
    return result;
}

UnlimitedInt *UnlimitedInt::mod(UnlimitedInt *i1, UnlimitedInt *i2){
    UnlimitedInt * a = div(i1,i2);
    UnlimitedInt * b = mul(i2,a);
    UnlimitedInt * c = sub(i1,b);
    return c;
}

string UnlimitedInt::to_string(){
    for(int i = 0;i<capacity;i++){
        if(unlimited_int[i] != 0){
            size = capacity-i;
            break;
        }
    }
    int itr = capacity - size;
    string res = "";
    while(itr <= capacity - 1){
        char current = '0' + unlimited_int[itr];
        res = res + current;
        itr++;
    }
    if(sign == -1){res = "-" + res;}
    if(res == "" || res == "-"){res = "0";}
    return res;
}

// int main()
// {cout<<"start"<<endl;
//     for (int i=1;i<1000;i++)
//     {
//         for (int j=1;j<1000;j++)
//         {
//             //cout<<i<<" "<<j<<endl;
//             UnlimitedInt * n=new UnlimitedInt(-i);
//             UnlimitedInt * n2=new UnlimitedInt(j);
//             UnlimitedInt * n1=new UnlimitedInt();
//             n1=n1->add(n,n2);
//             if (n1->to_string()!=std::to_string((-i)+(j)))
//             {
//                 cout<<n1->to_string()<<"c"<<std::to_string((-i)+(j))<<endl;
//                 cout<<i<<" "<<j<<"add"<<endl;
//                 break;
//             }
//             n1=n1->sub(n,n2);
//             if (n1->to_string()!=std::to_string((-i)-(j)))
//             {
//                 cout<<n1->to_string()<<"c"<<std::to_string((-i)-(j))<<endl;
//                 cout<<i<<" "<<j<<"sub"<<endl;
//                 break;
//             }
//             n1=n1->mul(n,n2);
//             if (n1->to_string()!=std::to_string((-i)*(j)))
//             {
//                 cout<<n1->to_string()<<"c"<<std::to_string((-i)*(j))<<endl;
//                 cout<<i<<" "<<j<<"mul"<<endl;
//                 break;
//             }
//             n1=n1->div(n,n2);
//             int ans=-i/j;
//             if (!(i%j==0))
//             {
//                 ans-=1;
//             }
//             if (n1->to_string()!=std::to_string(ans))
//             {
//                 cout<<n1->to_string()<<"c"<<std::to_string((-i)/(j))<<endl;
//                 cout<<i<<" "<<j<<"div"<<endl;
//                 break;
//             }
//             delete n;
//             delete n1;
//             delete n2;
//         }
//     }
//     cout<<"pass"<<endl;
//  }