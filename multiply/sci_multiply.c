#include "api_scilab.h"
#include "BOOL.h"


int sci_multiply(char *fname, unsigned long fname_len)
{
	SciErr sciErr;

	int m1 = 0, n1 = 0;
    	int *piAddressVarOne = NULL;
    	double *matrix1 = NULL;

    	double *newMatrix = NULL;

    	int m2 = 0, n2 = 0;
    	int *piAddressVarTwo = NULL;
    	double *matrix2 = NULL;

    	int i = 0, j = 0, k = 0;

	CheckInputArgument(pvApiCtx, 2, 2);
    	CheckOutputArgument(pvApiCtx, 1, 1);

//arguement1

	sciErr = getVarAddressFromPosition(pvApiCtx,1,&piAddressVarOne);
    	if (sciErr.iErr)
    	{
        	printError(&sciErr, 0);
        	return 0;
    	}

	
	if ( !isDoubleType(pvApiCtx, piAddressVarOne) ||  isVarComplex(pvApiCtx, piAddressVarOne) )
    	{
        	Scierror(999, "%s: Wrong type for input argument #%d: A real matrix expected.\n", fname, 1);
        	return 0;
    	}

	sciErr = getMatrixOfDouble(pvApiCtx, piAddressVarOne, &m1, &n1, &matrix1);
    	if (sciErr.iErr)
    	{
        	printError(&sciErr, 0);
        	return 0;
    	}

//arguement2

	sciErr = getVarAddressFromPosition(pvApiCtx,2,&piAddressVarTwo);
    	if (sciErr.iErr)
    	{
        	printError(&sciErr, 0);
        	return 0;
    	}

	if ( !isDoubleType(pvApiCtx, piAddressVarTwo) ||  isVarComplex(pvApiCtx, piAddressVarTwo) )
    	{
        	Scierror(999, "%s: Wrong type for input argument #%d: A real matrix expected.\n", fname, 1);
        	return 0;
    	}

	sciErr = getMatrixOfDouble(pvApiCtx, piAddressVarTwo, &m2, &n2, &matrix2);
    	if (sciErr.iErr)
    	{
        	printError(&sciErr, 0);
        	return 0;
    	}

	if ( n1 != m2 )
    	{
       		Scierror(999, "%s: MAtrix multiplication is not possible.\n", fname, 1);
        	return 0;
    	}

//Application code

	newMatrix = (double*)malloc(sizeof(double) * m1 * n2);

	for (i = 0; i < m1; i++)
    	{
		for(j = 0; j < n2; j++)
		{
			newMatrix[j] = 0;
			for(k = 0; k < n1; k++)
			{
		
        	/* For each element of the matrix, multiply by 2 */
        			newMatrix[j] = newMatrix[j] + matrix1[k] * matrix2[k];
			
			}
		}
    	}

	sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 1, m1, n2, newMatrix);

//	free(newMatrix);

	if (sciErr.iErr)
    	{
        	printError(&sciErr, 0);
        	return 0;
    	}

	AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;

	 ReturnArguments(pvApiCtx);

	return 0;
}
