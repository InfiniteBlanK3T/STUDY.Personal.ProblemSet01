
// COS30008, tutorial 3, 2023

#define _USE_MATH_DEFINES     // must be defined before any #include

#include "Matrix3x3.h"

#include <cassert>
#include <cmath>
#include <type_traits>
#include <iterator>

Matrix3x3::Matrix3x3() noexcept
{
    fRows[0] = Vector3D( 1.0f, 0.0f, 0.0f );
    fRows[1] = Vector3D( 0.0f, 1.0f, 0.0f );
    fRows[2] = Vector3D( 0.0f, 0.0f, 1.0f );
}

Matrix3x3::Matrix3x3( const Vector3D& aRow1, const Vector3D& aRow2, const Vector3D& aRow3 ) noexcept
{
    fRows[0] = aRow1;
    fRows[1] = aRow2;
    fRows[2] = aRow3;
}

const Vector3D Matrix3x3::row( size_t aRowIndex ) const
{
    assert( aRowIndex < 3 );
    
    return fRows[aRowIndex];
}

const Vector3D Matrix3x3::column( size_t aColumnIndex ) const
{
    assert( aColumnIndex < 3 );
    
    return Vector3D( row( 0 )[aColumnIndex],
                     row( 1 )[aColumnIndex],
                     row( 2 )[aColumnIndex] );
}

Matrix3x3 Matrix3x3::operator*( const float aScalar ) const noexcept
{
    return Matrix3x3( row( 0 ) * aScalar,
                      row( 1 ) * aScalar,
                      row( 2 ) * aScalar );
}

Matrix3x3 Matrix3x3::operator+( const Matrix3x3& aOther  ) const noexcept
{
    return Matrix3x3( row( 0 ) + aOther.row( 0 ),
                      row( 1 ) + aOther.row( 1 ),
                      row( 2 ) + aOther.row( 2 ) );
}

Vector3D Matrix3x3::operator*( const Vector3D& aVector ) const noexcept
{
    return Vector3D( row( 0 ).dot( aVector ),
                     row( 1 ).dot( aVector ),
                     row( 2 ).dot( aVector ) );
}

Matrix3x3 Matrix3x3::scale( const float aX, const float aY )
{
    return Matrix3x3( Vector3D( aX, 0.0f, 0.0f ),
                      Vector3D( 0.0f, aY, 0.0f ),
                      Vector3D( 0.0f, 0.0f, 1.0f )
                    );
}

Matrix3x3 Matrix3x3::translate( const float aX, const float aY )
{
    return Matrix3x3( Vector3D( 1.0f, 0.0f, aX ),
                      Vector3D( 0.0f, 1.0f, aY ),
                      Vector3D( 0.0f, 0.0f, 1.0f )
                    );
}

Matrix3x3 Matrix3x3::rotate( const float aAngleInDegree )
{
    float lRadTheta = aAngleInDegree * static_cast<float>(M_PI) / 180.0f;

    float lSinTheta = std::sin( lRadTheta );
    float lCosTheta = std::cos( lRadTheta );
    
    return Matrix3x3( Vector3D( lCosTheta, -lSinTheta, 0.0f ),
                      Vector3D( lSinTheta, lCosTheta, 0.0f ),
                      Vector3D( 0.0f, 0.0f, 1.0f ) );
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& aOther) const noexcept
{    
    return Matrix3x3(   Vector3D(row(0).dot(column(0)), row(0).dot(column(1)), row(0).dot(column(2))),
                        Vector3D(row(1).dot(column(0)), row(1).dot(column(1)), row(1).dot(column(2))),
                        Vector3D(row(2).dot(column(0)), row(2).dot(column(1)), row(2).dot(column(2))));
}

float Matrix3x3::det() const noexcept
{
    return row(0).x() * ( row(1).y() * row(2).w() - row(1).w() * row(2).y() )
        -  row(0).y() * ( row(1).x() * row(2).w() - row(1).w() * row(2).x() )
        +  row(0).w() * ( row(1).x() * row(2).y() - row(1).y() * row(2).x() ) ;
}

bool Matrix3x3::hasInverse() const noexcept
{
    if (Matrix3x3().det() != 0)
        return true;
    else return false;
}
//
Matrix3x3 Matrix3x3::transpose() const noexcept
{
    return Matrix3x3(   Vector3D(row(0).x(), row(1).x(), row(2).x()),
                        Vector3D(row(0).y(), row(1).y(), row(2).y()),
                        Vector3D(row(0).w(), row(1).w(), row(2).w()) );
}
Matrix3x3 Matrix3x3::inverse() const
{
    return Matrix3x3( Vector3D( row(1).y() * row(2).w() - row(1).w() * row(2).y(), row(0).w() * row(2).y() - row(0).y() * row(2).w(), row(0).y() * row(1).w() - row(0).w() * row(1).y() ),
                      Vector3D( row(1).y() * row(2).w() - row(1).w() * row(2).y(), row(0).w() * row(2).y() - row(0).y() * row(2).w(), row(0).y() * row(1).w() - row(0).w() * row(1).y() ),
                      Vector3D( row(1).y() * row(2).w() - row(1).w() * row(2).y(), row(0).w() * row(2).y() - row(0).y() * row(2).w(), row(0).y() * row(1).w() - row(0).w() * row(1).y() )
    ) * ( 1 / Matrix3x3().det() );
    
}

std::ostream& operator<<(std::ostream& aOStream, const Matrix3x3& aMatrix)
{
    return aOStream << "[" 
        << aMatrix.row(0) << ", "
        << aMatrix.row(1) << ", "
        << aMatrix.row(2) <<
        "]";
}
