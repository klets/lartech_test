#include "unique_subset.h"
#include "lartech.h"

int unique_subset_init(unique_subset_t *subset, int capacity)
{
	subset->set = (int32_t*) calloc(capacity, sizeof(int32_t));
	if ( !subset->set ) {
        return -1;
    }
	subset->size = 0;
	subset->cap = capacity;

	return 0;
}


void unique_subset_free(unique_subset_t *subset)
{
	if (subset->set)
		free(subset->set);	
}
	
void unique_subset_dump(unique_subset_t *subset)
{
	int i;
	pr_debug_puts("Current unique set:");
	for (i = 0; i < subset->size; i++) {
		pr_debug1("%d ", subset->set[i]);
	}
	pr_debug_puts("");
}
	
void unique_subset_push(unique_subset_t *subset, int32_t value)
{
	int32_t size = subset->size;
	int32_t middle = size;
    int32_t pos = 0;
    
    /* Set is empty */
    if ( size == 0 ) {
	    subset->set[0] = value;
	    subset->size++;
	    
	    return;
    }
    
    /* Find position */
    do {
	    middle = size / 2;
        if ( value > subset->set[middle]) {
	        size -= middle + 1;
	        /* move to the next interval */
	        pos += middle + 1;
        } else {
            size = middle;
        }
    } while ( size > 0 );

    /* Check position */
    if ( pos < subset->size ) {
        /* Insert */
        memmove(&subset->set[pos + 1],
                &subset->set[pos],
                (subset->size - pos) * sizeof(int32_t));
    }
    /* Copy into position */
    subset->set[pos] = value;
    ++subset->size;

    return;
}

int unique_subset_is_contain(unique_subset_t *subset, int32_t value)
{
	int32_t size = subset->size;
	int32_t middle = size;
	int32_t first = 0;

	int32_t last = size - 1;
	
	/* Subset is empty */
	if ( size == 0 ) {
		return 0;
	}

	middle = (first + last) / 2;
	
	while (first <= last) {
		if (subset->set[middle] < value) {
			first = middle + 1;
		} else if (subset->set[middle] == value) {
			return 1;
		} else
			last = middle - 1;

		middle = (first + last) / 2;
		
	}

	return 0;
}

int unique_subset_equal(unique_subset_t *subset1, unique_subset_t *subset2)
{
	int i;

	if (subset1->size == 0) return 0;
	
	if (subset1->size != subset2->size) return 0;

	for (i = 0; i < subset1->size; i++) {
		if (subset1->set[i] != subset2->set[i])
			return 0;
	}

	return 1;
}

int32_t find_max_equal_subset_number(int32_t* A, int32_t size)
{
	int32_t total_num = 0;
	int32_t* intervals_start;
	int i, j, m = 0, n = 0;
	int32_t* intervals_end;
	
	/** Number of unsynced values in subsets  */

	unique_subset_t subset1;
	unique_subset_t subset2;
	
	if (unique_subset_init(&subset1, size)) {
		handle_error("unique_subset_init() error");	
	}

	if (unique_subset_init(&subset2, size)) {
		handle_error("unique_subset_init() error");	
	}

	intervals_start = (int32_t*)calloc(size + 1, sizeof(int32_t)); 
	intervals_end = (int32_t*)calloc(size + 1, sizeof(int32_t));
		
	/* Build intervals */

	/* From begin */
	i = 0;
	j = size - 1;
	m = 1;
	intervals_start[0] = -1;
	n = 1;
	intervals_end[0] = size;
	
	while ((i < size) || (j > 0)) {
		int first_has_new = 0;
		int second_has_new = 0;
		int to_add_first = 0;
		int to_add_second = 0;
		
		for (; i < size; i++) {
			if (!unique_subset_is_contain(&subset1, A[i])) {
				pr_debug("New value in first subset A[%d] = %d", i, A[i]);
				intervals_start[m] = i;
				m++;
				
				subset1.last = A[i];
				to_add_first = 1;
				first_has_new = 1;
				break;
			}
		}

		if (i == size) {
			/* Reach end */
			intervals_start[m] = size;
			first_has_new = 1;
			m++;
		}

		for (; j > 0; j--) {
			if (!unique_subset_is_contain(&subset2, A[j])) {
				pr_debug("New value in second subset A[%d] = %d", j, A[j]);
				intervals_end[n] = j;
				n++;

				second_has_new = 1;
				to_add_second = 1;
				subset2.last = A[j];				

				break;
			}
		}

		if (j == 0) {
			/* Reached begin */
			intervals_end[n] = -1;
			n++;
			second_has_new = 1;
		}

		if (first_has_new && second_has_new) {
			pr_debug("Check for equal subsets on intervals (%d, %d) and (%d, %d)", intervals_start[m - 2], intervals_start[m - 1],
			         intervals_end[n - 2], intervals_end[n - 1]);
			
			if (unique_subset_equal(&subset1, &subset2)) {
				pr_debug_puts("Equal!");
				total_num += (intervals_end[n - 2] - intervals_end[n - 1]) * (intervals_start[m - 1]
				                                                              - intervals_start[m - 2]);
			}

			if (to_add_first)
				unique_subset_push(&subset1, subset1.last);

			if (to_add_second)
				unique_subset_push(&subset2, subset2.last);
			
			first_has_new = 0;
			second_has_new = 0;


			unique_subset_dump(&subset1);
			unique_subset_dump(&subset2);							
		}		
	}

	free(intervals_start);
	free(intervals_end);

	unique_subset_free(&subset1);
	unique_subset_free(&subset2);
	
	return total_num;
}

