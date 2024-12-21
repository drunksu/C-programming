#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

int compare(const void *a, const void *b) {
	return (*(int*)a) - (*(int*)b);
}

// Helper function to find the min and max values in the array
void find_min_max(int *nums, int n, int *min_value, int *max_value) {
	*min_value = nums[0];
	*max_value = nums[0];
	for (int i = 1; i < n; ++i) {
		if (nums[i] < *min_value) *min_value = nums[i];
		if (nums[i] > *max_value) *max_value = nums[i];
	}
}

void sort(int *nums, int n) {
	int k = n / 2;
	int *sizes = (int*)malloc(k * sizeof(int));  // Array to track bucket sizes
	int **buckets = (int**)malloc(k * sizeof(int*));  // Dynamic 2D array for buckets
	
	// Initialize bucket sizes and allocate memory
	for (int i = 0; i < k; ++i) {
		buckets[i] = (int*)malloc(n * sizeof(int));
		sizes[i] = 0;
	}
	
	// Find min and max values to normalize bucket indices
	int min_value, max_value;
	find_min_max(nums, n, &min_value, &max_value);
	
	// 1. Assign numbers to buckets
	for (int i = 0; i < n; ++i) {
		int idx = (nums[i] - min_value) * k / (max_value - min_value + 1);
		if (idx >= k) idx = k - 1;  // Ensure idx is within bounds
		buckets[idx][sizes[idx]++] = nums[i];
	}
	
	// 2. Sort each bucket
	for (int i = 0; i < k; ++i) {
		qsort(buckets[i], sizes[i], sizeof(int), compare);
	}
	
	// 3. Merge the buckets into the original array
	int idx = 0;
	for (int i = 0; i < k; ++i) {
		for (int j = 0; j < sizes[i]; ++j) {
			nums[idx++] = buckets[i][j];
		}
		free(buckets[i]);  // Free memory for each bucket
	}
	free(buckets);  // Free the array holding the bucket pointers
	free(sizes);    // Free the sizes array
}

int match(int *a, int *b, int n) {
	for (int i = 0; i < n; i++) {
		if (a[i] != b[i]) {
			return 0;
		}
	}
	return 1;
}

void Testcase1() {
	int nums[] = {2, 5, 6, 1, 4, 3};
	int n = 6;
	sort(nums, n);
	int ans[] = {1, 2, 3, 4, 5, 6};
	assert(match(nums, ans, n) == 1);
	printf("Pass Testcase1!\n");
}

void Testcase2() {
	int max = 128;
	int *nums = (int*)malloc(max * sizeof(int));
	int *ans = (int*)malloc(max * sizeof(int));
	for (int i = 0; i < max; i++) {
		nums[i] = max / 2 - i;
	}
	sort(nums, max);
	for (int i = 0; i < max; i++) {
		ans[i] = 1 - max / 2 + i;    
	}
	assert(match(nums, ans, max) == 1);
	printf("Pass Testcase2!\n");
	free(nums);
	free(ans);
}

void Testcase3() {
	srand(time(NULL));
	int n = rand() % 1024;
	if (n < 3) {
		printf("It's too small!\n");
		return;
	}
	int *nums1 = (int*)malloc(n * sizeof(int));
	int *nums2 = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		nums1[i] = rand();
		nums2[i] = nums1[i];
	}
	qsort(nums1, n, sizeof(int), compare);
	sort(nums2, n);
	assert(match(nums1, nums2, n) == 1);
	printf("Pass Testcase3!\n");
	free(nums1);
	free(nums2);
}

int main() {
	Testcase1();
	Testcase2();
	Testcase3();
	return 0;
}

