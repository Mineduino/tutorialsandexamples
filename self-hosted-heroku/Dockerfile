FROM docker.pkg.github.com/mineduino/tutorialsandexamples/nodered:squash

USER root
RUN apk update && apk add --no-cache mosquitto
COPY mosquitto.conf /mosquitto/config/mosquitto.conf
ENV PORT=1880
COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
COPY settings.js /settings.js
USER node-red
ENTRYPOINT ["/entrypoint.sh"]


