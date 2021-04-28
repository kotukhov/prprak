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
    // ��������� ����������������� ������.
    M1=1;M2=2;L=7;J=30;N=5;
    B1=1;B2=1;B3=5;B4=1;B5=1;B6=-0.013;Yzhel=1;
     const size_t steps = N;
    vector<double> X1(steps);
    vector<double> X2(steps);
    vector<double> Y(steps);
    vector<double> U(steps);
    double Q = 0, f;
        for (size_t i = 1; i < steps + 1; i++)
        {
            // ��������� ��������
            X1[i] = plant_measure(M1, plant);
            X2[i] = plant_measure(M2, plant);
            // ���������� ������������ �����������
            U[i] = uprl_vozd(B1, B2, X1[i], B3, Yzhel, B4, B5, B6, X2[i]);
            // ������ ������. ����. �� ������ ���������� L
            plant_control(L, U[i], plant);
            // ��������� ��������
            Y[i] = plant_measure(J, plant);
            // ����� �� ����� ��������
            cerr << "X1[" << i << "] = " << X1[i] << endl;
            cerr << "X2[" << i << "] = " << X2[i] << endl;
            cerr << "U[" << i << "] = " << U[i] << endl;
            cerr << "Y[" << i << "] = " << Y[i] << endl << endl;
            // ������ ������ �������� ���������� � ����� �� �����
            f = pow((Y[i] - Yzhel), 2) / N;
                Q = Q + f;
        }
    cerr << "Quality assessment = " << Q;
    return 0;
}
