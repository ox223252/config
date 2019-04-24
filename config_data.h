#ifndef __CONFIG_DATA_H__
#define __CONFIG_DATA_H__

////////////////////////////////////////////////////////////////////////////////
/// \copiright ox223252, 2017
///
/// This program is free software: you can redistribute it and/or modify it
///     under the terms of the GNU Lesser General Public License published by
///     the Free Software Foundation, either version 2 of the License, or (at
///     your option) any later version.
///
/// This program is distributed in the hope that it will be useful, but WITHOUT
///     ANY WARRANTY; without even the implied of MERCHANTABILITY or FITNESS FOR
///     A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
///     details.
///
/// You should have received a copy of the GNU Lesser General Public License
///     along with this program. If not, see <http://www.gnu.org/licenses/>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// \file config_data.h
/// \brief defines struct that will contain read data from command line of file
/// \author ox223252
/// \date 2017-07
/// \copyright GPLv2
/// \version 0.2
/// \warning NONE
/// \bug NONE
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////
/// \enum CONFIG_TYPE
/// \brief use to specify type of value
////////////////////////////////////////////////////////////////////////////////
#define cT(type) CONFIG_TYPE_##type

typedef enum
{
        CONFIG_TYPE_bool,       ///< boolean
        CONFIG_TYPE_ibool,      ///< inverted boolean, usable to set default
                // value of flag active and reset it using CMD line arg. In
                // other case it'll work like boolean
        CONFIG_TYPE_uint8_t,    ///< uint8_t
        CONFIG_TYPE_uint16_t,   ///< uint16_t
        CONFIG_TYPE_uint32_t,   ///< uint32_t
        CONFIG_TYPE_uint64_t,   ///< uint64_t
        CONFIG_TYPE_int8_t,     ///< int8_t
        CONFIG_TYPE_int16_t,    ///< int16_t
        CONFIG_TYPE_int32_t,    ///< int32_t
        CONFIG_TYPE_int64_t,    ///< int64_t
        CONFIG_TYPE_str,        ///< char []
        CONFIG_TYPE_ptrStr,     ///< char *
        CONFIG_TYPE_float32_t,  ///< float
        CONFIG_TYPE_float,      ///< float
        CONFIG_TYPE_float64_t,  ///< double
        CONFIG_TYPE_double      ///< double
}CONFIG_TYPE;

////////////////////////////////////////////////////////////////////////////////
/// \typedef config_el
/// \brief use to specify what parameter, what type, and where the will be
///     stored
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
        const char *key;                ///< key used in config file
        const CONFIG_TYPE type;         ///< type of value
        const void *value;              ///< pointer on value
        const char *help;               ///< string displayed to help
}config_el;

////////////////////////////////////////////////////////////////////////////////
/// \typedef param_el
/// \brief use to specify what parameter, what type, and where the will be
///     stored
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
        const char *keyLong;            ///< key used in config file
        const char *keyShort;           ///< key used in config file
        uint16_t nbEl;                  ///< nb elements
                                        ///< flag id for a boolean cT(bool), cast to uint8_t
        const CONFIG_TYPE type;         ///< type of value
        void *value;                    ///< pointer on value
        const char *help;               ///< string displayed to help
}param_el;

#endif
