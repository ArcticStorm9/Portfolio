#include <thread>
#include <exception>
#include "ThreadedGrid.h"

GridTask::GridTask( unsigned int row ) : mRow(row) {}

ThreadedGrid::ThreadedGrid() : NumberGrid() {}
ThreadedGrid::ThreadedGrid( const int& height, const int& width ) : NumberGrid( height, width ) {}
ThreadedGrid::~ThreadedGrid() {}
void ThreadedGrid::calculateAllNumbers() {
  int i;
  int MaxThreads = 4;

  std::vector<std::thread> threads;
  for ( i = 0; i < getHeight(); i++ ){
    mTasks.push_back(GridTask(i));
  }

  for(i = 0; i < MaxThreads; i++) {
    try {
      threads.push_back( std::thread(&ThreadedGrid::worker, this) );  // this->primeWork()
    } catch (std::exception &e) {
      std::cerr << "Unable to create thread number " << i << "." << std::endl;
    }
  }

  for(i = 0; i < MaxThreads; i++) {
    threads[i].join();
  }
}
void ThreadedGrid::worker() {
  std::vector<GridTask> task;

  while ( !mTasks.empty() ) {
    task.clear();
    mTasks.pop_back(task, 1);

    for ( unsigned int i = 0; i < task.size(); i++ ) {
      for ( int col = 0; col < getWidth(); col++ ) {
        int num = calculateNumber( task[i].mRow, col );
        setNumber( task[i].mRow, col, num );
      }
    }
  }
}
