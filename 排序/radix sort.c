#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

/* 获取元素 num 的第 k 位，其中 exp = 10^(k-1) */
int digit(int num, int exp) {
	return (num / exp) % 10;
}

/* 计数排序（根据 nums 第 k 位排序） */
void countingSortDigit(int nums[], int size, int exp) {
	int *counter = (int *)calloc(10, sizeof(int)); // 使用 calloc 初始化为 0
	// 统计 0~9 各数字的出现次数
	for (int i = 0; i < size; i++) {
		int d = digit(nums[i], exp);
		counter[d]++;
	}
	// 求前缀和，将“出现个数”转换为“数组索引”
	for (int i = 1; i < 10; i++) {
		counter[i] += counter[i - 1];
	}
	// 倒序遍历，根据桶内统计结果，将各元素填入 res
	int *res = (int *)malloc(sizeof(int) * size);
	for (int i = size - 1; i >= 0; i--) {
		int d = digit(nums[i], exp);
		int j = counter[d] - 1;
		res[j] = nums[i];
		counter[d]--;
	}
	// 使用结果覆盖原数组 nums
	for (int i = 0; i < size; i++) {
		nums[i] = res[i];
	}
	// 释放内存
	free(res);
	free(counter);
}

/* 基数排序 */
void sort(int nums[], int size) {
	// 获取数组的最大元素，用于判断最大位数
	int max = nums[0];
	for (int i = 1; i < size; i++) {
		if (nums[i] > max) {
			max = nums[i];
		}
	}
	// 按照从低位到高位的顺序遍历
	for (int exp = 1; max >= exp; exp *= 10) {
		countingSortDigit(nums, size, exp);
	}
}

int compare(const void *a, const void *b) {
	return (*(int*)a) - (*(int*)b);
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

