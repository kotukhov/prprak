/*#ifndef PLANT_H_INCLUDED*/
// #define PLANT_H_INCLUDED

#include <iostream>
#include <vector>
#include <cmath>
#ifdef __cplusplus
extern "C" {
#endif

	/** @brief �������� ��������� ������� ���������� ��� ������������. */
	typedef double Plant[53];

	/** @brief �������������� ��������� ������� ���������� ��� ������������. */
	void plant_init(Plant plant);

	/**
	 * @brief ��������� ���������� ������� ������������.
	 * @param kanal ����� ���������.
	 * @return �������� ����������.
	 */
	double plant_measure(int kanal, Plant plant);

	/**
	 * @brief ������ ����������� ����������� �� ������.
	 * @param kanal ����� ���������� (7..10).
	 * @param upr �������� ������������ �����������.
	 * @param plant ������ ������, ����������� ��������� �������.
	 */
	void plant_control(int kanal, double upr, Plant plant);

	void enter_int(size_t& a);
	void enter_double(double& a);
	double uprl_vozd(double a, double b, double c, double d, double e, double f, double g, double h, double p);

#ifdef __cplusplus
}  /* extern "C" */

#endif // PLANT_H_INCLUDED
