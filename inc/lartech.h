#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
#define pr_debug(X,...) fprintf(stdout, X "\n", ##__VA_ARGS__)
#define pr_debug1(X,...) fprintf(stdout, X, ##__VA_ARGS__)
#define pr_debug_puts(X) fprintf(stdout, X "\n")
#else
#define pr_debug(X,...)  
#define pr_debug1(X,...) 
#define pr_debug_puts(X) 

#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define handle_error(msg)	  \
	do { fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " msg "\n", __FILE__, __LINE__, clean_errno()); return -1; } while (0)

#define handle_error_ext(msg, ...)	  \
	do { fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " msg "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__); return -1; } while (0)


/**
   @brief Parse input file
   @param[in] name Input file name
   @param[out] n_out Number of array elements
   @param[out] array_out Allocated array

   @retval 0 if succed, -1 if failed 
 */
int parse_file(char *name, int32_t* n_out, int32_t** array_out);

/**
   @brief Find maximum sum of subset after one swap

   @param[in] A     input array
   @param[in] size  size of array

   @retval result
 */
int32_t find_max_subset_sum_swap(int32_t* A, int32_t size);



/**
   @brief Find conseq. subset with maximum sum 
   
   @desc Use Kadane's algo for problem solving

   @param[in]  A           set itself
   @param[in]  size        number of elements in set
   @param[out] start_idx   start index of subset with max sum
   @param[out] end_idx     end index of subset with max sum

   @retval  Maxmimum sum of conseq. subset
 */
int32_t find_max_subset_sum(int32_t* A, int32_t size, int32_t* start_idx, int32_t* end_idx);


/**
   @brief Find maximum number of subsets with equal values
   
   @desc Split set in intervals starting from begin to end (and backward) with equal partial unique set
   and product number of elments in appropriate intervals with equal sets.

   @param[in]  A           set itself
   @param[in]  size        number of elements in set

   @retval  Maxmimum number of subsets 
*/
int32_t find_max_equal_subset_number(int32_t* A, int32_t size);
