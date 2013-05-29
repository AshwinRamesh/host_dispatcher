#ifndef RESOURCES_H
#define RESOURCES_H

/* IO DEVICES AVAILABLE */
#define PRINTERS 	2
#define SCANNERS 	1
#define MODEMS 	1
#define CDS 		2

struct resource {
	int printers;
	int scanners;
	int modems;
	int cds;
};

typedef struct resource Rsrc;
typedef struct resource * RsrcPtr;

RsrcPtr create_resource(int printers, int scanners, int modems, int cds);
RsrcPtr allocate_resource(RsrcPtr io, PcbPtr ps);
int check_resource(RsrcPtr io, PcbPtr ps);
RsrcPtr free_resource(RsrcPtr io, PcbPtr ps);
void destroy_resource(RsrcPtr io);

#endif
