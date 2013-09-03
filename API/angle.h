#ifndef __ANGLE_H__
#define __ANGLE_H__

class angle;
class anglePI;
class angleRAD;
class angleDEG;

class angle
{public:
    float value;
    
    operator float() { return value; }
    
    angle() { value = 0.0; }
    angle(float f1) { value = f1; }
};

class anglePI : public angle
// Radians in terms of pi
{public:
    anglePI(const anglePI& an);// { value = an.value; }
    anglePI(const angleRAD& an);// { value = an.value / PI; }
    anglePI(const angleDEG& an);// { value = an.value / 180; }
    anglePI(float f1): angle(f1) {}
    anglePI(): angle() {}
};

class angleRAD : public angle
{public:
    angleRAD(const angleRAD& an);// { value = an.value; }
    angleRAD(const angleDEG& an);// { value = an.value * (180.0 / PI); }
    angleRAD(const anglePI& an);// { value = an.value * PI; }
    angleRAD(float f1): angle(f1) {}
    angleRAD(): angle() {}
};

class angleDEG : public angle
{public:
    angleDEG(const angleDEG& an);// { value = an.value; }
    angleDEG(const angleRAD& an);// { value = an.value * (PI / 180.0); }
    angleDEG(float f1): angle(f1) {}
    angleDEG(): angle() {}
};

#endif