#ifndef __PCM_SSD_H__
#define __PCM_SSD_H__

#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>
#include <string.h>

#include "HIL.h"

HIL_queue_t*	init_hi_queue(uint32_t capacity)
{
	HIL_queue_t* new_queue;
	new_queue->capacity = capacity;
	new_queue->n_entry = 0;
	new_queue->front = 0;
	new_queue->rear = 0;
	new_queue->_entry = (io_req_t*)malloc(sizeof(io_req_t) * capacity);

	return new_queue;
}

HIL_t*	init_HostInterfaceLayer(uint32_t capacity)
{
	HIL_t* new_if;
	new_if = (HIL_t*)malloc(sizeof(HIL_t));
	new_if->capacity = capacity;

	new_if->_SQ = init_hi_queue(capacity);
	new_if->_CQ = init_hi_queue(capacity);

	return new_if;
}

void submit_io_req(HIL_queue_t* _queue, io_req_t* new_entry)
{
	if (_queue->capacity == _queue->n_entry)	return;
	memcpy(&_queue->_entry[_queue->rear], new_entry, sizeof(io_req_t));
	_queue->rear++;
	if (_queue->rear == _queue->capacity)
		_queue->rear = 0;
	_queue->n_entry++;
}

void commit_io_req(HIL_t* _HIL)
{
	HIL_queue_t* _queue = _HIL->_SQ;
	HIL_queue_t* _cq = _HIL->_CQ;

	submit_io_req(_cq, &(_queue->_entry[_queue->front]));
	_queue->front++;
	if (_queue->front == _queue->capacity)
		_queue->front = 0;
	_queue->n_entry--;

}

#endif 