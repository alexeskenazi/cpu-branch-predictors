#pragma once

#define MAX_TABLE_SIZE 4096

#define NOT_TAKEN 0
#define TAKEN 1

// 2-bit predictor with 4 states
// 00: Strongly not taken
// 01: Weakly not taken
// 10: Weakly taken
// 11: Strongly taken
#define STRONGLY_NOT_TAKEN 0
#define WEAKLY_NOT_TAKEN 1
#define WEAKLY_TAKEN 2
#define STRONGLY_TAKEN 3

// 3-bit predictor with 6 states
#define THREE_STRONGLY_TAKEN 0
#define THREE_TAKEN 1
#define THREE_WEAKLY_TAKEN 2
#define THREE_WEAKLY_NOT_TAKEN 3
#define THREE_NOT_TAKEN 4
#define THREE_STRONGLY_NOT_TAKEN 5

// Tournament predictor
// 1. 00 – strongly prefer Gshare
// 2. 01 – weakly prefer Gshare
// 3. 10 – weakly prefer Bimodal
// 4. 11 – strongly prefer Bimodal
#define STRONGLY_GSHARE 0
#define WEAKLY_GSHARE 1
#define WEAKLY_BIMODAL 2
#define STRONGLY_BIMODAL 3

#define USE_GSHARE 0
#define USE_BIMODAL 1
