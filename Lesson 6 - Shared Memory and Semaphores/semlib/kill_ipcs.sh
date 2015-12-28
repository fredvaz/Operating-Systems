#--------------------------------------------------------------------------
#                   kill_ipcs.sh
#--------------------------------------------------------------------------
#!/bin/bash

ME=`whoami`      # Note: `whoami` == $(whoami)

IPCS_M=$(ipcs -m | egrep "0x[0-9]+ [0-9]+" | grep $ME | cut -f2 -d" ")
IPCS_S=$(ipcs -s | egrep "0x[0-9]+ [0-9]+" | grep $ME | cut -f2 -d" ")
IPCS_Q=$(ipcs -q | egrep "0x[0-9]+ [0-9]+" | grep $ME | cut -f2 -d" ")

for id in $IPCS_M; do
  ipcrm shm $id;
done

for id in $IPCS_S; do
  ipcrm sem $id;
done

for id in $IPCS_Q; do
  ipcrm msg $id;
done

#--------------------------------------------------------------------------

