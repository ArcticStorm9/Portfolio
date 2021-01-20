#include "ComplexFractal.h"

ComplexFractal::ComplexFractal() : ThreadedGrid( 200, 300 ), mDeltaX(0.01), mDeltaY(0.01), mMinX(-1.5), mMaxX(1.5), mMinY(-1), mMaxY(1), mEscapeRadius(2) {
  NumberGrid::setMaxNumber(255);
}
ComplexFractal::ComplexFractal( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y ) :
ThreadedGrid(height, width), mDeltaX(0.01), mDeltaY(0.01), mMinX(min_x), mMaxX(max_x), mMinY(min_y), mMaxY(max_y), mEscapeRadius(2) {
  NumberGrid::setMaxNumber(255);
}
ComplexFractal::~ComplexFractal(){}
double ComplexFractal::getMinX() const {
  return mMinX;
}
double ComplexFractal::getMaxX() const {
  return mMaxX;
}
double ComplexFractal::getMinY() const {
  return mMinY;
}
double ComplexFractal::getMaxY() const {
  return mMaxY;
}
void ComplexFractal::setGridSize( const int& height, const int& width ) {
  if ( width >= 2 && height >= 2 ) {
    NumberGrid::setGridSize( height, width );
    double delta_x = calculateDeltaX();
    double delta_y = calculateDeltaY();
    setDeltas(delta_x, delta_y);
  }
}
void ComplexFractal::setPlaneSize( const double& min_x, const double& max_x, const double& min_y, const double& max_y ) {
  if ( min_x <= 2 && min_x >= -2 && max_x <=2 && max_x >= -2 && max_x != min_x && min_y <= 2 && min_y >= -2 && max_y <= 2 && max_y >= -2 && max_y != min_y ) {
    if ( min_x > max_x ) {
      mMinX = max_x;
      mMaxX = min_x;
      mDeltaX = calculateDeltaX();
    }
    else {
      mMinX = min_x;
      mMaxX = max_x;
      mDeltaX = calculateDeltaX();
    }
    if ( min_y > max_y ) {
      mMinY = max_y;
      mMaxY = min_y;
      mDeltaY = calculateDeltaY();
    }
    else {
      mMinY = min_y;
      mMaxY = max_y;
      mDeltaY = calculateDeltaY();
    }
  }
}
double ComplexFractal::getDeltaX() const {
  return mDeltaX;
}
double ComplexFractal::getDeltaY() const {
  return mDeltaY;
}
void ComplexFractal::setDeltas( const double& delta_x, const double& delta_y ) {
  if ( delta_x >= 0 && delta_y >= 0 ) {
    mDeltaX = delta_x;
    mDeltaY = delta_y;
  }
}
double ComplexFractal::calculateDeltaY( ) const {
  return ( mMaxY - mMinY ) / ( mHeight - 1 );
}
double ComplexFractal::calculateDeltaX( ) const {
  return ( mMaxX - mMinX ) / ( mWidth - 1 );
}
double ComplexFractal::calculatePlaneXFromPixelColumn( const int& column ) const {
  if ( column < 0 || column >= mWidth ) {
    return 0;
  }
  else {
    return mMinX + column * getDeltaX();
  }
}
double ComplexFractal::calculatePlaneYFromPixelRow( const int& row ) const {
  if ( row < 0 || row >= mHeight ) {
    return 0;
  }
  else {
    return mMaxY - row * getDeltaY();
  }
}
void ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates( const int& row, const int& column, double& x, double& y ) const {
  if ( row < mHeight && row >= 0 && column < mWidth && column >= 0 ) {
    x = calculatePlaneXFromPixelColumn( column );
    y = calculatePlaneYFromPixelRow( row );
  }
  else {
    x = 0.0;
    y = 0.0;
  }
}
double ComplexFractal::getEscapeRadius() const {
  return mEscapeRadius;
}
void ComplexFractal::setEscapeRadius(const double& radius) {
  if ( radius > 0 ) {
    mEscapeRadius = radius;
  }
}
