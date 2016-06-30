#include "Grid.hpp"

namespace Step {

  // fonction qui fonctionne mais on n'utilise pas la classe grille en parametre
  __global__ void cudaStep(int * gridIn, int * gridOut, int dimRow, int dimColumn) {
    int threadId =  blockIdx.x * blockDim.x + threadIdx.x;

    if (threadId < dimRow * dimColumn) {
      int i = threadId / dimColumn;
      int j = threadId % dimColumn;

      int top=0, bottom=0, left=0, right=0, count=0;

      top = (i-1 != -1) ? i-1 : dimRow - 1;
      bottom = (i+1 != dimRow) ? i+1 : 0;
      left = (j-1 != -1) ? j-1 : dimColumn - 1;
      right = (j+1 != dimColumn) ? j+1 : 0;

      count += (gridIn[top*dimColumn + left] == 1) ? 1 : 0;
      count += (gridIn[top*dimColumn + j] == 1) ? 1 : 0;
      count += (gridIn[top*dimColumn + right] == 1) ? 1 : 0;
      count += (gridIn[i*dimColumn + left] == 1) ? 1 : 0;

      count += (gridIn[i*dimColumn + right] == 1) ? 1 : 0;
      count += (gridIn[bottom*dimColumn + left] == 1) ? 1 : 0;
      count += (gridIn[bottom*dimColumn + j] == 1) ? 1 : 0;
      count += (gridIn[bottom*dimColumn + right] == 1) ? 1 : 0;

      if(gridIn[i*dimColumn + j] == 1) {
        if ( !(count == 2 || count == 3) ) {
          gridOut[i*dimColumn + j] = 0;
        }
      }
      else {
        if( count == 3) {
          gridOut[i*dimColumn + j] = 1;
        }
      }
    }
  }

  __global__ void cudaStep(Grid * gridIn, Grid * gridOut) {
    int threadId = blockIdx.x * blockDim.x + threadIdx.x;

    if (threadId < gridIn->getDimRow() * gridIn->getDimColumn()) {
      int i = threadId / gridIn->getDimColumn();
      int j = threadId % gridIn->getDimColumn();

      int top=0, bottom=0, left=0, right=0, count=0;

      top = (i-1 != -1) ? i-1 : gridIn->getDimRow() - 1;
      bottom = (i+1 != gridIn->getDimRow()) ? i+1 : 0;
      left = (j-1 != -1) ? j-1 : gridIn->getDimColumn() - 1;
      right = (j+1 != gridIn->getDimColumn()) ? j+1 : 0;

      count += (gridIn->getTab(top, left) == 1) ? 1 : 0;
      count += (gridIn->getTab(top, j) == 1) ? 1 : 0;
      count += (gridIn->getTab(top, right) == 1) ? 1 : 0;
      count += (gridIn->getTab(i, left) == 1) ? 1 : 0;

      count += (gridIn->getTab(i, right) == 1) ? 1 : 0;
      count += (gridIn->getTab(bottom, left) == 1) ? 1 : 0;
      count += (gridIn->getTab(bottom, j) == 1) ? 1 : 0;
      count += (gridIn->getTab(bottom, right) == 1) ? 1 : 0;

      if(gridIn->getTab(i, j) == 1) {
        if ( !(count == 2 || count == 3) ) {
          gridOut->setTab(i, j, 0);
        }
      }
      else {
        if( count == 3) {
          gridOut->setTab(i, j, 1);
        }
      }
    }
  }

}
