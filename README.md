# config

## Purpose

This lib can be used to parse commands lines arguments or formatted config files for C/C++ projects.

## Usage
### Tree example:
```shell
.
├── makefile
└── src
    ├── lib
    │   └── config
    │      ├── config_arg.c
    │      ├── config_arg.h
    │      ├── config_data.h
    │      ├── config_file.c
    │      ├── config_file.h
    │      ├── LICENSE
    │      └── README.md
    └── main.c
```

### Code example:
```C
#include <stdio.h>

#include "lib/config/config_arg.h" // parse command line arguments
#include "lib/config/config_file.h" // read config file

int main ( int argc, char *argv[] )
{
	uint8_t param1 = 0;
	uint8_t param3[ 10 ] = { 0 };
	char param2[ 256 ] = { 0 };
	char * param4[ 3 ] = { 0 };
	char param5[ 3 ][ 256 ] = { 0 };

	uint8_t i = 0;

	config_el config[] = { // config file
		{ "PARAM_1", cT ( uint8_t ), &param1, "first parameter" },
		{ "PARAM_2", cT ( str ), param2, "second parameter" },
		{ NULL, 0, NULL, NULL}
	};

	param_el param[] = { // cmd line args
		{
			.keyLong = "--param1",
			.keyShort = "-p1",
			.nbEl = 1,
			.type = cT ( uint8_t ),
			.value = &param1,
			.help = "first argument"
		},
		{ "--param2", "-p2", 1, cT ( str ), &param2, "second argument" },
		{ "--param3", "-p3", 10,  cT ( uint8_t ),  &param3,  "third argument" },
		{ "--param4", "-p4", 3,  cT ( str ),  &param4,  NULL },
		{ NULL }
	};

	if ( readConfigFile ( "configFilePath", config ) )
	{
		// failure case
	}
	else if ( readConfigArgs ( argc, argv, config ) )
	{
		// failure case
	}
	else if ( readParamArgs ( argc, argv, param ) )
	{
		// failure case
	}
	else
	{
		// configFile read successfully
	}

	printf ( "1 - %d\n", param1 );
	printf ( "2 - %s\n", param2 );
	printf ( "3 -\n" );

	for ( i = 0; i < 10; i++ )
	{
		printf ( "    %d - %d\n", i, param3[ i ] );
	}

	printf ( "4 -\n" );
	for ( i = 0; i < 3; i++ )
	{
		printf ( "    %d - %s\n", i, param4[ i ] );
	}

	return ( 0 );
}
```

### ConfigFilePath example:
```
# param 1
# default value:
# PARAM_1=12
PARAM_1=6

# param 2
# default value:
# PARAM_2=pony
PARAM_2=str
```

### Call example: using **readConfigFile()**, **readConfigArgs** and **readParamArgs()**
```
$ ./exec PARAM_2=string_2 -p1 5 -p3 1 2 3 4 5 6 135 8 9 -p4 test test_2

1 - 5
2 - string_2
3 -
    0 - 1
    1 - 2
    2 - 3
    3 - 4
    4 - 5
    5 - 6
    6 - 135
    7 - 8
    8 - 9
    9 - 0
4 -
    0 - test
    1 - test_2
    2 - (null)
```

## Advanced
Be care we used two types of elements name `params args` and `configs args`, the fists ones defines element began by '-' separated by spaces, the seconds ones defines elements separates by '=':

```
params arguments : -key value -key value -key --longKey ...
configs arguments : KEY=value KEY=VALUE ...
```

### arguments order:
Be care with arguments order:
```
$  ./bin/exec PARAM_2=string_2 -p4 test test_2
1 - 10
2 - string_2
...
4 -
    0 - test
    1 - test_2
    2 - (null)
```
is different than:
```
$  ./bin/exec -p4 test test_2 PARAM_2=string_2

1 - 10
2 - string_2
...
4 -
    0 - test
    1 - test_2
    2 - PARAM_2=string_2
```

### Spécial cmds:
By default argument "`--`" stop parsing of arguments list, soo:
```
$ ./exec PARAM_2=string_2 -p1 5 -p3 1 2 3 -- 4 5 6 135 8 9 -p4 test test_2

1 - 5
2 - string_2
3 -
    0 - 1
    1 - 2
    2 - 3
    3 - 0
    4 - 0
    5 - 0
    6 - 0
    7 - 0
    8 - 0
    9 - 0
4 -
    0 - (null)
    1 - (null)
    2 - (null)
```

You can change the default comportement by redefining "`--`" argument, two modes exists:
1. set "`--`" as a valid element like everyone,
2. set "`--`" as invalid element,

```C
param_el param[] = { // cmd line args
		...
		{ // first case
			.keyLong = "`--`",
			.nbEl = 1,
			.type = cT ( uint8_t ),
			.value = &paramValue,
			.help = "help data"
		},
		{ //second case
			.keyLong = "`--`",
			.value = NULL,
			.help = "stop parsing"
		},
		{ NULL }
	};
```

The first case allow to use "`--`" like all other params, second case allow to use "`--`" to stop store data in the last specified data.
```
$ ./exec PARAM_2=string_2 -p1 5 -p3 1 2 3 -- 4 5 6 135 8 9 -p4 test test_2

1 - 5
2 - string_2
3 -
    0 - 1
    1 - 2
    2 - 3
    3 - 0
    4 - 0
    5 - 0
    6 - 0
    7 - 0
    8 - 0
    9 - 0
4 -
    0 - test
    1 - test_2
    2 - (null)
```

### booleans:
#### simplest:
You can use boolean in your cmd params for exemple:
```C
struct
{
	uitn8_t f1:1,
		f2:1,
		f3:1;
}
flags = { 0 };

...

param_el param[] = {
	{ "--flag1", "-f1", 0x01, cT ( bool ), &flags, "help data" },
	{ "--flag2", "-f2", 0x02, cT ( bool ), &flags, "help data" },
	{ "--flag3", "-f3", 0x04, cT ( bool ), &flags, "help data" },
	{ NULL, NULL, 0, 0, NULL, NULL },
}

```

```Shell
./exec -f1 --flag2
```
The last cmd will set the `flags.f1` and `flags.f2` to true ( 1 ).

#### combineted:
The third parameter is no the bit ID but a bit mask soo:
You can use boolean in your cmd prams for exemple:
```C
struct
{
	uitn8_t f1:1,
		f2:1,
		f3:1;
}
flags = { 0 };

...

param_el param[] = {
	{ "--flag1", "-f1", 0x01, cT ( bool ), &flags, "help data" },
	{ "--flag2", "-f2", 0x02, cT ( bool ), &flags, "help data" },
	{ "--flag3", "-f3", 0x04, cT ( bool ), &flags, "help data" },
	{ "--flag1_3", "-f13", 0x05, cT ( bool ), &flags, "help data" },
	{ NULL, NULL, 0, 0, NULL, NULL },
}
```

```Shell
./exec -f13
```
This cmd is equivalent too:

```Shell
./exec -f1 -f3
```

The last cmds will set the `flags.f1` and `flags.f3` to true ( 1 ).

#### inverted:
You can use the special type ibool to define an inverted flag, you should set it to true by default and reset it by cmd line. This type is only working with param els, not with config.

```C
flags = 0xff;
param_el param[] = {
	...
	{ "--flag6", "-f6", 0x20, cT ( ibool ), &flags, "inverted flag" },
	...
}
printf ( "-> %#x\n", flags );
```

```Shell
> gcc main.c && ./a.out
-> 0xdf
```
#### TRUE/FALSE:
For the config's boolean's els (only), you can use int values 0/1 or true/TRUE/false/FALSE:

./a.out PARAM=TRUE

#### more:
If you whant to use more flags in the same struct it's possible but a litle trick is needed.
```C
struct
{
	uitn8_t f1:1,
		f2:1,
		...;
	uint8_t f9:1,
		f0:1;
	uint8_t f17:1;
}
flags = { 0 };

...

param_el param[] = {
	{ "--flag1", "-f1", 0x01, cT ( bool ), &flags, "help data" },
	{ "--flag2", "-f2", 0x02, cT ( bool ), &flags, "help data" },
	...
	{ "--flag9", "-f9", 0x01, cT ( bool ), ((uint8_t * )&flags) + 1, "help data" },
	{ "--flag10", "-f10", 0x02, cT ( bool ), ((uint8_t * )&flags) + 1, "help data" },
	{ "--flag17", "-f17", 0x01, cT ( bool ), ((uint8_t * )&flags) + 2, "help data" },
	{ NULL, NULL, 0, 0, NULL, NULL },
}
```

you should cast flags pointer as int8_t pointer and add an offset.


### Help
The helps functions will display:
- for config ( *helpConfigArgs(config)* ):
	- key : help
	- key : type (if help pointer is null)
- for param ( *helpParamArgs(param)* ):
	- key : nbEl : help
	- key : nbEl : type (if help pointer is null)

Examples:
```C
helpConfigArgs ( config );
```

```
    usage : key=value key2=value2
             PARAM_1 : first parameter
             PARAM_2 : second parameter
```

```C
helpParamArgs ( param );
```

```
    usage : key value value2 key2 value3 ...
            key : key :  nb elements : help or type
       --param1 : -p1 :  1 : first argument
       --param2 : -p2 :  1 : second argument
       --param3 : -p3 : 10 : third argument
       --param4 : -p4 :  3 : string
         	 -- : stop parsing
```

