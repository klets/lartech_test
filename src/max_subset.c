#include "lartech.h"

int32_t find_max_subset_sum(int32_t* A, int32_t size, int32_t* start_idx, int32_t* end_idx)
{
	int32_t maxsum_start_idx = 0, maxsum_end_idx = 0;
	int32_t i = 0, j = 0;
	int32_t current_sum = 0, maxsum = LONG_MIN;
	
	while ((i < size) && (j < size)) {

		pr_debug("i = %d, j = %d", i, j);
		
		current_sum += A[j];
		if (current_sum > maxsum) {
			maxsum_start_idx = i;
			maxsum_end_idx = j;
			maxsum = current_sum;
		} 

		j++;
		
		if (current_sum <= 0) {
			i = j;
			current_sum = 0;
		}
	}

	*start_idx = maxsum_start_idx;
	*end_idx = maxsum_end_idx;
	
	return maxsum;
}
