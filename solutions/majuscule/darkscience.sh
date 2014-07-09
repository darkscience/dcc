#!/usr/bin/env bash
# written by dylan@dylansserver.com
# for the good folk at http://www.darkscience.net/wiki/dcc/

#q='http://directus.darkscience.net:6789'
#q=http://directus.darkscience.net:6789
#q=directus.darkscience.net:6789
#q=149.154.154.59:6789
c='curl -s 149.154.154.59:6789'
#curl $q -sd answer=$(curl -s $q|sed -re 's/.* ([0-9]+) x ([0-9]+).*/\1*\2\n/p'|bc)|sed -rne 's/.*(Correct|Wrong).*/\1/p'
#curl $q -sd answer=$(curl -s $q|sed -rn 's/.* ([0-9]+) x ([0-9]+).*/\1*\2\n/p'|bc)|sed -r 's/.*(C|W).*/\1/'|tr CW YN
#curl $q -sd answer=$(curl -s $q|awk '{print $12*$14}')|sed -r 's/.*(C|W).*/\1/'|tr CW YN
#curl $q -sd answer=`curl -s $q|awk '{print $12*$14}'`|sed -r 's/.*(C|W).*/\1/'|tr CW YN
#curl $q -sd answer=`curl -s $q|awk '{print $12*$14}'`|grep -q C;echo $?|tr 01 YN
#curl $q -sd answer=`curl -s $q|awk '{print $12*$14}'`|grep -q C&&echo Y||echo N
#curl $q -sd answer=`curl -s $q|awk '{print$12*$14}'`|grep -q C&&echo Y||echo N
#curl $q -sdanswer=`curl -s $q|awk '{print$12*$14}'`|grep -q C&&echo Y||echo N
# Thanks to Riviera and igli in freenode#awk
#curl $q -sdanswer=`curl -s $q|awk '{$0=$12+$14}1'`|grep -q C&&echo Y||echo N
# After confirmation by derecho@sector5d.org concerning output
#curl $q -sdanswer=`curl -s $q|awk '{$0=$12*$14}1'`|grep -q C;echo $?
# typos!
#curl $q -sdanswer=`curl -s $q|awk '{$0=$12*$14}1'`|grep -q W;echo $?
# Thanks to Camusensei in freenode#sed
$c -danswer=`$c |awk '{$0=$12*$14}1'`|grep -q W;echo $?


#!/usr/bin/env bash
# we'll find the second hashbang in this file, then we'll gather each SOC.
# we'll replace newlines with colons, then chomp, then count characters

solutionEnd=$(grep -n '#!' $0 | tail -n1 | awk -F: '{print $1}');

echo 'This solution is'        \
    $(head -n${solutionEnd} $0 \
        | sed -ne '/^[^#]/p'   \
        | sed -n 'N;s/\n/;/p'  \
        | tr -d '\n' | wc -c)  \
    'characters long.'
