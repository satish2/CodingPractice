/*
 * satish.h
 *
 *  Created on: Apr 20, 2015
 *      Author: Satish
 */

#ifndef SATISH_H_
#define SATISH_H_

typedef struct node {
	int data;
	struct node *next;
}node_t;

extern struct node* makeLinkedList(int *values);
extern void printLinkedList(struct node *head);
extern struct node* sortLinkedList(struct node *head);

#endif /* SATISH_H_ */
