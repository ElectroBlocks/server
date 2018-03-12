## Node Server that compile Arduino Code

So the end point is /upload-code/:board.  Right now it takes in raw code as the post body to compile. Right now we only compile for the arduino uno board.

``` 
curl -X POST \
  http://arduino-node.app/upload-code/uno \
  -H 'cache-control: no-cache' \
  -H 'postman-token: 907610fc-5665-71cb-ff6e-687ea34831a5' \
  -d 'void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}'
```

If you want to include libraries for the Arduino you have to put them in the sketchbook -> libraries folder.  You will also have to do sudo apt-get install arduino-mk to get the package that actually builds the arduino code.