A=2509937211:6789;curl $A -danswer=`curl $A|awk '{print $12*$14}'`|cut -c81-87
