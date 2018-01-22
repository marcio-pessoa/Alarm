#include <Alarm.h>

Alarm test1(40, 60);
Alarm test2(40, 50, 20, 10);
Alarm test3(40, 50, 20, 10, true);

void setup() {
  Serial.begin(9600);
  test1.nameWrite("Speed");
  test1.unitWrite("k/h");
  test2.nameWrite("Temperature");
  test2.unitWrite("celcius");
  test3.nameWrite("Lenght");
  test3.unitWrite("meters");
}

void loop() {
  int i;
  for (i=30; i<=70; i++) {
    test1.check(i);
    Serial.println(test1.nameRead() + "," + test1.valueRead() + "," + test1.status_name());
  }
  for (i=0; i<=60; i++) {
    test2.check(i);
    Serial.println(test2.nameRead() + "," + test2.valueRead() + "," + test2.status_name());
  }
  for (i=0; i<=60; i++) {
    test3.check(i);
    Serial.println(test3.nameRead() + "," + test3.valueRead() + "," + test3.status_name());
  }
  delay(10 * 1000);
}
