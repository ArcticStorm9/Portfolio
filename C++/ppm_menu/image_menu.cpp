//Index = (row*row_size + col*pixel_size + channel), row_size = width*pixel_size, pixel_size = 3
#include "image_menu.h"
#include "Image.h"
#include "PPM.h"
#include "ActionData.h"
#include "MenuData.h"
#include "NumberGrid.h"
#include "JuliaSet.h"
#include "ComplexFractal.h"
#include "ColorTable.h"
#include "MandelbrotSet.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

std::string getString( ActionData& action_data, const std::string& prompt ) {
  std::string word;
  action_data.getOS() << prompt;
  action_data.getIS() >> word;
  return word;
}
int getInteger( ActionData& action_data, const std::string& prompt ) {
  int num;
  action_data.getOS() << prompt;
  action_data.getIS() >> num;
  return num;
}
double getDouble( ActionData& action_data, const std::string& prompt ) {
  double decimal;
  action_data.getOS() << prompt;
  action_data.getIS() >> decimal;
  return decimal;
}
int assignment1( std::istream& is, std::ostream& os ) {
  ActionData action_data(is, os);
  std::string color;
  int number;
  double decimal;

  color = getString(action_data, "What's your favorite color? ");
  number = getInteger(action_data, "What's your favorite integer? ");
  decimal = getDouble(action_data, "What's your favorite number? ");

  for(int i = 1; i <= number; i++) {
    action_data.getOS() << i << " " << color << " " << decimal << std::endl;
  }

  return number;
}
void drawAsciiImage( ActionData& action_data ) {
  int row, col;
  for ( row = 0; row < action_data.getOutputImage().getHeight(); row ++ ) {
    for ( col = 0; col < action_data.getOutputImage().getWidth(); col ++ ) {
      char c;
      double scale = ( action_data.getOutputImage().getChannel( row, col, 0 ) + action_data.getOutputImage().getChannel( row, col, 1 ) + action_data.getOutputImage().getChannel( row, col, 2 ) ) / 765.0;
      if ( scale >= 1.0 ) {
        c = '@';
      }
      else if ( scale >= 0.9 ) {
        c = '#';
      }
      else if ( scale >= 0.8 ) {
        c = '%';
      }
      else if ( scale >= 0.7 ) {
        c = '*';
      }
      else if ( scale >= 0.6 ) {
        c = '|';
      }
      else if ( scale >= 0.5 ) {
        c = '+';
      }
      else if ( scale >= 0.4 ) {
        c = ';';
      }
      else if ( scale >= 0.3 ) {
        c = '~';
      }
      else if ( scale >= 0.2 ) {
        c = '-';
      }
      else if ( scale >= 0.1 ) {
        c = '.';
      }
      else {
        c = ' ';
      }
      action_data.getOS() << c;
    }
    action_data.getOS() << std::endl;
  }
}
int assignment2( std::istream& is, std::ostream& os ) {
  ActionData action_data(is, os);
  int height = getInteger( action_data, "Image height? " );
  int width = getInteger( action_data, "Image width? " );
  action_data.getOutputImage().setMaxColorValue(255);
  action_data.getOutputImage().setHeight(height);
  action_data.getOutputImage().setWidth(width);
  int row, col;
  for ( row = 0; row < action_data.getOutputImage().getHeight(); row ++ ) {
    for ( col = 0; col < action_data.getOutputImage().getWidth(); col ++ ) {
      if ( row < action_data.getOutputImage().getHeight() / 2 ) {
        action_data.getOutputImage().setChannel( row, col, 0, 0 );
      }
      else {
        action_data.getOutputImage().setChannel( row, col, 0, 255 );
      }
      if ( col < action_data.getOutputImage().getWidth() / 2 ) {
        action_data.getOutputImage().setChannel( row, col, 1, 0 );
      }
      else {
        action_data.getOutputImage().setChannel( row, col, 1, 255 );
      }
      action_data.getOutputImage().setChannel( row, col, 2, ( 2*row + 2*col ) % 256);
    }
  }
  drawAsciiImage(action_data);
  return 0;
}
void writeUserImage( ActionData& action_data ) {
  std::string file = getString( action_data, "Output filename? " );
  std::ofstream fout( file, std::ios::binary );
  action_data.getOutputImage().writeStream(fout);
  fout.close();
}
int assignment3( std::istream& is, std::ostream& os ) {
  ActionData action_data(is, os);
  int height = getInteger( action_data, "Image height? " );
  int width = getInteger( action_data, "Image width? " );
  action_data.getOutputImage().setHeight( height );
  action_data.getOutputImage().setWidth( width );
  int max = (action_data.getOutputImage().getHeight() + action_data.getOutputImage().getWidth()) / 3;
  if ( max > 255 ) {
    action_data.getOutputImage().setMaxColorValue( 255 );
  }
  else {
    action_data.getOutputImage().setMaxColorValue( max );
  }
  for ( int i = 0; i < action_data.getOutputImage().getHeight(); i++ ) {
    for ( int j = 0; j < action_data.getOutputImage().getWidth(); j++ ) {
      int red;
      if ( i < action_data.getOutputImage().getHeight() / 2 ) {
        red = 0;
      }
      else if ( i >= action_data.getOutputImage().getHeight() / 2 ) {
        if ( i % 3 == 0 ) {
          red = 0;
        }
        else {
          red = action_data.getOutputImage().getMaxColorValue();
        }
      }
      int green = ( i + action_data.getOutputImage().getWidth() - j - 1 ) % ( action_data.getOutputImage().getMaxColorValue() + 1 );
      int blue;
      if ( j < i ) {
        blue = 0;
      }
      else {
        blue = action_data.getOutputImage().getMaxColorValue();
      }
      action_data.getOutputImage().setPixel( i, j, red, green, blue );
    }
  }
  writeUserImage( action_data );
  return 0;
}
float getFloat( ActionData& action_data, const std::string& prompt ) {
  float deci;
  action_data.getOS() << prompt;
  action_data.getIS() >> deci;
  return deci;
}
int four_square_ascii(std::istream& is, std::ostream& os) {
  ActionData action_data(is, os);
  int size = getInteger( action_data, "Image size? " );
  action_data.getOutputImage().setHeight(size);
  action_data.getOutputImage().setWidth(size);
  int row, col;
  for ( row = 0; row < action_data.getOutputImage().getHeight(); row ++ ) {
    for ( col = 0; col < action_data.getOutputImage().getWidth(); col ++ ) {
      if ( row < action_data.getOutputImage().getHeight() / 2 ) {
        action_data.getOutputImage().setChannel( row, col, 0, 127 );
      }
      else {
        action_data.getOutputImage().setChannel( row, col, 0, 255 );
      }
      if ( col < action_data.getOutputImage().getWidth() / 2 ) {
        action_data.getOutputImage().setChannel( row, col, 1, 0 );
      }
      else {
        action_data.getOutputImage().setChannel( row, col, 1, 255 );
      }
      action_data.getOutputImage().setChannel( row, col, 2, 255);
    }
  }
  drawAsciiImage(action_data);
  return 0;
}
std::string getChoice( ActionData& action_data ) {
  std::string choice = getString( action_data, "Choice? " );
  return choice;
}
void copyImage( ActionData& action_data ) {
  action_data.getOutputImage() = action_data.getInputImage1();
}
void readUserImage1( ActionData& action_data ) {
  std::string file = getString( action_data, "Input filename? " );
  std::ifstream fin( file, std::ios::binary );
  action_data.getInputImage1().readStream( fin );
  fin.close();
}
void commentLine( ActionData& action_data ) {
  char c;
  action_data.getIS().read((char* )&c, sizeof(c));
  if ( action_data.getIS().good() && c != 10 ) {
    commentLine( action_data );
  }
}
void setSize( ActionData& action_data ) {
  int height = getInteger( action_data, "Height? " );
  int width = getInteger( action_data, "Width? ");
  action_data.getInputImage1().setHeight(height);
  action_data.getInputImage1().setWidth(width);
}
void setMaxColorValue( ActionData& action_data ) {
  int max = getInteger( action_data, "Max color value? " );
  action_data.getInputImage1().setMaxColorValue( max );
}
void setChannel( ActionData& action_data ) {
  int row = getInteger( action_data, "Row? " );
  int col = getInteger( action_data, "Column? " );
  int channel = getInteger( action_data, "Channel? " );
  int value = getInteger( action_data, "Value? " );
  action_data.getInputImage1().setChannel( row, col, channel, value );
}
void setPixel( ActionData& action_data ) {
  int row = getInteger( action_data, "Row? " );
  int column = getInteger( action_data, "Column? " );
  int red = getInteger( action_data, "Red? " );
  int green = getInteger( action_data, "Green? " );
  int blue = getInteger( action_data, "Blue? " );
  action_data.getInputImage1().setPixel( row, column, red, green, blue );
}
void clearAll( ActionData& action_data ) {
  for ( int row = 0; row < action_data.getInputImage1().getHeight(); row++ ) {
    for ( int col = 0; col < action_data.getInputImage1().getWidth(); col++ ) {
      action_data.getInputImage1().setPixel( row, col, 0, 0, 0 );
    }
  }
}
void quit( ActionData& action_data ) {
  action_data.setDone();
}
void showMenu( MenuData& menu_data, ActionData& action_data ) {
  std::string name = "";
  for ( int i = 0; i < static_cast<int>(menu_data.getNames().size()); i++ ) {
    name = menu_data.getNames()[i];
    action_data.getOS() << name << ") " << menu_data.getDescription(name) << std::endl;
  }
}
void takeAction(const std::string& choice, MenuData& menu_data, ActionData& action_data) {
  if ( choice == "menu" ){
    showMenu( menu_data, action_data );
  }
  else if( menu_data.getFunction( choice ) == 0 ){
    action_data.getOS() << "Unknown action '" << choice << "'." << std::endl;
  }
  else {
    menu_data.getFunction( choice )( action_data );
  }
}
void configureMenu( MenuData& menu_data ) {
  menu_data.addAction( "draw-ascii", drawAsciiImage, "Write output image to terminal as ASCII art." );
  menu_data.addAction( "write", writeUserImage, "Write output image to file." );
  menu_data.addAction( "copy", copyImage, "Copy input image 1 to output image." );
  menu_data.addAction( "read1", readUserImage1, "Read file into input image 1." );
  menu_data.addAction( "#", commentLine, "Comment to end of line." );
  menu_data.addAction( "size", setSize, "Set the size of input image 1." );
  menu_data.addAction( "max-color-value", setMaxColorValue, "Set the max color value of input image 1." );
  menu_data.addAction( "channel", setChannel, "Set a channel value in input image 1." );
  menu_data.addAction( "pixel", setPixel, "Set a pixel's 3 values in input image 1." );
  menu_data.addAction( "clear", clearAll, "Set all pixels to 0,0,0 in input image 1." );
  menu_data.addAction( "quit", quit, "Quit." );
  menu_data.addAction( "read2", readUserImage2, "Read file into input image 2." );
  menu_data.addAction( "+", plus, "Set output image from sum of input image 1 and input image 2.");
  menu_data.addAction( "+=", plusEquals, "Set input image 1 by adding in input image 2.");
  menu_data.addAction( "-", minus, "Set output image from difference of input image 1 and input image 2." );
  menu_data.addAction( "-=", minusEquals, "Set input image 1 by subtracting input image 2." );
  menu_data.addAction( "*", times, "Set output image from input image 1 multiplied by a number." );
  menu_data.addAction( "*=", timesEquals, "Set input image 1 by multiplying by a number." );
  menu_data.addAction( "/", divide, "Set output image from input image 1 divided by a number." );
  menu_data.addAction( "/=", divideEquals, "Set input image 1 by dividing by a number." );
  menu_data.addAction( "red-gray", grayFromRed, "Set output image from input image 1's grayscale from red." );
  menu_data.addAction( "green-gray", grayFromGreen, "Set output image from input image 1's grayscale from green." );
  menu_data.addAction( "blue-gray", grayFromBlue, "Set output image from input image 1's grayscale from blue." );
  menu_data.addAction( "linear-gray", grayFromLinearColorimetric, "Set output image from input image 1's grayscale from linear colorimetric." );
  menu_data.addAction( "circle", drawCircle, "Draw a circle shape in input image 1." );
  menu_data.addAction( "box", drawBox, "Draw a box shape in input image 1." );
  menu_data.addAction( "copy12", copyImage1ToImage2, "Copy input image 1 to input image 2." );
  menu_data.addAction( "*=-ppm", timesEqualsPPM, "Set input image 1 by multiplying by input image 2." );
  menu_data.addAction( "square", drawSquare, "Draw a square shape in input image 1." );
  menu_data.addAction( "grid", configureGrid, "Configure the grid." );
  menu_data.addAction( "grid-set", setGrid, "Set a single value in the grid." );
  menu_data.addAction( "grid-apply", applyGrid, "Use the grid values to set colors in the output image." );
  menu_data.addAction( "fractal-plane-size", setFractalPlaneSize, "Set the dimensions of the grid in the complex plane." );
  menu_data.addAction( "fractal-calculate", calculateFractal, "Calculate the escape values for the fractal, multi-thread." );
  menu_data.addAction( "julia-parameters", setJuliaParameters, "Set the parameters of the Julia Set function." );
  menu_data.addAction( "fractal-calculate-single-thread", calculateFractalSingleThread, "Calculate the escape values for the fractal, single-thread." );
  menu_data.addAction( "grid-apply-color-table", applyGridColorTable, "Use the grid values to set colors in the output image using the color table." );
  menu_data.addAction( "set-color-table-size", setColorTableSize, "Change the number of slots in the color table." );
  menu_data.addAction( "set-color", setColor, "Set the RGB values for one slot in the color table." );
  menu_data.addAction( "set-random-color", setRandomColor, "Randomly set the RGB values for one slot in the color table." );
  menu_data.addAction( "set-color-gradient", setColorGradient, "Smoothly set the RGB values for a range of slots in the color table." );
  menu_data.addAction( "julia-four", setJuliaFourFractal, "Choose to make a Julia set with the fourth power function." );
  menu_data.addAction( "escape-radius", setEscapeRadius, "Set the fractal escape radius." );
  menu_data.addAction( "julia", setJuliaFractal, "Choose to make a Julia set." );
  menu_data.addAction( "mandelbrot", setMandelbrotFractal, "Choose to make a Mandelbrot set." );
  menu_data.addAction( "mandelbar", setMandelbarFractal, "Choose to make a Mandelbar set." );
  menu_data.addAction( "set-random-color-gradient", setRandomColorGradient, "Smoothly set the values for a range of slots in the color table, using random colors." );
  //menu_data.addAction( "anti-alias", antiAliasFilter, "Set output image from Anti-alias filter on input image 1." );
  menu_data.addAction( "burning-ship", setBurningShipFractal, "Choose to make a Mandelbrot set with the burning ship function." );
}
int imageMenu(std::istream& is, std::ostream& os) {
  ActionData action_data( is, os );
  action_data.setGrid( new JuliaSet );
  MenuData menu_data;
  configureMenu( menu_data );
  while ( action_data.getDone() == false && action_data.getIS().good() == true ) {
    std::string choice = getChoice( action_data );
    takeAction( choice, menu_data, action_data );
  }
  return 0;
}
void readUserImage2( ActionData& action_data ) {
  std::string file = getString( action_data, "Input filename? " );
  std::ifstream fin( file, std::ios::binary );
  action_data.getInputImage2().readStream( fin );
  fin.close();
}
void plusEquals( ActionData& action_data ) {
  action_data.getInputImage1() += action_data.getInputImage2();
}
void minusEquals( ActionData& action_data ) {
  action_data.getInputImage1() -= action_data.getInputImage2();
}
void timesEquals( ActionData& action_data ) {
  double value;
  value = getDouble( action_data, "Factor? " );
  action_data.getInputImage1() *= value;
}
void divideEquals( ActionData& action_data ) {
  double value;
  value = getDouble( action_data, "Factor? " );
  action_data.getInputImage1() /= value;
}
void plus( ActionData& action_data ) {
  action_data.getOutputImage() = action_data.getInputImage1() + action_data.getInputImage2();
}
void minus( ActionData& action_data ) {
  action_data.getOutputImage() = action_data.getInputImage1() - action_data.getInputImage2();
}
void times( ActionData& action_data ) {
  double value;
  value = getDouble( action_data, "Factor? " );
  action_data.getOutputImage() = action_data.getInputImage1() * value;
}
void divide( ActionData& action_data ) {
  double value;
  value = getDouble( action_data, "Factor? " );
  action_data.getOutputImage() = action_data.getInputImage1() / value;
}
void grayFromRed(ActionData& action_data) {
  action_data.getInputImage1().grayFromRed( action_data.getOutputImage() );
}
void grayFromGreen(ActionData& action_data) {
  action_data.getInputImage1().grayFromGreen( action_data.getOutputImage() );
}
void grayFromBlue(ActionData& action_data) {
  action_data.getInputImage1().grayFromBlue( action_data.getOutputImage() );
}
void grayFromLinearColorimetric(ActionData& action_data) {
  action_data.getInputImage1().grayFromLinearColorimetric( action_data.getOutputImage() );
}
void drawCircle(ActionData& action_data) {
  double d;
  int row = getInteger( action_data, "Center Row? " );
  int col = getInteger( action_data, "Center Column? " );
  int radius = getInteger( action_data, "Radius? " );
  int red = getInteger( action_data, "Red? " );
  int green = getInteger( action_data, "Green? " );
  int blue = getInteger( action_data, "Blue? " );
  for( int y = 0; y < action_data.getInputImage1().getHeight( ); y++ ) {
    for( int x = 0; x < action_data.getInputImage1().getWidth( ); x++ ) {
      d = std::sqrt( ( y - row )*( y - row ) + ( x - col )*( x - col ) );
      if( d <= radius ) {
        action_data.getInputImage1().setPixel( y, x, red, green, blue );
      }
    }
  }
}
void drawBox(ActionData& action_data) {
  int top_row = getInteger( action_data, "Top Row? " );
  int left_col = getInteger( action_data, "Left Column? " );
  int bot_row = getInteger( action_data, "Bottom Row? " );
  int right_col = getInteger( action_data, "Right Column? " );
  int red = getInteger( action_data, "Red? " );
  int green = getInteger( action_data, "Green? " );
  int blue = getInteger( action_data, "Blue? " );
  for ( int i = top_row; i <= bot_row; i++ ) {
    for (int j = left_col; j <= right_col; j++ ) {
      action_data.getInputImage1().setPixel( i, j, red, green, blue );
    }
  }
}
void copyImage1ToImage2(ActionData& action_data) {
  action_data.getInputImage2() = action_data.getInputImage1();
}
void timesEqualsPPM(ActionData& action_data) {
  action_data.getInputImage1() *= action_data.getInputImage2();
}
void drawSquare(ActionData& action_data) {
  int row = getInteger( action_data, "Row? " );
  int col = getInteger( action_data, "Column? " );
  int size = getInteger( action_data, "Size? " );
  int red = getInteger( action_data, "Red? " );
  int green = getInteger( action_data, "Green? " );
  int blue = getInteger( action_data, "Blue? " );
  for ( int i = row - ( size / 2 ); i <= row + ( size / 2 ); i++ ) {
    for ( int j = col - ( size / 2 ); j <= col + ( size / 2 ); j++ ) {
      action_data.getInputImage1().setPixel( i, j, red, green, blue );
    }
  }
}
void configureGrid(ActionData& action_data) {
  int gridHeight = getInteger( action_data, "Grid Height? " );
  int gridWidth = getInteger( action_data, "Grid Width? " );
  int gridMaxValue = getInteger( action_data, "Grid Max Value? " );
  action_data.getGrid().setGridSize( gridHeight, gridWidth );
  action_data.getGrid().setMaxNumber( gridMaxValue );
}
void setGrid(ActionData& action_data) {
  int gridRow = getInteger( action_data, "Grid Row? " );
  int gridCol = getInteger( action_data, "Grid Column? " );
  int gridValue = getInteger( action_data, "Grid Value? " );
  action_data.getGrid().setNumber( gridRow, gridCol, gridValue );
}
void applyGrid(ActionData& action_data) {
  action_data.getGrid().setPPM( action_data.getOutputImage() );
}
void setFractalPlaneSize(ActionData& action_data) {
  double min_x = getDouble( action_data, "Min X? " );
  double max_x = getDouble( action_data, "Max X? " );
  double min_y = getDouble( action_data, "Min Y? " );
  double max_y = getDouble( action_data, "Max Y? " );
  ComplexFractal *ptr = dynamic_cast< ComplexFractal* >(&action_data.getGrid());
  if(ptr != 0) {
    ptr->setPlaneSize( min_x, max_x, min_y, max_y );
  }
  else {
    action_data.getOS() << "Not a JuliaSet object. Can’t set plane size." << std::endl;
  }
}
void calculateFractal(ActionData& action_data) {
  action_data.getGrid().calculateAllNumbers();
}
void setJuliaParameters(ActionData& action_data) {
  double a = getDouble( action_data, "Parameter a? " );
  double b = getDouble( action_data, "Parameter b? " );
  JuliaSet *ptr = dynamic_cast< JuliaSet* >(&action_data.getGrid());
  if(ptr != 0) {
    ptr->setParameters( a, b );
  }
  else {
    action_data.getOS() << "Not a JuliaSet object. Can't set parameters." << std::endl;
  }
}
void calculateFractalSingleThread(ActionData& action_data) {
  action_data.getGrid().NumberGrid::calculateAllNumbers();
}
void applyGridColorTable(ActionData& action_data) {
  action_data.getGrid().setPPM(action_data.getOutputImage(), action_data.getTable());
}
void setColorTableSize(ActionData& action_data) {
  int size = getInteger( action_data, "Size? " );
  action_data.getTable().setNumberOfColors(size);
}
void setColor(ActionData& action_data) {
  int pos = getInteger( action_data, "Position? " );
  int red = getInteger( action_data, "Red? " );
  int green = getInteger( action_data, "Green? " );
  int blue = getInteger( action_data, "Blue? " );
  action_data.getTable()[pos].setRed( red );
  action_data.getTable()[pos].setGreen( green );
  action_data.getTable()[pos].setBlue( blue );
}
void setRandomColor(ActionData& action_data) {
  int pos = getInteger( action_data, "Position? " );
  action_data.getTable().setRandomColor(255, pos);
}
void setColorGradient(ActionData& action_data) {
  int pos1 = getInteger( action_data, "First position? " );
  int red1 = getInteger( action_data, "First red? " );
  int green1 = getInteger( action_data, "First green? " );
  int blue1 = getInteger( action_data, "First blue? " );
  int pos2 = getInteger( action_data, "Second position? " );
  int red2 = getInteger( action_data, "Second red? " );
  int green2 = getInteger( action_data, "Second green? " );
  int blue2 = getInteger( action_data, "Second blue? " );
  Color color1(red1, green1, blue1);
  Color color2(red2, green2, blue2);
  action_data.getTable().insertGradient( color1, color2, pos1, pos2 );
}
void setJuliaFourFractal(ActionData& action_data) {
  JuliaSetFour *ptr = dynamic_cast< JuliaSetFour* >(&action_data.getGrid());
  if(ptr != 0) {
    action_data.setGrid( new JuliaSetFour );
  }
  else {
    action_data.getOS() << "Not a JuliaSetFour object. Can't set grid." << std::endl;
  }
}
void setEscapeRadius( ActionData& action_data ) {
  double radius = getDouble( action_data, "Escape Radius? " );
  ComplexFractal *ptr = dynamic_cast< ComplexFractal* >(&action_data.getGrid());
  if(ptr != 0) {
    ptr->setEscapeRadius( radius );
  }
  else {
    action_data.getOS() << "Not a ComplexFractal object. Can't set radius." << std::endl;
  }
}
void setJuliaFractal( ActionData& action_data ) {
  action_data.setGrid( new JuliaSet );
}
void setMandelbrotFractal( ActionData& action_data ) {
  action_data.setGrid( new MandelbrotSet );
}
void setMandelbarFractal( ActionData& action_data ) {
  action_data.setGrid( new MandelbarSet );
}
void setRandomColorGradient( ActionData& action_data ) {
  size_t first_pos = getInteger( action_data, "First position? " );
  size_t second_pos = getInteger( action_data, "Second position? " );
  int min_diff = getInteger( action_data, "Minimum difference? " );
  int max_diff = getInteger( action_data, "Maximum difference? " );
  action_data.getTable().insertRandomGradient( min_diff, max_diff, 255, first_pos, second_pos );
}
void antiAliasFilter( ActionData& action_data ) {
  int reduction_count = getInteger( action_data, "Reduction count? " );
  action_data.getInputImage1().antiAlias( reduction_count, action_data.getOutputImage() );
}
void setBurningShipFractal( ActionData& action_data ) {
  action_data.setGrid( new BurningShip );
}
