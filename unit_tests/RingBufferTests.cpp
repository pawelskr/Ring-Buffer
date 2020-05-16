#include <gtest/gtest.h>
#include "../RingBuffer.hpp"
#include <iostream>

#define PRINTF std::cerr << "[          ] [ INFO ]"

Ring_Buffer rb;

TEST(RingBuffer_T, CheckIfInitsWithNoElements) {
    EXPECT_EQ(rb.num_items(), 0);
}

TEST(RingBuffer_T, CheckNumElements1) {
    rb.put(1); 
    EXPECT_EQ(rb.num_items(), 1);
}

TEST(RingBuffer_T, CheckNumElements5) {
    rb.reset();
    for(int i = 0; i < 5; i++){
        rb.put(i); 
    }
    
    EXPECT_EQ(rb.num_items(), 5);
}

TEST(RingBuffer_T, CheckNumElementsMAX) {

    rb.reset();
    for(int i = 0; i < RING_BUFFER_SIZE; i++){
        rb.put(i); 
    }
    EXPECT_EQ(rb.num_items(), RING_BUFFER_CONTAINER_SIZE);
}


TEST(RingBuffer_T, CheckNumElementsOverflow) {
    rb.reset();
    for(int i = 0; i < RING_BUFFER_SIZE+10; i++){
        rb.put(i); 
    }
    EXPECT_EQ(rb.num_items(), RING_BUFFER_MASK);
}


TEST(RingBuffer_PutGet, CheckNumElementsPushGet) {
    char temp[RING_BUFFER_SIZE+10] = {0}; 
    char dummy = 0;
    rb.reset();
    for(int i = 0; i < RING_BUFFER_CONTAINER_SIZE; i++){
        rb.put(i); 
        temp[i] = i;
    }
    
    PRINTF << "Tail_index = " <<  std::to_string(rb.buffer.tail_index) << " Head_index =" << std::to_string(rb.buffer.head_index) << std::endl;
    EXPECT_EQ(rb.num_items(), RING_BUFFER_CONTAINER_SIZE);
    ASSERT_TRUE(rb.is_full()); 
    for(int i = 0; i < RING_BUFFER_CONTAINER_SIZE; i++){
        dummy = rb.get();
        ASSERT_EQ(dummy, temp[i]);
    }
    EXPECT_EQ(rb.num_items(), 0);
    EXPECT_TRUE(rb.is_empty());
    EXPECT_FALSE(rb.is_full());
}
