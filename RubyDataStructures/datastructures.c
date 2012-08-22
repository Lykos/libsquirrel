#include "datastructures.h"

static VALUE Example;

extern "C" void Init_datastructures(void)
{
  //Erstelle die Klasse Example als Subklasse von Object
  Example = rb_define_class("Example", rb_cObject);

  //Fge Example die Instanzmethode hello_world hinzu
  rb_define_method(Example, "hello_world", method_hello_world, 0);
}

/*
*Document-class: Example
*
*Diese Klasse ist eine Beispielklasse.
*/

/*
*call-seq:
*  hello_world ==> "Hello world!"
*
*Diese Methode gibt den String <tt>"Hello world!"</tt>
*zurck.
*/
VALUE method_hello_world(VALUE self) //self sollte explizit angegeben werden, auch wenn es nicht benutzt wird
{
  return rb_str_new2("Hello World!");
}
