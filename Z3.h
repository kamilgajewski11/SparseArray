#ifndef SPARSE_ARRAY_Z3_H
#define SPARSE_ARRAY_Z3_H
#include <ostream>
#include <cstdio>
using  namespace std;
class Z3 {
    short number;

public:
    Z3(){
        this->number = 0;
    }

    Z3(const short& number){
        if(number>=0)
            this->number = number%3;

        if(number<0){
            short tmp = number*(-1) % 3;
            if(tmp == 1)
                this->number = 2;
            if(tmp == 2)
                this->number = 1;
            if(tmp == 0)
                this->number = 0;
        }
    }



    Z3(const Z3& number){
        Z3 new_number = Z3(number.number);
        this->number = new_number;
    }

    ~Z3()= default;

    operator short () const{
        return number;
    }

    Z3& operator=(const Z3& input_number){
        Z3 new_number = Z3(input_number.number);
        this->number = new_number;
        return *this;
    }

    bool operator !=(const Z3& input_number){
        if(number == input_number.number){
            return false;
        }
        return true;
    }

    bool operator ==(const Z3& input_number){
        if(number == input_number.number){
            return true;
        }
        return false;
    }
    friend ostream& operator<<(ostream& o, const Z3& number_1) {
        o<<number_1.number;
        return o;
    }


};


#endif //SPARSE_ARRAY_Z3_H
