#pragma once
#include<vector>
#include<string>
#include<stdio.h>
using namespace std;
class large_number
{
private:
	vector<int> number;
	int size;
	int sign;

	
	int do_compare(large_number &b);
	large_number do_add(large_number &b);
	large_number do_subtract(large_number &b);
	
public:
	large_number(const int num);
	large_number(string num);
	large_number();
	large_number  operator = (string num);
	large_number  operator =(const int num);
	large_number operator +(large_number &b);
	large_number operator +(const int num);
	large_number operator*(const int num);
	large_number operator-(const int num);
	large_number operator -(large_number &b);
	large_number operator * (large_number &b);	
	bool operator < (large_number &b);
	bool operator == (large_number & b);
	bool operator <=(large_number &b);
	bool operator >=(large_number &b);
	bool operator >(large_number &b);
	bool operator !=(large_number &b);
	large_number operator +=(large_number &b);
	large_number operator +=(const int num);
	large_number operator *=(const int num);
	large_number operator -=(const int num);

	large_number operator *=(large_number &b);
	large_number operator -=(large_number &b);

	void swap(large_number &b);
	void print();

};

