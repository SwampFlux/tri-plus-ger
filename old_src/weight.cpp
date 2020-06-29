
#include <Arduino.h>

#define tmpl4                            \
   {                                     \
      4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 \
   }
#define tmpl2                            \
   {                                     \
      2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 \
   }
#define tmpl0                            \
   {                                     \
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 \
   }

int seq_weights[16][12] = {
    tmpl4, tmpl0, tmpl0, tmpl0,
    tmpl0, tmpl0, tmpl0, tmpl0,
    tmpl4, tmpl0, tmpl0, tmpl0,
    tmpl2, tmpl0, tmpl0, tmpl0};
