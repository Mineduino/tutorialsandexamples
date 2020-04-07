FROM nodered/node-red:latest-12

USER root
RUN apk update && apk add --no-cache mosquitto
COPY mosquitto.conf /mosquitto/config/mosquitto.conf

USER node-red
ENTRYPOINT ["/bin/sh", "-c", "mosquitto -c /mosquitto/config/mosquitto.conf& npm start -- --userDir /data --port $PORT"]

