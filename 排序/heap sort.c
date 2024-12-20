#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

/* 堆的长度为 n ，从节点 i 开始，从顶至底堆化 */
void siftDown(int nums[], int n, int i) {
	while (1) {
		// 判断节点 i, l, r 中值最大的节点，记为 ma
		int l = 2 * i + 1;
		int r = 2 * i + 2;
		int ma = i;
		if (l < n && nums[l] > nums[ma])
			ma = l;
		if (r < n && nums[r] > nums[ma])
			ma = r;
		// 若节点 i 最大或索引 l, r 越界，则无须继续堆化，跳出
		if (ma == i) {
			break;
		}
		// 交换两节点
		int temp = nums[i];
		nums[i] = nums[ma];
		nums[ma] = temp;
		// 循环向下堆化
		i = ma;
	}
}

/* 堆排序 */
void sort(int nums[], int n) {
	// 建堆操作：堆化除叶节点以外的其他所有节点
	for (int i = n / 2 - 1; i >= 0; --i) {
		siftDown(nums, n, i);
	}
	// 从堆中提取最大元素，循环 n-1 轮
	for (int i = n - 1; i > 0; --i) {
		// 交换根节点与最右叶节点（交换首元素与尾元素）
		int tmp = nums[0];
		nums[0] = nums[i];
		nums[i] = tmp;
		// 以根节点为起点，从顶至底进行堆化
		siftDown(nums, i, 0);
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

int cmp(const void*a,const void* b){
	return (*(int*)a) - (*(int*)b);
}

void Testcase1(){
	int nums[] = {2,5,6,1,4,3};
	sort(nums,6);
	int ans[] = {1,2,3,4,5,6};
	assert(match(nums,ans) == 1);
	printf("Pass Testcase1!\n");
	return ;
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
	return ;
}

void Testcase3(){
	srand(time(NULL));
	int n = rand() % 1024;
	if(n < 3){
		printf("It's too small!\n");
		return ;
	}
	int* nums1 = (int*) malloc(n * sizeof(int));
	int* nums2 = (int*) malloc(n * sizeof(int));
	for(int i = 0;i < n;i++){
		nums1[i] = rand();
		nums2[i] = nums1[i];
	}
	qsort(nums1,n,sizeof(int),cmp);
	sort(nums2,n);
	assert(match(nums1,nums2));
	printf("Pass Testcase3!\n");
	return ;
}


int main(){
	Testcase1();
	Testcase2();
	Testcase3();
	
	return 0;
}
