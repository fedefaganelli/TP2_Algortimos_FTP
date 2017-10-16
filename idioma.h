#ifndef IDIOMA__H
#define IDIOMA__H 1     /* proteccion de inclusiones multiples*/ 
#define LANG_ES_AR

#if defined(LANG_ES_AR)  /* para definir un idioma */
#include "es_ar.h"

#elif defined(LANG_EN_US) /* else if: para definir otro idioma, se usa else para varios idiomas */
#include "en_us.h"


#endif
#endif