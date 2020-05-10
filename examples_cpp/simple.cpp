#include <assert.h>
#include <stdio.h>
#include "../RingBuffer.hpp"

Ring_Buffer ring;

int main(void) {
  int i, cnt;
  char buf;
  char buf_arr[50];
  
  /* Create and initialize ring buffer */
  ring.reset();
  
  /* Add elements to buffer; one at a time */
  for(i = 0; i < 100; i++) {
    ring.put(i);
  }

  /* Verify size */
  assert(ring.num_items() == 100);

  /* Peek third element */
  cnt = ring.peek(&buf, 3);
  /* Assert byte returned */
  assert(cnt == 1);
  /* Assert contents */
  assert(buf == 3);

  /* Dequeue all elements */
  for(cnt = 0; ring.get(&buf) > 0; cnt++) {
    /* Do something with buf... */
    assert(buf == cnt);
    printf("Read: %d\n", buf);
  }
  printf("\n===============\n");

  /* Add array */
  ring.put_arr("Hello, Ring Buffer!", 20);

  /* Is buffer empty? */
  assert(!ring.is_empty());

  /* Dequeue all elements */
  while(ring.get(&buf) > 0) {
    /* Print contents */
    printf("Read: %c\n", buf);
  }
  
  /* Add new array */
  ring.put_arr("Hello again, Ring Buffer!", 26);
  
  /* Dequeue array in two parts */
  printf("Read:\n");
  cnt = ring.get_arr(buf_arr, 13);
  printf("%d\n", cnt);
  assert(cnt == 13);
  /* Add \0 termination before printing */
  buf_arr[13] = '\0';
  printf("%s\n", buf_arr);
  /* Dequeue remaining */
  cnt = ring.get_arr(buf_arr, 13);
  assert(cnt == 13);
  printf("%s", buf_arr);  
  

  printf("\n===============\n");

  /* Overfill buffer */
  for(i = 0; i < 1000; i++) {
    ring.put((i % 127));
  }
  
  /* Is buffer full? */
  if(ring.is_full()) {
    cnt = ring.num_items();
    printf("Buffer is full and contains %d bytes\n", cnt);
  }
  
  /* Dequeue all elements */
  while(ring.get(&buf) > 0) {
    /* Print contents */
    printf("Read: 0x%02x\n", buf);
  }
  
  return 0;
}
