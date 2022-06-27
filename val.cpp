#include <iostream>
#include "val.h"

using namespace std;
Value Value::operator+(const Value& op) const{
    if(this->IsString()){
        if(op.IsString()){
            return this->GetString() + op.GetString();
        }else{
            return Value();
        }
    }
    if(this->IsErr() ){
        return Value();
    }
    if(this->IsInt()){
        if(op.IsInt()){
            return this->GetInt() + op.GetInt();
        }else if(op.IsReal()){
            return this->GetInt() + op.GetReal();
        }else{
            return Value();
        }
    }
    if(this->IsReal()){
        if(op.IsInt()){
            return this->GetReal() + op.GetInt();
        }else if(op.IsReal()){
            return this->GetReal() + op.GetReal();
        }else{
            return Value();
        }
    }
    return Value();
}
Value Value::operator*(const Value& op) const{
    /*if(this->IsErr() ){
        return Value();
    }*/
    if(this->IsInt()){
        if(op.IsInt()){
            return this->GetInt() * op.GetInt();
        }else if(op.IsReal()){
            return this->GetInt() * op.GetReal();
        }else{
            return Value();
        }
    }
    if(this->IsReal()){
        if(op.IsInt()){
            return this->GetReal() * op.GetInt();
        }else if(op.IsReal()){
            return this->GetReal() * op.GetReal();
        }else{
            return Value();
        }
    }
    return Value();
}
Value Value::operator==(const Value& op) const{
    if(this->IsInt()){
        if(op.IsInt()){
            return this->GetInt() == op.GetInt();
        }else if(op.IsReal()){
            return this->GetInt() == op.GetReal();
        }else{
            return Value();
        }
    }
    if(this->IsReal()){
        if(op.IsInt()){
            return this->GetReal() == (float)op.GetInt();
         /*   if(this->GetReal() == (float)op.GetInt()){
                cout << "working" << endl;
                cout << Value(true) << endl;
                return Value(false);
        }else{

        }*/
        }else if(op.IsReal()){
            return this->GetReal() == op.GetReal();
        }else{
            return Value();
        }
    }
    if(this->IsBool()){
        if(op.IsBool()){
            return this->GetBool() == op.GetBool();
        }else{
            return Value();
        }
    }
    if(this->IsString()){
        if(op.IsString()){
            return this->GetString() == op.GetString();
        }else{
            return Value();
        }
    }
    return Value();
}
Value Value::operator/(const Value& op) const{
    //if(op.GetInt() == 0 || op.GetReal() == 0) return Value();
    if(this->IsInt()){
        if(op.IsInt()){
            if(op.GetInt() == 0) return Value();
            return this->GetInt() / op.GetInt();
        }else if(op.IsReal()){
            if(op.GetReal() == 0) return Value();
            return this->GetInt() / op.GetReal();
        }else{
            return Value();
        }
    }
    if(this->IsReal()){
        if(op.IsInt()){
            if(op.GetInt() == 0) return Value();
            return this->GetReal() / op.GetInt();
        }else if(op.IsReal()){
            if(op.GetReal() == 0.0) return Value();
            return this->GetReal() / op.GetReal();
        }else{
            return Value();
        }
    }
    return Value();
}
Value Value::operator-(const Value& op) const{
    if(this->IsInt()){
        if(op.IsInt()){
            return this->GetInt() - op.GetInt();
        }else if(op.IsReal()){
            return this->GetInt() - op.GetReal();
        }else{
            return Value();
        }
    }
    if(this->IsReal()){
        if(op.IsInt()){
            return this->GetReal() - op.GetInt();
        }else if(op.IsReal()){
            return this->GetReal() - op.GetReal();
        }else{
            return Value();
        }
    }
    return Value();
}

Value Value::operator>(const Value& op) const {
    if(this->IsInt()){
        if(op.IsInt()){
            return this->GetInt() > op.GetInt();
        }else if(op.IsReal()){
            return this->GetInt() > op.GetReal();
        }else{
            return Value();
        }
    }
    if(this->IsReal()){
        if(op.IsInt()){
            return this->GetReal() > op.GetInt();
        }else if(op.IsReal()){
            return this->GetReal() > op.GetReal();
        }else{
            return Value();
        }
    }
    return Value();
}

Value Value::operator<(const Value& op) const {
    if(this->IsInt()){
        if(op.IsInt()){
            return this->GetInt() < op.GetInt();
        }else if(op.IsReal()){
            return this->GetInt() < op.GetReal();
        }else{
            return Value();
        }
    }
    if(this->IsReal()){
        if(op.IsInt()){
            return this->GetReal() < op.GetInt();
        }else if(op.IsReal()){
            return this->GetReal() < op.GetReal();
        }else{
            return Value();
        }
    }
    return Value();
}
