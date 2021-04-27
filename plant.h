/*#ifndef PLANT_H_INCLUDED*/
// #define PLANT_H_INCLUDED

#include <iostream>
#include <vector>
#include <cmath>
#ifdef __cplusplus
extern "C" {
#endif

	/** @brief Описание состояния объекта управления или исследования. */
	typedef double Plant[53];

	/** @brief Инициализирует состояние объекта управления или исследования. */
	void plant_init(Plant plant);

	/**
	 * @brief Считывает показатели объекта исследования.
	 * @param kanal Канал измерений.
	 * @return Значение показателя.
	 */
	double plant_measure(int kanal, Plant plant);

	/**
	 * @brief Подает управляющее воздействие на объект.
	 * @param kanal Канал управления (7..10).
	 * @param upr Величина управляющего воздействия.
	 * @param plant Массив данных, описывающий состояние объекта.
	 */
	void plant_control(int kanal, double upr, Plant plant);

	void enter_int(size_t& a);
	void enter_double(double& a);
	double uprl_vozd(double a, double b, double c, double d, double e, double f, double g, double h, double p);

#ifdef __cplusplus
}  /* extern "C" */

#endif // PLANT_H_INCLUDED
