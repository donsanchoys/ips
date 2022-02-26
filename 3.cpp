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
double my_fun(double x)
{
	return 5 / sqrt(8 - 4 * x * x);
}

//метод Симпсона с автоматическим параллелизатором
double auto_parallel(int n)
{
	double min = -1;
	double max = 1;
	double sum = 0;

	double step = (max - min) / n;
	//автоматический параллелизатор
#pragma loop(hint_parallel(0))
	for (int i = 0; i < n; i++) {
		const double x1 = min + i * step;
		const double x2 = min + (i + 1) * step;
		sum += (x2 - x1) / 6.0 * (my_fun(x1) + 4.0 * my_fun(0.5 * (x1 + x2)) + my_fun(x2));
	}
	printf("Значение методом Симпсона (авто параллелизатор): %.15f, n = %d\n", sum, n);
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
		double trap = auto_parallel(i);
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		duration<double> duration = (t2 - t1);
		cout << "Время работы: " << duration.count() << " сек\n" << endl;
	}
	return 0;
}