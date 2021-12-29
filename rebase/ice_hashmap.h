/* TODO: Edit */

#define ice_hashmap_new(name, t1, t2)                               \
    struct {                                                        \
        t1** keys;                                                  \
        t2** values;                                                \
        unsigned long len;                                          \
        unsigned long size;                                         \
    } name;                                                         \
                                                                    \
    name.keys = ICE_HASHMAP_MALLOC(0);                              \
    name.values = ICE_HASHMAP_MALLOC(0);                            \
    name.len = 0;                                                   \
    name.size = 0;                                                  \

#define ice_hashmap_delete(map, key) {                              \
    int i;                                                          \
    int j;                                                          \
                                                                    \
    for (i = 0; i < map.len; i++) {                                 \
        if ((*((void*) map.keys[i]) == key) {                       \
            map.keys[i] = ICE_HASHMAP_NULL;                         \
            map.values[i] = ICE_HASHMAP_NULL;                       \
                                                                    \
            for (j = i + 1; j < map.len; j++) {                     \
                map.keys[j - 1] = maps.keys[j];                     \
                map.values[j - 1] = maps.values[j];                 \
            }                                                       \
                                                                    \
            map.len--;                                              \
            map.size -= sizeof(void*);                              \
                                                                    \
            map.values = ICE_HASHMAP_REALLOC(map.values, map.size); \
            map.keys = ICE_HASHMAP_REALLOC(map.keys, map.size);     \
                                                                    \
            break;                                                  \
        }                                                           \
    }                                                               \
}                                                                   \

#define ice_hashmap_clear(map) {                                    \
    ICE_HASHMAP_FREE(map.keys);                                     \
    ICE_HASHMAP_FREE(map.values);                                   \
                                                                    \
    name.keys = ICE_HASHMAP_MALLOC(0);                              \
    name.values = ICE_HASHMAP_MALLOC(0);                            \
                                                                    \
    map.len = 0;                                                    \
    map.size = 0;                                                   \
}                                                                   \

#define ice_hashmap_get(map, key, res) {                            \
    int i;                                                          \
                                                                    \
    for (i = 0; i < map.len; i++) {                                 \
        if ((*((void*) map.keys[i]) == key) {                       \
            res = map.values[i];                                    \
            break;                                                  \
        }                                                           \
    }                                                               \
}                                                                   \

#define ice_hashmap_set(map, key, val) {                            \
    int i;                                                          \
    ice_hashmap_bool is_set = ICE_HASHMAP_FALSE;                    \
                                                                    \
    for (i = 0; i < map.len; i++) {                                 \
        if ((*((void*) map.keys[i]) == key) {                       \
            map.values[i] = val;                                    \
            is_set = ICE_HASHMAP_TRUE;                              \
            break;                                                  \
        }                                                           \
    }                                                               \
                                                                    \
    if (is_set == ICE_HASHMAP_FALSE) {                              \
        map.len++;                                                  \
        map.size += sizeof(void*);                                  \
                                                                    \
        map.values = ICE_HASHMAP_REALLOC(map.values, map.size);     \
        map.keys = ICE_HASHMAP_REALLOC(map.keys, map.size);         \
                                                                    \
        map.keys[i] = key;                                          \
        map.values[i] = val;                                        \
    }                                                               \
}                                                                   \

#define ice_hashmap_has_key(map, key, res) {                        \
    int i;                                                          \
    res = ICE_HASHMAP_FALSE;                                        \
                                                                    \
    for (i = 0; i < map.len; i++) {                                 \
        if ((*((void*) map.keys[i]) == key) {                       \
            res = ICE_HASHMAP_TRUE;                                 \
            break;                                                  \
        }                                                           \
    }                                                               \
}                                                                   \

#define ice_hashmap_has_value(map, val, res) {                      \
    int i;                                                          \
    res = ICE_HASHMAP_FALSE;                                        \
                                                                    \
    for (i = 0; i < map.len; i++) {                                 \
        if ((*((void*) map.values[i]) == val) {                     \
            res = ICE_HASHMAP_TRUE;                                 \
            break;                                                  \
        }                                                           \
    }                                                               \
}                                                                   \

#define ice_hashmap_foreach(map, key, val, code) {                  \
    int i;                                                          \
                                                                    \
    for (i = 0; i < map.len; i++) {                                 \
        key = (*((void*) map.keys[i]));                             \
        val = (*((void*) map.values[i]));                           \
        code                                                        \
    }                                                               \
}                                                                   \

#define ice_hashmap_keys(map)   map.keys
#define ice_hashmap_values(map) map.values
#define ice_hashmap_len(map)    map.len
