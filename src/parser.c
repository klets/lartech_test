#include "lartech.h"


int parse_file(char *name, int32_t* n_out, int32_t** array_out)
{
	FILE* fp;
	char* line = NULL;
	size_t len = 0;
	int i;
	
	*n_out = 0;
	
	if (!n_out || !array_out || !name) 
		handle_error("Wrong args");	
	
	fp = fopen(name, "r");
	
	if (!fp) 
		handle_error_ext("Failed to open file %s", name);
	

	/* Read line by line */
	while (getline(&line, &len, fp) != -1) {
		char *saveptr, *p;

		if (!line) {
			handle_error("getline() error");
		}

		pr_debug1("read line: %s", line);
		
		p = line;

		while ((*p == ' ') && (*p != '\0'))
			p++; 
			
		if ((*p == '\0') || (*p == '\n')) {
			/** empty line */
			continue;				    
		}

		
		if (*n_out == 0) {
			*n_out = strtol(p, NULL, 10);
			if ((*n_out == LONG_MAX) ||
			    (*n_out == LONG_MIN) ||
			    (*n_out <= 0)) { /* <=0 Is impossible too */
				free(line);
				handle_error("Bad input file: wrong number of elements in set");	
			}

			pr_debug("Parsed number of elements in set: %d", *n_out);

			/** Allocate array for set */
			*array_out = calloc(*n_out, sizeof(int32_t));
			if (!*array_out) {
				free(line);
				handle_error("calloc()");
			}
			
		} else { /** read line with numbers */
			char *token, *str1;

			str1 = p;
			
			i = 0;
			do {
				
				token = strtok_r(str1, " ", &saveptr);
				if (!token) {
					break;
				}				
				str1 = NULL;
				(*array_out)[i] = strtol(token, NULL, 10);				
				if ((*n_out == LONG_MAX) ||
				    (*n_out == LONG_MIN)) {
					free(line);
					free(*array_out);
					*array_out = NULL;
					*n_out = 0;
					handle_error_ext("Bad input file: wrong %d element in set", i);	
				}
				i++;
			} while (1);

			break;
		}		
	}

	if (line)
		free(line);

	if (*n_out <= 0) {
		handle_error("Bad file format: no data");
	}
	
	if (i != *n_out) {
		handle_error("Bad file format: not enough elements in set or too much");
	}

	pr_debug_puts("Set:");
	for (i = 0; i < *n_out; i++) {
		pr_debug1("%d ", (*array_out)[i]);
	}
	pr_debug_puts("");
	
	return 0;
}
