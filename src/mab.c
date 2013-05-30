#include "../inc/mab.h"
#include <stdlib.h>


/* Create MAB */
MabPtr mabCreate(int size) {
	MabPtr m = (MabPtr)(malloc(sizeof(Mab)));
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
	if (size > 0 && memChk(m,size)) {
		m = memSplit(m,size);
		m->allocated = ALLOCATED_TRUE;
		return m;
	}
	return NULL;
}

/* Free a MAB */
MabPtr memFree(MabPtr m){
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
	left->next = right;
	right->prev = left;
	right->next = m->next;

	//Offset
	left->offset = m->offset;
	right->offset = left->offset + size;

	// Assigning left
	free(m);
	return left;
}
