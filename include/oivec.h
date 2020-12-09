#ifndef OIVEC_H
#define OIVEC_H

#include <QDebug>
#include <QtCore/QtMath>
#include <QFile>
#include <vector>
#include <stdexcept>

#include "global.h"

namespace oi{
namespace math{

class LinearAlgebra;
class OiMat;

using namespace std;

/*!
 * \brief The OiVec class
 */
class OI_MATH_EXPORT OiVec
{
public:
    OiVec();
    OiVec(const int &size);
    ~OiVec();

    static LinearAlgebra *myLinearAlgebra;

private:
    vector<double> values;

public:
    double getAt(int pos) const;
    int getSize() const;

    void set(vector<double> v);
    void setAt(const int &pos, const double &value);

    void add(const double &value);
    void removeLast();

    void replace(const OiVec&);

    OiVec& operator=(const OiVec&);
    OiVec operator+(const OiVec&) const;
    OiVec operator-(const OiVec&) const;
    OiVec& operator+=(const OiVec&);
    OiVec& operator-=(const OiVec&);
    friend OiVec operator*(const OiVec &v, const double value){
        return OiVec::mult(value, v);
    }
    friend OiVec operator*(const double value, const OiVec &v){
        return OiVec::mult(value, v);
    }
    friend OiVec operator/(const OiVec &v, const double value){
        return OiVec::mult((1.0 / value), v);
    }
    friend bool operator==(const OiVec &v1, const OiVec &v2) {
        if(v1.getSize() != v2.getSize()) {
            return false;
        }

        for(int i=0; i<v1.getSize(); i++) {
            if(v1.getAt(i) != v2.getAt(i)) {
                return false;
            }
        }

        return true;
    }

    void normalize();

    OiMat t() const;

    static void cross(OiVec &result, const OiVec &a, const OiVec &b);
    static void dot(double &result, const OiVec &a, const OiVec &b);

    static void concatenateRotations(OiVec &q, const OiVec &q1, const OiVec &q2);

    void writeTo(QString filename);
private:
    static OiVec mult(const double &value, const OiVec &v);

};

}
}

#endif // OIVEC_H
