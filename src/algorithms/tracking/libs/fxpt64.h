/*!
 * \file fxpt64.h
 * \brief Utility functions for fixed point 64 bit arithmetic
 * \authors <ul>
 *          <li> Cillian O'Driscoll, 2015. cillian.odriscoll(at)gmail.com
 *          </ul>
 *
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2015  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GNSS-SDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */

#ifndef GNSS_SDR_FXPT64_H_
#define GNSS_SDR_FXPT64_H_
#include <cstdint>

int64_t double_to_fxpt64( double in, unsigned int frac_len = 32 );
double fxpt64_to_double( int64_t in, unsigned int frac_len = 32 );

#endif