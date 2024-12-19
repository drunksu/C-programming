#include <stdio.h>
#include <assert.h>

int leap_year(int year) {
	return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

int date_to_days(int year, int month, int day) {
	if (year < 1 || month < 1 || month > 12 || day < 1) {
		return -1; 
	}
	
	int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	
	
	if (month == 2 && leap_year(year)) {
		days_in_month[1] = 29; 
	}
	
	if (day > days_in_month[month - 1]) {
		return -1; 
	}
	
	
	int ans = 0;
	
	for (int i = 1; i < year; i++) {
		ans += 365 + leap_year(i); 
	}
	
	for (int i = 0; i < month - 1; i++) {
		ans += days_in_month[i];
	}
	
	ans += day;
	
	return ans;
}

void TestCase1() {
	int days = date_to_days(2016, 2, 29);
	assert(days == 736023);
	printf("Passed TestCase1\n");
}

void TestCase2() {
	int days = date_to_days(2017, 2, 29);
	assert(days == -1);
	printf("Passed TestCase2\n");
}

void TestCase3() {
	int days = date_to_days(2024, 10, 12);
	assert(days == 739170);
	printf("Passed TestCase3\n");
}

int main() {
	TestCase1();
	TestCase2();
	TestCase3();
	return 0;
}

