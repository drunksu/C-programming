#include <stdio.h>
#include <math.h>
#include <assert.h>

#define EPS 1e-4

int double_equal(double a, double b) {
	return fabs(a - b) < EPS;
}

/*
  Given a continuous function f:R->R, and an interval [left, right],
  find 'total' solutions in [left, right], and store them in a
  list in increasing order.
  
  Return 1 if we manage to find 'total' solutions; return 0 otherwise.
 */
int find_root(double (*f)(double), double left, double right, double* root) {
	if (f(left) * f(right) > 0) {
		return 0;
	}
	
	while (right - left > EPS) {
		double mid = (left + right) / 2;
		if (double_equal(f(mid), 0.0)) {
			*root = mid;
			return 1;
		} else if (f(left) * f(mid) < 0) {
			right = mid;
		} else {
			left = mid;
		}
	}
	
	*root = (left + right) / 2;
	return 1;
}

int solve_equation(double (*f)(double), double left, double right,
	int total, double* list) {
		int found = 0;
		double step = (right - left) / 1000000; 
		
		for (double init = left; init <= right; init += step) {
			double end = init + step;
			if (end > right) {
				end = right;
			}
			
			double root;
			if (find_root(f, init, end, &root)) {
				int flag = 1;
				for (int i = 0; i < found; i++) {
					if (double_equal(list[i], root)) {
						flag = 0;
						break;
					}
				}
				if (flag) {
					list[found++] = root;
					if (found == total) {
						return 1; 
					}
				}
			}
		}
		
		return 0;
	}

double f1(double x) {
	return sin(x);
}

double f2(double x) {
	return x*x*x - 2*x*x - 4*x + 3;
}

double f3(double x) {
	return exp(sin(x)) - x;
}

void TestCase1() {
	double list[10];
	assert(solve_equation(f1, 0, 10, 4, list) == 1);
	int i;
	for (i = 0; i < 4; i++) {
		assert(double_equal(f1(list[1]), 0.0));
	}
	
	printf("TestCase1 passed!\n");
}

void TestCase2() {
	double list[10];
	assert(solve_equation(f2, -2, 4, 3, list) == 1);
	int i;
	for(i = 0;i < 3;i++){
		assert(double_equal(f2(list[i]), 0.0));
	}
	
	printf("TestCase2 passed!\n");
}

void TestCase3() {
	double list[10];
	assert(solve_equation(f3, 2, 4, 2, list) == 0);
	assert(solve_equation(f3, 2, 4, 1, list) == 1);
	assert(double_equal(f3(list[0]), 0.0));
	
	printf("TestCase3 passed!\n");
}

int main() {
	TestCase1();
	TestCase2();
	TestCase3();
	return 0;
}
