#ifndef MAB_H
#define MAB_H

#define ALLOCATED_TRUE		1
#define ALLOCATED_FALSE		0

struct mab {
	int offset;
	int size;
	int allocated;
	struct mab * next;
	struct mab * prev;
};

typedef struct mab Mab;
typedef Mab * MabPtr;

MabPtr memChk(MabPtr m, int size);
MabPtr memAlloc(MabPtr m, int size);
MabPtr memFree(MabPtr m);
MabPtr memMerge(MabPtr m);
MabPtr memSplit(MabPtr m, int size);

#endif
