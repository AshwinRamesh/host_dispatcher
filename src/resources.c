#include <stdio.h>
#include <stdlib.h>
#include "../inc/pcb.h"
#include "../inc/resources.h"

/* Allocating memory for the resource pointer */
RsrcPtr create_resource(int printers, int scanners, int modems, int cds){
	RsrcPtr temp_resource = (RsrcPtr)malloc(sizeof(Rsrc));
	temp_resource->printers = printers;
	temp_resource->scanners = scanners;
	temp_resource->modems = modems;
	temp_resource->cds = cds;
	return temp_resource;
}

/* Allocate resources for process */
RsrcPtr allocate_resource(RsrcPtr io, PcbPtr ps){
	io->printers = io->printers - ps->num_printers;
	io->scanners = io->scanners - ps->num_scanners;
	io->modems = io->modems - ps->num_modems;
	io->cds = io->cds - ps->num_cds;
	return io;
}

/* Check if resources are available for a given process*/
int check_resource(RsrcPtr io, PcbPtr ps){
	if(io->printers >= ps->num_printers && io->scanners >= ps->num_scanners && io->modems >= ps->num_modems && io->cds >= ps->num_cds ) {
		return 1; // available
	}
	return 0; // not available
}

/* Free resources for given process */
RsrcPtr free_resource(RsrcPtr io, PcbPtr ps){
	io->printers = io->printers + ps->num_printers;
	io->scanners = io->scanners + ps->num_scanners;
	io->modems = io->modems + ps->num_modems;
	io->cds = io->cds + ps->num_cds;
	return io;
}

/* Free memory for resources */
void destroy_resource(RsrcPtr io) {
	if (io) {
		free(io);
	}
}
