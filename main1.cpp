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
    // ������������� ��.
    Plant plant;
    plant_init(plant);
    // ���������� �������� ������
    size_t M1, M2; // ������ ������������ ��������
    size_t L; // ����� ������ ����������
    size_t J; // ����� ������ ��������� �������
    size_t N; // ����� �������� ��������� ����������� �����������
    double B1, B2, B3, B4, B5, B6; // ������������, ������������ ����� ����������
    double Yzhel; // �������� �������� ������� �������
    // ���� �������� ������
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
    cerr << "Enter response value Yzhel" << endl;
    cerr << "Yzhel = ";
    enter_double(Yzhel);
    size_t numB;
    double Bmax, Bmin, deB;
    cerr << "Chose koef B (1-6)" << endl;
    enter_int(numB);
    cerr << "Enter Bmax " << endl;
    enter_double(Bmax);
    cerr << "Enter Bmin " << endl;
    enter_double(Bmin);
    cerr << "Enter step(delta) " << endl;
    enter_double(deB);
    // ��������� ����������������� ������.
    const size_t steps = N;
    double C = ((Bmax - Bmin) / deB ) + 1;
    cerr << "+-------+-------------+" << endl;
    cerr /*<< "|" << setw(6) << "NOMER" */ << "|" << setw(6) << "B" << numB << "|" << setw(13) << "Q" << "|" << endl;
    cerr << "+-------+-------------+" << endl;
    for (double V = Bmin; V <= Bmax; V = V + deB)
    {
        double f = 0,Q = 0;
        vector<double> X1(steps);
        vector<double> X2(steps);
        vector<double> U(steps);
        vector<double> Y(steps);
        cerr << "|" << setw(7) << V << "|";
        for (size_t i = 0; i < steps ; i++)
        {
            // ��������� ��������
            X1[i] = plant_measure(M1, plant);
            X2[i] = plant_measure(M2, plant);
            if (numB == 1)
                U[i] = uprl_vozd(V, B2, X1[i], B3, Yzhel, B4, B5, B6, X2[i]);
            if (numB == 2)
                U[i] = uprl_vozd(B1, V, X1[i], B3, Yzhel, B4, B5, B6, X2[i]);
            if (numB == 3)
                U[i] = uprl_vozd(B1, B2, X1[i], V, Yzhel, B4, B5, B6, X2[i]);
            if (numB == 4)
                U[i] = uprl_vozd(B1, B2, X1[i], B3, Yzhel, V, B5, B6, X2[i]);
            if (numB == 5)
                U[i] = uprl_vozd(B1, B2, X1[i], B3, Yzhel, B4, V, B6, X2[i]);
            if (numB == 6)
                U[i] = uprl_vozd(B1, B2, X1[i], B3, Yzhel, B4, B5, V, X2[i]);
            // ������ ������. ����. �� ������ ���������� L
            plant_control(L, U[i], plant);
            // ��������� ��������
            Y[i] = plant_measure(J, plant);
            // ������ ������ �������� ���������� � ����� �� �����
            f = pow((Y[i] - Yzhel), 2);
            Q = (Q + f );
        }
        cerr << setw(13) << Q / N << "|" << endl;
        cerr << "+-------+-------------+" << endl;
    }
    return 0;
}

