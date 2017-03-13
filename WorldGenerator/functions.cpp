#include "functions.h"

/// returns false if something went wrong, true otherwise
bool make_base(Vecteur input, Vecteur& xout, Vecteur& yout, Vecteur& zout){
    if(input.x() == 0 and input.y() == 0 and input.z() == 0)
        return false;
    if(input.x() != 0 and input.y() != 0 and input.z() != 0){
        xout.set(input.x()/input.length(), input.y()/input.length(), input.z()/input.length());
        yout.set(-input.y(), input.x(), 0);
        yout.mult(1/yout.length());
        zout.set(-yout.y(), yout.x(), input.length()/input.z());
        zout.mult(1/zout.length());
    }
    else if(input.x() == 0){
        xout.set(0, input.y()/input.length(), input.z()/input.length());
        yout.set(0, -xout.z(), xout.y());
        zout.set(1, 0, 0);
    }
    else if(input.y() == 0){
        xout.set(input.x()/input.length(), 0, input.z()/input.length());
        yout.set(xout.z(), 0, -xout.x());
        zout.set(0, 1, 0);
    }
    else if(input.z() == 0){
        xout.set(input.x()/input.length(), input.y()/input.length(), 0);
        yout.set(-xout.y(), xout.x(), 0);
        zout.set(0, 0, 1);
    }
    return true;
}
