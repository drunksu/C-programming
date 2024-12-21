#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

int compare(const void *a, const void *b) {
	return (*(int*)a) - (*(int*)b);
}

void sort(int* nums,int n){
	int max = 0;
	for(int i = 0;i < n;i++ ){
		max = max > nums[i] ? max : nums[i];
	}
	
	int* cnt = (int*)calloc(max + 1,sizeof(int));
	if (cnt == NULL) {
		printf("Memory allocation failed.\n");
		return;
	}
	
	for(int i = 0;i < n;i++){
		cnt[nums[i]]++;
	}
	
	int i = 0;
	for(int num = 0;num < max + 1;num++){
		for(int j = 0;j < cnt[num];j++,i++){
			nums[i] = num;
		}
	}
	
	free(cnt);
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
	int max = 6;
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

