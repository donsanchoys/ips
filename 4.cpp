#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <thread>
#include <ctime>

using namespace std;

//метод Симпсона
void simpson_p(double min, double max, int n, double& simpson_integral)
{
	const double width = (max - min) / n;
	for (int step = 0; step < n; step++)
	{
		const double x1 = min + step * width;
		double f = 5 / sqrt(8 - 4 * x1 * x1);
		const double x2 = min + (step + 1) * width;
		double g = 5 / sqrt(8 - 4 * x2 * x2);
		double c = 5 / sqrt(8 - 4 * 0.5 * (x1 + x2) * 0.5 * (x1 + x2));
		simpson_integral += (x2 - x1) / 6.0 * (f + g + 4 * c);
	}

}

int main()
{
	setlocale(LC_ALL, "Russian");
	using namespace std::chrono;
	using namespace std;
	//Расчет методом Симпсона в четырёх потоках
	for (int i = 100; i <= 1000000; i = i * 10)
	{
		double area1 = 0;
		double area2 = 0;
		double area3 = 0;
		double area4 = 0;
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		//четыре области для потоков
		std::thread thr1(simpson_p, -1, -0.5, i, std::ref(area1));
		std::thread thr2(simpson_p, -0.5, 0, i, std::ref(area2));
		std::thread thr3(simpson_p, 0, 0.5, i, std::ref(area3));
		std::thread thr4(simpson_p, 0.5, 1, i, std::ref(area4));
		thr1.join();
		thr2.join();
		thr3.join();
		thr4.join();
		double area = area1 + area2 + area3 + area4;
		printf("Значение методом Симпсона (потоки): %.15f, n = %d\n", area, i);
		chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
		chrono::duration <double> duration = (t2 - t1);
		cout << "Время работы: " << duration.count() << " сек\n" << endl;
	}

	return 0;
}