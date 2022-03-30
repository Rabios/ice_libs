# Changelog

### March 30, 2022

1. Removed unit tests folder temporarily till unit tests are written completely (Will back soon...)
2. Rewrote `ice_str_rev` and `ice_str_copy` in `ice_str.h` to use `ice_str_sub` for simplicity...
3. Fixed simple typo in Nelua's `hello_ice_ffi.nelua` sample for `ice_ffi.h`
4. Both `ice_clip_use_native_activity` and `ice_batt_use_native_activity` in `ice_batt.h` now takes constant pointer to the Native Activity on Android for const-correctness...
5. `ice_clip_use_window` in `ice_clip.h` now takes constant pointer to the Window on Microsoft Windows for const-correctness...
6. `ice_fs_free_dir_content` in `ice_fs.h` now takes pointer to `ice_fs_dir` to free without any duplication when passing by value...
7. `ice_time_diff` and `ice_time_since` and `ice_time_dt` in `ice_time.h` now takes constant pointers to `ice_time_info` struct to avoid duplication when passing by value...
8. Fixed linking typo in Nelua's `ice_time.h` bindings for RPi Pico!

### March 21, 2022

1. Redesigned marcros for `ice_al.h`
2. Unit Tests for `ice_batt.h` and `ice_clip.h` and `ice_cpu.h` and `ice_ram.h`
3. Updated TODO for next goals, Also currently working on `ice_vecmath.h` and the bindings and also the site! :D

### March 9, 2022

1. Security improvements have been done for `ice_al.h` and `ice_ffi.h`
2. Extended string length for `ice_cpu_brand` (CPU Name) on Microsoft Platforms
3. Fixed `ice_fs_type` function in `ice_fs.h` to be compatible with MSVC!
4. Improved some samples...
5. Removed `zip` and `unzip` packages installation from `check_packages.sh` as we don't use them locally...

### March 8, 2022

1. ice_libs have passed 1 year on GitHub! (Happy Anniversary!)
2. `ice_fs.h` released, Which is a Single-Header Cross-Platform C library to work with files and directories and paths!
3. Done some patches to prevent crashes in some libraries!
4. Added sample for `ice_fs.h` along with bindings for DragonRuby, LuaJIT, and Nelua!
5. Added build scripts based on the same ones used in GitHub Actions, So you can build locally on your device.
6. Build flags for the workflow are now more strict, Which allowed to fix a lot of problems...
7. Renamed `ice_str_arr_free` to `ice_str_free_arr` in `ice_str.h`
8. Fixed `ice_cpu.h` on BSDs!
9. Updated TODO for next goals!
10. Simplified the GitHub Actions workflow build script...
11. Splitted DragonRuby/MRuby bindings into `cexts` folder and added Ruby files that loads the compiled shared library of the bindings along with Ruby definitions for each library!
12. Added invalid pointer error codes to the libraries that uses error enumerations (Like `ice_batt.h` and `ice_time.h`)
13. Fixed reverse of string mechanism for `ice_str_rev` in `ice_str.h`

### February 18, 2022

Re-added the changelog with more extended and easy-to-read info!

### February 17, 2022

1. Fixed retrieving the uptime on Linux for `ice_time.h`
2. The build workflow got working successfully and libraries are being built each time `dev` branch recieves a commit!

### February 16, 2022

The build workflow was extended to build all the libraries on Microsoft Windows (32-bit and 64-bit) and Linux (32-bit and 64-bit)

### February 15, 2022

The build workflow was back, Initially started with `ice_cpu.h`

### February 8, 2022

String replacement mechanism for `ice_str_rep` function in `ice_str.h` was rewritten to work more efficiently!

### February 7, 2022

Added schedule for upcoming stuff!

### January 27, 2022

Following improvements for `ice_str.h` were done:

1. Now `ice_str_sub` returns dynamically-allocated string that just contains a char if start index to finish index are both same...

2. Fixed `ice_str_split` due to fact that returns result incorrectly when the string has more than one delimiter but the delimiter is beside next/prev delimiter...

3. Fixed `ice_str_arr_free` and now it frees the array of strings completely...

### January 26, 2022

1. Replaced usage of `gettime` with `sysinfo` on Linux and that was done to void using `gnu99` standard...

2. As most Unix systems (Except for Apple Platforms and BSDs) does not have a programmatical way to calculate `uptime`, `ice_time.h` no longer supports these Unix systems...

### January 25, 2022

`ice_str_sub` in `ice_str.h` now able to create more longer substrings!

### January 24, 2022

1. Removed linking `msvcrt.lib` to avoid some warnings when compiling with MSVC...
2. Fixed bindings for Nelua and LuaJIT and DragonRuby, Plus that examples where added for them...
3. Fixed `ice_al.h` on Microsoft platforms
4. Fixed undefined reference to `ice_batt_get_info` in `ice_batt.h` and now removed `using namespace` lines for C++ implementations (UWP, BlackBerry 10) and added correct headers...
5. In `ice_clip.h`, removed `using namespace` lines for C++ implementations (UWP, BlackBerry 10) and added correct headers, In addition to check if no data is in Clipboard on Windows (Example now does not error and terminate if the Clipboard has no text...)
6. Fixed `ice_cpu.h` implementation for Microsoft platforms and removed requirement for C string functions...
7. Typo fixes (Retrive -> Retrieve)
8. Updated usage examples inside the headers...
9. In `ice_str.h` now `ice_str_len` returns `NULL` (zero) safely as string length if `NULL` (or zero) passed as parameter...
10. Updated header implementations and samples to comply with `-Wextra` flag!
11. `ice_test.h` now asserts for being the strings are not `NULL` (or zero) when comparing using `ICE_TEST_ASSERT_STR_EQU` and also used `ICE_TEST_CREATE` instead of `ICE_TEST_CREATE_EX` in the usage example...
12. Added disable security pragmas for `ice_time.h` so it won't warn because we are not using the C11 secure versions of the standard C library functions...
13. The examples of the bindings with the samples by all were both tested with MSVC and GCC on Microsoft Windows and they should also work fine on any other C compiler or platform as it can use the suitable implementation...
14. Updated TODO!
15. Fixed/Updated docs for the libraries!

### January 18, 2022

1. Fixed `ice_al.h` bindings for Nelua!
2. Improved linking for Nelua bindings of `ice_cpu.h` and `ice_ffi.h`
3. Now most of libraries links `msvcrt.lib` for MSVC when using standard C functions
4. Updated linking flags info for the libs
5. `ice_ease.h` is now more accurate when easing so it won't give wrong value if working with doubles
6. Fixed `alcGetContextsDevice` definition in `ice_al.h`
7. `ice_time_info` now uses `.seconds` instead of `.second` as property in `ice_time.h`, And also uses `.minutes` instead of `.minute` as property in `ice_time.h`
8. Added usage example for `ice_time.h`
9. Updated TODO!

### January 17, 2022

Improvements and fixes were done to the bindings (Nelua, LuaJIT, DragonRuby).

### January 15, 2022

1. Removed the build workflow temporarily till another working one being written...
2. Deleted incomplete libraries... (Which still WIP)
3. Fixed `ice_clip.h` support for macOS/OSX
4. Update list of libs.
5. Cleaned up `bindings` folder.
6. Included default linking flags for C compilers in the docs of the libs...
7. Optimized `ice_clip.h` for BlackBerry 10
8. Fixed documentation of `ice_batt.h`
9. Updated TODO!
10. Fixed includes of `ice_str.h` for UWP!
11. Updated the DragonRuby bindings, And `ice_batt.h` bindings for DragonRuby were added!
12. Extended the contributing info!
13. Updated the LuaJIT bindings!

### January 14, 2022

1. Polished the README with a new one!
2. `ice_batt.h` became compatible with all BSDs

### January 13, 2022

Fixed docs and improved platform checking for `ice_cpu.h`

### January 10, 2022

The following improvements to `ice_time.h` were done:

1. Fixed documentation inside the library...
2. Added LuaJIT and DragonRuby bindings for the library!
3. Removed the Emscripten support due to some constraints!

Also working on GitHub Actions workflow for building the libraries was started...

### January 7, 2022

1. Cleanup: Removed empty files...
2. `ice_ram.h` is now compatible with all BSDs in addition to QNX support (So it can work on BlackBerry PlayBook)
3. DragonRuby bindings for some libraries were added (In form of C extensions, DragonRuby Pro required to use C extensions...)
4. Improvements were done to some implementations that targets Apple platforms!

### January 4, 2022

Added LuaJIT bindings for following libraries:

1. `ice_batt.h`
2. `ice_clip.h`
3. `ice_cpu.h`
4. `ice_ram.h`
5. `ice_str.h`

And the first merge from `dev` to `master` was done! :D

### January 3, 2022

The following improvements for `ice_cpu.h` were done:

1. Now the library is compatible with all BSDs
2. Provided support for BlackBerry QNX! (Library now is able to run on BlackBerry PlayBook...)
3. Removed C++ code for BlackBerry 10 implementation (Now BlackBerry 10 support uses same implementation of QNX)

### January 2, 2022

Improvements were done for `ice_str.h`

### January 1, 2022

1. Bug fixes for a most of the libraries, In addition to providing Wiki for them...
2. Fixed fatal errors/bugs in some implementations...
3. Improved APIs and added examples for most libraries
4. Removed site and docs folder termporarily (Relying on Wiki for now...)
5. Removed images we don't need to...
6. Removed tests folder temporarily (As i'm testing libraries most of time)
7. Added the dual licenses in the entire repo and the libraries!

### December 30, 2021

1. Added samples for both of `ice_batt.h` and `ice_ffi.h`
2. Fixes were done to `ice_al.h` and `ice_ffi.h` and `ice_time.h`

### December 29, 2021

The rewrite of the libraries appeared on `dev` branch, Moving everything was in `master` to branch called `old` so stuff in `dev` can be merged easily to `master` with no troubles, Also following to libs were done:

1. Removed compound literals to comply with ANSI C
2. Done some improvements on ARC detection for Objective-C...
3. Cleaned some folders in dev branch
4. Edited libs info in rebase folder, where libraries are currently rewritten...
5. Added/Edited TODOs
6. Used C99 instead of C89 in `ice_ram.h` due to fact that RAM information on Microsoft Windows is retrieved in form 64-bit unsigned long integers...

### November 12, 2021

The `master` branch became obsolete, And hard stages of rewriting the libraries was into progress, And planned to initially push the rewrite into new branch called `dev` that will get merged to `master` depending on the state of the rewrite...

### September 5, 2021

Done some fixes to `ice_battery.h` for Android

### June 20, 2021

Released `ice_mouse.h` with usage sample in addition to sample that demonstrates the library with raylib, Also support for Tizen was implemented in some libraries.

### June 19, 2021

Done some fixes to `ice_joy.h` for Android, Fixed also Emscripten implementation of the libs.

### June 18, 2021

Added LuaJIT and Nelua bindings for some libraries!

### June 10, 2021

Added docs for `ice_al.h` and `ice_steam.h`

### May 27, 2021

Added the changelog!

### May 26, 2021

Fixed support of Linux and FreeBSD for `ice_joy.h` and added logos/icons, Also the Discord Server for ice_libs was created!

### May 24, 2021

After a long time, `ice_joy.h` added to the repo with usage sample.

### May 21, 2021

Fixed naming of GBA platform (Thanks to [Mahyar Koshkouei](https://github.com/deltabeard) for the fix)

### May 15, 2021

`ice_cpu.h` added to the repo with usage sample.

### April 25, 2021

`ice_arr.h` added to the repo and provided ability to work with custom memory allocators...

### April 23, 2021

`ice_str.h` and `ice_battery.h` were added to the repo with usage samples.

### April 22, 2021

`ice_fs.h` added to the repo and disable C11 security warnings for MSVC, In addition to some improvements for `ice_test.h`

### April 20, 2021

`ice_test.h` added to the repo with usage sample, And added licenses into each header...

### April 19, 2021

`ice_ram.h` added to the repo with usage sample, In addition to improvements for the other libs and their docs/samples.

### April 17, 2021

7 libraries added to the repo:

1. `ice_al.h`
2. `ice_clipboard.h`
3. `ice_easings.h`
4. `ice_ffi.h`
5. `ice_math.h`
6. `ice_steam.h`
7. `ice_time.h`

In addition to samples of each lib, Rewritten the libraries a bit to get more comfort, And added API docs page...

### April 8, 2021

ice_libs repo appeared on GitHub, Without libraries till April 17, 2021

### March 7, 2021

ice_libs started with `ice_joy.h` as the first library, Cross-Platform Single-Header library for working with Joystick input.

In the same time, Release time of `ice_joy.h` was delayed to after the repo appearation on GitHub by months...

### March 2021

ice_libs was into plans and about to be in development...
