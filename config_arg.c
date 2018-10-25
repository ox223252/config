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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "config_arg.h"

static const uint8_t maxArgSize = 80;

int readConfigArgs ( const int argc,  char * const argv[], config_el param[] )
{
	int index;
	int numArg = 1;
	int loopCounter;
	while ( 1 )
	{
		if ( numArg >= argc )
		{
			break;
		}
		index = -1;
		do
		{
			index++;
		}
		while ( ( argv[ numArg ][ index ] != '=' ) &&
			( argv[ numArg ][ index ] != '\0' ) &&
			( index < maxArgSize ) );

		if ( argv[ numArg ][ index ] != '=' )
		{
			numArg++;
			continue;
		}
		else
		{
			argv[ numArg ][ index ] = '\0';
		}

		for ( loopCounter = 0; param[ loopCounter ].key != NULL; loopCounter++ )
		{
			if ( !param[ loopCounter ].value )
			{ // in case of a null value pointer
				continue;
			}
			
			if ( !strcmp ( argv[ numArg ], param[ loopCounter ].key ) )
			{
				switch( param[ loopCounter ].type )
				{
					case CONFIG_TYPE_bool:
					case CONFIG_TYPE_uint8_t:
					{
						*( uint8_t* )( param[ loopCounter ].value ) = (uint8_t)atol ( &argv[ numArg ][ index + 1 ] );
						break;
					}
					case CONFIG_TYPE_uint16_t:
					{
						*( uint16_t* )( param[ loopCounter ].value ) = (uint16_t)atol ( &argv[ numArg ][ index + 1 ] );
						break;
					}
					case CONFIG_TYPE_uint32_t:
					{
						*( uint32_t* )( param[ loopCounter ].value ) = (uint32_t)atol ( &argv[ numArg ][ index + 1 ] );
						break;
					}
					case CONFIG_TYPE_uint64_t:
					{
						*( uint64_t* )( param[ loopCounter ].value ) = (uint64_t)atol ( &argv[ numArg ][ index + 1 ] );
						break;
					}
					case CONFIG_TYPE_int8_t:
					{
						*( int8_t* )( param[ loopCounter ].value ) = (int8_t)atol ( &argv[ numArg ][ index + 1 ] );
						break;
					}
					case CONFIG_TYPE_int16_t:
					{
						*( int16_t* )( param[ loopCounter ].value ) = (int16_t)atol ( &argv[ numArg ][ index + 1 ] );
						break;
					}
					case CONFIG_TYPE_int32_t:
					{
						*( int32_t* )( param[ loopCounter ].value ) = (int32_t)atol ( &argv[ numArg ][ index + 1 ] );
						break;
					}
					case CONFIG_TYPE_int64_t:
					{
						*( int64_t* )( param[ loopCounter ].value ) = (int64_t)atol ( &argv[ numArg ][ index + 1 ] );
						break;
					}
					case CONFIG_TYPE_str:
					{
						if ( (*(char **)param[ loopCounter ].value) == NULL )
						{
							(*(char **)param[ loopCounter ].value) = (char *)&argv[ numArg ][ index + 1 ];
						}
						else
						{
							sprintf ( (char *)param[ loopCounter ].value, "%s", &argv[ numArg ][ index + 1 ] );
						}
						break;
					}
					case CONFIG_TYPE_float:
					case CONFIG_TYPE_float32_t:
					{
						*( float* )( param[ loopCounter ].value ) = ( float ) atof ( &argv[ numArg ][ index + 1 ] );
						break;
					}
					case CONFIG_TYPE_double:
					case CONFIG_TYPE_float64_t:
					{
						*( double* )( param[ loopCounter ].value ) = atof ( &argv[ numArg ][ index + 1 ] );
						break;
					}
					default:
					{
						break;
					}
				}

				argv[ numArg ][ index ] = '=';
				break;
			}
		}
		numArg++;
	}
	return ( 0 );
}

int helpConfigArgs ( const config_el param[] )
{
	int loopCounter;

	printf ( "    usage : key=value key2=value2\n" );
	printf ( "%20s : %s\n", "key", "help or type" );

	for ( loopCounter = 0; param[ loopCounter ].key != NULL; loopCounter++ )
	{
		if ( param[ loopCounter ].help )
		{
			printf ( "%20s : %s\n", param[ loopCounter ].key, param[ loopCounter ].help );
		}
		else
		{
			printf ( "%20s : ", param[ loopCounter ].key );
			switch ( param[ loopCounter ].type )
			{
				case CONFIG_TYPE_bool:
				case CONFIG_TYPE_int8_t:
				{
					printf ( "int8_t\n" );
					break;
				}
				case CONFIG_TYPE_int16_t:
				{
					printf ( "int16_t\n" );
					break;
				}
				case CONFIG_TYPE_int32_t:
				{
					printf ( "int32_t\n" );
					break;
				}
				case CONFIG_TYPE_int64_t:
				{
					printf ( "int64_t\n" );
					break;
				}
				case CONFIG_TYPE_uint8_t:
				{
					printf ( "uint8_t\n" );
					break;
				}
				case CONFIG_TYPE_uint16_t:
				{
					printf ( "uint16_t\n" );
					break;
				}
				case CONFIG_TYPE_uint32_t:
				{
					printf ( "uint32_t\n" );
					break;
				}
				case CONFIG_TYPE_uint64_t:
				{
					printf ( "uint64_t\n" );
					break;
				}
				case CONFIG_TYPE_str:
				{
					printf ( "string\n" );
					break;
				}
				case CONFIG_TYPE_float:
				case CONFIG_TYPE_float32_t:
				{
					printf ( "float\n" );
					break;
				}
				case CONFIG_TYPE_double:
				case CONFIG_TYPE_float64_t:
				{
					printf ( "double\n" );
					break;
				}
				default:
				{
					break;
				}
			}
		}
	}

	return ( 0 );
}

int helpParamArgs ( const param_el param[] )
{
	int loopCounter;

	printf ( "    usage : key value value2 key2 value3 ...\n" );
	printf ( "%15s : %3s :  %s : %s\n", "key", "key", "nb elements", "help or type" );
	
	for ( loopCounter = 0; ( param[ loopCounter ].keyLong != NULL ) || ( param[ loopCounter ].keyShort != NULL ); loopCounter++ )
	{
		if ( param[ loopCounter ].type == CONFIG_TYPE_bool )
		{ // for boolean print only key
			printf ( "%15s : %3s : bool : ", param[ loopCounter ].keyLong, param[ loopCounter ].keyShort );
		}
		else if ( param[ loopCounter ].nbEl )
		{ // print key and nb elements
			printf ( "%15s : %3s : %4d : ", param[ loopCounter ].keyLong, param[ loopCounter ].keyShort, param[ loopCounter ].nbEl );
		}

		if ( param[ loopCounter ].help )
		{ // print help if defined
			printf ( "%s\n", param[ loopCounter ].help );
		}
		else
		{ // print type if help not defined
			switch ( param[ loopCounter ].type )
			{
				case CONFIG_TYPE_int8_t:
				{
					printf ( "int8_t" );
					break;
				}
				case CONFIG_TYPE_int16_t:
				{
					printf ( "int16_t" );
					break;
				}
				case CONFIG_TYPE_int32_t:
				{
					printf ( "int32_t" );
					break;
				}
				case CONFIG_TYPE_int64_t:
				{
					printf ( "int64_t" );
					break;
				}
				case CONFIG_TYPE_uint8_t:
				{
					printf ( "uint8_t" );
					break;
				}
				case CONFIG_TYPE_uint16_t:
				{
					printf ( "uint16_t" );
					break;
				}
				case CONFIG_TYPE_uint32_t:
				{
					printf ( "uint32_t" );
					break;
				}
				case CONFIG_TYPE_uint64_t:
				{
					printf ( "uint64_t" );
					break;
				}
				case CONFIG_TYPE_str:
				{
					printf ( "string" );
					break;
				}
				case CONFIG_TYPE_float:
				case CONFIG_TYPE_float32_t:
				{
					printf ( "float" );
					break;
				}
				case CONFIG_TYPE_double:
				case CONFIG_TYPE_float64_t:
				{
					printf ( "double" );
					break;
				}
				case CONFIG_TYPE_bool:
				{
					printf ( "bool" );
					break;
				}
				default:
				{
					break;
				}
			}
			printf ( "\n" );
		}
	}

	return ( 0 );
}

int readParamArgs ( const int argc, char * const argv[], param_el param[] )
{
	int numArg = 1;
	int loopCounter = 0;
	int lastCounter = 0;
	int paramId = -1;

	while ( numArg < argc )
	{
		if ( argv[ numArg ][ 0 ] == '-' )
		{ // maybe it is a key
			lastCounter = loopCounter;
			for ( loopCounter = 0; ( param[ loopCounter ].keyLong != NULL ) || ( param[ loopCounter ].keyShort != NULL ); loopCounter++ )
			{ // verify exiting key
				if ( ( param[ loopCounter ].keyLong != NULL ) &&
					!strcmp ( argv[ numArg ], param[ loopCounter ].keyLong ) ||
					( param[ loopCounter ].keyShort != NULL ) &&
					!strcmp ( argv[ numArg ], param[ loopCounter ].keyShort ) )
				{ // key vaild
					paramId = 0;
					if ( param[ loopCounter ].type == CONFIG_TYPE_bool )
					{
						if ( param[ loopCounter ].value != NULL )
						{
							* (uint8_t *) param[ loopCounter ].value |= param[ loopCounter ].nbEl;
						}
					}
					break;
				}
			}

			if ( ( param[ loopCounter ].keyLong == NULL ) &&
				( param[ loopCounter ].keyShort == NULL ) )
			{ // invalid key
				loopCounter = lastCounter;

				if ( !strcmp ( argv[ numArg ], "--" ) )
				{ // by default "--" stop parsing
					return ( 0 );
				}
			}
			else
			{ // if we found a valid key we will test next arg
				if ( param[ loopCounter ].value == NULL )
				{ // if no have value pointer, not allow param test
					paramId = -1;
				}
				numArg++;
				continue;
			}
		}

		if ( paramId == -1 )
		{ // we haven't already found a key
			numArg++;
			continue;
		}

		if (  param[ loopCounter ].nbEl == 1 )
		{
			// we only get one param, next we will need to found a new key
			paramId = -1;
			
			if ( param[ loopCounter ].value == NULL )
			{ // should never be occure
				continue;
			}

			switch( param[ loopCounter ].type )
			{
				case CONFIG_TYPE_bool:
				case CONFIG_TYPE_uint8_t:
				{
					*( uint8_t* )( param[ loopCounter ].value ) = atol ( argv[ numArg ] );
					break;
				}
				case CONFIG_TYPE_uint16_t:
				{
					*( uint16_t* )( param[ loopCounter ].value ) = atol ( argv[ numArg ] );
					break;
				}
				case CONFIG_TYPE_uint32_t:
				{
					*( uint32_t* )( param[ loopCounter ].value ) = atol ( argv[ numArg ] );
					break;
				}
				case CONFIG_TYPE_uint64_t:
				{
					*( uint64_t* )( param[ loopCounter ].value ) = atol ( argv[ numArg ] );
					break;
				}
				case CONFIG_TYPE_int8_t:
				{
					*( int8_t* )( param[ loopCounter ].value ) = atol ( argv[ numArg ] );
					break;
				}
				case CONFIG_TYPE_int16_t:
				{
					*( int16_t* )( param[ loopCounter ].value ) = atol ( argv[ numArg ] );
					break;
				}
				case CONFIG_TYPE_int32_t:
				{
					*( int32_t* )( param[ loopCounter ].value ) = atol ( argv[ numArg ] );
					break;
				}
				case CONFIG_TYPE_int64_t:
				{
					*( int64_t* )( param[ loopCounter ].value ) = atol ( argv[ numArg ] );
					break;
				}
				case CONFIG_TYPE_ptrStr:
				{
					*(char **) param[ loopCounter ].value = (void *)argv[ numArg ];
					break;
				}
				case CONFIG_TYPE_str:
				{
					sprintf ( (char *)param[ loopCounter ].value, "%s", argv[ numArg ] );
					break;
				}
				case CONFIG_TYPE_float:
				case CONFIG_TYPE_float32_t:
				{
					*(float *)param[ loopCounter ].value = ( float ) atof ( argv[ numArg ] );
					break;
				}
				case CONFIG_TYPE_double:
				case CONFIG_TYPE_float64_t:
				{
					*(double *)param[ loopCounter ].value = atof ( argv[ numArg ] );
					break;
				}
				default:
				{
					break;
				}
			}
		}
		else if ( paramId < param[ loopCounter ].nbEl )
		{
			if ( param[ loopCounter ].value == NULL )
			{ // should never be occure
				paramId = -1;
				continue;
			}

			switch( param[ loopCounter ].type )
			{
				case CONFIG_TYPE_bool:
				case CONFIG_TYPE_uint8_t:
				{
					(( uint8_t* ) param[ loopCounter ].value)[ paramId ] = atol ( argv[ numArg ] );
					break;
				}
				case CONFIG_TYPE_uint16_t:
				{
					(( uint16_t* ) param[ loopCounter ].value)[ paramId ] = atol ( argv[ numArg ] );
					break;
				}
				case CONFIG_TYPE_uint32_t:
				{
					(( uint32_t* ) param[ loopCounter ].value)[ paramId ] = atol ( argv[ numArg ] );
					break;
				}
				case CONFIG_TYPE_uint64_t:
				{
					(( uint64_t* ) param[ loopCounter ].value)[ paramId ] = atol ( argv[ numArg ] );
					break;
				}
				case CONFIG_TYPE_int8_t:
				{
					(( int8_t* ) param[ loopCounter ].value)[ paramId ] = atol ( argv[ numArg ] );
					break;
				}
				case CONFIG_TYPE_int16_t:
				{
					(( int16_t* ) param[ loopCounter ].value)[ paramId ] = atol ( argv[ numArg ] );
					break;
				}
				case CONFIG_TYPE_int32_t:
				{
					(( int32_t* ) param[ loopCounter ].value)[ paramId ] = atol ( argv[ numArg ] );
					break;
				}
				case CONFIG_TYPE_int64_t:
				{
					(( int64_t* ) param[ loopCounter ].value)[ paramId ] = atol ( argv[ numArg ] );
					break;
				}
				case CONFIG_TYPE_ptrStr:
				{
					((char **) param[ loopCounter ].value)[ paramId ] = (void *)argv[ numArg ];
					break;
				}
				case CONFIG_TYPE_str:
				{
					sprintf ( ((char **) param[ loopCounter ].value)[ paramId ], "%s", argv[ numArg ] );
					break;
				}
				case CONFIG_TYPE_float32_t:
				{
					((float *) param[ loopCounter ].value)[ paramId ] = ( float ) atof ( argv[ numArg ] );
					break;
				}
				case CONFIG_TYPE_float64_t:
				{
					((double *) param[ loopCounter ].value)[ paramId ] = atof ( argv[ numArg ] );
					break;
				}
				default:
				{
					break;
				}
			}
			
			paramId++;

			if ( paramId == param[ loopCounter ].nbEl )
			{ // we read all of objects
				paramId = -1;
			}
		}
		numArg++;
	}

	return ( 0 );
}
