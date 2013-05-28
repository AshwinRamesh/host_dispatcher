#include "../inc/mab.h"
#include <stdlib.h>


/* Check if a specified size of memory exists */
MabPtr memChk(MabPtr m, int size) {
	MabPtr temp = NULL;
	return temp;
}

/* Allocates memory block of given size */
MabPtr memAlloc(MabPtr m, int size){
	MabPtr temp = NULL;
	return temp;

}

/* Free a MAB */
MabPtr memFree(MabPtr m){
	if (m != NULL){
		m->allocated = ALLLOCATED_FALSE;
	}
	return NULL;

}

/* Merge MAB with next MAB */
MabPtr memMerge(MabPtr m){
	MabPtr temp = NULL;
	return temp;

}

/* Split MAB into 2: one part = size || other part = MAB->size - size */
MabPtr memSplit(MabPtr m, int size){
	MabPtr temp = NULL;
	return temp;

}
