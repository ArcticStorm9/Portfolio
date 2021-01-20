#ifndef _ACTIONDATA_H_
#define _ACTIONDATA_H_

#include <iostream>
#include "PPM.h"
#include "NumberGrid.h"
#include "JuliaSet.h"
#include "ColorTable.h"

class ActionData {
public:
  ActionData(std::istream& is, std::ostream& os);
  std::istream& getIS();
  std::ostream& getOS();
  PPM& getInputImage1();
  PPM& getInputImage2();
  PPM& getOutputImage();
  bool getDone() const;
  void setDone();
  ~ActionData();
  NumberGrid& getGrid();
  void setGrid(NumberGrid* grid);
  ColorTable& getTable();
protected:
  std::istream& mIS;
  std::ostream& mOS;
  PPM inputImage1;
  PPM inputImage2;
  PPM outputImage;
  bool mIsDone;
  NumberGrid *mGrid;
  ColorTable mTable;
};
#endif // _ACTIONDATA_H_
