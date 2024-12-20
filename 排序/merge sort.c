#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* 合并左子数组和右子数组 */
void merge(int *nums, int left, int mid, int right) {
	// 左子数组区间为 [left, mid], 右子数组区间为 [mid+1, right]
	// 创建一个临时数组 tmp ，用于存放合并后的结果
	int tmpSize = right - left + 1;
	int *tmp = (int *)malloc(tmpSize * sizeof(int));
	// 初始化左子数组和右子数组的起始索引
	int i = left, j = mid + 1, k = 0;
	// 当左右子数组都还有元素时，进行比较并将较小的元素复制到临时数组中
	while (i <= mid && j <= right) {
		if (nums[i] <= nums[j]) {
			tmp[k++] = nums[i++];
		} else {
			tmp[k++] = nums[j++];
		}
	}
	// 将左子数组和右子数组的剩余元素复制到临时数组中
	while (i <= mid) {
		tmp[k++] = nums[i++];
	}
	while (j <= right) {
		tmp[k++] = nums[j++];
	}
	// 将临时数组 tmp 中的元素复制回原数组 nums 的对应区间
	for (k = 0; k < tmpSize; ++k) {
		nums[left + k] = tmp[k];
	}
	// 释放内存
	free(tmp);
}

/* 归并排序 */
void sort(int *nums, int left, int right) {
	// 终止条件
	if (left >= right)
		return; // 当子数组长度为 1 时终止递归
	// 划分阶段
	int mid = left + (right - left) / 2;    // 计算中点
	sort(nums, left, mid);      // 递归左子数组
	sort(nums, mid + 1, right); // 递归右子数组
	// 合并阶段
	merge(nums, left, mid, right);
}

int match(int *a,int *b){
	int n = sizeof(a),m = sizeof(b);
	if(n != m){
		return 0;
	}
	for(int i = 0;i < n;i++){
		if(a[i] != b[i]){
			return 0;
		}
	}
	return 1;
}

void Testcase1(){
	int nums[] = {2,5,6,1,4,3};
	sort(nums,0,5);
	int ans[] = {1,2,3,4,5,6};
	assert(match(nums,ans) == 1);
	printf("Pass Testcase1!\n");
}

void Testcase2(){
	int max = 128;
	int *nums = (int*)malloc(max*sizeof(int));
	int *ans = (int*)malloc(max*sizeof(int));
	for(int i = 0;i < max;i++){
		nums[i] = max / 2 - i;
	}
	sort(nums,0,max-1);
	for(int i = 0;i < max;i++){
		ans[i] = 1 - max / 2 + i;	
	}
	assert(match(nums,ans));
	printf("Pass Testcase2!\n");
	
}

int main(){
	Testcase1();
	Testcase2();
	
	return 0;
}
