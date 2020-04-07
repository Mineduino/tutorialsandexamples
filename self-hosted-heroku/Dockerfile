FROM nodered/node-red:latest-12

USER root
RUN apk update && apk add --no-cache mosquitto
COPY mosquitto.conf /mosquitto/config/mosquitto.conf

USER node-red
COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
ENTRYPOINT ["/entypoint.sh"]


