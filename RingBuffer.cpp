#include "RingBuffer.hpp"

/**
 * @file
 * Implementation of ring buffer functions.
 */

Ring_Buffer::Ring_Buffer(){
  buffer.tail_index = 0;
  buffer.head_index = 0;
}

void Ring_Buffer::reset() {
  buffer.tail_index = 0;
  buffer.head_index = 0;
}

void Ring_Buffer::put(char data) {
  
  if(is_full()) {   // Is buffer full? 
    /* Is going to overwrite the oldest byte */
    /* Increase tail index */
    buffer.tail_index = ((buffer.tail_index + 1) & RING_BUFFER_MASK);
  }

  /* Place data in buffer */
  buffer.buffer[buffer.head_index] = data;
  buffer.head_index = ((buffer.head_index + 1) & RING_BUFFER_MASK);
}

void Ring_Buffer::put_arr(const char *data, ring_buffer_size_t size) {
  /* Add bytes; one by one */
  ring_buffer_size_t i;
  for(i = 0; i < size; i++) {
    put(data[i]);
  }
}

uint8_t Ring_Buffer::get(char *data) {
  if(is_empty()) {
    /* No items */
    return 0;
  }
  
  *data = buffer.buffer[buffer.tail_index];
  buffer.tail_index = ((buffer.tail_index + 1) & RING_BUFFER_MASK);
  return 1;
}

uint8_t Ring_Buffer::get() {
  if(is_empty()) {
    /* No items */
    return 0;
  }
  
  uint8_t data = buffer.buffer[buffer.tail_index];
  buffer.tail_index = ((buffer.tail_index + 1) & RING_BUFFER_MASK);

  return data;
}

ring_buffer_size_t Ring_Buffer::get_arr(char *data, ring_buffer_size_t len) {
  if(is_empty()) {
    /* No items */
    return 0;
  }

  char *data_ptr = data;
  ring_buffer_size_t cnt = 0;
  while((cnt < len) && get(data_ptr)) {
    cnt++;
    data_ptr++;
  }
  return cnt;
}

uint8_t Ring_Buffer::peek(char *data, ring_buffer_size_t index) {
  if(index >= num_items()) {
    /* No items at index */
    return 0;
  }
  
  /* Add index to pointer */
  ring_buffer_size_t data_index = ((buffer.tail_index + index) & RING_BUFFER_MASK);
  *data = buffer.buffer[data_index];
  return 1;
}

