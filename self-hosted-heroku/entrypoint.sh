#!/bin/sh

mosquitto -c /mosquitto/config/mosquitto.conf& npm start -- --userDir /data --port $PORT

