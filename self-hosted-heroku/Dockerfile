FROM razikus/nodered-squash:squash

USER root
RUN apk update && apk add --no-cache mosquitto nginx apache2-utils
COPY mosquitto.conf /mosquitto/config/mosquitto.conf
COPY entrypoint.sh /entrypoint.sh
COPY default.conf.template /etc/nginx/conf.d/default.conf.template
COPY nginx.conf /etc/nginx/nginx.conf
COPY settings.js /settings.js
COPY acl.conf /pass/acl.conf
COPY changepassword /usr/bin/changepassword
RUN touch /pass/passwd && mosquitto_passwd -b /pass/passwd  admin admin && htpasswd -cb /pass/nginx admin admin && chmod +x /entrypoint.sh && chown -R node-red:node-red /etc/nginx && chown -R node-red:node-red /var/lib/nginx/ && chown -R node-red:node-red /var/log && chown -R node-red:node-red /pass  
USER node-red
ENTRYPOINT ["/entrypoint.sh"]


