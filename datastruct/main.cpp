#include <iostream>
#include <ostream>
#include "IndirectList.h"
#include "xcept.h"
using namespace std;

int main(){
    try{
        IndirectList<int> L(5);
        cout<< "length="<<L.Length()<<endl;
        cout<<"isempty="<<L.IsEmpty()<<endl;
        L.Insert(0,2).Insert(1,6);
        cout<<"List is "<< L <<endl;
        cout<<"isempyt= "<<L.IsEmpty()<<endl;
        int z;
        L.Find(1,z);
        cout<<"first element is "<<z<<endl;
        cout<<"length "<< L.Length()<<endl;
        int index = L.Search(2);
        cout<<"position: "<<index<<endl;
        L.Delete(1,z);
        cout<<"Deleted element is " <<z<<endl;
        cout<< " List is "<<L<<endl;


    }
    catch(...){
        cerr<<"an exception has occurred"<<endl;
    }
}