#include <iostream>
#include "SparseArray.h"
#include "Z3.h"

void foo(const SparseArray<int,3>& a){
    for( SparseArray<int,3>::const_iterator r = a.begin();r!=a.end();r++)
    {cout << r.key() << " : " << r.value() << endl;}

    cout << "size: " << a.size() << endl;

    SparseArray<int,3>::Index i;
    i = 1,2,3;

    cout<<"======"<<endl;
    SparseArray<int,3>::const_reference r = a[i];
    int k = r;
    cout<<k<<endl;
    a.show();

}
int main() {
    SparseArray<int,3> array;
    SparseArray<int,3>::Index i;
    SparseArray<int,3>::Index j;
    SparseArray<int,3>::Index k;
    SparseArray<int,3>::Index a;
    SparseArray<int,3>::Index b;
    SparseArray<int,3>::Index c;
    i = 1,2,1;
    j = 0,5,7;
    k = 3,4,1;
    a = 4,0,0;
    b = 5,1,1;
    c = 6,0,0;
    array[i] = 10;
    array[j] = 6;
    array[k] = 8;
    array[a] = 9;
    array[b] = 10;
    array[c] = 11;
    array[j] = int();
    foo(array);

    cout<<"======"<<endl;

    for( SparseArray<int,3>::iterator r = array.begin();r!=array.end();r++)
    {array[r.key()] = array[r.key()] * 10; }
    array.show();

    cout<<"======"<<endl;

    SparseArray<Z3, 2> arrayZ3;
    SparseArray<Z3, 2>:: Index iZ3;
    iZ3 = 4,3;
    arrayZ3[iZ3] = Z3(28);
    iZ3 = 1,3;
    arrayZ3[iZ3] = Z3(2);
    iZ3 = 8,10;
    arrayZ3[iZ3] = Z3(5);

    arrayZ3.show();
    cout<<"======"<<endl;


    return 0;
}

