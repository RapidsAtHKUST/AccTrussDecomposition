#include <cstdint>

#define NUM_THREADS (16u)
#define CHUNK (16u)

/*
 * Compute Eager: only for a single-K.
 * Intersection in each iteration.
 */
void eager_ktruss(const uint32_t *IA, uint32_t *JA, // input matrix in CSR format
                  uint16_t *M, // array of support values
                  uint32_t NUM_VERTICES, uint32_t K) {
    bool notEqual = true;
    while (notEqual) { // repeat until no edges are removed

        notEqual = false;

#pragma omp parallel for num_threads (NUM_THREADS) schedule (dynamic, CHUNK)
        for (uint32_t i = 0; i < NUM_VERTICES; ++i) { // iterate over every row

            uint32_t a12_start = *(IA + i);
            uint32_t a12_end = *(IA + i + 1);
            uint32_t *JAL = JA + a12_start;

            for (uint32_t l = a12_start; *JAL != 0 && l != a12_end; ++l) { // and non−zero columns

                uint32_t A22_start = *(IA + *(JAL));
                uint32_t A22_end = *(IA + *(JAL) + 1);

                JAL++;

                uint16_t ML = 0;
                uint32_t *JAK = JAL;
                uint32_t *JAJ = JA + A22_start;
                uint16_t *MJ = M + A22_start;
                uint16_t *MK = M + l + 1;

                while (*JAK != 0 && *JAJ != 0 && // check early termination
                       JAK != JA + a12_end && JAJ != JA + A22_end) {

                    uint32_t JAj_val = *JAJ;
                    int update_val = (JAj_val == *JAK);

                    if (update_val) {
#pragma omp atomic
                        ++(*MK);
                    }

                    ML += update_val;

                    uint32_t tmp = *JAK;
                    uint32_t advanceK = (tmp <= JAj_val);
                    uint32_t advanceJ = (JAj_val <= tmp);
                    JAK += advanceK;
                    MK += advanceK;
                    JAJ += advanceJ;

                    if (update_val) {
#pragma omp atomic
                        ++(*MJ);
                    }
                    MJ += advanceJ;
                }
#pragma omp atomic
                *(M + l) += ML;
            }
        }

#pragma omp parallel for num_threads (NUM_THREADS) schedule ( dynamic, CHUNK)
        for (uint32_t n = 0; n < NUM_VERTICES; ++n) {

            uint32_t st = *(IA + n);
            uint32_t end = *(IA + n + 1);
            uint32_t *J = JA + st;
            uint32_t *Jk = JA + st;
            uint16_t *Mst = M + st;

            for (; *J != 0 && J != JA + end; ++Mst, ++J) {
                if (*Mst >= K - 2) { // check if edge needs to be filtered
                    *Jk = *J; // keep it in packed format
                    Jk++;
                }
                *Mst = 0; // reset support value for next iteration
            }
            if (Jk < J) { // some edges in this row has been deleted
                notEqual = true; // no locking needed since always set to 1
                *Jk = 0;
            }
        }
    }
}