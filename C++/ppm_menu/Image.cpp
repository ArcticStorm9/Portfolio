#include "Image.h"
#include <vector>
#include <iostream>

Image::Image() : mHeight(0), mWidth(0) {
  mImg.resize( mHeight * mWidth * 3 );
}
Image::Image( const int& height, const int& width ) {
  mHeight = height;
  mWidth = width;
  mImg.resize( height * width * 3 );
}
int Image::getHeight() const {
  return mHeight;
}
int Image::getWidth() const {
  return mWidth;
}
bool Image::indexValid( const int& row, const int& column, const int& channel ) const {
  if ( row < mHeight && row >= 0 && column < mWidth && column >= 0 && channel >= 0 && channel <= 2 ) {
    return true;
  }
  else {
    return false;
  }
}
int Image::index( const int& row, const int& column, const int& channel ) const {
  return ( ( row * mWidth * 3 + column * 3 ) + channel );
}
int Image::getChannel( const int& row, const int& column, const int& channel ) const {
  if ( indexValid( row, column, channel ) ) {
    return mImg[ index( row, column, channel ) ];
  }
  else {
    return -1;
  }
}
void Image::setHeight( const int& height ) {
  if ( height < 0 ) {
  }
  else {
    mHeight = height;
    mImg.resize( height * mWidth * 3 );
  }
}
void Image::setWidth( const int& width ) {
  if ( width < 0 ) {
  }
  else {
    mWidth = width;
    mImg.resize( mHeight * width * 3 );
  }
}
void Image::setChannel( const int& row, const int& column, const int& channel, const int& value ) {
  if ( indexValid( row, column, channel ) ) {
    mImg[ index( row, column, channel ) ] = value;
  }
}
