#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void sort(int* nums,int n){
	for(int i = 1;i < n;i++){
	int base = nums[i],j = i - 1;
		while(j >= 0 && nums[j] > base){
			nums[j + 1] = nums[j];
			j--;			
		}
		nums[j + 1] = base;
	}
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
	sort(nums,6);
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
	sort(nums,max);
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
