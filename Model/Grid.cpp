#include "Grid.hpp"
#include "Step.cuh"

void Grid::free(){
  // free the structure that contains blocks
  delete [] tab;
}

void Grid::copy(const Grid & g) {
  dimRow = g.getDimRow();
  dimColumn = g .getDimColumn();

  tab = new int[dimRow*dimColumn];
  for (int i = 0; i<dimRow; i++) {
    for(int j = 0; j< dimColumn; j++) {
      setTab(i,j, g.getTab(i,j));
    }
  }

}

Grid::Grid() : Grid(10) {};
Grid::Grid(int dim) : Grid(dim,dim){};
Grid::Grid(int dimR, int dimC) {
  srand (time(NULL));
  dimRow = dimR;
  dimColumn = dimC;
  tab = new int[dimRow*dimColumn];
  for(int i=0; i<getDimRow(); i++) {
    for(int j=0; j<getDimColumn(); j++) {
      setTab(i,j,rand()%2);
    }
  }
}
Grid::Grid(const Grid & g) {
  copy(g);
}

Grid::~Grid() {
  free();
}

int Grid::getDimRow() const  {
  return dimRow;
}
int Grid::getDimColumn() const {
  return dimColumn;
}
int Grid::getTab(int i, int j) const  {
  return tab[i*dimRow + j];
}
int * Grid::getTab() {
  return tab;
}

void Grid::setDimRow(int val) {
  dimRow = val;
}
void Grid::setDimColumn(int val) {
  dimColumn = val;
}
void Grid::setTab(int i, int j, int b) {
  tab[i*dimRow + j] = b;
}
Grid & Grid::operator=(const Grid g) {
  if(this != &g) {
    free();
    copy(g);
  }
  return *this;
}

void Grid::nextStep() {
  Grid copy(*this);

  int threadPerBlock = 512;
  int blocks = this->getDimRow() * this->getDimColumn() / threadPerBlock + 1;

  int *dev_copy = NULL, *dev_this = NULL;
  cudaMalloc( &dev_copy, this->getDimRow() * this->getDimColumn() * sizeof(int) );
  cudaMalloc( &dev_this, this->getDimRow() * this->getDimColumn() * sizeof(int) );
  cudaMemcpy(dev_copy, copy.getTab(), this->getDimRow() * this->getDimColumn() * sizeof(int), cudaMemcpyHostToDevice);
  cudaMemcpy(dev_this, this->getTab(), this->getDimRow() * this->getDimColumn() * sizeof(int), cudaMemcpyHostToDevice);
  Step::cudaStep<<< blocks, threadPerBlock >>>(dev_copy, dev_this, this->getDimRow(), this->getDimColumn());
  cudaMemcpy(this->getTab(), dev_this, this->getDimRow() * this->getDimColumn() * sizeof(int), cudaMemcpyDeviceToHost );

  /*Grid *dev_copy = NULL, *dev_g = NULL;
  cudaMalloc( &dev_copy, sizeof(copy) );
  cudaMalloc( &dev_g, sizeof(copy) );
  cudaMemcpy(dev_copy, &copy, sizeof(copy), cudaMemcpyHostToDevice);
  cudaMemcpy(dev_g, g, sizeof(copy), cudaMemcpyHostToDevice);
  cudaStep<<<blocks, threadPerBlock>>>(dev_copy, dev_g);
  cudaMemcpy(g, dev_g, sizeof(copy), cudaMemcpyDeviceToHost);*/

  cudaFree(dev_copy);
  cudaFree(dev_this);
}
