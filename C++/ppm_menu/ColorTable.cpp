#include <cstdlib>
#include <vector>
#include "ColorTable.h"

Color::Color() : mRed(0), mGreen(0), mBlue(0) {}
Color::Color( const int& red, const int& green, const int& blue ) : mRed( red ), mGreen( green ), mBlue( blue ) {}
int Color::getRed() const {
  return mRed;
}
int Color::getGreen() const {
  return mGreen;
}
int Color::getBlue() const {
  return mBlue;
}
int Color::getChannel( const int& channel ) const {
  if ( channel == 0 ) {
    return mRed;
  }
  else if ( channel == 1 ) {
    return mGreen;
  }
  else if ( channel == 2 ) {
    return mBlue;
  }
  else {
    return -1;
  }
}
void Color::setRed( const int& value ) {
  if ( value >= 0 ) {
    mRed = value;
  }
}
void Color::setGreen( const int& value ){
  if ( value >= 0 ) {
    mGreen = value;
  }
}
void Color::setBlue( const int& value ) {
  if ( value >= 0 ) {
    mBlue = value;
  }
}
void Color::setChannel( const int& channel, const int& value ) {
  if ( channel == 0 ) {
    setRed( value );
  }
  else if ( channel == 1 ) {
    setGreen( value );
  }
  else if ( channel == 2 ) {
    setBlue( value );
  }
}
void Color::invert( const int& max_color_value ) {
  if ( max_color_value < mRed || max_color_value < mGreen || max_color_value < mBlue ) {}
  else {
    mRed = max_color_value - mRed;
    mGreen = max_color_value - mGreen;
    mBlue = max_color_value - mBlue;
  }
}
bool Color::operator==( const Color& rhs ) const {
  if ( this->getRed() == rhs.getRed() && this->getGreen() == rhs.getGreen() && this->getBlue() == rhs.getBlue() ) {
    return true;
  }
  else {
    return false;
  }
}
int Color::operator-( const Color& rhs ) const {
  int d = std::abs( this->getRed() - rhs.getRed() ) + std::abs( this->getGreen() - rhs.getGreen() ) + std::abs( this->getBlue() - rhs.getBlue() );
  return d;
}

std::ostream& operator<<( std::ostream& os, const Color& color ) {
  os << color.getRed();
  os << ":";
  os << color.getGreen();
  os << ":";
  os << color.getBlue();
  return os;
}

ColorTable::ColorTable( const size_t& num_color ) : mColors(num_color) {}
size_t ColorTable::getNumberOfColors() const {
  return mColors.size();
}
void ColorTable::setNumberOfColors( const size_t& num_color ) {
  mColors.resize(num_color);
}
const Color& ColorTable::operator[]( const int& i ) const {
  unsigned int I = i;
  if ( I >= mColors.size() ) {
    static Color ec( -1, -1, -1 );
    static Color c( -1, -1, -1 );
    c = ec;
    return c;
  }
  return mColors[i];
}
Color& ColorTable::operator[]( const int& i ) {
  unsigned int I;
  unsigned int zero = 0;
  I = i;
  if ( I >= mColors.size() || I < zero ) {
    static Color ec( -1, -1, -1 );
    static Color c( -1, -1, -1 );
    c = ec;
    return c;
  }
  return mColors[i];
}
void ColorTable::setRandomColor( const int& max_color_value, const size_t& position ) {
  size_t zero = 0;
  if ( position >= zero && position < getNumberOfColors() && max_color_value >= 0 ) {
    mColors[position].setRed( std::rand() % (max_color_value + 1));
    mColors[position].setGreen( std::rand() % (max_color_value + 1));
    mColors[position].setBlue( std::rand() % (max_color_value + 1));
  }
}
void ColorTable::insertGradient( const Color& color1, const Color& color2, const size_t& position1, const size_t& position2 ) {
  size_t zero = 0;
  if ( position1 < position2 && position1 >= zero && position2 < getNumberOfColors() ) {
    int dist = (position2 - position1) + 1;
    double red_step = ( (double)color2.getRed() - color1.getRed() ) / ( dist - 1 );
    double green_step = ( (double)color2.getGreen() - color1.getGreen() ) / ( dist - 1 );
    double blue_step = ( (double)color2.getBlue() - color1.getBlue() ) / ( dist - 1 );
    for ( int i = 0; i < dist; i++ ) {
      mColors[position1 + i].setRed( color1.getRed() + i * red_step );
      mColors[position1 + i].setGreen( color1.getGreen() + i * green_step );
      mColors[position1 + i].setBlue( color1.getBlue() + i * blue_step );
    }
  }
}
int ColorTable::getMaxChannelValue() const {
  int greatest = 0;
  for ( unsigned int i = 0; i < getNumberOfColors(); i++ ) {
    if ( mColors[i].getRed() > greatest ) {
      greatest = mColors[i].getRed();
    }
    if ( mColors[i].getGreen() > greatest ) {
      greatest = mColors[i].getGreen();
    }
    if ( mColors[i].getBlue() > greatest ) {
      greatest = mColors[i].getBlue();
    }
  }
  return greatest;
}
void ColorTable::insertInvertedGradient( const Color& color1, const size_t& position1, const size_t& position2 ) {
  Color invertedColor = color1;
  invertedColor.invert(255);
  insertGradient( color1, invertedColor, position1, position2 );
}
void ColorTable::insertRandomGradient( const int& min_dist, const int& max_dist, const int& max_color_value, const size_t& position1, const size_t& position2 ) {
  Color color1 = Color(std::rand() % (max_color_value + 1), std::rand() % (max_color_value + 1), std::rand() % (max_color_value + 1));
  Color color2 = Color(std::rand() % (max_color_value + 1), std::rand() % (max_color_value + 1), std::rand() % (max_color_value + 1));
  while ( color1 - color2 < min_dist || color1 - color2 > max_dist ) {
    color1.setChannel( 0, std::rand() % (max_color_value + 1) );
    color1.setChannel( 1, std::rand() % (max_color_value + 1) );
    color1.setChannel( 2, std::rand() % (max_color_value + 1) );
    color2.setChannel( 0, std::rand() % (max_color_value + 1) );
    color2.setChannel( 1, std::rand() % (max_color_value + 1) );
    color2.setChannel( 2, std::rand() % (max_color_value + 1) );
  }
  insertGradient( color1, color2, position1, position2 );
}
