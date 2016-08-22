#ifndef algo.h
#define algo.h

void algorithm(int asset, float *lowerbound, float *upperbound, float lambda, float *average_u, float *covariance, float *x)
{
//achieve feasibility
	int j = 0;
	int i = 0;
	int t = 0;
	int k = 0;
	float sum = 0;
	for(i = 0; i < asset; i++)
	{
	x[i] = lowerbound[i];
	}
	float upperboundsum = 0;
	float lowerboundsum = 0;
	for(i = 0; i < asset; i++)
	{
		upperboundsum += upperbound[i];
		lowerboundsum += lowerbound[i];
	}
	if(lowerboundsum > 1 || upperboundsum < 1)
	{
		printf("no solution exists\n");
		return(-2);
	}
	else if(lowerboundsum == 1)
	{
		printf("We already get the optimal. ");
		
	}
	else
	{
		int a = -1;
		sum = 0;
		while(sum < 1)
		{
			a++;
			sum += upperbound[a];
		}
		if(a <= 1)
		{
			x[0] = lowerbound[0] + (1 - lowerboundsum);
		}
		else
		{
			for(i = 0; i < a; i++)
			{
				x[i] = upperbound[i];
			}
			x[a] = 1 - (sum - upperbound[a]);
		}
	
//improvement phase
		for(k = 0; k < 5; k++)
		{
			for(j = 0; j < asset; j++)
			{
				for(i = 0; i < j; i++ )
				{
					sum = 0;
					for(t = 0; t < asset; t++)
					{
						if(t != j && t != i)
						{
							sum += (covariance[t*asset + i] - covariance[t*asset + j])*x[t];
						}
					}
					float change = - (2*lambda*(-covariance[j*asset + j]*x[j] + covariance[i*asset + i]*x[i] + covariance[j*asset + i]*(x[j] - x[i]) + sum) + average_u[j] - average_u[i])/(2*lambda*(covariance[j*asset + j] + covariance[i*asset + i] - 2*covariance[j*asset + i]));
					//printf("%f\n", change);
					//change the proper change
					float changeplus;
					float changeminus;
					if(x[j] - lowerbound[j] < upperbound[i] - x[i])
					{
						changeplus = x[j] - lowerbound[j];
					}
					else
					{
						changeplus = upperbound[i] - x[i];
					}
					if(upperbound[j] - x[j] < x[i] - lowerbound[i])
					{
						changeminus = upperbound[j] - x[j];
					}
					else
					{
						changeminus = x[i] - lowerbound[i];
					}
					//get x[i]
					if(change >= -changeminus && change <= changeplus)
					{
						x[j] -= change;
						x[i] += change;
					}
					else if(change < -changeminus)
					{
						x[j] -= -changeminus;
						x[i] += -changeminus;
					}
					else if(change > changeplus)
					{
						x[j] -= changeplus;
						x[i] += changeplus;
					}
				}
			}
			
		}
		
	}	
}

#endif

