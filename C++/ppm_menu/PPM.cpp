#include <iostream>
#include <vector>
#include <string>
#include "PPM.h"

PPM::PPM() : Image::Image(), mMaxColorValue(1) {
}
PPM::PPM( const int& height, const int& width )
: Image::Image( height, width ), mMaxColorValue( 1 ) {
}
int PPM::getMaxColorValue() const {
  return mMaxColorValue;
}
bool PPM::valueValid( const int& value ) const {
  if ( value >= 0 && value <= mMaxColorValue ) {
    return true;
  }
  else {
    return false;
  }
}
void PPM::setMaxColorValue( const int& max_color_value ) {
  if ( max_color_value <= 255 && max_color_value >= 1 ) {
    mMaxColorValue = max_color_value;
  }
}
void PPM::setChannel( const int& row, const int& column, const int& channel, const int& value ) {
  if ( valueValid( value ) ) {
    Image::setChannel( row, column, channel, value );
  }
}
void PPM::setPixel( const int& row, const int& column, const int& red, const int& green, const int& blue ) {
  setChannel( row, column, 0, red );
  setChannel( row, column, 1, green );
  setChannel( row, column, 2, blue );
}
void PPM::writeStream( std::ostream& os ) const {
  os << "P6" << " " << Image::getWidth() << " " << Image::getHeight() << " " << getMaxColorValue() << "\n";
  for ( int i = 0; i < Image::getHeight(); i++ ) {
    for ( int j = 0; j < Image::getWidth(); j++ ) {
      for ( int k = 0; k < 3; k++ ) {
        unsigned char c = Image::getChannel( i, j, k );
        os.write((char *) &c, sizeof(c));
      }
    }
  }
}
void PPM::magenta(const int& row, const int& column) {
  setPixel( row, column, getMaxColorValue(), 0, getMaxColorValue() );
}
void PPM::readStream(std::istream& is) {
  std::string magic;
  int width, height, max;
  is >> magic >> width >> height >> max;
  Image::setWidth(width);
  Image::setHeight(height);
  PPM::setMaxColorValue(max);
  unsigned char v;
  is.read((char*) &v, sizeof(v));
  for ( int i = 0; i < Image::getHeight(); i++ ) {
    for ( int j = 0; j < Image::getWidth(); j++ ) {
      for ( int k = 0; k < 3; k++ ) {
        is.read((char*) &v, sizeof(v));
        Image::setChannel(i, j, k, v);
      }
    }
  }
}
bool PPM::operator==( const PPM& rhs ) const {
  if ( ( this->getHeight() * this->getWidth() * 3 ) == ( rhs.getHeight() * rhs.getWidth() * 3 ) ) {
    return true;
  }
  else {
    return false;
  }
}
bool PPM::operator!=( const PPM& rhs ) const {
  if ( ( this->getHeight() * this->getWidth() * 3 ) != ( rhs.getHeight() * rhs.getWidth() * 3 ) ) {
    return true;
  }
  else {
    return false;
  }
}
bool PPM::operator<( const PPM& rhs ) const {
  if ( ( this->getHeight() * this->getWidth() * 3 ) < ( rhs.getHeight() * rhs.getWidth() * 3 ) ) {
    return true;
  }
  else {
    return false;
  }
}
bool PPM::operator<=( const PPM& rhs ) const {
  if ( ( this->getHeight() * this->getWidth() * 3 ) <= ( rhs.getHeight() * rhs.getWidth() * 3 ) ) {
    return true;
  }
  else {
    return false;
  }
}
bool PPM::operator>( const PPM& rhs ) const {
  if ( ( this->getHeight() * this->getWidth() * 3 ) > ( rhs.getHeight() * rhs.getWidth() * 3 ) ) {
    return true;
  }
  else {
    return false;
  }
}
bool PPM::operator>=( const PPM& rhs ) const {
  if ( ( this->getHeight() * this->getWidth() * 3 ) >= ( rhs.getHeight() * rhs.getWidth() * 3 ) ) {
    return true;
  }
  else {
    return false;
  }
}
PPM& PPM::operator+=( const PPM& rhs ) {
  int newVal;
  for ( int row = 0; row < this->getHeight(); row++ ) {
    for ( int col = 0; col < this->getWidth(); col++ ) {
      for ( int channel = 0; channel < 3; channel++ ) {
        newVal = this->getChannel( row, col, channel ) + rhs.getChannel( row, col, channel );
        if ( newVal > this->getMaxColorValue() ) {
          newVal = this->getMaxColorValue();
        }
        this->setChannel(row, col, channel, newVal);
      }
    }
  }
  return *this;
}
PPM& PPM::operator-=( const PPM& rhs ) {
  int newVal;
  for ( int row = 0; row < this->getHeight(); row++ ) {
    for ( int col = 0; col < this->getWidth(); col++ ) {
      for ( int channel = 0; channel < 3; channel++ ) {
        newVal = this->getChannel( row, col, channel ) - rhs.getChannel( row, col, channel );
        if ( newVal < 0 ) {
          newVal = 0;
        }
        this->setChannel(row, col, channel, newVal);
      }
    }
  }
  return *this;
}
PPM& PPM::operator*=( const double& rhs ) {
  int newVal;
  for ( int row = 0; row < this->getHeight(); row++ ) {
    for ( int col = 0; col < this->getWidth(); col++ ) {
      for ( int channel = 0; channel < 3; channel++ ) {
        newVal = this->getChannel( row, col, channel ) * rhs;
        if ( newVal > this->getMaxColorValue() ) {
          newVal = this->getMaxColorValue();
        }
        else if ( newVal < 0 ) {
          newVal = 0;
        }
        this->setChannel(row, col, channel, newVal);
      }
    }
  }
  return *this;
}
PPM& PPM::operator/=( const double& rhs ) {
  int newVal;
  for ( int row = 0; row < this->getHeight(); row++ ) {
    for ( int col = 0; col < this->getWidth(); col++ ) {
      for ( int channel = 0; channel < 3; channel++ ) {
        newVal = this->getChannel( row, col, channel ) / rhs;
        if ( newVal > this->getMaxColorValue() ) {
          newVal = this->getMaxColorValue();
        }
        else if ( newVal < 0 ){
          newVal = 0;
        }
        this->setChannel(row, col, channel, newVal);
      }
    }
  }
  return *this;
}
PPM PPM::operator+( const PPM& rhs ) const {
  PPM newPPM( this->getHeight(), this->getWidth() );
  newPPM.setMaxColorValue( this->getMaxColorValue() );
  int newVal;
  for ( int row = 0; row < newPPM.getHeight(); row++ ) {
    for ( int col = 0; col < newPPM.getWidth(); col++ ) {
      for ( int channel = 0; channel < 3; channel++ ) {
        newVal = this->getChannel( row, col, channel ) + rhs.getChannel( row, col, channel );
        if ( newVal > this->getMaxColorValue() ) {
          newVal = this->getMaxColorValue();
        }
        newPPM.setChannel(row, col, channel, newVal);
      }
    }
  }
  return newPPM;
}
PPM PPM::operator-( const PPM& rhs ) const {
  PPM newPPM( this->getHeight(), this->getWidth() );
  newPPM.setMaxColorValue( this->getMaxColorValue() );
  int newVal;
  for ( int row = 0; row < newPPM.getHeight(); row++ ) {
    for ( int col = 0; col < newPPM.getWidth(); col++ ) {
      for ( int channel = 0; channel < 3; channel++ ) {
        newVal = this->getChannel( row, col, channel ) - rhs.getChannel( row, col, channel );
        if ( newVal < 0 ) {
          newVal = 0;
        }
        newPPM.setChannel(row, col, channel, newVal);
      }
    }
  }
  return newPPM;
}
PPM PPM::operator*( const double& rhs ) const {
  PPM newPPM( this->getHeight(), this->getWidth() );
  newPPM.setMaxColorValue( this->getMaxColorValue() );
  int newVal;
  for ( int row = 0; row < newPPM.getHeight(); row++ ) {
    for ( int col = 0; col < newPPM.getWidth(); col++ ) {
      for ( int channel = 0; channel < 3; channel++ ) {
        newVal = this->getChannel( row, col, channel ) * rhs;
        if ( newVal > this->getMaxColorValue() ) {
          newVal = this->getMaxColorValue();
        }
        else if ( newVal < 0 ) {
          newVal = 0;
        }
        newPPM.setChannel(row, col, channel, newVal);
      }
    }
  }
  return newPPM;
}
PPM PPM::operator/( const double& rhs ) const {
  PPM newPPM( this->getHeight(), this->getWidth() );
  newPPM.setMaxColorValue( this->getMaxColorValue() );
  int newVal;
  for ( int row = 0; row < newPPM.getHeight(); row++ ) {
    for ( int col = 0; col < newPPM.getWidth(); col++ ) {
      for ( int channel = 0; channel < 3; channel++ ) {
        newVal = this->getChannel( row, col, channel ) / rhs;
        if ( newVal > this->getMaxColorValue() ) {
          newVal = this->getMaxColorValue();
        }
        else if ( newVal < 0 ) {
          newVal = 0;
        }
        newPPM.setChannel(row, col, channel, newVal);
      }
    }
  }
  return newPPM;
}
void PPM::grayFromChannel( PPM& dst, const int& src_channel ) const {
  int channelValue = 0;
  dst.setHeight( this->getHeight() );
  dst.setWidth( this->getWidth() );
  dst.setMaxColorValue( this->getMaxColorValue() );
  for ( int row = 0; row < this->getHeight(); row++ ) {
    for ( int col = 0; col < this->getWidth(); col++ ) {
      channelValue = this->getChannel( row, col, src_channel );
      for ( int channel = 0; channel < 3; channel++ ) {
        dst.setPixel( row, col, channelValue, channelValue, channelValue );
      }
    }
  }
}
void PPM::grayFromRed( PPM& dst ) const {
  grayFromChannel( dst, 0 );
}
void PPM::grayFromGreen( PPM& dst ) const {
  grayFromChannel( dst, 1 );
}
void PPM::grayFromBlue( PPM& dst ) const {
  grayFromChannel( dst, 2 );
}
double PPM::linearColorimetricPixelValue( const int& row, const int& column ) const {
  int red = this->getChannel( row, column, 0 );
  int green = this->getChannel( row, column, 1 );
  int blue = this->getChannel( row, column, 2 );
  return 0.2126 * red + 0.7152 * green + 0.0722 * blue;
}
void PPM::grayFromLinearColorimetric( PPM& dst ) const {
  dst.setHeight( this->getHeight() );
  dst.setWidth( this->getWidth() );
  dst.setMaxColorValue( this->getMaxColorValue() );
  double v;
  for( int row = 0; row < mHeight; row++ ) {
    for( int column = 0; column < mWidth; column++ ) {
      v = linearColorimetricPixelValue( row, column );
      for( int channel = 0; channel < 3; channel++ ) {
        dst.setChannel( row, column, channel, v );
      }
    }
  }
}
PPM& PPM::operator*=( const PPM& rhs ) {
  int newVal;
  for ( int row = 0; row < this->getHeight(); row++ ) {
    for ( int col = 0; col < this->getWidth(); col++ ) {
      for ( int channel = 0; channel < 3; channel++ ) {
        newVal = ( this->getChannel( row, col, channel ) * rhs.getChannel( row, col, channel ) ) / rhs.getMaxColorValue();
        if ( newVal > this->getMaxColorValue() ) {
          newVal = this->getMaxColorValue();
        }
        else if ( newVal < 0 ) {
          newVal = 0;
        }
        this->setChannel(row, col, channel, newVal);
      }
    }
  }
  return *this;
}
void PPM::antiAlias(const int& n, PPM& dst) const {
  if (this->getWidth() > 0 || this->getHeight() > 0) {
    dst.setWidth( this->getWidth() / n );
    dst.setHeight( this->getHeight() / n );
    dst.setMaxColorValue( this->getMaxColorValue() );
    int totalred = 0;
    int totalgreen = 0;
    int totalblue = 0;
    for ( int row = 0; row < this->getHeight(); row+=n ) {
      for ( int col = 0; col < this->getWidth(); col+=n ) {
        for ( int i = 0; i < n; i++ ) {
          for ( int j = 0; i < n; j++ ) {
            totalred += getChannel(row + i, col + j, 0);
            totalgreen += getChannel(row + i, col + j, 0);
            totalblue += getChannel(row + i, col + j, 0);
          }
        }
        totalred /= (n*n);
        totalgreen /= (n*n);
        totalblue /= (n*n);
        dst.setPixel( row/n, col/n, totalred, totalgreen, totalblue );
        totalred = 0;
        totalgreen = 0;
        totalblue = 0;
      }
    }
  }
}
