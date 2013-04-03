#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mat.h"

int main () {
	static MATFile		*pmat;
	static const char	**dir;
	static const char	*file = "simpleMat.mat";
	static const char	*vector = "simpleVector";
	static int			ndir;
	static int			i;
	static int			numToRead;
	static mxArray		*pa;
	static double		*pr;

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
	* get a list of variable in this MAT-file
	*/
	dir = (const char **)matGetDir(pmat, &ndir); //need casting here since dir is declared as const
	if (dir == NULL) {
		printf("Error reading directory of file %s\n", file);
		return(1);
	} else {
		printf("Directory of %s:\n", file);
		for (i=0; i < ndir; i++)
			printf("%s\n",dir[i]);
	}

	if (strcmp(dir[0],vector) != 0) {
		printf("%s contains %s, but not %s\n", file, dir[0], vector);
		return 1;
	} else {
		printf("Found vector: %s\n", vector);
	}

	/*read the variable*/
	pa = matGetVariable(pmat, dir[0]);

	if (pa == NULL) {
		printf("Error reading %s in %s\n", dir[0], file);
		return(1);
    }

	numToRead = mxGetNumberOfElements(pa);
	pr = mxGetPr(pa);

	printf("According to its contents, array %s has %d elements\n", dir[0], numToRead);

	for (i = 0; i < numToRead; i++) {
		printf("%f\n", pr[i]);

	}

	mxFree(dir);
	mxDestroyArray(pa);

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

