#include "oimat.h"

#include "oivec.h"
#include "linearalgebra.h"

using namespace oi::math;

LinearAlgebra* OiMat::myLinearAlgebra = NULL;

OiMat::OiMat(){
    this->values.clear();
    this->rows = 0;
    this->cols = 0;
}

OiMat::OiMat(const int &rows, const int &cols){
    this->values.clear();
    this->rows = rows;
    this->cols = cols;
    for(int i = 0; i < rows*cols; ++i){
        this->values.push_back(0.0);
    }
}

/*!
 * \brief OiMat::getAt
 * Get the value at the specified position
 * \param row
 * \param col
 * \return
 */
double OiMat::getAt(const int &row, const int &col) const{
    if(this->rows > row && this->cols > col){
        return this->values.at( row*this->cols + col );
    }
    throw runtime_error("Size of matrix less than requested position");
}

/*!
 * \brief OiMat::getRowCount
 * \return
 */
unsigned int OiMat::getRowCount() const{
    return this->rows;
}

/*!
 * \brief OiMat::getColCount
 * \return
 */
unsigned int OiMat::getColCount() const{
    return this->cols;
}

/*!
 * \brief OiMat::getRow
 * Get row vector at the specified position
 * \param row
 * \return
 */
void OiMat::getRow(OiVec &result, const int &row) const{
    if(this->rows > row && this->cols > 0 && (result.getSize() == 0 || result.getSize() == this->cols)){
        if(result.getSize() == 0){
            for(int i = 0; i < this->cols; ++i){
                result.add(this->values.at( row*this->cols + i ));
            }
        }else{
            for(int i = 0; i < this->cols; ++i){
                result.setAt(i, this->values.at( row*this->cols + i ));
            }
        }
    }else{
        throw runtime_error("Size of matrix less than requested position");
    }
}

/*!
 * \brief OiMat::getCol
 * Get column vector at the specified position
 * \param col
 * \return
 */
void OiMat::getCol(OiVec &result, const int &col) const{
    if(this->cols > col && this->rows > 0 && (result.getSize() == 0 || result.getSize() == this->rows)){
        if(result.getSize() == 0){
            for(int i = 0; i < this->rows; ++i){
                result.add(this->values.at( col+i*this->cols ));
            }
        }else{
            for(int i = 0; i < this->rows; ++i){
                result.setAt(i, this->values.at( col+i*this->cols ));
            }
        }
    }else{
        throw runtime_error("Size of matrix less than requested position");
    }
}

/*!
 * \brief OiMat::set
 * Set this matrix to m
 * \param m
 */
void OiMat::replace(const OiMat &m){
    this->values.clear();
    this->rows = m.getRowCount();
    this->cols = m.getColCount();
    for(int i = 0; i < this->rows; ++i){
        for(int j = 0; j < this->cols; ++j){
            this->values.push_back(m.getAt(i, j));
        }
    }
}

/*!
 * \brief OiMat::setAt
 * Set the matrix element at the specified position
 * \param row
 * \param col
 * \param value
 */
void OiMat::setAt(const int &row, const int &col, const double &value){
    if(this->rows > row && this->cols > col){
        this->values.at(row*this->cols + col) = value ;
        return;
    }
    throw runtime_error("Size of matrix less than requested position");
}

/*!
 * \brief OiMat::diag
 * Set this matrix to diagonal matrix with diagVec holding the diagonal elements
 * \param diagVec
 */
void OiMat::diag(vector<double> diagVec){
    if(diagVec.size() == this->rows && this->rows == this->cols){
        for(int i = 0; i < this->rows; i++){
            for(int j = 0; j < this->rows; j++){
                if(i == j){
                    this->setAt(i, j, diagVec.at(i));
                }else{
                    this->setAt(i, j, 0.0);
                }
            }
        }
    }else{
        throw logic_error("Size of diagVec incompatible to this matrix");
    }
}

/*!
 * \brief OiMat::setRow
 * Replace the row at index by the given row
 * \param index
 * \param row
 */
void OiMat::setRow(const int &index, const OiVec &row){
    if(this->rows > index){ //if there is a row at index

        if(this->cols == row.getSize()){ //if the given row has the right number of elements

            for(int i = 0; i < this->cols; ++i){
                this->values.at(index*this->cols + i) = row.getAt(i);
            }

        }else{
            throw logic_error("Cannot replace a row of a matrix by a given row with incompatible size");
        }

    }else{
        throw logic_error("Cannot replace a row of a matrix by a given row because of an invalid index");
    }
}

/*!
 * \brief OiMat::setCol
 * Replace the column at index by the given column
 * \param index
 * \param col
 */
void OiMat::setCol(const int &index, const OiVec &col){
    if(this->cols > index){ //if there is a column at index

        if(this->rows == col.getSize()){ //if the given column has the right number of elements

            for(int i = 0; i < this->rows; ++i){
                this->values.at(index + i*this->cols) = col.getAt(i);
            }

        }else{
            throw logic_error("Cannot replace a column of a matrix by a given column with incompatible size");
        }

    }else{
        throw logic_error("Cannot replace a column of a matrix by a given column because of an invalid index");
    }
}

/*!
 * \brief OiMat::operator =
 * Assign a matrix to another
 * \param m
 * \return
 */
OiMat& OiMat::operator =(const OiMat &m){
    if(this->rows == m.getRowCount() && this->cols == m.getColCount()){ //sizes of matrices need to be equal...
        for(int i = 0; i < this->rows; i++){
            for(int j = 0; j < this->cols; j++){
                this->values.at(i*this->cols + j) = m.getAt(i, j);
            }
        }
        return *this;
    }else if(this->rows == 0 && this->cols == 0){ //...or this matrix has size 0 (is undefined)
        this->replace(m);
        return *this;
    }else{
        throw logic_error("A matrix cannot be assigned to another matrix with a different size");
        return *this;
    }
}

/*!
 * \brief OiMat::operator +
 * Add m to this matrix
 * \param v
 * \return
 */
OiMat OiMat::operator+(const OiMat &m) const{
    if(this->rows == m.getRowCount() && this->cols == m.getColCount()
            && this->rows > 0 && this->cols > 0 ){
        OiMat result(this->rows, this->cols);
        OiMat::myLinearAlgebra->addIn(result, *this, m);
        return result;
    }else{
        throw logic_error("Cannot add two matrices of different size");
        return OiMat();
    }
}

/*!
 * \brief OiMat::operator -
 * Substract m from this matrix
 * \param v
 * \return
 */
OiMat OiMat::operator-(const OiMat &m) const{
    if( this->rows == m.getRowCount() && this->cols == m.getColCount()
            && this->rows > 0 && this->cols > 0 ){
        OiMat result(this->rows, this->cols);
        OiMat::myLinearAlgebra->substract(result, *this, m);
        return result;
    }else{
        throw logic_error("Cannot substract two matrices of different size");
        return OiMat();
    }
}

/*!
 * \brief OiMat::operator +=
 * Add m to this matrix
 * \param m
 * \return
 */
OiMat& OiMat::operator+=(const OiMat &m){
    if(this->rows == m.getRowCount() && this->cols == m.getColCount()
            && this->rows > 0 && this->cols > 0 ){
        OiMat::myLinearAlgebra->addIn(*this, *this, m);
        return *this;
    }else{
        throw logic_error("Cannot add two matrices of different size");
        return *this;
    }
}

/*!
 * \brief OiMat::operator +=
 * Substract m from this matrix
 * \param m
 * \return
 */
OiMat& OiMat::operator-=(const OiMat &m){
    if( this->rows == m.getRowCount() && this->cols == m.getColCount()
            && this->rows > 0 && this->cols > 0 ){
        OiMat::myLinearAlgebra->substract(*this, *this, m);
        return *this;
    }else{
        throw logic_error("Cannot substract two matrices of different size");
        return *this;
    }
}

/*!
 * \brief OiMat::operator *
 * Multiply m by this matrix
 * \param v
 * \return
 */
OiMat OiMat::operator*(const OiMat &m) const{
    if( this->cols == m.getRowCount() && this->cols > 0 ){
        OiMat result(this->rows, m.getColCount());
        OiMat::myLinearAlgebra->multiply(result, *this, m);
        return result;
    }else{
        throw logic_error("Cannot multiply two matrices of incompatible size");
        return OiMat();
    }
}

/*!
 * \brief OiMat::operator *
 * Multiply v by this matrix
 * \param v
 * \return
 */
OiVec OiMat::operator*(const OiVec &v) const{
    if( this->cols == v.getSize() && this->cols > 0 ){
        OiVec result(this->rows);
        OiVec::myLinearAlgebra->multiply(result, *this, v);
        return result;
    }else{
        throw logic_error("Cannot multiply a vector by a matrix with incompatible size");
        return OiVec();
    }
}

OiMat OiMat::operator*(const double &value) const{
    OiMat result(this->rows, this->cols);
    OiMat::myLinearAlgebra->multiply(result, value, *this);
    return result;
}

/*!
 * \brief OiMat::mult
 * Multiply the vector by a scalar
 * \param result
 * \param value
 * \param m
 */
void OiMat::mult(OiMat &result, const double &value, const OiMat &m){
    OiMat::myLinearAlgebra->multiply(result, value, m);
}

/*!
 * \brief OiMat::t
 * Calculate the transposed matrix
 * \return
 */
OiMat OiMat::t() const{
    if( this->rows > 0 && this->cols > 0 ){
        OiMat result(this->cols, this->rows);
        OiMat::myLinearAlgebra->transpose(result, *this);
        return result;
    }else{
        return OiMat();
    }
}

/*!
 * \brief OiMat::inv
 * Calculate the inverse matrix
 * \return
 */
OiMat OiMat::inv() const{
    if( this->rows == this->cols && this->rows > 0 ){
        OiMat result(this->rows, this->rows);
        OiMat::myLinearAlgebra->invert(result, *this);
        return result;
    }else{
        throw logic_error("Cannot calculate inverse of non-square matrix");
        return OiMat();
    }
}

/*!
 * \brief OiMat::det
 * Calculate the determinant of the matrix
 * \return
 */
double OiMat::det() const{
    if( this->rows == this->cols && this->rows > 0 ){
        double result = 0.0;
        OiMat::myLinearAlgebra->det(result, *this);
        return result;
    }else{
        throw logic_error("Cannot calculate determinant of non-square matrix");
        return 0.0;
    }
}

/*!
 * \brief OiMat::svd
 * Calculate singular value decomposition
 * \param u
 * \param d
 * \param v
 */
void OiMat::svd(OiMat &u, OiVec &d, OiMat &v) const{
    OiMat::myLinearAlgebra->svd(u, d, v, *this);
}

/*!
 * \brief OiMat::solve
 * Solves a linear equation of the form A*x = b (x = inv(A)*b)
 * \param x
 * \param A
 * \param b
 * \return
 */
bool OiMat::solve(OiVec &x, const OiMat &A, const OiVec &b){
    if(x.getSize() == A.getRowCount() && x.getSize() == A.getColCount()
            && x.getSize() == b.getSize() && x.getSize() > 0){
        return OiMat::myLinearAlgebra->solve(x, A, b);
    }else{
        throw logic_error("No valid linear equation system");
        return false;
    }
}

/*!
 * \brief OiMat::solve
 * Solves a linear equation of the form A*X = B (X = inv(A)*B)
 * \param X
 * \param A
 * \param B
 * \return
 */
bool OiMat::solve(OiMat &X, const OiMat &A, const OiMat &B){
    if(X.getRowCount() == X.getColCount() && X.getRowCount() == A.getRowCount()
            && X.getRowCount() == A.getColCount() && X.getRowCount() == B.getRowCount()
            && X.getRowCount() == B.getColCount()){
        return OiMat::myLinearAlgebra->solve(X, A, B);
    }else{
        throw logic_error("No valid linear equation system");
        return false;
    }
}

/*!
 * \brief OiMat::getRotationMatrix
 * Get the rotation matrix corresponding to a rotation around an arbitrary rotation axis by the given amount
 * \param angle
 * \param axis
 * \return
 */
OiMat OiMat::getRotationMatrix(const double &angle, const OiVec &axis){
    if(axis.getSize() == 3){
        OiMat result(3, 3);

        OiVec axisN = axis;
        axisN.normalize();

        double w = qCos(angle / 2.0);
        OiVec x = qSin(angle / 2.0) * axisN;

        result.setAt(0, 0, 1.0 - 2.0 * (x.getAt(1)*x.getAt(1) + x.getAt(2)*x.getAt(2)));
        result.setAt(0, 1, 2.0 * (x.getAt(0)*x.getAt(1) - w * x.getAt(2)));
        result.setAt(0, 2, 2.0 * (x.getAt(0)*x.getAt(2) + w * x.getAt(1)));
        result.setAt(1, 0, 2.0 * (x.getAt(0)*x.getAt(1) + w * x.getAt(2)));
        result.setAt(1, 1, 1.0 - 2.0 * (x.getAt(0)*x.getAt(0) + x.getAt(2)*x.getAt(2)));
        result.setAt(1, 2, 2.0 * (x.getAt(1)*x.getAt(2) - w * x.getAt(0)));
        result.setAt(2, 0, 2.0 * (x.getAt(0)*x.getAt(2) - w * x.getAt(1)));
        result.setAt(2, 1, 2.0 * (x.getAt(1)*x.getAt(2) + w * x.getAt(0)));
        result.setAt(2, 2, 1.0 - 2.0 * (x.getAt(0)*x.getAt(0) + x.getAt(1)*x.getAt(1)));

        return result;
    }else{
        throw logic_error("To set up the rotation matrix the given axis has to be of size 3");
        return OiMat();
    }
}

/*!
 * \brief OiMat::getRotationMatrix
 * \param q
 * \return
 */
OiMat OiMat::getRotationMatrix(const OiVec &q){

    //check quaternion
    if(q.getSize() != 4){
        return OiMat();
    }

    //build rotation matrix
    OiMat r(3,3);

    r.setAt(0, 0, 1.0 - 2.0 * (q.getAt(2)*q.getAt(2) + q.getAt(3)*q.getAt(3)));
    r.setAt(0, 1, 2.0 * (q.getAt(1)*q.getAt(2) - q.getAt(0) * q.getAt(3)));
    r.setAt(0, 2, 2.0 * (q.getAt(1)*q.getAt(3) + q.getAt(0) * q.getAt(2)));
    r.setAt(1, 0, 2.0 * (q.getAt(1)*q.getAt(2) + q.getAt(0) * q.getAt(3)));
    r.setAt(1, 1, 1.0 - 2.0 * (q.getAt(1)*q.getAt(1) + q.getAt(3)*q.getAt(3)));
    r.setAt(1, 2, 2.0 * (q.getAt(2)*q.getAt(3) - q.getAt(0) * q.getAt(1)));
    r.setAt(2, 0, 2.0 * (q.getAt(1)*q.getAt(3) - q.getAt(0) * q.getAt(2)));
    r.setAt(2, 1, 2.0 * (q.getAt(2)*q.getAt(3) + q.getAt(0) * q.getAt(1)));
    r.setAt(2, 2, 1.0 - 2.0 * (q.getAt(1)*q.getAt(1) + q.getAt(2)*q.getAt(2)));




    /*r.setAt(0, 0, q.getAt(0)*q.getAt(0) + q.getAt(1)*q.getAt(1) - q.getAt(2)*q.getAt(2) - q.getAt(3)*q.getAt(3));
    r.setAt(0, 1, 2.0*(q.getAt(1)*q.getAt(2) - q.getAt(0)*q.getAt(3)));
    r.setAt(0, 2, 2.0*(q.getAt(1)*q.getAt(3) + q.getAt(0)*q.getAt(2)));
    r.setAt(1, 0, 2.0*(q.getAt(1)*q.getAt(2) + q.getAt(0)*q.getAt(3)));
    r.setAt(1, 1, q.getAt(0)*q.getAt(0) - q.getAt(1)*q.getAt(1) + q.getAt(2)*q.getAt(2) - q.getAt(3)*q.getAt(3));
    r.setAt(1, 2, 2.0*(q.getAt(2)*q.getAt(3) - q.getAt(0)*q.getAt(1)));
    r.setAt(2, 0, 2.0*(q.getAt(3)*q.getAt(1) - q.getAt(0)*q.getAt(2)));
    r.setAt(2, 1, 2.0*(q.getAt(3)*q.getAt(2) + q.getAt(0)*q.getAt(1)));
    r.setAt(2, 2, q.getAt(0)*q.getAt(0) - q.getAt(1)*q.getAt(1) - q.getAt(2)*q.getAt(2) + q.getAt(3)*q.getAt(3));*/

    return r;

}

/*!
 * \brief OiMat::getRotationMatrix
 * \param rx
 * \param ry
 * \param rz
 * \return
 */
OiMat OiMat::getRotationMatrix(const double &rx, const double &ry, const double &rz){

    OiMat r(3,3);
    r.setAt(0, 0, cos(ry)*cos(rz));
    r.setAt(0, 1, cos(rx)*sin(rz)+sin(rx)*sin(ry)*cos(rz));
    r.setAt(0, 2, sin(rx)*sin(rz)-cos(rx)*sin(ry)*cos(rz));
    r.setAt(1, 0, -cos(ry)*sin(rz));
    r.setAt(1, 1, cos(rx)*cos(rz)-sin(rx)*sin(ry)*sin(rz));
    r.setAt(1, 2, sin(rx)*cos(rz)+cos(rx)*sin(ry)*sin(rz));
    r.setAt(2, 0, sin(ry));
    r.setAt(2, 1, -sin(rx)*cos(ry));
    r.setAt(2, 2, cos(rx)*cos(ry));

    return r;

}

/*!
 * \brief OiMat::getRotationAngles
 * \param r
 * \return
 */
OiVec OiMat::getRotationAngles(const OiMat &r){

    //check matrix
    if(r.getRowCount() != 3 || r.getRowCount() != r.getColCount()){
        return OiVec();
    }

    OiVec angles(3);
    angles.setAt(0, atan2(-r.getAt(2,1), r.getAt(2,2))); //rx
    angles.setAt(1, asin(r.getAt(2,0))); //ry
    angles.setAt(2, atan2(-r.getAt(1,0), r.getAt(0,0))); //rz
    if( abs(cos(angles.getAt(1)) * cos(angles.getAt(2))) - abs(r.getAt(0,0)) > 0.01 ){
        angles.setAt(1, 3.141592653589793 - angles.getAt(1));
    }

    return angles;

}

/*!
 * \brief OiMat::getQuaternion
 * \param r
 * \return
 */
OiVec OiMat::getQuaternion(const OiMat &r){

    if(r.getColCount() != 3 || r.getRowCount() != 3){
        return OiVec();
    }
    OiVec rotAngles = getRotationAngles(r);
    OiVec quat = getQuaternion(rotAngles.getAt(0), rotAngles.getAt(1), rotAngles.getAt(2));
    return quat;
}

/*!
 * \brief OiMat::getQuaternion
 * \param rx
 * \param ry
 * \param rz
 * \return
 */
OiVec OiMat::getQuaternion(const double &rx, const double &ry, const double &rz)
{
    oi::math::OiMat rotMat = oi::math::OiMat::getRotationMatrix(rx, ry, rz);

    int factor;
    double factor2;
    if((rotMat.getAt(0,0)+rotMat.getAt(1,1)+rotMat.getAt(2,2)) > 0){
        factor = 1;
    }else if((rotMat.getAt(0,0) > rotMat.getAt(1,1)) && (rotMat.getAt(0,0) > rotMat.getAt(2,2))){
        factor = 2;
    }else if(rotMat.getAt(1,1) > rotMat.getAt(2,2)){
        factor = 3;
    }else{
        factor = 4;
    }

    if(factor == 1){
        factor2 = 2* sqrt(1+rotMat.getAt(0,0) + rotMat.getAt(1,1) + rotMat.getAt(2,2));
    }else if(factor == 2){
        factor2 = 2* sqrt(1 + rotMat.getAt(0,0) - rotMat.getAt(1,1) - rotMat.getAt(2,2));
    }else if(factor == 3){
        factor2 =  2* sqrt(1+rotMat.getAt(1,1) - rotMat.getAt(0,0) - rotMat.getAt(2,2));
    }else if(factor ==4){
        factor2 = 2* sqrt(1+ rotMat.getAt(2,2) - rotMat.getAt(0,0) - rotMat.getAt(1,1));
    }

    oi::math::OiVec quatVec;

    if(factor == 1){
        quatVec.add(0.25*factor2);
        quatVec.add((rotMat.getAt(2,1)-rotMat.getAt(1,2))/factor2);
        quatVec.add((rotMat.getAt(0,2)-rotMat.getAt(2,0))/factor2);
        quatVec.add((rotMat.getAt(1,0)-rotMat.getAt(0,1))/factor2);
    }else if(factor == 2){
        quatVec.add((rotMat.getAt(2,1)-rotMat.getAt(1,2))/factor2);
        quatVec.add(0.25*factor2);
        quatVec.add((rotMat.getAt(0,1)+rotMat.getAt(1,0))/factor2);
        quatVec.add((rotMat.getAt(0,2)+rotMat.getAt(2,0))/factor2);
    }else if(factor == 3){
        quatVec.add((rotMat.getAt(0,2)-rotMat.getAt(2,0))/factor2);
        quatVec.add((rotMat.getAt(0,1)+rotMat.getAt(1,0))/factor2);
        quatVec.add(0.25*factor2);
        quatVec.add((rotMat.getAt(1,2)+rotMat.getAt(2,1))/factor2);
    }else if(factor == 4){
        quatVec.add((rotMat.getAt(1,0)-rotMat.getAt(0,1))/factor2);
        quatVec.add((rotMat.getAt(0,2)+rotMat.getAt(2,0))/factor2);
        quatVec.add((rotMat.getAt(1,2)+rotMat.getAt(2,1))/factor2);
        quatVec.add(0.25*factor2);
    }

    return quatVec;
}

void OiMat::writeTo(QString filename){
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    for(int row=0; row<this->getRowCount(); row++){
        for(int col=0; col<this->getColCount();col++){
            stream << QString::number(this->getAt(row, col), 'f', 10);
            stream << "\t";
        }
        stream << endl;
    }
    file.close();
}
