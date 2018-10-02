/*
 *                              Jez Toolkit (JTK)
 *     Copyright (C) 2018 OneCube Software Solutions. All rights reserved.
 *
 * This file is part of Jez Toolkit Free Edition, version 1.0.
 *
 * See the file "LICENSE" included in the distribution for the terms and conditions,
 * or visit http://www.onecube.in/jtk/free-license.
 *
 * IMPORTANT NOTE: You may NOT copy the content of this file, either partially
 * or fully, into your source code.
 */

// Monday, July 23, 2018

#include <jtk/math/Math.h>

int32_t jtk_Math_findPowerOfTwo(int32_t n) {
	int32_t r = 1;
	while (r < n) {
		r <<= 1;
	}
	return r;
}
