#include <stdint.h>
#include <stdlib.h>
#include <string.h>


/**
   @brief Unique subset for problem with R2 subsets
 */
typedef struct unique_subset_s {
	/** Sorted set of unique values of capacity N */
	int32_t* set;
	/** Number of unique elements  */
	uint32_t size;
	/** Capacity (alway less or equal number of elements in array  */
	uint32_t cap;
	/** Last taken  */
	int32_t last;
} unique_subset_t;

/**
   @brief Init unique subset
   @param[in] subset pointer to subset
   @param[in] capacity maximumsubset size
   
   @retval 0 -- succeed, -1 -- some memory error
 */
int unique_subset_init(unique_subset_t *subset, int capacity);

/**
   @brief Push value in unique subset
   @param[in] subset pointer
   @param[in] value to push   
 */
void unique_subset_push(unique_subset_t *subset, int32_t value);


/**
   @brief Check if value in unique subset
   @param[in] subset pointer
   @param[in] value to check

   @retval >= 0 -- value in subset, -1 -- not in subset
 */
int unique_subset_is_contain(unique_subset_t *subset, int32_t value);

void unique_subset_dump(unique_subset_t *subset);

int unique_subset_equal(unique_subset_t *subset1, unique_subset_t *subset2);

void unique_subset_free(unique_subset_t *subset);
