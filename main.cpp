#include <iostream>
#include <vector>
#include <cmath>
#include "plant.h"
#include "discpp.h"

using namespace std;

void enter_int(size_t& a)
{
	cin >> a;
}

void enter_double(double& a)
{
	cin >> a;
}

double uprl_vozd(double a, double b, double c, double d, double e, double f, double g, double h, double p)
{
	double u;
	u = a + b * c + d * log(e + f + g * exp(h * p));
	return u;
}


int
main(int argc, char* argv[])
{
    // Инициализация ОУ.
    Plant plant;
    plant_init(plant);
    // Объявление исходных данных
    size_t M1, M2; // Номера опрашиваемых датчиков
    size_t L; // Номер канала управления
    size_t J; // Номер канала измерения отклика
    size_t N; // Число моментов выработки управляющих воздействий
    double B1, B2, B3, B4, B5, B6; // коэффициенты, определяющие закон управления
    double Yzhel; // Желаемое значение отклика объекта
    // Ввод исходных данных
    cerr << "Enter numbers of sencors" << endl;
    cerr << "M1 = ";
    enter_int(M1);
    cerr << "M2 = ";
    enter_int(M2);
    cerr << "Enter L, J, N" << endl;
    cerr << "L = ";
    enter_int(L);
    cerr << "J = ";
    enter_int(J);
    cerr << "N = ";
    enter_int(N);
    cerr << "Enter coefficients" << endl;
    cerr << "B1 = ";
    enter_double(B1);
    cerr << "B2 = ";
    enter_double(B2);
    cerr << "B3 = ";
    enter_double(B3);
    cerr << "B4 = ";
    enter_double(B4);
    cerr << "B5 = ";
    enter_double(B5);
    cerr << "B6 = ";
    enter_double(B6);
    cerr << "Enter response value Yzhel";
    enter_double(Yzhel);
    // Получение экспериментальных данных.
   /* M1=1;M2=2;L=7;J=30;N=3;  // при N=1;Yzhel=553; Q ~ 0 //
    B1=1;B2=1;B3=5;B4=1;B5=1;B6=-0.013;Yzhel=553; */
     const size_t steps = N;
    vector<double> X1(steps);
    vector<double> X2(steps);
    vector<double> Y(steps);
    vector<double> U(steps);
    double Q = 0, f;
        cerr << "+---+" << "-----------+" << "------------+" << "------------+" << "------------+" << endl;
            cerr << "| N |" << "    X1     |" << "     X2     |" << "     U      |" << "     Y      |" << endl;
        for (size_t i = 1; i < steps + 1; i++)
        {
            // Измерение значений
            X1[i] = plant_measure(M1, plant);
            X2[i] = plant_measure(M2, plant);
            // Вычисление управляющего воздействия
            U[i] = uprl_vozd(B1, B2, X1[i], B3, Yzhel, B4, B5, B6, X2[i]);
            // Подача управл. возд. по каналу управления L
            plant_control(L, U[i], plant);
            // Измерение значения
            Y[i] = plant_measure(J, plant);
            // Вывод на экран значений
            cerr << "+---+-----------+------------+------------+------------+" << endl;
            cerr << "| " << i << " |" << " " << X1[i] << "    " ;
            cerr << "  " << X2[i] << "    " << "   " << U[i] << "    ";
            cerr << "  " << Y[i] << "    " << endl;
            // Расчёт оценки качества управления и вывод на экран
            f = pow((Y[i] - Yzhel), 2);
                Q = Q + f;
        }
        cerr << "+---+" << "-----------+" << "------------+" << "------------+" << "------------+" << endl;

    cerr << endl << "Quality assessment = " << Q / N << endl;
     cerr << "+---+-----------+------------+------------+------------+" << endl;
    return 0;
}
