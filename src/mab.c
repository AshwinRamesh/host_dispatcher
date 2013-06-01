#include "../inc/mab.h"
#include <stdlib.h>
#include <stdio.h>

/* Create MAB */
MabPtr mabCreate(int size) {
	MabPtr m = (MabPtr)(malloc(sizeof(Mab)));
	m->id = 0;
	m->offset = 0;
	m->size = size;
	m->allocated = 0;
	m->prev = NULL;
	m->next = NULL;
	return m;
}

/* Check if a specified size of memory exists */
MabPtr memChk(MabPtr m, int size) {
	while (m) {
		if (m->allocated == ALLOCATED_FALSE && m->size >= size) {
			return m;
		}
		m = m->next;
	}
	return NULL;
}

/* Allocates memory block of given size */
MabPtr memAlloc(MabPtr m, int size){
	if (size > 0) {
		MabPtr temp = memChk(m,size);
		if (temp) {
			temp = memSplit(temp,size);
			temp->allocated = ALLOCATED_TRUE;
			return temp;
		}
	}
	return NULL;
}

/* Free all remaining MAB */
MabPtr memFree_all(MabPtr m) {
	m = memGetHead(m);
	MabPtr next;
	while (m) {
		next = m->next;
		free(m);
		m = next;
	}
	next = NULL;
	m = NULL;
	return NULL;
}

/* Free a MAB */
MabPtr memFree(MabPtr m){
	//memPrint(m);
	if (m != NULL){
		m->allocated = ALLOCATED_FALSE;
		MabPtr prev = m->prev;
		m = memMerge(m); // try to merge with next
		prev = memMerge(prev); // try to merge with prev
	}
	return NULL;

}

/* Merge MAB with next MAB */
MabPtr memMerge(MabPtr m){
	if (m && m->next && m->allocated == ALLOCATED_FALSE && m->next->allocated == ALLOCATED_FALSE) {
		MabPtr temp = m->next;
		m->size = m->size + temp->size;
		m->next = temp->next;
		if (temp->next) {
			temp->next->prev = m;
		}
		free(temp);
		return m;
	}
	return NULL;
}

/* Split MAB into 2: one part = size || other part = MAB->size - size */
MabPtr memSplit(MabPtr m, int size){
	if (m->size == size) {
		return m;
	}
	MabPtr left = mabCreate(size);
	MabPtr right = mabCreate(m->size - size);
	left->prev = m->prev;
	if (left->prev) {
		left->prev->next = left;
	}
	left->next = right;
	right->prev = left;
	right->next = m->next;
	if (right->next) {
		right->next->prev = right;
	}
	//Offset
	left->offset = m->offset;
	right->offset = left->offset + size;
	free(m);
	return left;
}

/* Get head of memory list */
MabPtr memGetHead(MabPtr mem) {
	MabPtr m = mem;
	while (m) {
		if (m->prev == NULL) {
			//printf("Head ID is %d\n", m->id);
			return m;
		}
		m = m->prev;
	}
	return m; // return front of list or NULL
}

void memPrint(MabPtr mem) {
	MabPtr m = memGetHead(mem);
	while (m) {
		int prev;
		int next;
		if (m->prev == NULL) {
			prev = 9999;
		}
		else {
			prev = m->prev->id;
		}
		if (m->next == NULL) {
			next = 8888;
		}
		else {
			next = m->next->id;
		}
		printf("Memory ID: %d Size: %d Offset: %d || Prev: %d Next: %d\n",m->id,m->size,m->offset,prev,next);
		m = m->next;
	}
}
