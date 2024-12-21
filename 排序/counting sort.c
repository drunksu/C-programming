#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

int compare(const void *a, const void *b) {
	return (*(int*)a) - (*(int*)b);
}

void sort1(int* nums,int n){
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

void sort2(int* nums,int n){
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
	// 求 counter 的前缀和，将“出现次数”转换为“尾索引”
	// 即 counter[num]-1 是 num 在 res 中最后一次出现的索引
	for (int i = 0; i < max; i++) {
		cnt[i + 1] += cnt[i];
	}
	
	// 倒序遍历 nums ，将各元素填入结果数组 res
	// 初始化数组 res 用于记录结果
	int *res = (int*)malloc(sizeof(int) * n);
	for (int i = n - 1; i >= 0; i--) {
		int num = nums[i];
		res[cnt[num] - 1] = num; // 将 num 放置到对应索引处
		cnt[num]--;              // 令前缀和自减 1 ，得到下次放置 num 的索引
	}
	
	// 使用结果数组 res 覆盖原数组 nums
	memcpy(nums, res, n * sizeof(int));
	// 释放内存
	free(res);
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

