#ifndef __COMMON_H__
#define __COMMON_H__

#include <inttypes.h>

typedef enum
{
	READ,
	WRITE
} op_type;

typedef struct io_request io_req_t;

//* why seperate io_req_t & blk_req_t?
//* --> could add more information into block_request in near future..?
struct io_request
{
	uint32_t	core_id;
	op_type		req_type;
	uint64_t	blk_addr;

	uint64_t	submission_time;
	uint64_t	completion_time;
	uint64_t	total_latency;
	uint64_t	queueing_latency;
};	//* io_request queue should be in-order circular queue

//* request packet structure
//*	- a basic packet for communication between simulator components.
//* - blk_request queue should be an out-of-order queue
typedef struct block_request
{
	uint32_t	core_id;
	op_type		req_type;
	uint64_t	blk_addr;

	uint64_t	arrival_time;
	uint64_t	dispatch_time;
	uint64_t	comp_time;

	//blk_req_t*	_next;
} blk_req_t;

#endif