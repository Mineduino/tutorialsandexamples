FROM nodered/node-red:latest-12

USER root
RUN apk update && apk add --no-cache mosquitto
COPY mosquitto.conf /mosquitto/config/mosquitto.conf

COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
USER node-red
ENTRYPOINT ["/entypoint.sh"]


