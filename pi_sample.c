#include <stdio.h>
#include <time.h>
#include <math.h>

/*
  Sample a random point (x, y) in the square [-1, 1] * [-1, 1].
  There is a unit circle C centered on (0, 0) with a radius of 1.
  The probability that a randomly chosen point falls inside
  the circle C is exactly PI / 4.
  
  Estimate the value of PI with a precision of 1e-3 by sampling
  a sufficient number of points.
 */
int main() {
	int cnt = 0;
	srand((unsigned)time(NULL));
	for(int i = 0;i < 999999;i++){
		double x = rand()/32767.0;
		double y = rand()/32767.0;
		if(x*x + y*y <= 1){
			cnt++;
		}
	}
	double pi = 4.0*cnt / 999999;
	printf("%.3f",pi);
	
	
	return 0;
}
