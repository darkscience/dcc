c='curl -s 149.154.154.59:6789';$c -danswer=`$c |awk '{$0=$12*$14}1'`|grep -q W;echo $?
