#include <iostream>
#include "ActionData.h"

ActionData::ActionData( std::istream& is, std::ostream& os ) : mIS(is), mOS(os), mIsDone(false), mGrid(0), mTable(16) {
  Color color1(0, 255, 0);
  Color color2( 255, 0, 255 );
  mTable.insertGradient( color1, color2, 0, 15 );
}
std::istream& ActionData::getIS() {
  return mIS;
}
std::ostream& ActionData::getOS() {
  return mOS;
}
PPM& ActionData::getInputImage1() {
  return inputImage1;
}
PPM& ActionData::getInputImage2() {
  return inputImage2;
}
PPM& ActionData::getOutputImage() {
  return outputImage;
}
bool ActionData::getDone() const {
  return mIsDone;
}
void ActionData::setDone() {
  mIsDone = true;
}
ActionData::~ActionData() {
  if ( mGrid != 0 ) {
    delete mGrid;
  }
}
NumberGrid& ActionData::getGrid() {
  return *mGrid;
}
void ActionData::setGrid( NumberGrid* grid ) {
  if ( mGrid != 0 ) {
    delete mGrid;
    mGrid = grid;
  }
  else {
    mGrid = grid;
  }
}
ColorTable& ActionData::getTable() {
  return mTable;
}
