
#include "ccsv.h"

static VALUE rb_cC;

static VALUE foreach(VALUE self, VALUE filename) {
  FILE *file = fopen(StringValueCStr(filename), "r");
  
  char line[MAX_LENGTH];
  char *token;
  VALUE parsed;
  
  int i, j;
  while (fgets(line, sizeof(line), file) != NULL) {
    token = strtok(line, DELIMITERS);
    parsed = rb_ary_new2(2);
    
    while (token != NULL) {
      rb_ary_push(parsed, rb_str_new2(token));
      token = strtok(NULL, DELIMITERS);
    }
    rb_yield_splat(parsed);
  }

  return Qnil;
}

void
Init_ccsv()
{
  rb_cC = rb_define_class("Ccsv", rb_cObject);
  rb_define_singleton_method(rb_cC, "foreach", foreach, 1);
}