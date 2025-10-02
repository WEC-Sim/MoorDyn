/*
 * Copyright (c) 2022, Matt Hall
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** @file Moordyn2.h
 * C API for the moordyn::MoorDyn object, which is the main simulation handler
 */

#ifndef __MOORDYN2_H__
#define __MOORDYN2_H__

#include "MoorDynAPI.h"
/* #include "Waves.h"
#include "Seafloor.h"
#include "Point.h"
#include "Rod.h"
#include "Line.h"
#include "Body.h"
#include <stdlib.h>
#include <stdint.h>*/

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef WIN32
#include <windows.h>
#endif

/** @defgroup new_c_api The C API
 *  @{
 */

/// A mooring system instance
typedef struct __MoorDyn* MoorDyn;

/** @brief Creates a MoorDyn instance
 *
 * At the time of creating a new MoorDyn instance, the input file is read
 * and all the objects and structures are created. You must call afterwards
 * MoorDyn_Init() to compute the initial conditions
 *
 * @param infilename The input file, if either NULL or "", then
 * "Mooring/lines.txt" will be considered
 * @return The mooring instance, NULL if errors happened
 */
MoorDyn DECLDIR
MoorDyn_Create(const char* infilename);

/** @brief Compute the initial condition of a MoorDyn system
 *
 * At the time of creating a new MoorDyn instance, the input file is read
 * and all the objects and structures are created. You must call afterwards
 * MoorDyn_Init() to compute the initial conditions
 *
 * @param system The Moordyn system
 * @param x Position vector (6 components per coupled body or cantilevered
 * rod and 3 components per pinned rod or coupled point)
 * @param xd Velocity vector (6 components per coupled body or cantilevered
 * rod and 3 components per pinned rod or coupled point)
 * @return MOORDYN_SUCESS If the mooring system is correctly initialized,
 * an error code otherwise (see @ref moordyn_errors)
 * @note MoorDyn_NCoupledDOF() can be used to know the number of components
 * required for \p x and \p xd
 */
int DECLDIR
MoorDyn_Init(MoorDyn system, const double* x, const double* xd);

/** @brief Runs a time step of the MoorDyn system
 * @param system The Moordyn system
 * @param x Position vector
 * @param xd Velocity vector
 * @param f Output forces
 * @param t Simulation time
 * @param dt Time step
 * @return MOORDYN_SUCESS if the mooring system has correctly evolved, an
 * error code otherwise (see @ref moordyn_errors)
 * @note MoorDyn_NCoupledDOF() can be used to know the number of components
 * required for \p x, \p xd and \p f
 */
int DECLDIR
MoorDyn_Step(MoorDyn system,
             const double* x,
             const double* xd,
             double* f,
             double* t,
             double* dt);

/** @brief Releases MoorDyn allocated resources
 * @param system The Moordyn system
 * @return MOORDYN_SUCESS If the mooring system is correctly destroyed, an
 * error code otherwise (see @ref moordyn_errors)
 */
int DECLDIR
MoorDyn_Close(MoorDyn system);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
