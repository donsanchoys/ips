#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <thread>
#include <ctime>

# define M_PI 3.14159265358979323846 /* pi, #include <math.h> */

using namespace std;

//подынтегральная функция
double my_func(double x)
{
	return 5 / sqrt(8 - 4 * x * x);
}

//метод Симпсона с отключением векторизации
double no_vector(int n)
{
	double min = -1;
	double max = 1;
	double sum = 0;

	double step = (max - min) / n;
	//отключение векторизации
#pragma loop(no_vector)
	for (int i = 0; i < n; i++)
	{
		const double x1 = min + i * step;
		const double x2 = min + (i + 1) * step;
		sum += (x2 - x1) / 6.0 * (my_func(x1) + 4.0 * my_func(0.5 * (x1 + x2)) + my_func(x2));
	}
	printf("Значение методом Симпсона: %.15f, n = %d\n", sum, n);
	return sum;
}

int main()
{
	using namespace std::chrono;
	using namespace std;
	setlocale(LC_ALL, "Russian");

	for (int i = 100; i <= 1000000; i = i * 10)
	{
		//засекаем время
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		double trap = no_vector(i);
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		duration<double> duration = (t2 - t1);
		cout << "Время работы: " << duration.count() << " сек\n" << endl;
	}
	return 0;
}