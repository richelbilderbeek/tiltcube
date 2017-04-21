const int pin_red = 9;
const int pin_green = 10;
const int pin_blue = 11;
const int pin_tilt_x = A0;
const int pin_tilt_y = A1;
const int pin_tilt_z = A2;

///State of x axis as a moving average
///Will go to zero, if pin_tilt_x is zero
///Will go to 1023, if pin_tilt_x is 1023
int x = 0;

///State of y axis as a moving average
///Will go to zero, if pin_tilt_y is zero
///Will go to 1023, if pin_tilt_y is 1023
int y = 0;

///State of z axis as a moving average
///Will go to zero, if pin_tilt_z is zero
///Will go to 1023, if pin_tilt_z is 1023
int z = 0;

///Used to calculate the new states of the x, y and z axes.
///alpha denotes the influence of the current value measured
///alpha = 1.0: no moving average, just respond to current values
///alpha = 0.1: it takes some time to converge to the current (constant value)
//double alpha = 0.5;

///LED redness
int red = 0;
///LED greenness
int green = 0;
///LED blueness
int blue = 0;

void setup()
{
  pinMode(pin_red, OUTPUT);
  pinMode(pin_green, OUTPUT);
  pinMode(pin_blue, OUTPUT);
  pinMode(pin_tilt_x, INPUT);
  pinMode(pin_tilt_y, INPUT);
  pinMode(pin_tilt_z, INPUT);
}

void loop()
{
  //X
  const int x_prev = x;
  const int x_now = analogRead(pin_tilt_x);
  if (x_prev < 512 && x_now > 512) red += 64;
  if (x_prev > 512 && x_now < 512) red += 64;
  //Y
  const int y_prev = y;
  const int y_now = analogRead(pin_tilt_y);
  if (y_prev < 512 && y_now > 512) green += 64;
  if (y_prev > 512 && y_now < 512) green += 64;
  //Z
  const int z_prev = z;
  const int z_now = analogRead(pin_tilt_z);
  if (z_prev < 512 && z_now > 512) blue += 64;
  if (z_prev > 512 && z_now < 512) blue += 64;
  //Display
  red %= 256;
  green %= 256;
  blue %= 256;
  analogWrite(pin_red, red);
  analogWrite(pin_green, green);
  analogWrite(pin_blue, blue);
  //Update
  x = x_now;
  y = y_now;
  z = z_now;
  //Wait
  delay(10);
}
