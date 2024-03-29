/* Header file for mab.c*/

#ifndef MAB_H
#define MAB_H

/* Defining boolean values for allocated memory */
#define ALLOCATED_TRUE		1
#define ALLOCATED_FALSE		0

/* maximum memory allocation for real time and user processes */
#define REAL_TIME_MEMORY 	64
#define USER_TIME_MEMORY	960

/* memory struct. uses First Fit Allocation Algorithm*/
struct mab {
	int id; // id of the process
	int offset;
	int size;
	int allocated;
	struct mab * next;
	struct mab * prev;
};

typedef struct mab Mab;
typedef Mab * MabPtr;

MabPtr mabCreate(int size);
MabPtr memChk(MabPtr m, int size);
MabPtr memAlloc(MabPtr m, int size);
MabPtr memFree_all(MabPtr m);
MabPtr memFree(MabPtr m);
MabPtr memMerge(MabPtr m);
MabPtr memSplit(MabPtr m, int size);
MabPtr memGetHead(MabPtr m);
void memPrint(MabPtr m);

#endif
