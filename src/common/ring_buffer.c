#include<stdint.h>
#include<stdbool.h>
#include"common/ring_buffer.h"

//buffer is full if head+1 == tail
bool ring_buffer_full(const struct ring_buffer *rb)
{
 uint8_t next_head = (rb->head +1);
 if (next_head == rb->size ){
     next_head = 0;
 }
   return next_head == rb->tail;
}

// buffer is empty if head == tail
bool ring_buffer_empty(const struct ring_buffer *rb)
{
  return rb->head == rb->tail;
}

// Adds a new element to the inx pointed by head and then increments head. So that it points to the next empty loc
//Note: the function does not check if the buffer if the buffer is full. That code must be implemented in Main
void ring_buffer_put(struct ring_buffer *rb, uint8_t data)
{
    rb->buffer[rb->head] = data;
      rb->head++;
   if(rb->head == rb->size)
   {
      rb->head = 0;
   }
  }

//Reads an element from the tail position of the ring_buffer. Increments the tail so that it points to the next loc.
//Note: This function does not check if the buffer is empty. That code must be implemented in Main
uint8_t ring_buffer_get(struct ring_buffer *rb)
{

    uint8_t data = rb->buffer[rb->tail];
    rb->tail++;
    if(rb->tail == rb->size)
    {
        rb->tail = 0;
    }
    return data;
}

// Returns the element from the tail position but does not increment the tail.
uint8_t ring_buffer_peek(const struct ring_buffer *rb)
{
    return rb->buffer[rb->tail];
}
