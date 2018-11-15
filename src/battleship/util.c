/*
 * util.c
 *
 *  Created on: 22 Oct 2018
 *      Author: pejdavies1606
 */

#include "util.h"

#include <errno.h>
#include <limits.h>

bool ParseUnsignedLong(const char *str, unsigned long *val)
{
    bool ret = true;
    char *endstr = NULL;
    errno = 0;
    *val = strtoul(str, &endstr, 10); // radix 10 = decimal

    if (str == endstr)
       ret = false; // invalid  (no digits found, 0 returned)
    else if (errno == ERANGE && *val == LONG_MIN)
       ret = false; // invalid  (underflow occurred)
    else if (errno == ERANGE && *val == LONG_MAX)
       ret = false; // invalid  (overflow occurred)
    else if (errno == EINVAL)  /* not in all c99 implementations - gcc OK */
       ret = false; // invalid  (base contains unsupported value)
    else if (errno != 0 && *val == 0)
       ret = false; // invalid  (unspecified error occurred)
    else if (errno == 0 && str && !*endstr)
       ret = true; // valid  (and represents all characters read)
    else if (errno == 0 && str && *endstr != 0)
       ret = true; // valid  (but additional characters remain)

    return ret;
}

uint Number_Width(int n)
{
   uint w = 0;
   while (n != 0)
   {
      n /= 10;
      ++w;
   }
   return w;
}