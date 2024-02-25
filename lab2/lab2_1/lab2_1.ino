#include <Arduino.h>
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task_idle.h"

void setup() {
    task1_setup();
    task2_setup();
    task3_setup();
    task_idle_setup();
}

void loop() {
    task1_loop();
    task2_loop();
    task3_loop();
    task_idle_loop();
}