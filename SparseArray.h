#ifndef SPARSE_ARRAY_SPARSEARRAY_H
#define SPARSE_ARRAY_SPARSEARRAY_H
#include <iostream>
#include <map>
#include <cstdlib>
#include <stdexcept>

using namespace std;

template <class V, unsigned D>
class SparseArray {
public:

    class Index{
    private:
        unsigned *indexArray;
        unsigned counter;
    public:
        Index(){
            counter = 0;
            indexArray = new unsigned[D];
            for (unsigned i = 0; i < D; i++) {
                indexArray[i] *= 0;
            }
        }

        Index(const Index& ind){
            counter = ind.counter;
            unsigned *new_array = new unsigned[D];
            for(unsigned i = 0; i<D; i++){
                new_array[i] = ind.indexArray[i];
            }
            indexArray = new_array;
        }
        ~Index(){
            delete[] indexArray;
        }

        unsigned& operator[](unsigned id){
            if(id < 0 || id>D-1){
                throw runtime_error("Invalid index");
            }
            return indexArray[id];
        }
        unsigned operator[](unsigned id) const{
            if(id < 0 || id>D-1){
                throw runtime_error("Invalid index");
            }
            return indexArray[id];
        }

        Index& operator,(unsigned a){
            counter++;
            if(counter >= D){
                throw runtime_error("Index overflow");
            }
            indexArray[counter] = a;
            return *this;
        }

        Index& operator=(unsigned a){
            counter = 0;
            for(unsigned i = 0; i<D; i++){
                indexArray[i] = 0;
            }
            indexArray[0] = a;
            return *this;
        }


        friend bool operator==(const Index& ind1, const Index& ind2){
            for(unsigned i = 0; i<D; i++){
                if(ind1[i] != ind2[i]){
                    return false;
                }
            }
            return true;
        }

        Index& operator=(const Index& ind){
            if(this == &ind) {
                return *this;
            }

            unsigned *new_array = new unsigned[D];
            for(int i = 0; i<D; i++){
                new_array[i] = indexArray[i];
            }

            indexArray = new_array;
            return *this;
        }
        friend bool operator<(const Index& ind1, const Index& ind2){
            for(unsigned i = 0; i<D; i++){
                if(ind1[i] < ind2.indexArray[i]){
                    return true;
                }
                if(ind1[i]> ind2.indexArray[i]){
                    return false;
                }
            }
            return false;
        }

        friend ostream& operator<<(ostream& o, const Index& ind) {
            o<<"{";
            for(int i = 0; i<D-1; i++){
                o<<ind.indexArray[i]<<",";
            }
            o<<ind.indexArray[D-1];
            o<<"}";
            return o;
        }
    };
    class reference {
    public:
        Index ind;
        map<const Index, V>* refMap;

        reference()= default;
        reference(const Index& ind,map<const Index, V>& refMap): ind(ind), refMap(&refMap){}
        reference(const reference& ref){
            ind = ref.ind;
            refMap = ref.refMap;
        }
        reference& operator =(const reference& ref) {
            if(this == &ref){
                return *this;
            }
            ind = ref.ind;
            refMap = ref.refMap;
        }


        reference& operator =(const V& v){
            if(v != V()) {
                (*refMap)[ind] = v;
            }
            if(v == V() && (*refMap).count(ind)){
                (*refMap).erase(ind);
            }

            return *this;
        }
        operator V() {
            if(!(*refMap).count(ind)){
                return V();
            }
            return (*refMap)[ind];
        }

    };
    reference operator[](const Index& ind){
        return reference(ind, mapa);
    }

    class const_reference{
    public:
        Index ind;
        const map<const Index, V>* refMap;

        const_reference()= default;
        const_reference(const Index& ind,const map<const Index, V>& refMap): ind(ind), refMap(&refMap){}
        const_reference(const const_reference& ref){
            ind = ref.ind;
            refMap = ref.refMap;
        }
        const_reference(const reference& ref){
            ind = ref.ind;
            refMap = ref.refMap;
        }
        const_reference& operator =(const reference& ref) {
            ind = ref.ind;
            refMap = ref.refMap;
        }

        const_reference& operator =(const const_reference& ref) {
            if(this == &ref){
                return *this;
            }
            ind = ref.ind;
            refMap = ref.refMap;
        }

        operator V() const{

            if(!(*refMap).count(ind)){
                return V();
            }
            return (*refMap).at(ind);
        }

    };
    const_reference operator[](const Index& ind) const{
        return const_reference(ind, mapa);
    }

    class iterator{
    public:
        typename map<Index,V>::iterator it;
        map<const Index, V>* itMap;

        iterator()= default;
        iterator(const typename map<Index,V>::iterator& it, map<const Index, V>& itMap): it(it), itMap(&itMap){}

        Index key(){
            return it->first;
        }
        V value(){
            return it->second;
        }
        reference operator*(){
            return reference(it->first, *itMap);
        }

        bool operator ==(const iterator& iter){
            if(it == iter.it){
                return true;
            }
            return false;
        }
        bool operator !=(const iterator& iter){
            if(it == iter.it){
                return false;
            }
            return true;
        }
        void operator++(){
            if(it != (*itMap).end()){
                ++it;
            } else{
                throw runtime_error("Iterator overflow");
            }
        }
        void operator++(int){
            if(it != (*itMap).end()){
                ++it;
            } else{
                throw runtime_error("Iterator overflow");
            }
        }

    };

    iterator begin(){
        return iterator(mapa.begin(), mapa);
    }
    iterator end(){
        return iterator(mapa.end(), mapa);
    }

    class const_iterator{
    public:
        typename map<Index,V>::const_iterator it;
        const map<const Index, V>* itMap;

        const_iterator()= default;
        const_iterator(const typename map<Index,V>::const_iterator& it,const map<const Index, V>& itMap): it(it), itMap(&itMap){}
        const_iterator(const const_iterator& iter): it(iter.it), itMap(iter.itMap){}
        const_iterator& operator =(const const_iterator& iter){
            if(this == &iter){
                return *this;
            }
            it = iter.it;
            itMap = iter.itMap;
        }
        bool operator ==(const const_iterator& iter){
            if(it == iter.it){
                return true;
            }
            return false;
        }
        bool operator !=(const const_iterator& iter){
            if(it == iter.it){
                return false;
            }
            return true;
        }
        Index key(){
            return it->first;
        }
        V value(){
            return it->second;
        }
        const_reference operator*(){
            return const_reference(it->first, *itMap);
        }
        void operator++(){
            if(it != (*itMap).end()){
                ++it;
            } else{
                throw runtime_error("Iterator overflow");
            }
        }
        void operator++(int){
            if(it != (*itMap).end()){
                ++it;
            } else{
                throw runtime_error("Iterator overflow");
            }
        }
    };

    const_iterator begin() const{
        return const_iterator(mapa.begin(), mapa);
    }
    const_iterator end() const{
        return const_iterator(mapa.end(), mapa);
    }

    SparseArray()= default;
    SparseArray(const SparseArray<V,D>& arr){
        mapa = arr.mapa;
    }
    SparseArray<V,D>& operator =(const SparseArray<V,D>& arr){
        mapa = arr.mapa;
        return *this;
    }


    map<const Index, V> mapa;

    void show() const{
        typename std::map<Index, V>::const_iterator it = mapa.cbegin();

        while (it!=mapa.end()) {
            cout << it->first << " = " << it->second << endl;
            ++it;
        }
        if(mapa.begin() == mapa.end()){
            cout<<"Pusta tablica"<<endl;
        }
        cout<<endl;
    };
    unsigned size() const{
        unsigned counter = 0;
        typename std::map<Index, V>::const_iterator it = mapa.begin();

        while (it!=mapa.end()) {
            it++;
            counter++;
        }
        return counter;
    }

};


#endif //SPARSE_ARRAY_SPARSEARRAY_H
