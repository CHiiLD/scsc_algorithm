#ifndef __BINFUNC_H__
#define __BINFUNC_H__

#include "bintree.h"
#include "binadd.h"

bnode *bin_copy(bnode *origin);

bnode *bin_mirrorCopy(bnode *origin);

int bin_equal(bnode *expect, bnode *actual);

void bin_bintreeOperTest();

#endif //__BINFUNC_H__