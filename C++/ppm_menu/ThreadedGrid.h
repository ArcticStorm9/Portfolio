#ifndef _THREADEDGRID_H_
#define _THREADEDGRID_H_

#include <vector>
#include <thread>
#include "ThreadedVector.h"
#include "NumberGrid.h"

class GridTask {
public:
  GridTask( unsigned int row );
  unsigned int mRow;
};

class ThreadedGrid : public NumberGrid {
public:
  ThreadedGrid();
  ThreadedGrid( const int& height, const int& width );
  virtual ~ThreadedGrid();
  virtual void calculateAllNumbers();
  virtual void worker();
protected:
  ThreadedVector<GridTask> mTasks;
};

#endif // _THREADEDGRID_H_
