#include "plant.h"
#include "discpp.h"

using namespace std;

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
    // ��������� ����������������� ������.
     const size_t steps = N;
    vector<double> X1(steps);
    vector<double> X2(steps);
    vector<double> Y(steps);
    vector<double> U(steps);
    double Q = 0;
        for (size_t i = 1; i < steps; i++)
        {
            // ��������� ��������
            X1[i] = plant_measure(M1, plant);
            X2[i] = plant_measure(M1, plant);
            // ���������� ������������ �����������
            U[i] = uprl_vozd(B1, B2, X1[i], B3, Yzhel, B4, B5, B6, X2[i]);
            // ������ ������. ����. �� ������ ���������� L
            plant_control(L, U[i], plant);
            // ��������� ��������
            Y[i] = plant_measure(J, plant);
            // ����� �� ����� ��������
            cerr << "X1[" << i << "] = " << X1[i];
            cerr << "X2[" << i << "] = " << X2[i];
            cerr << "U[" << i << "] = " << U[i];
            cerr << "Y[" << i << "] = " << Y[i];
            // ������ ������ �������� ���������� � ����� �� �����
            double f = 0;
            f = pow((Y[i] - Yzhel), 2) / N;
                Q = Q + f;
        }
    cerr << "Quality assessment" << Q;
    return 0;
}
