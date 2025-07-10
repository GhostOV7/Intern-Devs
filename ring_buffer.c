#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_BUFFER_SIZE 5

typedef struct {
    char buffer[MAX_BUFFER_SIZE];
    int head;
    int tail;
    int count;
} RingBuffer;

void RingBufferInit(RingBuffer *rb);
void RingBufferWrite(RingBuffer *rb, char data);
char RingBufferRead(RingBuffer *rb);
bool RingBufferIsFull(RingBuffer *rb);
bool RingBufferIsEmpty(RingBuffer *rb);

int main() {
    RingBuffer rb;
    RingBufferInit(&rb);
    
    char transmitted_data[] = "eclipse";
    int length = strlen(transmitted_data);
    
    printf("Yazilacak veri: %s\n", transmitted_data);
    printf("Buffer boyutu: %d\n\n", MAX_BUFFER_SIZE);
    
    // Veri yazma
    for(int i = 0; i < length; i++) {
        printf("%c yaziliyor... ", transmitted_data[i]);
        
        if (RingBufferIsFull(&rb)) {
            char overwritten = rb.buffer[rb.head];
            printf("('%c' yerine gecti)", overwritten);
        }
        
        RingBufferWrite(&rb, transmitted_data[i]);
        
        // Buffer durumunu göster (tail'den başlayarak sıralı okuma)
        printf(" -> ");
        for(int k = 0; k < rb.count; k++) {
            int index = (rb.tail + k) % MAX_BUFFER_SIZE;
            printf("[%c]", rb.buffer[index]);
        }
        printf("\n");
    }
    
    printf("Okuma: ");
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
    
    // Buffer'ı temizle
    for(int i = 0; i < MAX_BUFFER_SIZE; i++) {
        rb->buffer[i] = '\0';
    }
}

void RingBufferWrite(RingBuffer *rb, char data) {
    // Eğer buffer dolu ise, tail'i ilerlet (overwrite)
    if (rb->count == MAX_BUFFER_SIZE) {
        rb->tail = (rb->tail + 1) % MAX_BUFFER_SIZE;
    } else {
        rb->count++;
    }
    
    // Veriyi yaz ve head'i ilerlet
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