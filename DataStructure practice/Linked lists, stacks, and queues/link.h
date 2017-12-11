/*
 * This file contains the definition of a link structure for implementing
 * singly-linked lists that contain integer values.
 */

#ifndef __LINK_H
#define __LINK_H

struct link {
  int value;
  struct link* next;
};

#endif
