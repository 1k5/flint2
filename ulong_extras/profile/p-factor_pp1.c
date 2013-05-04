/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright 2012 William Hart

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "profiler.h"
#include "flint.h"
#include "ulong_extras.h"

int main(void)
{
   ulong c;
   ulong B1; 
   mp_limb_t n, p;

   flint_rand_t state;
   flint_randinit(state);

   while(1)
   {
      printf("Enter number to be factored: "); fflush(stdout);
      if (!scanf("%lu", &n))
      {
         printf("Read failed\n");
         abort();
      }
   
      printf("Enter B1: "); fflush(stdout);
      if (!scanf("%lu", &B1))
      {
         printf("Read failed\n");
         abort();
      }
    
      do
      {
         c = n_randint(state, n);
      } while (c <= 2UL);

      p = n_factor_pp1(n, B1, c);
      if (p >= 2)
         printf("Factor: %lu\n", p);
      else
         printf("Factor not found!\n");
   } while(1);
   
   flint_randclear(state);

   return 0;
}