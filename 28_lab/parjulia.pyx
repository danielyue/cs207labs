# distutils: extra_compile_args = -fopenmp
# distutils: extra_link_args = -fopenmp

cimport cython
import numpy as np
cimport numpy as np
from cython.parallel cimport prange

cdef inline double norm2(double complex z) nogil:
    return z.real*z.real + z.imag*z.imag

cdef int escape(int maxiter, double complex z, double complex c) nogil:
    cdef int n=0
    while n < maxiter and norm2(z) < 4:
        z=z*z+c
        n+=1
    return n

@cython.boundscheck(False)
@cython.wraparound(False)
cpdef run_cython_amalgamated2(int gridsize, box, double complex c, int maxiter):
    cdef double complex[:,::1] zs = np.empty((gridsize,gridsize),dtype=np.complex)
    cdef long[:,::1] output = np.empty((gridsize,gridsize), dtype=np.long)
    
    cdef long xstep = (box.x2 - box.x1)/(gridsize - 1.0)
    cdef long ystep = (box.y2 - box.y1)/(gridsize - 1.0)
    cdef long xstart = box.x1
    cdef long ystart = box.y2
    cdef int i,j
    cdef double x,y
    cdef double complex z;
    for i in prange(gridsize, nogil=True, schedule='static', chunksize=1):
        x = xstart + i*xstep
        for j in range(gridsize):
            y = ystart + j*ystep
            z = x + 1j*y
            output[i,j] = escape(maxiter, z, c)
    return output