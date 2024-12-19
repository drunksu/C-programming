#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Implement selection sort or bubble sort.
// Given an array of integers, sort them in
// the increasing order.
void sort(int* list, int len) {
	for(int i = 0;i < len;i++){
		for(int j = 0;j < len - i;j++){
			if(list[j] > list[j + 1]){
				int tmp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = tmp;
			}
		}
	}
	
}

void TestSort3() {
	int list[3] = {4, 1, 0};
	sort(list, 3);
	assert(list[0] == 0);
	assert(list[1] == 1);
	assert(list[2] == 4);
	printf("Passed Test Case 1\n"); 
}

int cmp(const void* first, const void* second) {
	int val_x = *(int*) first;
	int val_y = *(int*) second;
	if (val_x == val_y) {
		return 0;
	}
	return val_x < val_y ? -1 : 1;
}

// Generate n random integers as a test case.
void TestSortWithSize(int n, int test_case_number) {
	int list[n], list_cpy[n];
	int i;
	for (i = 0; i < n; i ++) {
		list[i] = rand(); 
		list_cpy[i] = list[i];
	}
	qsort(list_cpy, n, sizeof(int), cmp);
	sort(list, n);
	// Compare if two arrays are equal.
	for (i = 0; i < n; i ++) {
		assert(list[i] == list_cpy[i]);
	}
	printf("Passed Test Case %d\n", test_case_number); 
}

int main() {
	TestSort3();
	TestSortWithSize(10, 2);
	TestSortWithSize(100, 3);
	TestSortWithSize(1000, 4);
	TestSortWithSize(10000, 5);
	return 0;
}
