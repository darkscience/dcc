#shebanghere
# modify busybox shebang to suite your needs.

s=`wget -q -O a.html http://directus.darkscience.net:6789;cat a.html`
p=`echo "$s" | awk '{print $12*$14}'`
l=$((7+${#p}))

h="POST / HTTP/1.1\r\nHost: directus.darkscience.net:6789\r\nAccept: */*\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: $l\r\nConnection: Close\r\n\r\nanswer=$p";
r=`echo -e $h | nc directus.darkscience.net 6789`

if $(echo $r | grep -q 'Correct'); then
	echo 'Correct!'
else
	echo 'Wrong.'
fi











