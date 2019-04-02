#ifndef __PCM_ARRAY_H__
#define __PCM_ARRAY_H__

#include <inttypes.h>

/*
a pcm array structure which was made last time is single-banked device:
(line 31 @ main.cc)

Now, we should consider multi-bank/package/channel pcm array for exploiting inter-parallelism.
*/

#define	MAX_NUM_CHANNEL		4
#define MAX_NUM_WAY				4
#define MAX_NUM_BANK			8

typedef struct pcm_device pcm_device_t;

struct pcm_device
{
	uint64_t		total_size;
	
	//* new parameters -------
	uint32_t		n_channel;
	uint32_t		n_way;
	//*-----------------------
	uint32_t		n_bank;
	uint32_t		n_row;
	uint32_t		n_column;

	uint32_t		tRCD;
	uint32_t		tRP;
	uint32_t		tCAS;
	uint32_t		tRC;
	uint32_t		tRAS;

	uint32_t		tBL;

	uint64_t		next_pre[MAX_NUM_CHANNEL][MAX_NUM_WAY][MAX_NUM_BANK];
	uint64_t		next_act[MAX_NUM_CHANNEL][MAX_NUM_WAY][MAX_NUM_BANK];
	uint64_t		next_read[MAX_NUM_CHANNEL][MAX_NUM_WAY][MAX_NUM_BANK];
	uint64_t		next_write[MAX_NUM_CHANNEL][MAX_NUM_WAY][MAX_NUM_BANK];
	//TODO: some member variables need a common header file (state_t, pcm_queue_t)
	state_t			bank_state[MAX_NUM_CHANNEL][MAX_NUM_WAY][MAX_NUM_BANK];	
	uint32_t		row_buffer_act[MAX_NUM_CHANNEL][MAX_NUM_WAY][MAX_NUM_BANK];

	uint64_t		data_bus[MAX_NUM_CHANNEL];

	pcm_queue_t	*reqQ;
};

#endif