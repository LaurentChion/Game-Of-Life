namespace Step {
    __global__ void cudaStep(int * gridIn, int * gridOut, int dimRow, int dimColumn);
    __host__ void nextStep(Grid * g);
}
