#ifndef __DRAM_H__
#define __DRAM_H__

#include <inttypes.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define BUF_SIZE 4194304

typedef struct buffer_table buffer_table_t;

typedef struct dram_buffer
{
	uint32_t dram_latency;
	buffer_table_t *buffer_table;
} dram_buffer_t;

struct buffer_table
{
	int entry_num;
	uint64_t address_table[BUF_SIZE];
};
dram_buffer_t* init_dram_buffer(buffer_table_t* table, uint32_t latency);


buffer_table_t* init_buffer_table();



void insert_buffer(buffer_table_t* table, uint64_t addr);
void remove_buffer(buffer_table_t* table, uint64_t addr);
void check_buffer(dram_buffer_t* buffer, uint64_t addr);


#endif#pragma once
