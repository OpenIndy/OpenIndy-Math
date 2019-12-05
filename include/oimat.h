#ifndef OIMAT_H
#define OIMAT_H

#include <vector>
#include <stdexcept>
#include <QFile>

#include "global.h"

namespace oi{
namespace math{

class LinearAlgebra;
class OiVec;

using namespace std;

/*!
 * \brief The OiMat class
 */
class OI_MATH_EXPORT OiMat
{
public:
    OiMat();
    OiMat(const int &rows, const int &cols);

    static LinearAlgebra *myLinearAlgebra;

private:
    vector<double> values;
    int rows, cols;

public:

    double getAt(const int &row, const int &col) const;
    unsigned int getRowCount() const;
    unsigned int getColCount() const;
    void getRow(OiVec &result, const int &row) const;
    void getCol(OiVec &result, const int &col) const;

    void replace(const OiMat &m);
    void setAt(const int &row, const int &col, const double &value);
    void diag(vector<double> diagVec);
    void setRow(const int &index, const OiVec &row);
    void setCol(const int &index, const OiVec &col);

    OiMat& operator=(const OiMat &m);
    OiMat operator+(const OiMat &m) const;
    OiMat operator-(const OiMat &m) const;
    OiMat& operator+=(const OiMat &m);
    OiMat& operator-=(const OiMat &m);
    OiMat operator*(const OiMat &m) const;
    OiMat operator*(const double &value) const;
    OiVec operator*(const OiVec &v) const;
    friend OiMat operator*(const double &value, const OiMat &m){
        OiMat result(m.getRowCount(), m.getColCount());
        OiMat::mult(result, value, m);
        return result;
    }
    friend OiMat operator/(const OiMat &m, const double &value){
        OiMat result(m.getRowCount(), m.getColCount());
        OiMat::mult(result, (1.0 / value), m);
        return result;
    }

    OiMat t() const;
    OiMat inv() const;

    double det() const;

    void svd(OiMat &u, OiVec &d, OiMat &v) const;

    static bool solve(OiVec &x, const OiMat &A, const OiVec &b);
    static bool solve(OiMat &X, const OiMat &A, const OiMat &B);

    static OiMat getRotationMatrix(const double &angle, const OiVec &axis);
    static OiMat getRotationMatrix(const OiVec &q);
    static OiMat getRotationMatrix(const double &rx, const double &ry, const double &rz);

    static OiVec getRotationAngles(const OiMat &r);
    static OiVec getQuaternion(const OiMat &r);
    static OiVec getQuaternion(const double &rx, const double &ry, const double &rz);

    void writeTo(QString filename);
private:
    static void mult(OiMat &result, const double &value, const OiMat &m);

};

}
}

#endif // OIMAT_H
