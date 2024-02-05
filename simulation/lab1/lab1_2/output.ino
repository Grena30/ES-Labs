FILE f_out;
int sput(char c, __attribute__((unused)) FILE* f) {return !Serial.write(c);}

void redirectOutput(){
  fdev_setup_stream(&f_out, sput, nullptr, _FDEV_SETUP_WRITE); // cf https://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html#gaf41f158c022cbb6203ccd87d27301226
  stdout = &f_out;
}
