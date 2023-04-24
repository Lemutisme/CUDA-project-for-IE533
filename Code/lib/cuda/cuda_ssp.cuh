/* 
 * Simple CUDA library for APSP problem
 */

#ifndef _CUDA_APSP_
#define _CUDA_APSP_

#include "../ssp.h"

// CONSTS for CUDA FW
#define BLOCK_SIZE 16

/**
 * Naive implementation algorithm in CUDA
 *
 * @param data: unique ptr to graph data with allocated fields on host
 */
void cudaNaiveFW(const std::unique_ptr<graphAPSPTopology>& dataHost);

/**
 * Blocked implementation algorithm in CUDA
 *
 * @param data: unique ptr to graph data with allocated fields on host
 */
void cudaBlockedFW(const std::unique_ptr<graphAPSPTopology>& dataHost);


#endif /* _APSP_ */
