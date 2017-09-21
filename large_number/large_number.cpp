// large_number.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<algorithm>
#include"large_number.h"

int main()
{
	large_number a = 1000,b =999,c;
	c = a-b;
	c.print();
	getchar(); getchar();
	return 0;
}

void large_number::print()
{
	if (sign == -1)printf("-");
	for (int i = size-1; i >=0 ; i--)
		printf("%d", number[i]);
	printf("\n");
}

int large_number::do_compare(large_number & b)
{
	// return -1 means < ;0 means = ;1 means > 
	if (this->sign == -1 && b.sign == 1)return -1;
	if (this->sign == 1 && b.sign == -1)return 1;
	int  flag;
	if (this->size > b.size)
	{
		flag = 1;
		goto result;
	}
	if (this->size < b.size)
	{
		flag = -1;
		goto result;
	}
	for (int i = b.size - 1; i >= 0; i--)
	{
		if (this->number[i] < b.number[i])
		{
			flag = -1;
			goto result;

		}
		if (this->number[i] > b.number[i])
		{
			flag = 1;
			goto result;
		}
	}
	return 0;
result:
	if (this->sign == 1 && b.sign == 1)
		return flag;
	else
		return -flag;

}

large_number large_number::do_add(large_number & b)
{
	large_number c;
	c.number.clear();
	c.sign = 1;
	int i;
	if (b.size > this->size)
	{
		for (i = 0; i < this->size; i++)
		{
			int x = b.number[i] + this->number[i];
			c.number.push_back(x);
		}
		for (; i < b.size; i++)
		{
			c.number.push_back(b.number[i]);
		}
		int k = 0;
		for (i = 0; i < b.size; i++)
		{
			int x;
			x = c.number[i] + k;
			c.number[i] = x % 10;
			k = x / 10;
		}
		if (k != 0)
		{
			c.number.push_back(k);
			c.size = b.size + 1;
		}
		else
			c.size = b.size;
	}
	else
	{
		for (i = 0; i < b.size; i++)
		{
			int x = b.number[i] + this->number[i];
			c.number.push_back(x);
		}
		for (; i < this->size; i++)
		{
			c.number.push_back(this->number[i]);
		}
		int k = 0;
		for (i = 0; i < this->size; i++)
		{
			int x;
			x = c.number[i] + k;
			c.number[i] = x % 10;
			k = x / 10;
		}
		if (k != 0)
		{
			c.number.push_back(k);
			c.size = this->size + 1;
		}
		else
			c.size = this->size;
	}
	return c;
}

large_number large_number::do_subtract(large_number & b)
{
	int x, y;
	x = this->sign;
	y = b.sign;
	this->sign = 1;
	b.sign = 1;

	int n;
	large_number ans, minuend, meiosis;
	n = do_compare(b);
	this->sign = x;
	b.sign = y;

	if (n == 0) return ans;
	if (n == -1)
	{
		ans.sign = -1;
		minuend = b;
		meiosis = *this;
	}
	else
	{
		minuend = *this;
		meiosis = b;
	}
	int i;
	for (i = 0; i < meiosis.size; i++)
		minuend.number[i] = minuend.number[i] - meiosis.number[i];
	for(i=0;i<minuend.size;i++)
		if (minuend.number[i] < 0)
		{
			minuend.number[i + 1]--;
			minuend.number[i] += 10;
		}
	ans.size = 0;
	for(i=0;i<minuend.size;i++)
		if (minuend.number[i] != 0)
		{
			ans.size++;
		}
		else
		{
			break;
		}
	ans.number.clear();
	for (i = 0; i < ans.size; i++)
		ans.number.push_back(minuend.number[i]);
	return ans;
}

large_number::large_number(int num)
{
	int i = 0;
	if (num < 0)
	{
		sign = -1;
		num = -num;
	}
	else
		sign = 1;
	while (true)
	{
		if (num == 0)break;
		i++;
		int x = num % 10;
		number.push_back(x);
		num = num / 10;
	}
	size = i;
}

large_number::large_number(string num)
{
	int len;
	len =  num.size();

	int i;
	if (num[0] == '-')
	{
		sign = -1;
		size = len - 1;
	}
	else
	{
		size = len;
		sign = 1;

	}
	for (i = 0; i < size; i++)
	{
		int x = num[len - i - 1] - '0';
		number.push_back(x);
	}
}

large_number::large_number()
{
	this->number.push_back(0);
	sign = 1;
	size = 1;
}

large_number large_number::operator=(string num)
{
	number.clear();
	int len;
	len = num.size();

	int i;
	if (num[0] == '-')
	{
		sign = -1;
		size = len - 1;
	}
	else
	{
		size = len;
		sign = 1;

	}
	for (i = 0; i < size; i++)
	{
		int x = num[len - i - 1] - '0';
		number.push_back(x);
	}
	return *this;
}

large_number large_number::operator=(int num)
{
	number.clear();
	int i = 0;
	if (num < 0)
	{
		sign = -1;
		num = -num;
	}
	else
		sign = 1;
	while (true)
	{
		if (num == 0)break;
		i++;
		int x = num % 10;
		number.push_back(x);
		num = num / 10;
	}
	size = i;
	return *this;
}

large_number large_number::operator+(large_number & b)
{
	large_number ans;
	if (this->sign == b.sign)
	{
		ans = do_add(b);
		ans.sign = ans.sign * b.sign;
	}
	else
	{
		ans = do_subtract(b);
		ans.sign = ans.sign * (this->sign);
	}
	return ans;
}

large_number large_number::operator-(large_number & b)
{
	large_number ans;
	if (this->sign == b.sign)
	{
		ans = do_subtract(b);
		ans.sign = ans.sign * (this->sign);
	}
	else
	{
		ans = do_add(b);
		ans.sign = ans.sign * (this->sign);
	}
	return ans;
}

bool large_number::operator<(large_number & b)
{
	int x;
	x = do_compare(b);
	return x == -1;
}

bool large_number::operator==(large_number & b)
{
	int x;
	x = do_compare(b);
	return x == 0;
}

bool large_number::operator<=(large_number & b)
{
	int x;
	x = do_compare(b);
	return x == -1 || x == 0;
}

bool large_number::operator>=(large_number & b)
{
	int x;
	x = do_compare(b);
	return x == 1 || x == 0;
}

bool large_number::operator>(large_number & b)
{
	int x;
	x = do_compare(b);
	return x == 1;
}

bool large_number::operator!=(large_number & b)
{
	return !(*this == b);
}

large_number large_number::operator+=(large_number & b)
{
	*this = *this + b;

	return *this;
}

large_number large_number::operator*(large_number & b)
{
	large_number c;
	c.number.clear();
	c.size = 0;
	c.sign = b.sign * (this->sign);
	if (this->size < b.size)
		this->swap(b);
	for (int i = 0; i < b.size; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			int l = i + j;
			int x = this->number[j] * b.number[i];
			if (l == c.size)
			{
				c.number.push_back(x);
				c.size++;
			}
			else
				c.number[l] += x;
		}
	}
	int i;
	int k = 0;
	for (i = 0; i < c.size; i++)
	{
		int x;
		x = c.number[i] + k;
		c.number[i] = x % 10;
		k = x / 10;
	}
	while (true)
	{
		if (k == 0)break;
		c.number.push_back(k % 10);
		c.size++;
		k = k / 10;
	}
	if (this->size < b.size)
		this->swap(b);
	return c;
}

large_number large_number::operator*=(large_number & b)
{
	*this = *this * b;

	return *this;
}

large_number large_number::operator-=(large_number & b)
{
	*this = *this - b;
	return *this;
}

void large_number::swap(large_number & b)
{
	vector<int> c;
	int t;
	c = this->number;
	this->number = b.number;
	b.number = c;
	t = this->size;
	this->size = b.size;
	b.size = t;
}


