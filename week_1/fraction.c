#include "fraction.h"
#include <stdlib.h>

Fraction add ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.den + a.den * b.num, a.den * b.den };
}

Fraction multiply ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.num, a.den * b.den };
}

Fraction reduce ( Fraction a) {
  int bottom, upper, num_final, den_final;

  if (a.den == 0 && a.num == 0)
  {
     num_final = 0;
     den_final = 0;
  }
  else if (a.den == 0 )
  {
     num_final = 1;
     den_final = 0;
  }
  else if (a.num == 0)
  {
     num_final = 0;
     den_final = 1;
  }
  else if (abs(a.den) > abs(a.num))
  {
    bottom = abs(a.num);
    upper = abs(a.den);

    int c = upper % bottom;

    while (c > 0)
    {
       upper = bottom;
       bottom = c;
       c = upper % bottom;
    }
    
    num_final = a.num / bottom;
    den_final = a.den / bottom;
  }
  else
  {
    bottom = abs(a.den);
    upper = abs(a.num);

    int c = upper % bottom;

    while (c > 0)
    {    
       upper = bottom;
       bottom = c;
       c = upper % bottom;
    }

    num_final = a.num / bottom;
    den_final = a.den / bottom;
  }
     
  return (Fraction) {num_final, den_final};
}