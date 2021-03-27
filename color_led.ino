int red_pin = 11;
int blue_pin = 10;
int green_pin = 9;

int val;
char * incoming_buffer ;
char * last_color;

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_pin, red_light_value);
  analogWrite(green_pin, green_light_value);
  analogWrite(blue_pin, blue_light_value);
}

void setup() { 
 // set the pins
 pinMode(red_pin, OUTPUT);
 pinMode(blue_pin, OUTPUT);
 pinMode(green_pin, OUTPUT);
 
  Serial.begin(9600); 
  while(!Serial){
   ;// waiting for the serial port to connect 
  }
  Serial.println("Hello from arduino!");
  
  RGB_color(0, 0, 0); // Red
  delay(1000);
}

void loop() {
  
  
  Serial.readBytes(incoming_buffer, 1);

  last_color = incoming_buffer;
  switch (atoi(incoming_buffer)){
   case 1:
     RGB_color(255, 0, 0); // Red
     Serial.println("RED");
     delay(1000);
     break;
   case 2:
     RGB_color(0, 255, 0); // Green
     Serial.println("GREEN");
     delay(1000);
     break;
   case 3:
     RGB_color(0, 0, 255); // Blue
     Serial.println("BLUE");
     delay(1000);
     break;
   case 4:
     RGB_color(255, 255, 125); // Raspberry
     Serial.print("Raspberry");
     delay(1000);
     break;
   case 5:
     RGB_color(0, 255, 255); // Cyan
     delay(1000);
     break;
   case 6:
     RGB_color(255, 0, 255); // Magenta
     delay(1000);
     break;
   case 7:
     RGB_color(255, 255, 0); // Yellow
     delay(1000);
     break;
  }
  
  if(!Serial.available()){
     RGB_color(0, 0, 0); // Red
     delay(1000);
  }
  
}
