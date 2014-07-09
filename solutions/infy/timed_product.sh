#!/bin/bash

str=`curl -s http://directus.darkscience.net:6789/`

number_one=`echo $str | grep -oP '([0-9]{1,4}) x' | rev | cut -c 2- | rev`
number_two=`echo $str | grep -oP 'x ([0-9]{1,4})' | cut -c 2-`

product=$(($number_one*$number_two))

test=`curl --silent --header "Content-Type: application/x-www-form-urlencoded" --data-urlencode "answer=$product" http://directus.darkscience.net:6789`

if $(echo $test | grep --quiet 'Correct'); then
    echo 'Correct!'
else
    echo 'Wrong.'
fi