#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100 // 假定最大替换字符串长度不超过100


void create_map(char*** map, int* mapSize, int*** mapColSize) {
	int n;
	printf("请输入你要替换的个数: ");
	if (scanf("%d", &n) != 1) {
		printf("输入错误，程序退出。\n");
		return;
	}
	
	*mapSize = n;
	
	*map = (char**)malloc(52 * sizeof(char*));  // 26 for lowercase and 26 for uppercase
	*mapColSize = (int**)malloc(52 * sizeof(int*));
	
	if (!*map || !*mapColSize) {
		printf("内存分配失败，程序退出。\n");
		return ;
	}
	
	for (int i = 0; i < 52; i++) {
		(*map)[i] = (char*)malloc(MAX * sizeof(char));  // allocate space for each string in map
		for(int j=0;j < MAX;j++){
			map[0][i][j]='\0';
		}
		(*mapColSize)[i] = (int*)malloc(sizeof(int));   // allocate space for the size of each mapping
		(*mapColSize)[i][0] = 0;  // initialize the mapping size to 0
	}
	
	for (int i = 0; i < n; i++) {
		char a;
		char t[MAX];
		printf("你要将哪个字符替换? ");
		if (scanf(" %c", &a) != 1) {
			printf("字符输入错误！\n");
			return;
		}
		
		printf("你要将%c替换为: ", a);
		if (scanf("%s", t) != 1) {
			printf("字符串输入错误！\n");
			return;
		}
		
		// Store the replacement rules based on character case
		int index = (a >= 'a' && a <= 'z') ? a - 'a' : a - 'A' + 26;
		for (int j = 0; j < strlen(t); j++) {
				(*map)[index][j] = t[j];
		}
		
		(*mapColSize)[index][0] = strlen(t);  // Store the length of the replacement string
	}
}

char* replace(char** map, char* s, int mapSize, int** mapColSize) {
	int n = 0;
	
	// 计算替换后的新字符串的长度
	for (int i = 0; i < strlen(s); i++) {
		int index = (s[i] >= 'a' && s[i] <= 'z') ? s[i] - 'a' : (s[i] >= 'A' && s[i] <= 'Z') ? s[i] - 'A' + 26 : -1;
		if (index != -1) {
			n += mapColSize[index][0];  // 如果字符有替换规则，增加替换后的字符长度
		} else {
			n++;  // 对于没有替换规则的字符，直接加 1
		}
	}
	
	// 为新字符串分配足够的内存（包括结尾的 '\0'）
	char* ans = (char*)malloc((n + 1) * sizeof(char));
	int cnt = 0;
	
	// 进行替换操作
	for (int i = 0; i < strlen(s); i++) {
		int index = (s[i] >= 'a' && s[i] <= 'z') ? s[i] - 'a' : (s[i] >= 'A' && s[i] <= 'Z') ? s[i] - 'A' + 26 : -1;
		if (index != -1 && map[index][0]) {
			for (int j = 0; j < mapColSize[index][0]; j++) {
				ans[cnt++] = map[index][j];
			}
		} else {
			ans[cnt++] = s[i];
		}
		ans[cnt]='\0';
	}
	
	ans[cnt] = '\0';  // 结束字符，确保字符串是正确的
	return ans;
}

int main() {
	char** map;
	int mapSize;
	int** mapColSize;
	create_map(&map, &mapSize, &mapColSize);
	
	if (map == NULL || mapColSize == NULL) {
		printf("地图创建失败，程序退出！\n");
		return 1;
	}
	
	char s[MAX];
	printf("请输入要替换的字符串: ");
	if (scanf("%s", s) != 1) {
		printf("字符串输入错误！\n");
		return 1;
	}
	
	char* result = replace(map, s, mapSize, mapColSize);
	printf("替换后的字符串: %s\n", result);
	
	// Free memory
	for (int i = 0; i < 52; i++) {
		free(map[i]);
		free(mapColSize[i]);
	}
	free(map);
	free(mapColSize);
	
	free(result);
	
	return 0;
}

