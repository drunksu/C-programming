#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/* swap two elements */
void swap(int nums[], int i, int j) {
	int tmp = nums[i];
	nums[i] = nums[j];
	nums[j] = tmp;
}

/* division and partition */
int partition(int nums[], int left, int right) {
	//set nums[left] as the base
	int i = left, j = right;
	while (i < j) {
		while (i < j && nums[j] >= nums[left]) {
			j--; // find the first element that less than the base from right to left
		}
		while (i < j && nums[i] <= nums[left]) {
			i++; // find the first element that more then the base from left to right
		}
		// swap the found elelments
		swap(nums, i, j);
	}
	swap(nums, i, left);
	return i;
}

/* quicksort */
void sort(int nums[], int left, int right) {
	if (left >= right) {
		return;
	}
	int pivot = partition(nums, left, right);
	
	sort(nums, left, pivot - 1);
	sort(nums, pivot + 1, right);
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
