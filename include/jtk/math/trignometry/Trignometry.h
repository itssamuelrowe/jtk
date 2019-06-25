/*
 * Copyright 2018-2019 OneCube
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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