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

dram_buffer_t* init_dram_buffer(buffer_table_t* table, uint32_t latency)
{
	dram_buffer_t* new_buffer = (dram_buffer_t*)malloc(sizeof(dram_buffer_t));
	new_buffer->dram_latency = latency;
	new_buffer->buffer_table = table;
	return new_buffer;
}

buffer_table_t* init_buffer_table()
{
	buffer_table_t* new_table = (buffer_table_t*)malloc(sizeof(buffer_table_t));
	new_table->entry_num = 0;
	for (uint32_t i = 0; i < BUF_SIZE; i++)
	{
		new_table->address_table[i] = UINT64_MAX;
	}
	return new_table;
}

void insert_buffer(buffer_table_t* table, uint64_t addr);
void remove_buffer(buffer_table_t* table, uint64_t addr);

void check_buffer(dram_buffer_t* buffer, uint64_t addr)
{
	buffer_table_t* table = buffer->buffer_table;
	if (table->address_table[addr%BUF_SIZE] == addr)
	{
		printf("HIT\n");
		// buffer->dram_latency;
	}
	else
	{
		printf("MISS\n");
		insert_buffer(table, addr);
	}
}

void insert_buffer(buffer_table_t* table, uint64_t addr)
{
	if (table->address_table[addr%BUF_SIZE] == UINT64_MAX)
	{
		table->address_table[addr%BUF_SIZE] = addr;
		table->entry_num++;
	}
	else
	{
		table->address_table[addr%BUF_SIZE] = addr;
	}
}

void remove_buffer(buffer_table_t* table, uint64_t addr)
{
	if (table->entry_num != 0)
	{
		table->address_table[addr%BUF_SIZE] = UINT64_MAX;
		table->entry_num--;
	}
	else
		printf("ERROR\n");
}

int main(int argc, char** argv)
{
	buffer_table_t* table = init_buffer_table();
	dram_buffer_t* buffer = init_dram_buffer(table, 5);
	return 0;
}
