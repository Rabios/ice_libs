#!/usr/bin/env bash

# TODO: fix the build script, so it won't build ice_test.h

# Create directories for each platform...
mkdir -p ice_libs_builds/{win32,win64,linux32,linux64}

cp -rf rebase/*.h ice_libs_builds

libs=("ice_al" "ice_ffi" "ice_fs" "ice_batt" "ice_cpu" "ice_ease" "ice_ram" "ice_str" "ice_time" "ice_clip")

for l in ${libs[@]}; do
  x=$(echo "${l}"|tr '[:lower:]' '[:upper:]')
  printf "#define ${x}_IMPL 1\n#include \"${l}.h\"\n" > ice_libs_builds/${l}.c
done

win_link_flags=("-lkernel32" "-lkernel32" "-lkernel32" "-lkernel32" "-lm" "-lkernel32" "-lkernel32" "" "-lkernel32" "-lkernel32 -luser32")
linux_link_flags=("-ldl" "-ldl" "-lc" "-lc" "-lc" "-lm" "-lc" "-lc" "-lc")

for i in ${!libs[@]}; do
  # ========== Build: Microsoft Windows (x86/i386, x86_64) ========== #
  compile_flags_win="-Ofast"
  
  if [ "$i" -gt "1" ]; then
    if [ "$i" -eq "6" ]; then
      compile_flags_win="-std=c99 -pedantic -Wall -Wextra -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Werror -Ofast"
    else
      compile_flags_win="-std=c89 -pedantic -Wall -Wextra -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Werror -Ofast"
    fi
  fi
  
  i686-w64-mingw32-gcc -shared ice_libs_builds/${libs[$i]}.c -o ice_libs_builds/win32/${libs[$i]}.dll ${compile_flags_win} ${win_link_flags[$i]}
  x86_64-w64-mingw32-gcc -shared ice_libs_builds/${libs[$i]}.c -o ice_libs_builds/win64/${libs[$i]}.dll ${compile_flags_win} ${win_link_flags[$i]}
  
  # ========== Build: Linux (x86/i386, x86_64) ========== #
  if [ "$i" -ne "9" ]; then
    compile_flags_linux="-Ofast"
    
    if [ "$i" -eq "0" ] || [ "$i" -eq "4" ]; then
      compile_flags_linux+=" -fPIC"
    fi
    
    if [ "$i" -gt "2" ]; then
      compile_flags_linux+=" -pedantic -Wall -Wextra -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Werror"
      
      if [ "$i" -eq "6" ]; then
        compile_flags_linux+=" -std=c99"
      else
        compile_flags_linux+=" -std=c89"
      fi
    fi
    
    gcc -shared ice_libs_builds/${libs[$i]}.c -o ice_libs_builds/linux32/${libs[$i]}.so -m32 ${compile_flags_linux} ${linux_link_flags[$i]}
    gcc -shared ice_libs_builds/${libs[$i]}.c -o ice_libs_builds/linux64/${libs[$i]}.so ${compile_flags_linux} ${linux_link_flags[$i]}
  fi
done

rm -fr ice_libs_builds/*.c ice_libs_builds/*.h
