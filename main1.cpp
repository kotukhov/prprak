#include <iostream>
#include <vector>
#include <cmath>
#include "plant.h"
#include "discpp.h"
#include <iomanip>
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
    /* cerr << "Enter numbers of sencors" << endl;
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
     enter_double(Yzhel); */
    size_t numB;
    double Bmax, Bmin, deB;
    /* cerr << "Chose koef B (1-6)" << endl;
     enter_int(numB);
     cerr << "Enter Bmax " << endl;
     enter_double(Bmax);
     cerr << "Enter Bmin " << endl;
     enter_double(Bmin);
     cerr << "Enter step(delta) " << endl;
     enter_double(deB);*/
    // Получение экспериментальных данных.
    M1=1;
    M2=2;
    L=7;
    J=30;
    N=2;  // при N=1;Yzhel=553; Q ~ 0
    B1=1;
    B2=1;
    B3=1;
    B4=1;
    B5=1;
    B6= 1/*-0.013*/;
    Yzhel=553;
    numB=1;
    Bmax=15;
    Bmin=0;
    deB=1;
    const size_t steps = N;
    vector<double> X1(steps);
    vector<double> X2(steps);
    double f;
    for (size_t i = 1; i < steps + 1; i++)
    {
        // Измерение значений
        X1[i] = plant_measure(M1, plant);
        X2[i] = plant_measure(M2, plant);
        // Вычисление управляющего воздействия
        double C = ((Bmax - Bmin) / deB ) + 1;
        vector<double> U(C);
        vector<double> Y(C);
        vector<double> Q(C);
        cerr << "+--------+---------+----------+------------+---------+" << endl;
        cerr << "| " << setw(5) << "B" << numB << " |" << setw(8) <<"U" <<" | " << setw(8) << "Y" << " |" << setw(10) << "Q" << "  |" << " N = " << i << " ! |"<< endl;
        cerr << "+--------+---------+----------+------------+---------+" << endl;
        for (double V = Bmin; V <= Bmax; V = V + deB)
        {
            cerr << "| " << setw(5) << V << "  |";
            if (numB == 1)
                U[V] = uprl_vozd(V, B2, X1[i], B3, Yzhel, B4, B5, B6, X2[i]);
            if (numB == 2)
                U[V] = uprl_vozd(B1, V, X1[i], B3, Yzhel, B4, B5, B6, X2[i]);
            if (numB == 3)
                U[V] = uprl_vozd(B1, B2, X1[i], V, Yzhel, B4, B5, B6, X2[i]);
            if (numB == 4)
                U[V] = uprl_vozd(B1, B2, X1[i], B3, Yzhel, V, B5, B6, X2[i]);
            if (numB == 5)
                U[V] = uprl_vozd(B1, B2, X1[i], B3, Yzhel, B4, V, B6, X2[i]);
            if (numB == 6)
                U[V] = uprl_vozd(B1, B2, X1[i], B3, Yzhel, B4, B5, V, X2[i]);
            cerr << setw(8) << U[V] << " | ";
            // Подача управл. возд. по каналу управления L
            plant_control(L, U[V], plant);
            // Измерение значения
            Y[V] = plant_measure(J, plant);
            // Вывод на экран значений
            /* cerr << "+---+-----------+------------+------------+------------+" << endl;
            cerr << "| " << i << " |" << " " << X1[i] << "    " ;
            cerr << "  " << X2[i] << "    " << "   " << U[i] << "    "; */
            cerr << setw(8) << Y[V] << " | ";
            // Расчёт оценки качества управления и вывод на экран
            f = pow((Y[V] - Yzhel), 2);
            Q[V] = (Q[V] + f ) / N;
            cerr << setw(10) << Q[V] << " |" << endl;
            cerr << "+--------+---------+----------+------------+" << endl;
        }
        cerr << endl;
    }
    return 0;
}
