#include "common.h"
#include "resourcemanager.h"
#include "hashmap.h"

struct HashMap hmap_new(uint32 size)
{
	struct HashMap hmap;
	hmap.size   = size;
	hmap.keys   = scalloc((uintptr)size, sizeof(size));
	hmap.values = smalloc(size * sizeof(void*));

	return hmap;
}

/* https://en.wikipedia.org/wiki/Jenkins_hash_function */
uint32 hmap_hash(char* key)
{
	uint32 hash = 0;
	for (uint8 i = 0; key[i] != '\0'; i++) {
		hash += (uint32)(key[i]);
		hash += hash << 10;
		hash ^= hash >> 6;
	}
	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;

	return hash;
}

/* TODO: collision checks */
void hmap_set(struct HashMap* hmap, char* key, void* value)
{
	uint32 i = 0;
	while (hmap->keys[i]) i++;
	uint32 hash = hmap_hash(key);
	hmap->keys[i]   = hash;
	hmap->values[i] = (int64)((size_t)value - (size_t)hash);
}

void* hmap_get(struct HashMap* hmap, char* key)
{
	uint32 hash = hmap_hash(key);
	for (uint32 i = 0; i < hmap->size; i++)
		if (hmap->keys[i] == hash)
			return (void*)(hmap->values[i] + hash);

	return NULL;
}
