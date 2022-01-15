# ice_libs

> NOTE: This project is still work in progress, Development of the project is still continuous in [`dev`](https://github.com/Rabios/ice_libs/tree/dev) branch and everyone is welcome to join development, Thanks for your patience...

<div align="center">
  <img src="img/icon1.png" width="256", height="256"><br><br>
  <p>Collection of Cross-Platform Single-Header C libraries for doing a lot of stuff! (Still WIP)</p>
</div>
<br>

### Brief and Goals

ice_libs is collection of Cross-Platform Single-Header C libraries for doing a lot of stuff...

Libraries were originally designed to cover what other Single-Header libraries miss (ex. `sokol_time.h` does not have Sleep function...) and in the same time it tries to provide backward compatibility with oldest standard ANSI C (C89) as best as possible, Except if libraries where in need to do implementation in C99, C++ (BeOS/Haiku, BlackBerry 10, UWP), or even Objective-C (Apple Platforms)

The libraries can detect the platform automatically to provide the suitable implementation, As they are able to run on any platform possible to implement like Mobile, Desktop, Web, Embeddable Platforms, and even Game Consoles (via Homebrew SDKs) with goal of keeping the portability and abstraction of them, Empowering softwares with high-level and user-friendly optimized API that does the same job without any changes required

Also, The libraries are designed to be bindings-friendly so the developer can write/generate bindings for his favourite programming language with ease and no pain, And allows developers to do some customizations on their own like changing the call convention or changing default memory allocation functions, Giving the developers a full power to write softwares the way they like...

The libraries are Dual-Licensed, The developer can choose between MIT and Public Domain depending on his preferences, See license [here](#license)

For more info check out the [Documentation](https://github.com/Rabios/ice_libs/wiki)

### Story

ice_libs originally started by [Rabia Alhaffar](https://github.com/Rabios) in March 2021 when he was working on gamepad input support for a project called fegame, Which would be a Cross-Platform game framework that leverages a lisp-like scripting language called [fe](https://github.com/rxi/fe)

At that time Rabia saw a project called [gainput](https://gainput.johanneskuhlmann.de) which represents his idea, But it's written in C++ and had bit of bugs and doesn't even support some platforms! (like BSD)

So at that time he started with library called `crosspad.h` that designed to be a cross-platform gamepad input library, Which later evolved into `ice_joy.h` as the first ice_libs library being in development, Then in April he decided to stop working on fegame in order to extend the project workspace to have more libs and form ice_libs!

### Libraries

For the list of libraries see [here](https://github.com/Rabios/ice_libs/wiki/Libraries)

### License

```
ice_libs is dual-licensed, Choose the one you prefer!

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

------------------------------------------------------------------------
LICENSE B - MIT LICENSE
------------------------------------------------------------------------
Copyright (c) 2021 - <Present> Rabia Alhaffar

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

1. [r-lyeh](https://github.com/r-lyeh), [Eduardo Bart](https://github.com/edubart), [André L. Alvares](https://github.com/Andre-LA), and [Nicolas Sauzede](https://github.com/nsauzede) for encouraging me to work on this!
2. [Together C and C++ Discord Server](https://discord.gg/99A4kq4a) community, They are very amazing and helped me when got stuck.
3. [Sean Barrett](https://github.com/nothings), [Dominik Madarász](https://github.com/zaklaus), [Andre Weissflog](https://github.com/floooh), and [Micha Mettke](https://github.com/vurtun) as i got inspiration from their libs to work on my own!
4. [younlok](https://github.com/younlok) for logos.
5. Also it worth mentioning [Amir Rajan](https://github.com/amirrajan) and [Ramon Santamaria](https://github.com/raysan5) for their help!
6. Everyone including you!
