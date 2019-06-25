// Sunday, September 06, 2018

#ifndef JTK_MATH_TRIGNOMETRY_TRIGNOMETRY_H
#define JTK_MATH_TRIGNOMETRY_TRIGNOMETRY_H

#include <jtk/Configuration.h>
#include <jtk/units/SiUnit.h>

/*******************************************************************************
 * Trignometry                                                                 *
 *******************************************************************************/

/* Cosine */

/**
 * @memberof Trignometry
 */
double jtk_Trignometry_cosine(double angle);

/**
 * @memberof Trignometry
 */
double jtk_Trignometry_cosineEx(double angle, jtk_SiUnit_t unit);

/* Cotangent */

/**
 * @memberof Trignometry
 */
double jtk_Trignometry_cotangent(double angle);

/**
 * @memberof Trignometry
 */
double jtk_Trignometry_cotangentEx(double angle, jtk_SiUnit_t unit);

/* Secant */

/**
 * @memberof Trignometry
 */
double jtk_Trignometry_secant(double angle);

/**
 * @memberof Trignometry
 */
double jtk_Trignometry_secantEx(double angle, jtk_SiUnit_t unit);

/* Sine */

/**
 * @memberof Trignometry
 */
double jtk_Trignometry_sine(double angle);

/**
 * @memberof Trignometry
 */
double jtk_Trignometry_sineEx(double angle, jtk_SiUnit_t unit);

/* Tangent */

/**
 * @memberof Trignometry
 */
double jtk_Trignometry_tangent(double angle);

/**
 * @memberof Trignometry
 */
double jtk_Trignometry_tangentEx(double angle, jtk_SiUnit_t unit);

#endif /* JTK_MATH_TRIGNOMETRY_TRIGNOMETRY_H */