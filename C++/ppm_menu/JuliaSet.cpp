#include <cmath>
#include "JuliaSet.h"

JuliaSet::JuliaSet() : mA(-0.650492), mB(-0.478235) {
  NumberGrid::setMaxNumber(255);
}
JuliaSet::JuliaSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b ) :
ComplexFractal( height, width, min_x, max_x, min_y, max_y ), mA(a), mB(b) {
  NumberGrid::setMaxNumber(255);
}
JuliaSet::~JuliaSet( ) {}
double JuliaSet::getA( ) const {
  return mA;
}
double JuliaSet::getB( ) const {
  return mB;
}
void JuliaSet::setParameters( const double& a, const double& b ) {
  if ( a >= -2.0 && a <= 2.0 && b >= -2.0 && b <= 2.0 ) {
    mA = a;
    mB = b;
  }
}
void JuliaSet::calculateNextPoint( const double x0, const double y0, double& x1, double &y1 ) const {
  x1 = x0 * x0 - y0 * y0 + getA();
  y1 = 2 * x0 * y0 + getB();
}
int JuliaSet::calculatePlaneEscapeCount( const double& x0, const double& y0 ) const {
  int maxEscapeCount = NumberGrid::getMaxNumber();
  double dist = sqrt( ( x0*x0 ) + ( y0*y0 ) );
  double x1 = x0;
  double y1 = y0;
  int i;
  for ( i = 0; i < maxEscapeCount; i++ ) {
    if ( dist > getEscapeRadius() ) {
      break;
    }
    calculateNextPoint( x1, y1, x1, y1 );
    dist = sqrt( ( x1*x1 ) + ( y1*y1 ) );
  }
  return i;
}
int JuliaSet::calculateNumber( const int& row, const int& column ) const {
  if ( row < 0 || row >= mHeight || column < 0 || column >= mWidth ) {
    return -1;
  }
  else {
    double x = calculatePlaneXFromPixelColumn( column );
    double y = calculatePlaneYFromPixelRow( row );
    calculatePlaneCoordinatesFromPixelCoordinates( row, column, x, y );
    return calculatePlaneEscapeCount( x, y );
  }
}
JuliaSetFour::JuliaSetFour() : JuliaSet() {}
JuliaSetFour::~JuliaSetFour(){}
void JuliaSetFour::calculateNextPoint( const double x0, const double y0, double& x1, double &y1 ) const {
  x1 = (x0 * x0 * x0 * x0) - (6 *(x0*x0) * (y0*y0)) + (y0*y0*y0*y0) + getA();
  y1 = (4 * (x0*x0*x0) * y0) - (4 * x0 * (y0*y0*y0)) + getB();
}
