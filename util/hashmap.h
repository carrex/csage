#ifndef HASHMAP_H
#define HASHMAP_H

struct HashMap {
	uint32 size;
	uint32* keys;
	int64* values;
};

struct HashMap hmap_new(uint32 size);
uint32 hmap_hash(char* key);
void   hmap_set(struct HashMap* hmap, char* key, void* value);
void*  hmap_get(struct HashMap* hmap, char* key);

#endif
