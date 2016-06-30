#ifndef _GRID
   #define _GRID
   #ifdef __CUDACC__
   #define CUDA_HOSTDEV __host__ __device__
   #else
   #define CUDA_HOSTDEV
   #endif

     class Grid {
         private:
           // number of rows
           int dimRow;
           // number of columns
           int dimColumn;
           // (list, tab, or vect ...) of blocks
           int * tab;

           void free();
           void copy(const Grid &);

         public:
           Grid();
           Grid(int);
           Grid(int, int);
           Grid(const Grid &);
           ~Grid();

           __host__ __device__ int getDimRow() const ;
           __host__ __device__ int getDimColumn() const ;
           __host__ __device__ int getTab(int, int) const ;
           int * getTab();

           void setDimRow(int);
           void setDimColumn(int);
           __host__ __device__ void setTab(int, int, int);

           Grid & operator=(const Grid);

           void nextStep();
     };
#endif
