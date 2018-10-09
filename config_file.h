#ifndef __CONFIG_FILE_H__
#define __COFNIG_FILE_H__


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
/// \file config_file.h
/// \brief library to parse file and store result in formated struct
/// \author ox223252
/// \date 2017-07
/// \copyright GPLv2
/// \version 0.2
/// \warning NONE
/// \bug NONE
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#include "config_data.h"

////////////////////////////////////////////////////////////////////////////////
/// \fn int readConfigFile ( const char * file, const config_el param[] )
/// \param[ in ] file: file name which contain data
/// \param[ out ] param: strut that will contain read data
/// \brief this one will parse file which contain config and store it in
///     internal struct
/// \return if 0 OK then see errno for maore details
////////////////////////////////////////////////////////////////////////////////
int readConfigFile ( const char * file, const config_el param[] );

////////////////////////////////////////////////////////////////////////////////
/// \fn int writeConfigFile ( const char * file, const config_el param[] )
/// \param[ in ] file: file name that will contain data
/// \param[ out ] param: strut that will contain read data
/// \brief this one will write config stored in memory in a file
/// \return if 0 OK then see errno for maore details
////////////////////////////////////////////////////////////////////////////////
int writeConfigFile ( const char * file, const config_el param[] );

////////////////////////////////////////////////////////////////////////////////
/// \fn void writeConfigFile ( FILE * f, const config_el param[] )
/// \param[ in ] f: file destriptor that will contain data
/// \param[ out ] param: strut that will contain read data
/// \brief this one will write config stored in memory in a file
////////////////////////////////////////////////////////////////////////////////
void writeConfigFileDescriptor ( FILE * f, const config_el param[] );

////////////////////////////////////////////////////////////////////////////////
/// \fn int updateConfigFile ( const char * file, const config_el param[] )
/// \param[ in ] file: file name that will be updated
/// \param[ out ] param: strut that will contain read data
/// \brief this one will write config stored in memory in a file
/// \return if 0 OK then see errno for maore details
////////////////////////////////////////////////////////////////////////////////
int updateConfigFile ( const char * file, const config_el param[] );

#endif
