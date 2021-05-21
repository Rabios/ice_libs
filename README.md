# ice_libs

Collection of cross-platform single-header C libraries for doing a lot of stuff! (Still WIP)

### Brief

ice_libs is collection of Single-Header C libraries, Designed to introduce stuff that sokol and some single-header libs didn't offered, In addition to more stuff offered by these libs.

### Goals

1. Portability: Supports ANSI C and onwards!
2. Cross-Platform: Runs on a lot of platform, Including Game Consoles.
3. Customizable: You can build shared libs of any ice library by the way you want.
4. Platform-Detectable: ice libraries can detect platform that program runs on, So you are not forced to define implementation platform and backend used.
5. Controllable: Offers custom memory allocators, Custom calling conventions, And more...
6. Bindings-Friendly: Designed to make bindings much easier!
7. Easy to code.
8. Optimizable.
9. Easy to license: ice libraries allows you to choose between 2 licenses: Public Domain and MIT!

### Libraries

| library                                                                               | library description                                              | platforms supported                                                                                                                                     | languages     | lines of code |
|---------------------------------------------------------------------------------------|------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------|---------------|---------------|
| [ice_ffi.h](https://github.com/Rabios/ice_libs/raw/master/ice_ffi.h)                  | Cross-Platform Single-Header library to work with shared libs    | Microsoft platforms, Unix, Unix-like                                                                                                                    | C             | 299           |
| [ice_fs.h](https://github.com/Rabios/ice_libs/raw/master/ice_fs.h)                    | Cross-Platform Single-Header library for filesystem functions    | Anywhere                                                                                                                                                | C             | 1888          |
| [ice_clipboard.h](https://github.com/Rabios/ice_libs/raw/master/ice_clipboard.h)      | Cross-Platform Single-Header Clipboard library                   | Anywhere                                                                                                                                                | C, C++, Obj-C | 706           |
| [ice_ram.h](https://github.com/Rabios/ice_libs/raw/master/ice_ram.h)                  | Cross-Platform Single-Header library to get RAM info             | Microsoft platforms, Unix, Unix-like, Web, PSP                                                                                                          | C             | 384           |
| [ice_time.h](https://github.com/Rabios/ice_libs/raw/master/ice_time.h)                | Cross-Platform Single-Header Time library                        | Anywhere                                                                                                                                                | C             | 917           |
| [ice_easings.h](https://github.com/Rabios/ice_libs/raw/master/ice_easings.h)          | Cross-Platform Single-Header Easings library                     | Anywhere                                                                                                                                                | C             | 447           |
| [ice_math.h](https://github.com/Rabios/ice_libs/raw/master/ice_math.h)                | Cross-Platform Single-Header Math library                        | Anywhere                                                                                                                                                | C             | 3609          |
| [ice_al.h](https://github.com/Rabios/ice_libs/raw/master/ice_al.h)                    | Cross-Platform Single-Header OpenAL API loader                   | OpenAL API supported platforms                                                                                                                          | C             | 656           |
| [ice_steam.h](https://github.com/Rabios/ice_libs/raw/master/ice_steam.h)              | Cross-Platform Single-Header Steamworks API loader               | Steamworks API supported platforms                                                                                                                      | C             | 4754          |
| [ice_test.h](https://github.com/Rabios/ice_libs/raw/master/ice_test.h)                | Cross-Platform Single-Header Tiny unit testing lib               | Anywhere                                                                                                                                                | C             | 165           |
| [ice_str.h](https://github.com/Rabios/ice_libs/raw/master/ice_str.h)                  | Cross-Platform Single-Header for working with strings            | Anywhere                                                                                                                                                | C             | 614           |
| [ice_arr.h](https://github.com/Rabios/ice_libs/raw/master/ice_arr.h)                  | Cross-Platform Single-Header for working with numeric arrays     | Anywhere                                                                                                                                                | C             | 773           |
| [ice_battery.h](https://github.com/Rabios/ice_libs/raw/master/ice_battery.h)          | Cross-Platform Single-Header for getting battery info            | Microsoft platforms, Unix, Unix-like, Web, Nintendo Switch, PSP, PSVita                                                                                 | C             | 996           |
| [ice_cpu.h](https://github.com/Rabios/ice_libs/raw/master/ice_cpu.h)                  | Cross-Platform Single-Header for getting basic CPU info          | Microsoft platforms, Unix, Unix-like, Web, Nintendo Switch, PSP, PSVita, PS1, PS2, PS3, PS4, PS5, NDS, 3DS, HP-UX, IRIX, GameCube, Wii, WiiU, GBA   | C             | 719           |

> More libs incoming, Get prepared for!

> NOTE: Unix and Unix-like platforms means Linux, iOS, OSX, Haiku, BeOS, and Android.

> For docs of ice_libs see [here!](https://github.com/Rabios/ice_libs/blob/master/docs/README.md)

### License

All libraries in ice_libs are "Dual-Licensed" (MIT and Public Domain), Choose the one you prefer!

```
------------------------------------------------------------------------
LICENSE A - PUBLIC DOMAIN LICENSE
------------------------------------------------------------------------
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.
In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
```

```
------------------------------------------------------------------------
LICENSE B - MIT LICENSE
------------------------------------------------------------------------
Copyright (c) 2021 - 2022 Rabia Alhaffar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
```

### Special Thanks

1. [Eduardo Bart](https://github.com/edubart), [André L. Alvares](https://github.com/Andre-LA), and [Nicolas Sauzede](https://github.com/nsauzede) for encouraging me to work on this!
2. [Together C and C++ Discord Server](https://discord.gg/99A4kq4a) community, They are very amazing and helped me when got stuck.
3. [Sean Barrett](https://github.com/nothings), [Andre Weissflog](https://github.com/floooh), and [Micha Mettke](https://github.com/vurtun) as i got inspiration from their libs to work on my own!
4. Everyone including you!
