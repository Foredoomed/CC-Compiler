/***************************************************************************
*cr
*cr            (C) Copyright 1995-2009 The Board of Trustees of the
*cr                        University of Illinois
*cr                         All Rights Reserved
*cr
***************************************************************************/

/***************************************************************************
* RCS INFORMATION:
*
*      $RCSfile: hash.h,v $
*      $Author: johns $        $Locker:  $             $State: Exp $
*      $Revision: 1.8 $      $Date: 2013/05/30 21:57:27 $
*
***************************************************************************
* DESCRIPTION:
*   A simple hash table implementation for strings, contributed by John Stone,
*   derived from his ray tracer code.
***************************************************************************/
#ifndef HASH_H
#define HASH_H

typedef struct hash_t {
  struct hash_node_t **bucket;      /* array of hash nodes */
  int size;                         /* size of the array */
  int entries;                      /* number of entries in table */
  int downshift;                    /* shift count, used in hash function */
  int mask;                         /* used to select bits for hashing */
} hash_t;

#define HASH_FAIL -1


void hash_init(hash_t *, int);

char * hash_lookup (const hash_t *, const char *);

int hash_insert (hash_t *, const char *, char *);

char * hash_delete (hash_t *, const char *);

int hash_entries(hash_t *);

void hash_destroy(hash_t *);

char *hash_stats (hash_t *);

#endif
