#!/bin/bash

delay="0.1"
if [ "$#" -eq 1 ]; then
    delay=$1
fi

y=0
chars_with_pos=()

while read -r line; do
  x=0
  for char in $(echo $line | od -v -t x1 -A n); do
      chars_with_pos+=("$x;$y;$char")
      ((x++))
  done
  ((y++))
done

tput clear

(echo "${chars_with_pos[@]}" | xargs -n1 | sort -R) | \
while IFS=';' read -r i j char
do
  tput cup "$j" "$i"
  echo -ne "\x$char"
  sleep $delay
done

tput cup $y 0