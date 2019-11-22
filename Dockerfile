FROM node:9-slim
RUN apt-get update && apt-get install -y arduino-mk
WORKDIR /app
COPY package.json /app
COPY package-lock.json /app 
RUN npm install
COPY . /app
CMD ["npm", "start"]
