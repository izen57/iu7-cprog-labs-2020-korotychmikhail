#ifndef __STRUCTURES_H__
#define __STRUCUTURES_H__
#define LEN_STRUCT 15
#define LEN_NAME 25
typedef struct
{
	char name[LEN_NAME + 1];
	float weight;
	float volume;
} information;
#endif