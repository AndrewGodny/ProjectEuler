#include "problem_set.h"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

namespace ProjectEuler
{

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

void task9(int sum)
{
	/*
		Helper lamba-function
	*/
	auto gcd = [](int a, int b) {
		while (b != 0)
		{
			int buf = a % b;
			a = b; b = buf;
		}
		return a;
	};
	
	int s = sum / 2;
	int limit = ceil(sqrt(s)) - 1;
	for (int m = 2; m < limit; m++)
	{
		if (s % m == 0)
		{
			int sm = s / m;
			while (sm % 2 == 0) sm /= 2;
			int k;
			if (m % 2 == 1) k = m + 2; else k = m + 1;
			while (k < 2 * m && k <= sm)
			{
				if (sm % k == 0 && gcd(k, m) == 1)
				{
					int d = s / (k * m);
					int n = k - m;
					int a = d * (m * m - n * n);
					int b = 2 * d * m * n;
					int c = d * (m * m + n * n);
					cout << a << "*" << b << "*"<< c << "=" << a * b * c << endl;
					return;
				}
				k += 2;
			}
		}
	}
}

void task10(int n)
{
	auto isPrime = [](int a) {
		if (a < 2) return false;
		if (a == 2) return true;
		if (!(a % 2)) return false;
		for (int i = 3; i <= sqrt((double)a); i += 2)
			if (!(a % i)) return false;
		return true;
	};

	long long sum = 2;
	for (int i = 3; i <= n; i += 2)
		if (isPrime(i))
		{
			sum += i;
		}
	cout << sum << endl;
}

}