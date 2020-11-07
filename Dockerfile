FROM node:15
WORKDIR /app
ENV PATH="/app/bin:${PATH}"
COPY package.json /app
COPY package-lock.json /app 
COPY install_arduino.sh /app
RUN sh install_arduino.sh
# COPY arduino-lib.tar.gz /usr/share/arduino
RUN npm install
COPY . /app
CMD ["npm", "start"]
