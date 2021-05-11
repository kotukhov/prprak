#include <iostream>
#include <vector>
#include <cmath>
#include "NEWPRAK\prof\plant.h"
#include "NEWPRAK\prof\discpp.h"

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
    cerr << "Enter response value Yzhel";
    enter_double(Yzhel);

    int numB; double Bmax, Bmin, deB;
    cerr << "Chose foef B (1-6)" << endl;
    enter_int(numB);
    cerr << "Enter Bmax " << endl;
    enter_double(Bmax);
    cerr << "Enter Bmin " << endl;
    enter_double(Bmin);
    cerr << "Enter step(delta) " << endl;
    enter_double(deB);
    // ��������� ����������������� ������.
    /*M1=1;M2=2;L=7;J=30;N=3;  // ��� N=1;Yzhel=553; Q ~ 0 //
    B1=1;B2=1;B3=5;B4=1;B5=1;B6=-0.013;Yzhel=553; */
     const size_t steps = N;
    vector<double> X1(steps);
    vector<double> X2(steps);
     //vector<double> Y(steps);
    /* vector<double> U(C); */
    double f;
        /* cerr << "+---+" << "-----------+" << "------------+" << "------------+" << "------------+" << endl;
            cerr << "| N |" << "    X1     |" << "     X2     |" << "     U      |" << "     Y      |" << endl; */
        for (size_t i = 1; i < steps + 1; i++)
        {
            // ��������� ��������
            X1[i] = plant_measure(M1, plant);
            X2[i] = plant_measure(M2, plant);
            // ���������� ������������ �����������
            C = ((Bmax - Bmin) / deB ) + 1;
            vector<double> U(C);
            vector<double> Y(C);
            vector<double> Q(C);
            cerr << "+----+---------+---------+" << endl;
            cerr << "| B" << numB << "  " << "     U     " << "    Y    " << "     Q     " << endl;
    for (V = Bmin; V <= Bmax; V + deB)
    {
        cerr << "| " << V << " ";
            if (numB == 1)
            {
                U[V] = uprl_vozd(V, B2, X1[i], B3, Yzhel, B4, B5, B6, X2[i]);
        }
       if (numB == 2)
            {
                U[V] = uprl_vozd(B1, V, X1[i], B3, Yzhel, B4, B5, B6, X2[i]);
        }
        if (numB == 3)
            {
                U[V] = uprl_vozd(B1, B2, X1[i], V, Yzhel, B4, B5, B6, X2[i]);
        }
        if (numB == 4)
            {
                U[V] = uprl_vozd(B1, B2, X1[i], B3, Yzhel, V, B5, B6, X2[i]);
        }
        if (numB == 5)
            {

                U[V] = uprl_vozd(B1, B2, X1[i], B3, Yzhel, B4, V, B6, X2[i]);
        }
        if (numB == 6)
            {
                U[V] = uprl_vozd(B1, B2, X1[i], B3, Yzhel, B4, B5, V, X2[i]);
        }

        cerr << "    " << U[V] << "   ";

            // ������ ������. ����. �� ������ ���������� L
            plant_control(L, U[V], plant);
            // ��������� ��������
            Y[V] = plant_measure(J, plant);
            // ����� �� ����� ��������
            /* cerr << "+---+-----------+------------+------------+------------+" << endl;
            cerr << "| " << i << " |" << " " << X1[i] << "    " ;
            cerr << "  " << X2[i] << "    " << "   " << U[i] << "    "; */
            cerr << "   " << Y[V] << "    " << endl;
            // ������ ������ �������� ���������� � ����� �� �����
            f = pow((Y[V] - Yzhel), 2);
                Q[V] = Q[V] + f;
    }
        }
        cerr << "+---+" << "-----------+" << "------------+" << "------------+" << "------------+" << endl;
    cerr << "Quality assessment = " << Q / N;
    return 0;
}
