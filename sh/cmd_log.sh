#!/system/bin/sh

#while true; do cat /sys/class/thermal/thermal_zone*/temp;sleep 1; done; > /data/d.txt

a=1

while true
do 
   cat /sys/class/thermal/thermal_zone*/temp >> /data/d.txt
   sleep 1; 
   echo $a >> /data/d.txt
   a=$(($a+1))
   echo "===" >> /data/d.txt
done
