#include "problem_set.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

void task6(int max)
{
	long square = 0;
	long sum = 0;
	for (int i = 1; i <= max; i++)
	{
		square += i * i;
		sum += i;
	}
	cout << sum * sum - square << endl;
}

void task7(int prime_index)
{
	vector <int> primes = { 2,3,5,7,11,13 };

	while (primes.size() < prime_index)
	{
		int curr_index = primes.size() - 1;
		int last_prime = primes[curr_index];
		for (int i = 1; i < prime_index; i++)
			primes.push_back(last_prime + i);
		for (int prime_index = 0; prime_index < primes.size(); prime_index++)
		{
			for (int i = curr_index + 1; i < primes.size();)
			{
				if (primes[i] % primes[prime_index] == 0) primes.erase(primes.begin() + i);
				else i++;
			}
			if (curr_index - prime_index == 1) curr_index++;
		}
	}
	cout << primes[prime_index - 1] << endl;
}

void task8(char * huge_number)
{
	long long product = 0;
	string result, curr_number;
	while (*huge_number != '\0')
	{
		char c = *huge_number++;
		if (c == '0')
		{
			curr_number.clear();
			continue;
		}
		curr_number.push_back(c);
		if (curr_number.size() == 13)
		{
			long long curr_product = 1;
			for (char t : curr_number) curr_product *= t - '0';
			if (curr_product > product)
			{
				product = curr_product;
				result = curr_number;
			}
			curr_number.erase(curr_number.begin());
		}
	}
	if (curr_number.size() == 13)
	{
		long long curr_product = 1;
		for (char t : curr_number) curr_product *= t - '0';
		if (curr_product > product)
		{
			product = curr_product;
			result = curr_number;
		}
		curr_number.erase(curr_number.begin());
	}
	cout << result << endl << result.size() << endl << product << endl;
}

void task9()
{
	int a = 0, b = 0, c = 0;
	int m = 10, n = 2;
	while (a + b + c != 1000)
	{
		a = m * m - n * n;
		b = 2 * m * n;
		c = m * m + n * n;
		cout << a << "+" << b << "+" << c << "=" << a + b + c << endl;
		m++;
		if (m > 499)
		{
			n++; m = n + 5;
		}
	}
	cout << a * b * c << endl;
}
