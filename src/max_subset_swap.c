#include "lartech.h"

int32_t func_add(int32_t a, int32_t b)
{
	return a + b;
}

int32_t func_max(int32_t a, int32_t b)
{
	return a > b ? a : b;
}

int32_t func_min(int32_t a, int32_t b)
{
	return a > b ? b : a;
}

static int32_t* partial_sum(int32_t* A, int32_t size, int32_t (*func)(int32_t a, int32_t b))
{
	int32_t* res;
	int i;

	if (size == 0)
		return NULL;
	
	res = (int32_t*) calloc(size, sizeof(int32_t));

	res[0] = A[0];
	for (i = 1; i < size; i++) {
		res[i] = func(res[i - 1], res[i]);
	}

	return res;
}
	
static int32_t calc_subset(int32_t* A, int32_t* A_reverse, int32_t size)
{
	int32_t sum = 0;
	int32_t* psum = NULL;
	int32_t* r_psum = NULL;
	
	int32_t* min_psum = NULL;
	int32_t* min_r_psum = NULL;
	
	int32_t* sub = NULL;
	int32_t* min_sub = NULL;
	int32_t* former = NULL;
	
	int i, res = 0;
	
	for (i = 0; i < size; i++) {
		sum += A[i];
	}

	psum = partial_sum(A, size, func_add);
	min_psum = partial_sum(A, size, func_max);
	sub = (int32_t*) calloc(size, sizeof(int32_t));

	for (i = 0; i < size; i++) {
		sub[i] = psum[i] - min_psum[i];
	}
	
	min_sub = partial_sum(sub, size, func_min);

	former = (int32_t*) calloc(size, sizeof(int32_t));

	for (i = 0; i < size; i++) {
		former[i] = func_min(((i - 1 >= 0 ? min_sub[i-1] : 0) + A[i]),
		                     ((i - 1 >= 0 ? former[i-1] : 0)));
	}

	r_psum = partial_sum(A_reverse, size, func_add);
	min_r_psum = partial_sum(r_psum, size, func_min);

	for (i = 0; i < size / 2; i++) {
		int32_t tmp;
		tmp = min_r_psum[i];
		
		min_r_psum[i] = min_r_psum[size - 1 - i];
		min_r_psum[size - 1 - i] = tmp;
	}

	
	for (i = 0; i < size; i++) {
		res = func_max(res, (sum - former[i] - (i + 1 >= size ? 0 : min_r_psum[i+1])));
	}


	free(psum);
	free(r_psum);
	free(min_psum);
	free(min_r_psum);
	free(sub);
	free(min_sub);
	free(former);
	
	return res;
}


int32_t find_max_subset_sum_swap(int32_t* A, int32_t size)
{
	int32_t* A_reverse;
	int i, r1, r2, r;
	
	A_reverse = (int32_t*) calloc(size, sizeof(int32_t));
	
	for (i = 0; i < size; i++) {
		A_reverse[i] = A[size - 1 - i];			
	}

	r1 = calc_subset(A, A_reverse, size);
	r2 = calc_subset(A_reverse, A, size);
	
	/* 0 result means no subarray have sum larger than 0, */
	/* we need to choose a largest negative element */

	r = r1 > r2 ? r1 : r2;
	
	if (r == 0) {
		r = A[0];
		for (i = 1; i < size; i++) {
			r = r > A[i] ? r : A[i];
		}
	} 

	return r;
}
