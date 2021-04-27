#include "plant.h"
#include "discpp.h"

using namespace std;

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
    cerr << "Enter numbers of sencors";
    enter_int(M1);
    enter_int(M2);
    cerr << "Enter L, J, N";
    enter_int(L);
    enter_int(J);
    enter_int(N);
    cerr << "Enter coefficients";
    enter_double(B1);
    enter_double(B2);
    enter_double(B3);
    enter_double(B4);
    enter_double(B5);
    enter_double(B6);
    cerr << "Enter response value";
    enter_double(Yzhel);
    // Получение экспериментальных данных.
     const size_t steps = N;
    vector<double> X1(steps);
    vector<double> X2(steps);
    vector<double> Y(steps);
    vector<double> U(steps);
    double Q = 0;
        for (size_t i = 1; i < steps; i++)
        {
            // Измерение значений
            X1[i] = plant_measure(M1, plant);
            X2[i] = plant_measure(M1, plant);
            // Вычисление управляющего воздействия
            U[i] = uprl_vozd(B1, B2, X1[i], B3, Yzhel, B4, B5, B6, X2[i]);
            // Подача управл. возд. по каналу управления L
            plant_control(L, U[i], plant);
            // Измерение значения
            Y[i] = plant_measure(J, plant);
            // Вывод на экран значений
            cerr << "X1[" << i << "] = " << X1[i];
            cerr << "X2[" << i << "] = " << X2[i];
            cerr << "U[" << i << "] = " << U[i];
            cerr << "Y[" << i << "] = " << Y[i];
            // Расчёт оценки качества управления и вывод на экран
            double f = 0;
            f = pow((Y[i] - Yzhel), 2) / N;
                Q = Q + f;
        }
    cerr << "Quality assessment" << Q;
    return 0;
}
