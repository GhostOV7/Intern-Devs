#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_BUFFER_SIZE 5  ///< Ring buffer maximum capacity

/**
 * @brief Ring buffer structure
 */
typedef struct {
    char buffer[MAX_BUFFER_SIZE];  ///< Data storage array
    int head;                      ///< Last written position
    int tail;                      ///< Last read position
    int count;                     ///< Current element count
} RingBuffer;

/**
 * @brief Initialize the ring buffer (reset to zero).
 * @param rb RingBuffer pointer
 */
void RingBufferInit(RingBuffer *rb);

/**
 * @brief Write data to the ring buffer.
 * 
 * If buffer is full, oldest data is overwritten.
 * 
 * @param rb RingBuffer pointer
 * @param data Character to write
 */
void RingBufferWrite(RingBuffer *rb, char data);

/**
 * @brief Read data from the ring buffer.
 * @param rb RingBuffer pointer
 * @return Read character
 */
char RingBufferRead(RingBuffer *rb);

/**
 * @brief Check if buffer is full.
 * @param rb RingBuffer pointer
 * @return true if full, false otherwise
 */
bool RingBufferIsFull(RingBuffer *rb);

/**
 * @brief Check if buffer is empty.
 * @param rb RingBuffer pointer
 * @return true if empty, false otherwise
 */
bool RingBufferIsEmpty(RingBuffer *rb);

int main() {
    RingBuffer rb;
    RingBufferInit(&rb);
    
    char transmitted_data[] = "eclipse";
    int length = strlen(transmitted_data);
    
    printf("Data to write: %s\n", transmitted_data);
    printf("Buffer size: %d\n\n", MAX_BUFFER_SIZE);
    
    // Write data character by character to buffer
    for(int i = 0; i < length; i++) {
        printf("%c writing... ", transmitted_data[i]);
        
        if (RingBufferIsFull(&rb)) {
            // If full, notify which character will be overwritten
            char overwritten = rb.buffer[rb.head];
            printf("(replacing '%c')", overwritten);
        }
        
        RingBufferWrite(&rb, transmitted_data[i]);
        
        // Show current buffer content
        printf(" -> ");
        for(int k = 0; k < rb.count; k++) {
            int index = (rb.tail + k) % MAX_BUFFER_SIZE;
            printf("[%c]", rb.buffer[index]);
        }
        printf("\n");
    }
    
    // Read data from buffer sequentially
    printf("Reading: ");
    while (!RingBufferIsEmpty(&rb)) {
        char c = RingBufferRead(&rb);
        printf("%c", c);
    }
    
    return 0;
}

void RingBufferInit(RingBuffer *rb) {
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
    
    // Clear buffer content (optional)
    for(int i = 0; i < MAX_BUFFER_SIZE; i++) {
        rb->buffer[i] = '\0';
    }
}

void RingBufferWrite(RingBuffer *rb, char data) {
    if (rb->count == MAX_BUFFER_SIZE) {
        // If full, overwrite oldest data
        rb->tail = (rb->tail + 1) % MAX_BUFFER_SIZE;
    } else {
        rb->count++;
    }
    
    rb->buffer[rb->head] = data;
    rb->head = (rb->head + 1) % MAX_BUFFER_SIZE;
}

char RingBufferRead(RingBuffer *rb) {
    char data = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % MAX_BUFFER_SIZE;
    rb->count--;
    return data;
}

bool RingBufferIsFull(RingBuffer *rb) {
    return (rb->count == MAX_BUFFER_SIZE);
}

bool RingBufferIsEmpty(RingBuffer *rb) {
    return (rb->count == 0);
}