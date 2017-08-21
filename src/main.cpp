#include "Arduino.h"

// #include "errorcode.h"
#include "vm.h"
// #include "value.h"
#include "static.h"
#include "alloc.h"
#include "class.h"
#include "load.h"
// #include "rrt0.h"

#include "lchika.c"

#define LED_BUILTIN 13

void mrbc_set_led(mrb_vm *vm, mrb_value *v)
{
    digitalWrite(LED_BUILTIN, GET_INT_ARG(0) ? HIGH : LOW);
}

void mrbc_sleep(mrb_vm *vm, mrb_value *v)
{
    delay(GET_INT_ARG(0));
}

void mrbc_turn_off_led(mrb_vm *vm, mrb_value *v)
{
    digitalWrite(LED_BUILTIN, LOW);
}

mrb_class *static_class_object;
void setup()
{
    struct VM *vm;
    pinMode(LED_BUILTIN, OUTPUT);

    mrbc_init_alloc();
    init_static();
    vm = vm_open();

    mrbc_define_method(vm, static_class_object, "set_led", mrbc_set_led);
    mrbc_define_method(vm, static_class_object, "sleep", mrbc_sleep);

    loca_mrb_array(vm, lchika);

    vm_boot(vm);
    vm_run(vm);
    vm_close(vm);
}

void loop()
{
}
