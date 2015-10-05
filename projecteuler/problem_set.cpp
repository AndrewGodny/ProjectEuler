#include "problem_set.h"

#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
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
	int sieve_bound = (n - 1) / 2;
	vector<bool> sieve(sieve_bound);
	fill(sieve.begin(), sieve.end(), false);
	int crosslimit = (floor(sqrt(n)) - 1) / 2;
	for (int i = 1; i < crosslimit; i++)
		if (!sieve[i])
			for (int j = 2 * i * (i + 1); j < sieve_bound; j += 2 * i + 1)
				sieve[j] = true;
	long long sum = 2;
	for (int i = 1; i < sieve_bound; i++)
		if (!sieve[i]) sum += 2 * i + 1;
	cout << sum << endl;
}

void task11(std::string filename)
{
	vector<vector<int>> data;
	// Read matrix from file
	ifstream file(filename);
	if (file.is_open())
	{
		string line;
		while (!getline(file, line).eof())
		{
			istringstream reader(line);
			vector<int> line_data;
			while (!reader.eof())
			{
				int elem;
				reader >> elem;
				line_data.push_back(elem);
			}
			data.push_back(line_data);
		}
		file.close();
	}
	else
	{
		throw new exception("Can't open data file");
	}
	
	// Get submatrix 4X4. If such matrix can't be built return emprty matrix
	auto getSubMatrix = [data](int x, int y) {
		vector<vector<int>> matrix;
		// Check if indexes are in bounds
		if (data.size() < x + 4)		return matrix;
		if (data[x].size() < y + 4)	return matrix;
		for (int i = x; i < x + 4; ++i)
		{
			vector<int> line;
			for (int j = y; j < y + 4; ++j)
				line.push_back(data[i][j]);
			matrix.push_back(line);
		}
		return matrix;
	};

	// Find greatest product of elements in matrix by rows, columns and diagonals
	auto greatestProduct = [](vector<vector<int>> matrix)
	{
		if (matrix.empty())
		{
			std::cout << "Matrix is empty" << std::endl;
			return (long)1;
		}
		long final_res = 1;
		long res_one = 1, res_two = 1;

		for (int i = 0; i < matrix.size(); ++i)
		{
			res_one = 1; res_two = 1;
			for (int j = 0; j < matrix[i].size(); ++j)
			{
				res_one *= matrix[i][j];
				res_two *= matrix[j][i];
			}
			std::cout << i + 1 << " row =\t\t" << res_one << std::endl;
			std::cout << i + 1 << " column =\t" << res_two << std::endl << std::endl;
			int res = res_one > res_two ? res_one : res_two;
			if (res > final_res) final_res = res;
		}		
		res_one = res_two = 1;
		int delta = matrix.size() - 1;
		for (int i = 0; i < matrix.size(); ++i)
		{
			res_one *= matrix[i][i];
			res_two *= matrix[i][delta - i];
		}
		std::cout << "first diagonal = " << res_one << std::endl;
		std::cout << "second diagonal = " << res_two << std::endl;
		res_one = res_one > res_two ? res_one : res_two;
		final_res = res_one > final_res ? res_one : final_res;

		return final_res;
	};
	/*
	vector<vector<int>> test = getSubMatrix(0, 0);
	for (int i = 0; i < test.size(); ++i)
	{
		for (int j = 0; j < test[i].size(); j++)
			std::cout << setw(2) << test[i][j] << " ";
		std::cout << std::endl;
	}
	long product = greatestProduct(test);
	std::cout << "\nGreatest product = " << product << std::endl;
	*/
	long res = 0;
	for (int i = 0; i < data.size() - 4; ++i)
		for (int j = 0; j < data[i].size() - 4; j++)
		{
			long curr = greatestProduct(getSubMatrix(i, j));
			if (curr > res) res = curr;
		}
	std::cout << "\nGreatest product = " << res << std::endl;
}

}