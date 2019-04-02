#ifndef __HOST_INTERFACE_LAYER_H__
#define __HOST_INTERFACe_LAYER_H__

#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>

#include "common.h"

typedef struct HIL_queue
{
	uint32_t		capacity;
	uint32_t		n_entry;
	uint32_t		front;
	uint32_t		rear;
	io_req_t*		_entry;
} HIL_queue_t;

typedef struct host_interface
{
	uint32_t			capacity;
	HIL_queue_t*	_SQ;
	HIL_queue_t*	_CQ;
} HIL_t;

HIL_t*				init_HostInterfaceLayer(uint32_t capacity);
HIL_queue_t*	init_hi_queue(uint32_t capacity);
void					submit_io_req(HIL_queue_t* _queue, io_req_t* new_entry);
void					commit_io_req(HIL_t* _HIL);

#endif