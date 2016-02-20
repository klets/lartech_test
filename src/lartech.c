#include "lartech.h"
#include "unique_subset.h"

static void pr_help(char* progname)
{
	fprintf(stderr, "usage: %s <file>\n", progname);	
}

int print_file(char*  name, int32_t maxsum, int32_t maxsum_swap, int32_t total_num_R2)
{
	char* fname_out;
	size_t size = strlen(name) + strlen(".res") + 1;
	FILE* fp;
	
	fname_out = (char*) calloc(1, size);

	snprintf(fname_out, size, "%s.res", name);

	fp = fopen(fname_out, "w");
	
	if (!fp) 
		handle_error_ext("Failed to open output file %s", fname_out);

	snprintf(fname_out, size, "%d\n", maxsum);
	
	fputs(fname_out, fp);

	snprintf(fname_out, size, "%d\n", maxsum_swap);
	
	fputs(fname_out, fp);
	
	snprintf(fname_out, size, "%d\n", total_num_R2);
	
	fputs(fname_out, fp);

	fclose(fp);

	free(fname_out);
	
	return 0;
}


int main(int argc, char* argv[])
{	
	int32_t N; 					/** Number of elemets */
	int32_t* array; 			/** Array of elements */
	int32_t maxsum;
	int32_t maxsum_swap;
	int32_t start_idx, end_idx;
	int32_t total_num_R2;
	
	if (argc < 2) {		
		pr_help(argv[0]);
		return -1;
	}

	pr_debug("Parse file %s", argv[1]);
	
	if (parse_file(argv[1], &N, &array)) {
		return -1;
	}

	maxsum = find_max_subset_sum(array, N, &start_idx, &end_idx);

	pr_debug("maxsum = %d at interval (%d, %d)", maxsum, start_idx, end_idx);

	total_num_R2 = find_max_equal_subset_number(array, N);
	
	pr_debug("total num R2 subsets = %d", total_num_R2);

	maxsum_swap = find_max_subset_sum_swap(array, N);

	pr_debug("maxsum swap = %d", maxsum_swap);
	/* Print to file data */

	free(array);
	
	if (print_file(argv[1], maxsum, maxsum_swap, total_num_R2)) {
		return -1;
	}

	return 0;
}
