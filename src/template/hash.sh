#!/bin/sh
file=${1:-$(ls -t *.cpp | head -n 1)}
out="${file%.*}"

g++ -std=gnu++2a -D_DEBUG -Wall -Wextra -Wshadow -Wconversion -fsanitize=undefined,address -ggdb "$file" -o "$out" &&
g++ -dD -E -P -fpreprocessed "$file" | tr -d '[:space:]' | md5sum | cut -c-6