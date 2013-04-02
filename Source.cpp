#include <stdio.h>
#include <stdlib.h>
#include "mat.h"

int main () {
	MATFile *pmat;
	//const char **dir;
	//const char *name;
	static const char *file = "simpleMat.mat";
	//int	  ndir;
	//int	  i;
	//mxArray *pa;

	printf("Reading file %s...\n\n", file);

	/*
	 * Open file to get directory
	 */
	pmat = matOpen(file, "r");
	if (pmat == NULL) {
		printf("Error opening file %s\n", file);
		return 1;
	}


	/*
	 * Must try to close the file handle at the end
	 */
	if (matClose(pmat) != 0) {
		printf("Error closing file %s\n",file);
		return 1;
	}
	printf("Done!\n");

	return 0;
}

