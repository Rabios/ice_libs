# ice_time.h Documentation

### Enums

```c
typedef enum {
    ICE_TIME_SUNDAY = 1,
    ICE_TIME_MONDAY,
    ICE_TIME_TUESDAY,
    ICE_TIME_WEDNESDAY,
    ICE_TIME_THURSDAY,
    ICE_TIME_FRIDAY,
    ICE_TIME_SATURDAY,
} ice_time_day;

typedef enum {
    ICE_TIME_JANUARY = 1,
    ICE_TIME_FEBRUARY,
    ICE_TIME_MARCH,
    ICE_TIME_APRIL,
    ICE_TIME_MAY,
    ICE_TIME_JUNE,
    ICE_TIME_JULY,
    ICE_TIME_AUGUST,
    ICE_TIME_SEPTEMBER,
    ICE_TIME_OCTOBER,
    ICE_TIME_NOVEMBER,
    ICE_TIME_DECEMBER,
} ice_time_month;

typedef enum {
    ICE_TIME_WINTER = 1,
    ICE_TIME_SPRING,
    ICE_TIME_SUMMER,
    ICE_TIME_AUTUMN,
} ice_time_season;
```

### Definitions

```c
// Definitions
// Implements ice_time source code, Works same as #pragma once
#define ICE_TIME_IMPL

#define ICE_TIME_EXTERN  // Extern functions of the library with extern keyword (Enabled by default)
#define ICE_TIME_STATIC  // Makes functions of the library static with static keyword
#define ICE_TIME_INLINE  // Inline functions of the library with inline keyword

// Call conventions (You could define one of these to set compiler calling convention)
#define ICE_TIME_CALLCONV_VECTORCALL
#define ICE_TIME_CALLCONV_FASTCALL
#define ICE_TIME_CALLCONV_STDCALL
#define ICE_TIME_CALLCONV_CDECL

// Platforms could be defined (But not forced to...)
#define ICE_TIME_MICROSOFT     // Microsoft platforms (Not autodefined -> using Unix)

// If no platform defined, This definition will define itself
// This definition sets platform depending on platform-specified C compiler definitions
#define ICE_TIME_PLATFORM_AUTODETECTED

// In case you want to build DLL on Microsoft Windows!
// Keep in mind you should set backend (But it's defined by default if not...)
#define ICE_TIME_DLLEXPORT
#define ICE_TIME_DLLIMPORT
```

### Functions

```c
// Time Control
double          ice_time_tick(void);
double          ice_time_diff(double t1, double t2);
double          ice_time_fps(double t1, double t2);
double          ice_time_dt(double t1, double t2);
char*           ice_time_string(void);
int             ice_time_current_second(void);
int             ice_time_current_minute(void);
int             ice_time_current_hour(void);
int             ice_time_current_month_day(void);
ice_time_month  ice_time_current_month(void);
int             ice_time_current_year(void);
int             ice_time_current_year_day(void);
ice_time_day    ice_time_current_week_day(void);
ice_time_season ice_time_get_season(void);
void            ice_time_sleep(unsigned int ms);

// Time Conversion
double ice_time_ns_to_ms(double ns);
double ice_time_ns_to_sec(double ns);
double ice_time_ns_to_min(double ns);
double ice_time_ns_to_hour(double ns);
double ice_time_ns_to_day(double ns);
double ice_time_ns_to_week(double ns);
double ice_time_ns_to_month(double ns);
double ice_time_ns_to_year(double ns);
double ice_time_ns_to_decade(double ns);
double ice_time_ns_to_century(double ns);

double ice_time_ms_to_ns(double ms);
double ice_time_ms_to_sec(double ms);
double ice_time_ms_to_min(double ms);
double ice_time_ms_to_hour(double ms);
double ice_time_ms_to_day(double ms);
double ice_time_ms_to_week(double ms);
double ice_time_ms_to_month(double ms);
double ice_time_ms_to_year(double ms);
double ice_time_ms_to_decade(double ms);
double ice_time_ms_to_century(double ms);

double ice_time_min_to_ns(double min);
double ice_time_min_to_ms(double min);
double ice_time_min_to_sec(double min);
double ice_time_min_to_hour(double min);
double ice_time_min_to_day(double min);
double ice_time_min_to_week(double min);
double ice_time_min_to_month(double min);
double ice_time_min_to_year(double min);
double ice_time_min_to_decade(double min);
double ice_time_min_to_century(double min);

double ice_time_hour_to_ns(double hr);
double ice_time_hour_to_ms(double hr);
double ice_time_hour_to_sec(double hr);
double ice_time_hour_to_min(double hr);
double ice_time_hour_to_day(double hr);
double ice_time_hour_to_week(double hr);
double ice_time_hour_to_month(double hr);
double ice_time_hour_to_year(double hr);
double ice_time_hour_to_decade(double hr);
double ice_time_hour_to_century(double hr);

double ice_time_day_to_ns(double day);
double ice_time_day_to_ms(double day);
double ice_time_day_to_sec(double day);
double ice_time_day_to_min(double day);
double ice_time_day_to_hour(double day);
double ice_time_day_to_week(double day);
double ice_time_day_to_month(double day);
double ice_time_day_to_year(double day);
double ice_time_day_to_decade(double day);
double ice_time_day_to_century(double day);

double ice_time_week_to_ns(double week);
double ice_time_week_to_ms(double week);
double ice_time_week_to_sec(double week);
double ice_time_week_to_min(double week);
double ice_time_week_to_hour(double week);
double ice_time_week_to_day(double week);
double ice_time_week_to_month(double week);
double ice_time_week_to_year(double week);
double ice_time_week_to_decade(double week);
double ice_time_week_to_century(double week);

double ice_time_month_to_ns(double month);
double ice_time_month_to_ms(double month);
double ice_time_month_to_sec(double month);
double ice_time_month_to_min(double month);
double ice_time_month_to_hour(double month);
double ice_time_month_to_day(double month);
double ice_time_month_to_week(double month);
double ice_time_month_to_year(double month);
double ice_time_month_to_decade(double month);
double ice_time_month_to_century(double month);

double ice_time_year_to_ns(double year);
double ice_time_year_to_ms(double year);
double ice_time_year_to_sec(double year);
double ice_time_year_to_min(double year);
double ice_time_year_to_hour(double year);
double ice_time_year_to_day(double year);
double ice_time_year_to_week(double year);
double ice_time_year_to_month(double year);
double ice_time_year_to_decade(double year);
double ice_time_year_to_century(double year);

double ice_time_decade_to_ns(double decade);
double ice_time_decade_to_ms(double decade);
double ice_time_decade_to_sec(double decade);
double ice_time_decade_to_min(double decade);
double ice_time_decade_to_hour(double decade);
double ice_time_decade_to_day(double decade);
double ice_time_decade_to_week(double decade);
double ice_time_decade_to_month(double decade);
double ice_time_decade_to_year(double decade);
double ice_time_decade_to_century(double decade);

double ice_time_century_to_ns(double century);
double ice_time_century_to_ms(double century);
double ice_time_century_to_sec(double century);
double ice_time_century_to_min(double century);
double ice_time_century_to_hour(double century);
double ice_time_century_to_day(double century);
double ice_time_century_to_week(double century);
double ice_time_century_to_month(double century);
double ice_time_century_to_year(double century);
double ice_time_century_to_decade(double century);
```