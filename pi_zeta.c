#include <stdio.h>
#include <math.h>

/*
  Let zeta(s) = 1/1^s + 1/2^s + 1/3^s + ...
  It is known that
  zeta(2) = PI^2 / 6
  zeta(4) = PI^4 / 90
  
  The goal is to compute the constant PI to a precision of 1e-3
  (meaning three decimal places) using the Riemann zeta function.
 */

int main() {
	double sum1 = 0.0,sum2 = 0.0,pi1,pi2;
	for(int i = 1;i < 9;i++){
		sum1 = sum1 + 1.0/(i*i);
		sum2 = sum2 + 1.0/(i*i*i*i);
	}
	
	pi1 = sqrt(6*sum1);
	pi2 = sqrt(sqrt(90*sum2));
	
	printf("%.3f %.3f\n",sum1,sum2);
	printf("%.3f %.3f\n",pi1,pi2);
	
	
	
	return 0;
}
