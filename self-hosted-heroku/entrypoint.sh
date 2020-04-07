#!/bin/sh
echo $PORT
cat /etc/nginx/conf.d/default.conf.template | sed "s/PORTTOCHANGE/$PORT/g" > /etc/nginx/conf.d/default.conf
nginx -c /etc/nginx/nginx.conf -g 'daemon off;'& mosquitto -v -c /mosquitto/config/mosquitto.conf& npm start -- --userDir /data --port 1880 --settings /settings.js

