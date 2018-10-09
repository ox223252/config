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

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "config_file.h"

int readConfigFile ( const char * file, const config_el param[] )
{
	FILE *f;
	char key[81];
	int tmp;
	int index;
	int loopCounter;

	f = fopen ( file, "r" );

	#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
	if ( !f )
	{
		return ( __LINE__ );
	}
	#pragma GCC diagnostic pop

	while ( 1 )
	{
		tmp = fscanf ( f , "%80[^\n]\n", key );

		if ( tmp < 0 )
		{
			break;
		}

		if ( key[0] == '#' )
		{
			continue;
		}

		index = -1;
		do
		{
			index++;
		}
		while ( ( key[ index ] != '=' ) &&
			( key[ index ] != '\0' ) &&
			( index < 80 ) );

		if ( key[ index ] != '=' )
		{
			continue;
		}
		else
		{
			key[ index ] = '\0';
		}

		for ( loopCounter = 0; param[ loopCounter ].key != NULL; loopCounter++ )
		{
			if ( !param[ loopCounter ].value )
			{ // in case of a null value pointer
				continue;
			}

			if ( !strcmp ( key, param[ loopCounter ].key ) )
			{
				switch( param[ loopCounter ].type )
				{
					case CONFIG_TYPE_bool:
					case CONFIG_TYPE_uint8_t:
					{
						*( uint8_t* )( param[ loopCounter ].value ) = (uint8_t)atol ( &key[ index + 1 ] );
						break;
					}
					case CONFIG_TYPE_uint16_t:
					{
						*( uint16_t* )( param[ loopCounter ].value ) = (uint16_t)atol ( &key[ index + 1 ] );
						break;
					}
					case CONFIG_TYPE_uint32_t:
					{
						*( uint32_t* )( param[ loopCounter ].value ) = (uint32_t)atol ( &key[ index + 1 ] );
						break;
					}
					case CONFIG_TYPE_uint64_t:
					{
						*( uint64_t* )( param[ loopCounter ].value ) = (uint64_t)atol ( &key[ index + 1 ] );
						break;
					}
					case CONFIG_TYPE_int8_t:
					{
						*( int8_t* )( param[ loopCounter ].value ) = (int8_t)atol ( &key[ index + 1 ] );
						break;
					}
					case CONFIG_TYPE_int16_t:
					{
						*( int16_t* )( param[ loopCounter ].value ) = (int16_t)atol ( &key[ index + 1 ] );
						break;
					}
					case CONFIG_TYPE_int32_t:
					{
						*( int32_t* )( param[ loopCounter ].value ) = (int32_t)atol ( &key[ index + 1 ] );
						break;
					}
					case CONFIG_TYPE_int64_t:
					{
						*( int64_t* )( param[ loopCounter ].value ) = (int64_t)atol ( &key[ index + 1 ] );
						break;
					}
					case CONFIG_TYPE_str:
					{
						sprintf ( (char *)param[ loopCounter ].value, "%s", &key[ index + 1 ] );
						break;
					}
					case CONFIG_TYPE_float:
					case CONFIG_TYPE_float32_t:
					{
						*( float* )( param[ loopCounter ].value ) = ( float ) atof ( &key[ index + 1 ] );
						break;
					}
					case CONFIG_TYPE_double:
					case CONFIG_TYPE_float64_t:
					{
						*( double* )( param[ loopCounter ].value ) = atof ( &key[ index + 1 ] );
						break;
					}
					default:
					{
						break;
					}
				}
				break;
			}
		}
	}

	if ( fclose ( f ) )
	{
		return ( __LINE__ );
	}

	return ( 0 );
}

int writeConfigFile ( const char * file, const config_el param[] )
{
	FILE *f;

	f = fopen ( file, "r" );
	
	#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
	if ( !f )
	{
		return ( __LINE__ );
	}
	#pragma GCC diagnostic pop

	writeConfigFileDescriptor ( f, param );

	if ( fclose ( f ) )
	{
		return ( __LINE__ );
	}

	return ( 0 );
}

void writeConfigFileDescriptor ( FILE * f, const config_el param[] )
{
	int loopCounter;

	for ( loopCounter = 0; param[ loopCounter ].key != NULL ; loopCounter++ )
	{
		switch( param[ loopCounter ].type )
		{
			case CONFIG_TYPE_bool:
			case CONFIG_TYPE_uint8_t:
			{
				fprintf ( f, "%s=%" PRIu8 "\n", param[ loopCounter ].key, *( uint8_t* )( param[ loopCounter ].value ) );
				break;
			}
			case CONFIG_TYPE_uint16_t:
			{
				fprintf ( f, "%s=%" PRIu16 "\n", param[ loopCounter ].key, *( uint16_t* )( param[ loopCounter ].value ) );
				break;
			}
			case CONFIG_TYPE_uint32_t:
			{
				fprintf ( f, "%s=%" PRIu32 "\n", param[ loopCounter ].key, *( uint32_t* )( param[ loopCounter ].value ) );
				break;
			}
			case CONFIG_TYPE_uint64_t:
			{
				fprintf ( f, "%s=%" PRIu64 "\n", param[ loopCounter ].key, *( uint64_t* )( param[ loopCounter ].value ) );
				break;
			}
			case CONFIG_TYPE_int8_t:
			{
				fprintf ( f, "%s=%" PRId8 "\n", param[ loopCounter ].key, *( int8_t* )( param[ loopCounter ].value ) );
				break;
			}
			case CONFIG_TYPE_int16_t:
			{
				fprintf ( f, "%s=%" PRId16 "\n", param[ loopCounter ].key, *( uint16_t* )( param[ loopCounter ].value ) );
				break;
			}
			case CONFIG_TYPE_int32_t:
			{
				fprintf ( f, "%s=%" PRId32 "\n", param[ loopCounter ].key, *( uint32_t* )( param[ loopCounter ].value ) );
				break;
			}
			case CONFIG_TYPE_int64_t:
			{
				fprintf ( f, "%s=%" PRId64 "\n", param[ loopCounter ].key, *( int64_t* )( param[ loopCounter ].value ) );
				break;
			}
			case CONFIG_TYPE_str:
			{
				fprintf ( f, "%s=%s\n", param[ loopCounter ].key, (char *)( param[ loopCounter ].value ) );
				break;
			}
			case CONFIG_TYPE_float:
			case CONFIG_TYPE_float32_t:
			{
				fprintf ( f, "%s=%f\n", param[ loopCounter ].key, *( float* )( param[ loopCounter ].value ) );
				break;
			}
			case CONFIG_TYPE_double:
			case CONFIG_TYPE_float64_t:
			{
				fprintf ( f, "%s=%lf\n", param[ loopCounter ].key, *( double* )( param[ loopCounter ].value ) );
				break;
			}
			default:
			{
				break;
			}
		}
	}
}

int updateConfigFile ( const char * file, const config_el param[] )
{
	FILE *f, *f2;
	char key[81];
	int tmp;
	int index;
	int loopCounter;

	f = fopen ( file, "r" );
	f2 = fopen ( "/tmp/config_file.tmp", "w" );

	#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
	if ( !f )
	{
		return ( __LINE__ );
	}

	if ( !f2 )
	{
		if ( fclose ( f ) )
		{
			return ( __LINE__ );
		}
		return ( __LINE__ );
	}
	#pragma GCC diagnostic pop

	while ( 1 )
	{
		tmp = fscanf ( f , "%80[^\n]\n", key );

		if ( tmp < 0 )
		{
			break;
		}

		if ( key[0] == '#' )
		{
			fprintf ( f2, "%s\n", key );
			continue;
		}

		index = -1;
		do
		{
			index++;
			if ( key[ index ] == '=' )
			{
				key[ index ] = '\0';
			}
		}
		while ( ( key[ index ] != '\0')  &&
			( index < 80 ) );


		if ( index >= 80 )
		{
			fprintf ( f2, "%s\n", key );
			continue;
		}

		for ( loopCounter = 0; param[ loopCounter ].key != NULL; loopCounter++ )
		{
			if ( !strcmp ( key, param[ loopCounter ].key ) )
			{
				switch( param[ loopCounter ].type )
				{
					case CONFIG_TYPE_bool:
					case CONFIG_TYPE_uint8_t:
					case CONFIG_TYPE_uint16_t:
					case CONFIG_TYPE_uint32_t:
					case CONFIG_TYPE_uint64_t:
					{
						fprintf ( f2, "%s=%" PRIu64 "\n", param[ loopCounter ].key, *( uint64_t* )( param[ loopCounter ].value ) );
						break;
					}
					case CONFIG_TYPE_int8_t:
					case CONFIG_TYPE_int16_t:
					case CONFIG_TYPE_int32_t:
					case CONFIG_TYPE_int64_t:
					{
						fprintf ( f2, "%s=%" PRId64 "\n", param[ loopCounter ].key, *( int64_t* )( param[ loopCounter ].value ) );
						break;
					}
					case CONFIG_TYPE_str:
					{
						fprintf ( f2, "%s=%s\n", param[ loopCounter ].key, ( char* )( param[ loopCounter ].value ) );
						break;
					}
					case CONFIG_TYPE_float:
					case CONFIG_TYPE_float32_t:
					{
						fprintf ( f2, "%s=%f\n", param[ loopCounter ].key, *( float* )( param[ loopCounter ].value ) );
						break;
					}
					case CONFIG_TYPE_double:
					case CONFIG_TYPE_float64_t:
					{
						fprintf ( f2, "%s=%lf\n", param[ loopCounter ].key, *( double* )( param[ loopCounter ].value ) );
						break;
					}
					default:
					{
						break;
					}
				}
				break;
			}
		}

		if ( param[ loopCounter ].key == NULL )
		{
			fprintf ( f2, "%s=%s\n", key, &key[ index + 1 ] );
		}
	}

	if ( fclose ( f ) )
	{
		if ( fclose ( f2 ) )
		{
			return ( __LINE__ );
		}
		return ( __LINE__ );
	}

	if ( fclose ( f2 ) )
	{
		return ( __LINE__ );
	}

	if ( remove ( file ) )
	{
		return ( __LINE__ );
	}

	if ( rename ( "/tmp/config_file.tmp", file ) )
	{
		return ( __LINE__ );
	}

	return ( 0 );
}
