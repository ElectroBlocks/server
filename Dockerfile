FROM node:15
RUN mkdir -p /app
WORKDIR /app
ENV PATH="/app/bin:${PATH}"
COPY package.json /app
COPY package-lock.json /app 
COPY app.js /app
COPY install_arduino.sh /app
RUN sh install_arduino.sh
RUN npm install -g pm2
EXPOSE 8080
# COPY arduino-lib.tar.gz /usr/share/arduino
RUN npm install
CMD [ "pm2-runtime", "start", "app.js", "-i", "max" ]
