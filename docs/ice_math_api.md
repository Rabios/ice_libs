# ice_math.h Documentation

### Enums

```c
typedef enum {
    ICE_MATH_TRUE = 0,
    ICE_MATH_FALSE = -1,
} ice_math_bool;
```

### Definitions

```c
// Typedefs
typedef struct ice_math_vec2 {
    double x;
    double y;
} ice_math_vec2;

typedef struct ice_math_vec3 {
    double x;
    double y;
    double z;
} ice_math_vec3;

typedef struct ice_math_vec4 {
    double x;
    double y;
    double z;
    double w;
} ice_math_vec4;

typedef ice_math_vec4 ice_math_quat;

typedef struct ice_math_rect {
    double x;
    double y;
    double w;
    double h;
} ice_math_rect;

typedef struct ice_math_mat {
    double m0;
    double m1;
    double m2;
    double m3;
    
    double m4;
    double m5;
    double m6;
    double m7;
    
    double m8;
    double m9;
    double m10;
    double m11;
    
    double m12;
    double m13;
    double m14;
    double m15;
} ice_math_mat;

typedef struct ice_math_mtrand {
    unsigned long mt[ICE_MATH_STATE_VECTOR_LENGTH];
    int index;
} ice_math_mtrand;

// Definitions
// Implements ice_math source code, Works same as #pragma once
#define ICE_MATH_IMPL

#define ICE_MATH_EXTERN  // Extern functions of the library with extern keyword (Enabled by default)
#define ICE_MATH_STATIC  // Makes functions of the library static with static keyword
#define ICE_MATH_INLINE  // Inline functions of the library with inline keyword

// Call conventions (You could define one of these to set compiler calling convention)
#define ICE_MATH_CALLCONV_VECTORCALL
#define ICE_MATH_CALLCONV_FASTCALL
#define ICE_MATH_CALLCONV_STDCALL
#define ICE_MATH_CALLCONV_CDECL

// Platforms could be defined (But not forced to...)
#define ICE_MATH_MICROSOFT      // Microsoft platforms (Not autodefined -> using Unix)

// In case you want to build DLL on Microsoft Windows!
#define ICE_MATH_DLLEXPORT
#define ICE_MATH_DLLIMPORT

// Custom memory allocators
#define ICE_MATH_MALLOC(sz)             // malloc(sz)
#define ICE_MATH_CALLOC(n, sz)          // calloc(n, sz)
#define ICE_MATH_REALLOC(ptr, sz)       // realloc(ptr, sz)
#define ICE_MATH_FREE(ptr)              // free(ptr)

// Library definitions
#define ICE_MATH_PI                     3.14159265358979323846
#define ICE_MATH_E                      2.7182818284590452354
#define ICE_MATH_EPSILON                2.2204460492503130808472633361816
#define ICE_MATH_PI_2                   1.57079632679489661923
#define ICE_MATH_PI_4                   0.78539816339744830962
#define ICE_MATH_1_PI                   0.31830988618379067154
#define ICE_MATH_2_PI                   0.63661977236758134308
#define ICE_MATH_2_SQRTPI               1.12837916709551257390
#define ICE_MATH_LN2                    0.69314718055994530942
#define ICE_MATH_LN10                   2.30258509299404568402
#define ICE_MATH_LOG2E                  1.4426950408889634074
#define ICE_MATH_LOG10E                 0.43429448190325182765
#define ICE_MATH_SQRT2                  1.41421356237309504880
#define ICE_MATH_SQRT1_2                0.70710678118654752440
#define ICE_MATH_INFINITY               1 / 0
#define ICE_MATH_NAN                    7ff8000000000000
#define ICE_MATH_FLT_RADIX              2
#define ICE_MATH_TAU                    ICE_MATH_PI * 2
#define ICE_MATH_UNDEFINED              NULL

#define ICE_MATH_SIN_0_RADIANS          0
#define ICE_MATH_SIN_30_RADIANS         ICE_MATH_PI / 6
#define ICE_MATH_SIN_45_RADIANS         ICE_MATH_PI / 4
#define ICE_MATH_SIN_60_RADIANS         ICE_MATH_PI / 3
#define ICE_MATH_SIN_90_RADIANS         ICE_MATH_PI / 2
#define ICE_MATH_SIN_120_RADIANS        (2 * ICE_MATH_PI) / 3
#define ICE_MATH_SIN_135_RADIANS        (3 * ICE_MATH_PI) / 4
#define ICE_MATH_SIN_150_RADIANS        (5 * ICE_MATH_PI) / 6
#define ICE_MATH_SIN_180_RADIANS        ICE_MATH_PI
#define ICE_MATH_SIN_210_RADIANS        (7 * ICE_MATH_PI) / 6
#define ICE_MATH_SIN_225_RADIANS        (5 * ICE_MATH_PI) / 4
#define ICE_MATH_SIN_240_RADIANS        (4 * ICE_MATH_PI) / 3
#define ICE_MATH_SIN_270_RADIANS        (3 * ICE_MATH_PI) / 2
#define ICE_MATH_SIN_300_RADIANS        (5 * ICE_MATH_PI) / 3
#define ICE_MATH_SIN_315_RADIANS        (7 * ICE_MATH_PI) / 4
#define ICE_MATH_SIN_330_RADIANS        (11 * ICE_MATH_PI) / 6
#define ICE_MATH_SIN_360_RADIANS        ICE_MATH_PI * 2

#define ICE_MATH_SIN_0                  0
#define ICE_MATH_COS_0                  1
#define ICE_MATH_TAN_0                  0
#define ICE_MATH_COT_0                  ICE_MATH_UNDEFINED
#define ICE_MATH_SEC_0                  1
#define ICE_MATH_CSC_0                  ICE_MATH_UNDEFINED

#define ICE_MATH_SIN_30                 1 / 2
#define ICE_MATH_COS_30                 0.8660254037844386
#define ICE_MATH_TAN_30                 0.5773502691896258
#define ICE_MATH_COT_30                 1.7320508075688772
#define ICE_MATH_SEC_30                 1.1547005383792517
#define ICE_MATH_CSC_30                 2

#define ICE_MATH_SIN_45                 0.7071067811865475
#define ICE_MATH_COS_45                 0.7071067811865475
#define ICE_MATH_TAN_45                 1
#define ICE_MATH_COT_45                 1
#define ICE_MATH_SEC_45                 1.4142135623730951
#define ICE_MATH_CSC_45                 1.4142135623730951

#define ICE_MATH_SIN_60                 0.8660254037844386
#define ICE_MATH_COS_60                 1 / 2
#define ICE_MATH_TAN_60                 1.7320508075688772
#define ICE_MATH_COT_60                 0.5773502691896258
#define ICE_MATH_SEC_60                 2
#define ICE_MATH_CSC_60                 0.47140452079103173

#define ICE_MATH_SIN_90                 1
#define ICE_MATH_COS_90                 0
#define ICE_MATH_TAN_90                 ICE_MATH_UNDEFINED
#define ICE_MATH_COT_90                 1
#define ICE_MATH_SEC_90                 ICE_MATH_UNDEFINED
#define ICE_MATH_CSC_90                 0

#define ICE_MATH_SIN_120                0.8660254037844386
#define ICE_MATH_COS_120                -(1 / 2)
#define ICE_MATH_TAN_120                -1.7320508075688772
#define ICE_MATH_COT_120                -1.1547005383792517
#define ICE_MATH_SEC_120                -2
#define ICE_MATH_CSC_120                -0.47140452079103173

#define ICE_MATH_SIN_135                0.7071067811865475
#define ICE_MATH_COS_135                -0.7071067811865475
#define ICE_MATH_TAN_135                -1
#define ICE_MATH_COT_135                -1
#define ICE_MATH_SEC_135                -1.4142135623730951
#define ICE_MATH_CSC_135                1.4142135623730951

#define ICE_MATH_SIN_150                1 / 2
#define ICE_MATH_COS_150                1.7320508075688772
#define ICE_MATH_TAN_150                -0.5773502691896258
#define ICE_MATH_COT_150                -1.7320508075688772
#define ICE_MATH_SEC_150                -1.1547005383792517
#define ICE_MATH_CSC_150                2

#define ICE_MATH_SIN_180                0
#define ICE_MATH_COS_180                -1
#define ICE_MATH_TAN_180                0
#define ICE_MATH_COT_180                ICE_MATH_UNDEFINED
#define ICE_MATH_SEC_180                -1
#define ICE_MATH_CSC_180                ICE_MATH_UNDEFINED

#define ICE_MATH_SIN_210                -(1 / 2)
#define ICE_MATH_COS_210                -1.7320508075688772
#define ICE_MATH_TAN_210                0.5773502691896258
#define ICE_MATH_COT_210                1.7320508075688772
#define ICE_MATH_SEC_210                -1.1547005383792517
#define ICE_MATH_CSC_210                -2

#define ICE_MATH_SIN_225                -0.7071067811865475
#define ICE_MATH_COS_225                -0.7071067811865475
#define ICE_MATH_TAN_225                1
#define ICE_MATH_COT_225                1
#define ICE_MATH_SEC_225                -1.4142135623730951
#define ICE_MATH_CSC_225                -1.4142135623730951

#define ICE_MATH_SIN_240                -0.8660254037844386
#define ICE_MATH_COS_240                -(1 / 2)
#define ICE_MATH_TAN_240                1.7320508075688772
#define ICE_MATH_COT_240                1.1547005383792517
#define ICE_MATH_SEC_240                -2
#define ICE_MATH_CSC_240                -0.47140452079103173

#define ICE_MATH_SIN_270                -1
#define ICE_MATH_COS_270                0
#define ICE_MATH_TAN_270                ICE_MATH_UNDEFINED
#define ICE_MATH_COT_270                0
#define ICE_MATH_SEC_270                ICE_MATH_UNDEFINED
#define ICE_MATH_CSC_270                -1

#define ICE_MATH_SIN_300                -0.8660254037844386
#define ICE_MATH_COS_300                1 / 2
#define ICE_MATH_TAN_300                -1.7320508075688772
#define ICE_MATH_COT_300                -1.1547005383792517
#define ICE_MATH_SEC_300                2
#define ICE_MATH_CSC_300                -0.47140452079103173

#define ICE_MATH_SIN_315                -0.7071067811865475
#define ICE_MATH_COS_315                0.7071067811865475
#define ICE_MATH_TAN_315                -1
#define ICE_MATH_COT_315                -1
#define ICE_MATH_SEC_315                1.4142135623730951
#define ICE_MATH_CSC_315                -1.4142135623730951

#define ICE_MATH_SIN_330                -(1 / 2)
#define ICE_MATH_COS_330                1.7320508075688772
#define ICE_MATH_TAN_330                -0.5773502691896258
#define ICE_MATH_COT_330                -1.7320508075688772
#define ICE_MATH_SEC_330                1.1547005383792517
#define ICE_MATH_CSC_330                -2

#define ICE_MATH_SIN_360                0
#define ICE_MATH_COS_360                1
#define ICE_MATH_TAN_360                0
#define ICE_MATH_COT_360                ICE_MATH_UNDEFINED
#define ICE_MATH_SEC_360                1
#define ICE_MATH_CSC_360                ICE_MATH_UNDEFINED

#define ICE_MATH_UPPER_MASK             0x80000000
#define ICE_MATH_LOWER_MASK             0x7fffffff
#define ICE_MATH_TEMPERING_MASK_B       0x9d2c5680
#define ICE_MATH_TEMPERING_MASK_C       0xefc60000
#define ICE_MATH_STATE_VECTOR_LENGTH    624
#define ICE_MATH_STATE_VECTOR_M         397         // changes to ICE_MATH_STATE_VECTOR_LENGTH also require changes to this
```

### Functions

```c
// Math Implementations (+ Extra Stuff)
double  ice_math_rad(double n);
double  ice_math_deg(double n);
double  ice_math_abs(double n);
double  ice_math_acos(double n);
double  ice_math_asin(double n);
double  ice_math_atan(double n);
double  ice_math_acot(double n);
double  ice_math_asec(double n);
double  ice_math_acsc(double n);
double  ice_math_max(double a, double b);
double  ice_math_min(double a, double b);
double  ice_math_ceil(double n);
double  ice_math_floor(double n);
double  ice_math_round(double n);
double  ice_math_imul(double a, double b);
double  ice_math_sqr(double n);
double  ice_math_pow(double a, double b);
double  ice_math_log2(double n);
double  ice_math_exp(double n);
double  ice_math_expm1(double n);
double  ice_math_log(double n);
double  ice_math_log10(double n);
double  ice_math_log1p(double n);
double  ice_math_exp2(double n);
double  ice_math_sqrt(double n);
double  ice_math_sinh(double n);
double  ice_math_cosh(double n);
double  ice_math_tanh(double n);
double  ice_math_coth(double n);
double  ice_math_sech(double n);
double  ice_math_csch(double n);
double  ice_math_trunc(double n);
double  ice_math_sign(double n);
double  ice_math_fib(double n);
double  ice_math_fact(double n);
double  ice_math_cos(double n);
double  ice_math_sin(double n);
double  ice_math_tan(double n);
double  ice_math_cot(double n);
double  ice_math_sec(double n);
double  ice_math_csc(double n);
double  ice_math_sin_sum(double a, double b);
double  ice_math_sin_diff(double a, double b);
double  ice_math_cos_sum(double a, double b);
double  ice_math_cos_diff(double a, double b);
double  ice_math_tan_sum(double a, double b);
double  ice_math_tan_diff(double a, double b);
double  ice_math_sin2(double n);
double  ice_math_cos2(double n);
double  ice_math_tan2(double n);
double  ice_math_sin3(double n);
double  ice_math_cos3(double n);
double  ice_math_tan3(double n);
double  ice_math_sin4(double n);
double  ice_math_cos4(double n);
double  ice_math_tan4(double n);
double  ice_math_sin5(double n);
double  ice_math_cos5(double n);
double  ice_math_tan5(double n);
double  ice_math_double_sin(double n);
double  ice_math_double_cos(double n);
double  ice_math_double_tan(double n);
double  ice_math_double_cot(double n);
double  ice_math_double_sec(double n);
double  ice_math_double_csc(double n);
double  ice_math_double_sinh(double n);
double  ice_math_double_cosh(double n);
double  ice_math_double_tanh(double n);
double  ice_math_triple_sin(double n);
double  ice_math_triple_cos(double n);
double  ice_math_triple_tan(double n);
double  ice_math_triple_cot(double n);
double  ice_math_triple_sec(double n);
double  ice_math_triple_csc(double n);
double  ice_math_triple_sinh(double n);
double  ice_math_triple_cosh(double n);
double  ice_math_triple_tanh(double n);
double  ice_math_quadruple_sin(double n);
double  ice_math_quadruple_cos(double n);
double  ice_math_quadruple_tan(double n);
double  ice_math_quadruple_sinh(double n);
double  ice_math_quadruple_cosh(double n);
double  ice_math_quadruple_tanh(double n);
double  ice_math_quintuple_sin(double n);
double  ice_math_quintuple_cos(double n);
double  ice_math_quintuple_tan(double n);
double  ice_math_sextuple_sin(double n);
double  ice_math_sextuple_cos(double n);
double  ice_math_sextuple_tan(double n);
double  ice_math_hypot(double a, double b);
double  ice_math_atan2(double a, double b);
double  ice_math_asinh(double n);
double  ice_math_acosh(double n);
double  ice_math_atanh(double n);
double  ice_math_acoth(double n);
double  ice_math_asech(double n);
double  ice_math_acsch(double n);
double  ice_math_cbrt(double n);
double  ice_math_ldexp(double a, double b);
double  ice_math_scalbn(double a, double b);
double  ice_math_fma(double a, double b, double c);
double  ice_math_dim(double a, double b);
double  ice_math_logb(double n);
double  ice_math_sin_to_cos(double n);
double  ice_math_sin_to_tan(double n);
double  ice_math_sin_to_cot(double n);
double  ice_math_sin_to_sec(double n);
double  ice_math_sin_to_csc(double n);
double  ice_math_cos_to_sin(double n);
double  ice_math_cos_to_tan(double n);
double  ice_math_cos_to_cot(double n);
double  ice_math_cos_to_sec(double n);
double  ice_math_cos_to_csc(double n);
double  ice_math_tan_to_sin(double n);
double  ice_math_tan_to_cos(double n);
double  ice_math_tan_to_cot(double n);
double  ice_math_tan_to_sec(double n);
double  ice_math_tan_to_csc(double n);
double  ice_math_cot_to_sin(double n);
double  ice_math_cot_to_cos(double n);
double  ice_math_cot_to_tan(double n);
double  ice_math_cot_to_sec(double n);
double  ice_math_cot_to_csc(double n);
double  ice_math_sec_to_sin(double n);
double  ice_math_sec_to_cos(double n);
double  ice_math_sec_to_tan(double n);
double  ice_math_sec_to_cot(double n);
double  ice_math_sec_to_csc(double n);
double  ice_math_csc_to_sin(double n);
double  ice_math_csc_to_cos(double n);
double  ice_math_csc_to_tan(double n);
double  ice_math_csc_to_cot(double n);
double  ice_math_csc_to_sec(double n);
double  ice_math_co_angle(double n);
double  ice_math_versin(double n);
double  ice_math_vercos(double n);
double  ice_math_coversin(double n);
double  ice_math_covercos(double n);
double  ice_math_haversin(double n);
double  ice_math_havercos(double n);
double  ice_math_hacoversin(double n);
double  ice_math_hacovercos(double n);
double  ice_math_exsec(double n);
double  ice_math_excosec(double n);
double  ice_math_crd(double n);
double  ice_math_mod(double a, double b);
double  ice_math_frexp(double n);
double  ice_math_gamma(double n);

// Math Algorithms/Math Formulas
ice_math_bool  ice_math_even(int n);
ice_math_bool  ice_math_odd(int n);
double         ice_math_discriminant(double a, double b, double c);
double         ice_math_trinomial(double a, double b);
double         ice_math_iter_log(double a, double b);
double         ice_math_avg(double a, double b, double c);
double         ice_math_birthday_paradox(double n);
double         ice_math_parity(int n);
double         ice_math_binceoff(double a, double b);
int            ice_math_cassini(int n);
double         ice_math_leonardo(double n);
double         ice_math_double_fact(double n);
double         ice_math_hexagonal(double n);
double         ice_math_gcd(int a, int b);
double         ice_math_phi(double n);
ice_math_bool  ice_math_sqrt_exist(int a, int b, int c);
double         ice_math_seq(double n);
double         ice_math_pairwise_sum(double n);
double         ice_math_ncr(double a, double b);
double         ice_math_dyckpaths(double n);
ice_math_bool  ice_math_prime(int n);
double         ice_math_rasphon(double n);
double         ice_math_nth_group_sum(double n);
double         ice_math_trajectory_time(double a, double b);
double         ice_math_catalan(double n);
double         ice_math_pad(double n);
ice_math_bool  ice_math_composite(int n);
double         ice_math_nth_prime_factor(int a, int b);
double         ice_math_moser_seq(int n);
double         ice_math_lrotate(int a, int b, int bits);
double         ice_math_rrotate(int a, int b, int bits);
double         ice_math_politness(int n);
double         ice_math_multi_order(int a, int b);
double         ice_math_find_nth(double n);
int            ice_math_perfect_square_min_number(int n);
double         ice_math_sum(int n);
ice_math_bool  ice_math_amicable(double a, double b);
double         ice_math_bisection(double a, double b);
double         ice_math_fermat(double n);
double         ice_math_exact_prime_factor_count(double n);
double         ice_math_abundance(double n);
ice_math_bool  ice_math_abundant(double n);
double         ice_math_clamp(double value, double min, double max);
double         ice_math_lerp(double start, double end, double amount);
double         ice_math_norm(double value, double start, double end);
double         ice_math_remap(double value, double in_start, double in_end, double out_start, double out_end);

// Vectors
// Vector2
ice_math_vec2  ice_math_vec2_zero(void);
ice_math_vec2  ice_math_vec2_one(void);
ice_math_vec2  ice_math_vec2_neg(ice_math_vec2 v);
ice_math_vec2  ice_math_vec2_reflect(ice_math_vec2 v1, ice_math_vec2 v2);
ice_math_vec2  ice_math_vec2_add(ice_math_vec2 v1, ice_math_vec2 v2);
ice_math_vec2  ice_math_vec2_add_num(ice_math_vec2 v, double n);
ice_math_vec2  ice_math_vec2_sub(ice_math_vec2 v1, ice_math_vec2 v2);
ice_math_vec2  ice_math_vec2_sub_num(ice_math_vec2 v, double n);
ice_math_vec2  ice_math_vec2_mult(ice_math_vec2 v1, ice_math_vec2 v2);
ice_math_vec2  ice_math_vec2_div(ice_math_vec2 v1, ice_math_vec2 v2);
ice_math_vec2  ice_math_vec2_scale(ice_math_vec2 v, double scale);
double         ice_math_vec2_dot_product(ice_math_vec2 v1, ice_math_vec2 v2);
double         ice_math_vec2_cross_product(ice_math_vec2 v1, ice_math_vec2 v2);
ice_math_vec2  ice_math_vec2_lerp(ice_math_vec2 v1, ice_math_vec2 v2, double x);
ice_math_vec2  ice_math_vec2_norm(ice_math_vec2 v);
double         ice_math_vec2_len(ice_math_vec2 v);
double         ice_math_vec2_len_sqr(ice_math_vec2 v);
double         ice_math_vec2_angle(ice_math_vec2 v1, ice_math_vec2 v2);
double         ice_math_vec2_dist(ice_math_vec2 v1, ice_math_vec2 v2);
ice_math_vec2  ice_math_vec2_rotate(ice_math_vec2 v, double n);
ice_math_vec2  ice_math_vec2_move_towards(ice_math_vec2 v1, ice_math_vec2 v2, double max_dist);

// Vector3
ice_math_vec3  ice_math_vec3_zero(void);
ice_math_vec3  ice_math_vec3_one(void);
ice_math_vec3  ice_math_vec3_neg(ice_math_vec3 v);
ice_math_vec3  ice_math_vec3_add(ice_math_vec3 v1, ice_math_vec3 v2);
ice_math_vec3  ice_math_vec3_add_num(ice_math_vec3 v, double n);
ice_math_vec3  ice_math_vec3_sub(ice_math_vec3 v1, ice_math_vec3 v2);
ice_math_vec3  ice_math_vec3_sub_num(ice_math_vec3 v, double n);
ice_math_vec3  ice_math_vec3_mult(ice_math_vec3 v1, ice_math_vec3 v2);
ice_math_vec3  ice_math_vec3_div(ice_math_vec3 v1, ice_math_vec3 v2);
ice_math_vec3  ice_math_vec3_scale(ice_math_vec3 v, double scale);
double         ice_math_vec3_dot_product(ice_math_vec3 v1, ice_math_vec3 v2);
ice_math_vec3  ice_math_vec3_cross_product(ice_math_vec3 v1, ice_math_vec3 v2);
ice_math_vec3  ice_math_vec3_triple_product(ice_math_vec3 v1, ice_math_vec3 v2);
ice_math_vec3  ice_math_vec3_lerp(ice_math_vec3 v1, ice_math_vec3 v2, double x);
ice_math_vec3  ice_math_vec3_norm(ice_math_vec3 v);
void           ice_math_vec3_ortho_norm(ice_math_vec3* v1, ice_math_vec3* v2);
double         ice_math_vec3_len(ice_math_vec3 v);
double         ice_math_vec3_len_sqr(ice_math_vec3 v);
double         ice_math_vec3_angle(ice_math_vec3 v1, ice_math_vec3 v2);
double         ice_math_vec3_dist(ice_math_vec3 v1, ice_math_vec3 v2);
ice_math_vec3  ice_math_vec3_perpendicular(ice_math_vec3 v);
ice_math_vec3  ice_math_vec3_transform(ice_math_vec3 v, ice_math_mat m);
ice_math_vec3  ice_math_vec3_rotate_by_quat(ice_math_vec3 v, ice_math_quat q);
ice_math_vec3  ice_math_vec3_reflect(ice_math_vec3 v1, ice_math_vec3 v2);
ice_math_vec3  ice_math_vec3_min(ice_math_vec3 v1, ice_math_vec3 v2);
ice_math_vec3  ice_math_vec3_max(ice_math_vec3 v1, ice_math_vec3 v2);
ice_math_vec3  ice_math_vec3_barycenter(ice_math_vec3 p, ice_math_vec3 a, ice_math_vec3 b, ice_math_vec3 c);
ice_math_vec3  ice_math_vec3_unproj(ice_math_vec3 source, ice_math_mat projection, ice_math_mat view);

// Vector4
ice_math_vec4  ice_math_vec4_zero(void);
ice_math_vec4  ice_math_vec4_one(void);
ice_math_vec4  ice_math_vec4_neg(ice_math_vec4 v);
ice_math_vec4  ice_math_vec4_add(ice_math_vec4 v1, ice_math_vec4 v2);
ice_math_vec4  ice_math_vec4_add_num(ice_math_vec4 v, double n);
ice_math_vec4  ice_math_vec4_sub(ice_math_vec4 v1, ice_math_vec4 v2);
ice_math_vec4  ice_math_vec4_sub_num(ice_math_vec4 v, double n);
ice_math_vec4  ice_math_vec4_mult(ice_math_vec4 v1, ice_math_vec4 v2);
ice_math_vec4  ice_math_vec4_div(ice_math_vec4 v1, ice_math_vec4 v2);
ice_math_vec4  ice_math_vec4_scale(ice_math_vec4 v, double scale);
double         ice_math_vec4_dot_product(ice_math_vec4 v1, ice_math_vec4 v2);
ice_math_vec4  ice_math_vec4_lerp(ice_math_vec4 v1, ice_math_vec4 v2, double x);
ice_math_vec4  ice_math_vec4_norm(ice_math_vec4 v);
double         ice_math_vec4_len(ice_math_vec4 v);
double         ice_math_vec4_len_sqr(ice_math_vec4 v);
double         ice_math_vec4_dist(ice_math_vec4 v1, ice_math_vec4 v2);
ice_math_vec4  ice_math_vec4_min(ice_math_vec4 v1, ice_math_vec4 v2);
ice_math_vec4  ice_math_vec4_max(ice_math_vec4 v1, ice_math_vec4 v2);

// Quaternions
ice_math_quat  ice_math_quat_add(ice_math_quat q1, ice_math_quat q2);
ice_math_quat  ice_math_quat_add_num(ice_math_quat q, double n);
ice_math_quat  ice_math_quat_sub(ice_math_quat q1, ice_math_quat q2);
ice_math_quat  ice_math_quat_sub_num(ice_math_quat q, double n);
ice_math_quat  ice_math_quat_identity(void);
double         ice_math_quat_len(ice_math_quat q);
double         ice_math_quat_len_sqr(ice_math_quat q);
ice_math_quat  ice_math_quat_norm(ice_math_quat q);
ice_math_quat  ice_math_quat_inv(ice_math_quat q);
ice_math_quat  ice_math_quat_mult(ice_math_quat q1, ice_math_quat q2);
ice_math_quat  ice_math_quat_scale(ice_math_quat q, double n);
ice_math_quat  ice_math_quat_div(ice_math_quat q1, ice_math_quat q2);
ice_math_quat  ice_math_quat_lerp(ice_math_quat q1, ice_math_quat q2, double n);
ice_math_quat  ice_math_quat_nlerp(ice_math_quat q1, ice_math_quat q2, double n);
ice_math_quat  ice_math_quat_slerp(ice_math_quat q1, ice_math_quat q2, double n);
ice_math_quat  ice_math_quat_from_vec3_to_vec3(ice_math_vec3 from, ice_math_vec3 to);
ice_math_quat  ice_math_quat_from_mat(ice_math_mat m);
ice_math_mat   ice_math_quat_to_mat(ice_math_quat q);
ice_math_quat  ice_math_quat_from_axis_angle(ice_math_vec3 axis, double angle);
double         ice_math_quat_from_quat_to_angle(ice_math_quat q);
ice_math_vec3  ice_math_quat_from_quat_to_axis(ice_math_quat q);
ice_math_quat  ice_math_quat_from_euler(double roll, double pitch, double yaw);
ice_math_vec3  ice_math_quat_to_euler(ice_math_quat q);
ice_math_quat  ice_math_quat_transform(ice_math_quat q, ice_math_mat m);

// Matrices
double        ice_math_mat_determinant(ice_math_mat m);
double        ice_math_mat_trace(ice_math_mat m);
ice_math_mat  ice_math_mat_transpose(ice_math_mat m);
ice_math_mat  ice_math_mat_inv(ice_math_mat m);
ice_math_mat  ice_math_mat_norm(ice_math_mat m);
ice_math_mat  ice_math_mat_identity(void);
ice_math_mat  ice_math_mat_add(ice_math_mat left, ice_math_mat right);
ice_math_mat  ice_math_mat_sub(ice_math_mat left, ice_math_mat right);
ice_math_mat  ice_math_mat_translate(double x, double y, double z);
ice_math_mat  ice_math_mat_rotate(ice_math_vec3 axis, double angle);
ice_math_mat  ice_math_mat_rotate_xyz(ice_math_vec3 ang);
ice_math_mat  ice_math_mat_rotate_zyx(ice_math_vec3 ang);
ice_math_mat  ice_math_mat_rotate_x(double ang);
ice_math_mat  ice_math_mat_rotate_y(double ang);
ice_math_mat  ice_math_mat_rotate_z(double ang);
ice_math_mat  ice_math_mat_scale(double x, double y, double z);
ice_math_mat  ice_math_mat_mult(ice_math_mat left, ice_math_mat right);
ice_math_mat  ice_math_mat_frustum(double left, double right, double bottom, double top, double near, double far);
ice_math_mat  ice_math_mat_perspective(double fovy, double aspect, double near, double far);
ice_math_mat  ice_math_mat_ortho(double left, double right, double bottom, double top, double near, double far);
ice_math_mat  ice_math_mat_lookat(ice_math_vec3 eye, ice_math_vec3 target, ice_math_vec3 up);

// Vertices
// WARNING: They allocate memory, Consider freeing vertices with ice_math_free_vertices() when program finishes!
double*  ice_math_point2d_vertices(ice_math_vec2 v);
double*  ice_math_line2d_vertices(ice_math_vec2 v1, ice_math_vec2 v2);
double*  ice_math_rect2d_vertices(ice_math_rect r);
double*  ice_math_circle2d_vertices(ice_math_vec2 pos, double r);
double*  ice_math_triangle2d_vertices(ice_math_vec2 v1, ice_math_vec2 v2, ice_math_vec2 v3);
double*  ice_math_polygon2d_vertices(ice_math_vec2 v, double size, int sides);
double*  ice_math_tex2d_rect_vertices(ice_math_rect src, ice_math_rect dst, int width, int height);
double*  ice_math_tex2d_tex_vertices(ice_math_rect src, ice_math_rect dst, int width, int height);

double*  ice_math_cube_vertices(ice_math_vec3 v, double s);
double*  ice_math_cuboid_vertices(ice_math_vec3 v, ice_math_vec3 s);
double*  ice_math_sphere_vertices(ice_math_vec3 v, double s);
double*  ice_math_point3d_vertices(ice_math_vec3 v);
double*  ice_math_line3d_vertices(ice_math_vec3 v1, ice_math_vec3 v2);
double*  ice_math_rect3d_vertices(ice_math_rect r, double z);
double*  ice_math_circle3d_vertices(ice_math_vec3 pos, double r);
double*  ice_math_triangle3d_vertices(ice_math_vec3 v1, ice_math_vec3 v2, ice_math_vec3 v3);
double*  ice_math_polygon3d_vertices(ice_math_vec3 v, double size, int sides);
double*  ice_math_tex3d_rect_vertices(ice_math_rect src, ice_math_rect dst, double z, int width, int height);
double*  ice_math_tex3d_tex_vertices(ice_math_rect src, ice_math_rect dst, double z, int width, int height);

void     ice_math_free_vertices(double* vertices);

// Distances
ice_math_vec2  ice_math_dist2d(ice_math_vec2 v1, ice_math_vec2 v2);
double         ice_math_dist2d_between(ice_math_vec2 v1, ice_math_vec2 v2);
ice_math_vec2  ice_math_rotate_around2d(ice_math_vec2 v1, ice_math_vec2 v2, double angle);
ice_math_vec3  ice_math_dist3d(ice_math_vec3 v1, ice_math_vec3 v2);
ice_math_vec4  ice_math_dist4d(ice_math_vec4 v1, ice_math_vec4 v2);

double         ice_math_rand(void);
```