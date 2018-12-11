#ifndef DISPLAYBUFFER_H
#define DISPLAYBUFFER_H

#define MemorySize 234*16
struct TreeDisplayBuffer{
    TreeDisplayBuffer();
    virtual ~TreeDisplayBuffer();
    int* drawingMemory[MemorySize];
    int* displayMemory[MemorySize];
};
#endif