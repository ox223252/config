#ifndef __CONFIG_ARG_H__
#define __CONFIG_ARG_H__

////////////////////////////////////////////////////////////////////////////////
/// \copiright ox223252, 2017
///
/// This program is free software: you can redistribute it and/or modify it
///     under the terms of the GNU General Public License published by the Free
///     Software Foundation, either version 2 of the License, or (at your
///     option) any later version.
///
/// This program is distributed in the hope that it will be useful, but WITHOUT
///     ANY WARRANTY; without even the implied of MERCHANTABILITY or FITNESS FOR
///     A PARTICULAR PURPOSE. See the GNU General Public License for more
///     details.
///
/// You should have received a copy of the GNU General Public License along with
///     this program. If not, see <http://www.gnu.org/licenses/>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// \file config_arg.h
/// \brief library to parse commands line and store result in formated struct
/// \author ox223252
/// \date 2017-07
/// \copyright GPLv2
/// \version 0.3
/// \warning NONE
/// \bug NONE
////////////////////////////////////////////////////////////////////////////////

#include "config_data.h"

////////////////////////////////////////////////////////////////////////////////
/// \fn int readConfigArgs ( const int argc,  char * const argv[],
///     config_el param[] )
/// \param[ in ] argc: number of arg in argv,
/// \param[ in ] argv: arg passed by commande line,
/// \param[ in/out ] param: out struct that will contain read params,
/// \brief this function will parse args passed by commande line and copare then
///     with data configured in struct param.
/// \return 0
////////////////////////////////////////////////////////////////////////////////
int readConfigArgs ( const int argc,  char * const argv[], config_el param[] );

////////////////////////////////////////////////////////////////////////////////
/// \fn int helpConfigArgs ( const config_el param[] )
/// \param[ in ] param: struct which contain read params,
/// \brief this function will display data on the param struct to help user to
///     understand how to configure that
/// \return 0
////////////////////////////////////////////////////////////////////////////////
int helpConfigArgs ( const config_el param[] );

////////////////////////////////////////////////////////////////////////////////
/// \fn int helpParamArgs ( const param_el param[] )
/// \param[ in ] param: struct which contain read params,
/// \brief this function will display data on the param struct to help user to
///     understand how to configure that
/// \return 0
////////////////////////////////////////////////////////////////////////////////
int helpParamArgs ( const param_el param[] );

////////////////////////////////////////////////////////////////////////////////
/// \fn int readParamArgs ( const int argc, char * const argv[],
///     param_el param[] )
/// \param[ in ] argc: number of arg in argv,
/// \param[ in ] argv: arg passed by commande line,
/// \param[ in ] param: out struct that will contain read params,
/// \brief this function will parse args passed by commande line and copare then
///     with data configured in struct param.
/// \return 0
////////////////////////////////////////////////////////////////////////////////
int readParamArgs ( const int argc, char * const argv[], param_el param[] );

#endif
