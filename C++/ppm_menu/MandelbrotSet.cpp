#include <cmath>
#include "MandelbrotSet.h"

MandelbrotSet::MandelbrotSet() : ComplexFractal() {}
MandelbrotSet::MandelbrotSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y )
: ComplexFractal(height, width, min_x, max_x, min_y, max_y){}
MandelbrotSet::~MandelbrotSet() {}
void MandelbrotSet::calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const {
  x1 = x0*x0 - y0*y0 + a;
  y1 = 2*x0*y0 + b;
}
int MandelbrotSet::calculatePlaneEscapeCount( const double& a, const double& b ) const {
  int maxEscapeCount = NumberGrid::getMaxNumber();
  double dist = sqrt( ( a*a ) + ( b*b ) );
  double x1 = a;
  double y1 = b;
  int i;
  for ( i = 0; i < maxEscapeCount; i++ ) {
    if ( dist > getEscapeRadius() ) {
      break;
    }
    calculateNextPoint( x1, y1, a, b, x1, y1 );
    dist = sqrt( ( x1*x1 ) + ( y1*y1 ) );
  }
  return i;
}
int MandelbrotSet::calculateNumber( const int& row, const int& column ) const {
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

MandelbarSet::MandelbarSet() : MandelbrotSet() {}
MandelbarSet::~MandelbarSet() {}
void MandelbarSet::calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const {
  // x' = x*x - y*y + a
  x1 = x0*x0 - y0*y0 + a;
  // y' = -2*x*y + b
  y1 = -2*x0*y0 + b;
}

BurningShip::BurningShip() : MandelbrotSet() {}
BurningShip::~BurningShip() {}
void BurningShip::calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const {
  // x' = x*x - y*y + a
  x1 = x0*x0 - y0*y0 + a;
  // y' = -2*|x*y| + b
  y1 = -2 * std::abs(x0*y0) + b;
}
