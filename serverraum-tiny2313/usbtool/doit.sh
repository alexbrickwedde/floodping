for a in `seq 1 3` ; do /usr/src/vusb-20100715/examples/usbtool/usbtool  -v 0x16c0 -p 0x5dc -V floodping.org -P servert -d 1,2,3,4 control in 1 1 $a 0 0 ; sleep 1 ; done
