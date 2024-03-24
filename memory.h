#ifndef ctiny_memory_h
#define ctiny_memory_h

#define ALLOCATE(type, count) \
    (type*)reallocate(NULL, 0, sizeof(type) * (count))

#endif