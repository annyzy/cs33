//OpenMP version.  Edit and submit only this file.
/* Enter your details below
 * Name : Ziying Yu
 * UCLA ID : 105182320
 * Email : annyu@g.ucla.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "utils.h"

void work_it_par(long *old, long *new)
{
    long aggregate = 1.0;
    const long a = we_need_the_func();
    const long b = gimmie_the_func();
    const long DIM_2 = DIM * DIM;
    
    omp_set_num_threads(omp_get_num_procs());
#pragma omp parallel reduction(+ \
: aggregate)
    {
        
        int address;
        int i, j, k, u;
        long temp;
        int histogram[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#pragma omp for
        for (i = 1; i < DIM - 1; i++)
        {
            for (j = 1; j < DIM - 1; j++)
            {
                for (k = 1; k < DIM - 1; k++)
                {
                    address = i * DIM_2 + j * DIM + k;
                    aggregate += old[address] * a / b;
                    temp = (old[address - DIM_2 - DIM - 1] +
                            old[address - DIM_2 - DIM] +
                            old[address - DIM_2 - DIM + 1]) +
                    (old[address - DIM_2 - 1] +
                     old[address - DIM_2] +
                     old[address - DIM_2 + 1]) +
                    (old[address - DIM_2 + DIM - 1] +
                     old[address - DIM_2 + DIM] +
                     old[address - DIM_2 + DIM + 1]) +
                    (old[address - DIM - 1] +
                     old[address - DIM] +
                     old[address - DIM + 1]) +
                    (old[address - 1] +
                     old[address] +
                     old[address + 1]) +
                    (old[address + DIM - 1] +
                     old[address + DIM] +
                     old[address + DIM + 1]) +
                    (old[address + DIM_2 - DIM - 1] +
                     old[address + DIM_2 - DIM] +
                     old[address + DIM_2 - DIM + 1]) +
                    (old[address + DIM_2 - 1] +
                     old[address + DIM_2] +
                     old[address + DIM_2 + 1]) +
                    (old[address + DIM_2 + DIM - 1] +
                     old[address + DIM_2 + DIM] +
                     old[address + DIM_2 + DIM + 1]);
                    temp /= 27;
                    new[address] = temp;
                    
                    u = temp / 100;
                    u = u <= 0 ? 0 : (u >= 9 ? 9 : u);
                    histogram[u]++;
                }
            }
        }
#pragma omp critical
        for (i = 0; i < 10; i++)
            histogrammy[i] += histogram[i];
    }
    
    printf("AGGR:%ld\n", aggregate);
}

