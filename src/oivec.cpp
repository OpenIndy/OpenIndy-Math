#include "oivec.h"

#include "oimat.h"
#include "linearalgebra.h"

using namespace oi::math;

LinearAlgebra* OiVec::myLinearAlgebra = NULL;

OiVec::OiVec()
{
    this->values.clear();
}

OiVec::OiVec(const int &size){
    this->values.clear();
    for(int i = 0; i < size; i++){
        this->values.push_back(0.0);
    }
}

OiVec::~OiVec(){

}

/*!
 * \brief OiVec::getAt
 * Get The value at the specified position
 * \param pos
 * \return
 */
double OiVec::getAt(int pos) const{
    if(this->values.size() > pos){
        return this->values.at(pos);
    }else{
        throw runtime_error("Size of vector less than requested position");
        return -1.0;
    }
}

/*!
 * \brief OiVec::getSize
 * Returns the size of the vector
 * \return
 */
int OiVec::getSize() const{
    return this->values.size();
}

/*!
 * \brief OiVec::set
 * Replace the list by another
 * \param v
 */
void OiVec::set(vector<double> v){
    this->values = v;
}

/*!
 * \brief OiVec::setAt
 * Set the vector element at the specified position
 * \param pos
 * \param value
 */
void OiVec::setAt(const int &pos, const double &value){
    if(this->values.size() > pos){
        this->values.at(pos) = value;
    }else{
        throw runtime_error("Size of vector less than requested position");
    }
}

/*!
 * \brief OiVec::add
 * Add an element at the end of the vector
 * \param value
 */
void OiVec::add(const double &value){
    this->values.push_back(value);
}

/*!
 * \brief OiVec::removeLast
 */
void OiVec::removeLast(){
    if(this->values.size() > 0){
        this->values.pop_back();
    }
}

/*!
 * \brief OiVec::replace
 */
void OiVec::replace(const OiVec &v){
    this->values.clear();
    for(int i = 0; i < v.getSize(); i++){
        this->add(v.getAt(i));
    }
}

/*!
 * \brief OiVec::operator =
 * Assign a vector to another
 * \param v
 * \return
 */
OiVec& OiVec::operator =(const OiVec &v){
    if(this->getSize() == v.getSize()){ //sizes of vectors need to be equal...
        for(int i = 0; i < this->getSize(); i++){
            this->setAt(i, v.getAt(i));
        }
        return *this;
    }else if(this->getSize() == 0){ //...or this vector has size 0 (is undefined)
        for(int i = 0; i < v.getSize(); i++){
            this->add(v.getAt(i));
        }
        return *this;
    }else{
        throw logic_error("A vector cannot be assigned to another vector with a different size");
        return *this;
    }
}

/*!
 * \brief OiVec::operator +
 * Add v to this vector
 * \param v
 * \return
 */
OiVec OiVec::operator+(const OiVec &v) const{
    if(this->getSize() == v.getSize()){
        OiVec result(v.getSize());
        OiVec::myLinearAlgebra->addIn(result, *this, v);
        return result;
    }else{
        throw logic_error("Cannot add two vectors of different size");
        return OiVec();
    }
}

/*!
 * \brief OiVec::operator -
 * Substract v from this vector
 * \param v
 * \return
 */
OiVec OiVec::operator-(const OiVec &v) const{
    if(this->getSize() == v.getSize()){
        OiVec result(v.getSize());
        OiVec::myLinearAlgebra->substract(result, *this, v);
        return result;
    }else{
        throw logic_error("Cannot substract two vectors of different size");
        return OiVec();
    }
}

/*!
 * \brief OiVec::operator +=
 * \param v
 * \return
 */
OiVec& OiVec::operator +=(const OiVec &v){
    if(this->getSize() == v.getSize()){
        OiVec::myLinearAlgebra->addIn(*this, *this, v);
        return *this;
    }else{
        throw logic_error("Cannot add two vectors of different size");
        return *this;
    }
}

/*!
 * \brief OiVec::operator -=
 * \param v
 * \return
 */
OiVec& OiVec::operator -=(const OiVec &v){
    if(this->getSize() == v.getSize()){
        OiVec::myLinearAlgebra->substract(*this, *this, v);
        return *this;
    }else{
        throw logic_error("Cannot substract two vectors of different size");
        return *this;
    }
}

/*!
 * \brief OiVec::normalize
 */
void OiVec::normalize(){
    double l = 0.0;
    for(int i = 0; i < this->getSize(); i++){
        l += this->getAt(i) * this->getAt(i);
    }
    if(l > 0.0){
        l = qSqrt(l);
        for(int i = 0; i < this->getSize(); i++){
            this->setAt(i, this->getAt(i) / l);
        }
    }
}

/*!
 * \brief OiVec::t
 * Calculate the transposed of this vector which is a matrix
 * \return
 */
OiMat OiVec::t() const{
    if(this->getSize() > 0){
        OiMat result(1, this->getSize());
        for(int i = 0; i < this->getSize(); i++){
            result.setAt(0, i, this->getAt(i));
        }
        return result;
    }
    return OiMat();
}

/*!
 * \brief OiVec::cross
 * Calculate cross product (only if a and b are 3 dimensional vectors)
 * \param result
 * \param a
 * \param b
 */
void OiVec::cross(OiVec &result, const OiVec &a, const OiVec &b){
    if(a.getSize() == b.getSize() && a.getSize() == 3 && (result.getSize() == 0 || result.getSize() == a.getSize())){
        if(result.getSize() == 0){
            for(int i = 0; i < a.getSize(); i++){
                result.add(0.0);
            }
        }
        OiVec::myLinearAlgebra->cross(result, a, b);
    }else{
        throw logic_error("Cannot calculate cross product of non - 3 dimesnional vectors");
    }
}

/*!
 * \brief OiVec::dot
 * Calculate scalar product (only if a and b are of same size)
 * \param result
 * \param a
 * \param b
 */
void OiVec::dot(double &result, const OiVec &a, const OiVec &b){
    if(a.getSize() == b.getSize() && a.getSize() > 0){
        OiVec::myLinearAlgebra->dot(result, a, b);
    }else{
        throw logic_error("Cannot calculate scalar product of vectors with incompatible size");
    }
}

/*!
 * \brief OiVec::concatenateRotations
 * Concatenate two rotations defined by the quaternions q1 and q2
 * \param q
 * \param q1
 * \param q2
 */
void OiVec::concatenateRotations(OiVec &q, const OiVec &q1, const OiVec &q2){

    //rotate by q2 and afterwards by q1
    //q = q2 * q1 == R = R1 * R2
    //q = [w, vx, vy, vz]

    if(q.getSize() == 0){
        for(int i = 0; i < 4; i++){
            q.add(0.0);
        }
    }

    if(q.getSize() != 4 || q1.getSize() != 4 || q2.getSize() != 4){
        throw logic_error("Cannot concatenate two quaternion-rotations of incompatible size");
    }

    OiVec a(3), b(3);
    a.setAt(0, q1.getAt(1));
    a.setAt(1, q1.getAt(2));
    a.setAt(2, q1.getAt(3));
    b.setAt(0, q2.getAt(1));
    b.setAt(1, q2.getAt(2));
    b.setAt(2, q2.getAt(3));

    OiVec n;
    double s;
    OiVec::dot(s, a, b);
    OiVec::cross(n, a, b);

    OiVec qv = n + q1.getAt(0) * b + q2.getAt(0) * a;

    q.setAt(0, q1.getAt(0) * q2.getAt(0) - s);
    q.setAt(1, qv.getAt(0));
    q.setAt(2, qv.getAt(1));
    q.setAt(3, qv.getAt(2));
}

/*!
 * \brief OiVec::mult
 * Multiply the vector by a scalar
 * \param value
 * \param v
 * \return
 */
OiVec OiVec::mult(const double &value, const OiVec &v){
    OiVec result(v.getSize());
    OiVec::myLinearAlgebra->multiply(result, value, v);
    return result;
}
