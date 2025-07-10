
---

```c
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_BUFFER_SIZE 5  ///< Ring buffer'ýn maksimum kapasitesi

/**
 * @brief Ring buffer yapýsý
 */
typedef struct {
    char buffer[MAX_BUFFER_SIZE];  ///< Verilerin tutulduðu dizi
    int head;                      ///< Son yazýlan konum
    int tail;                      ///< Son okunan konum
    int count;                     ///< Mevcut eleman sayýsý
} RingBuffer;

/**
 * @brief Ring buffer'ý baþlatýr (sýfýrlar).
 * @param rb RingBuffer pointer'ý
 */
void RingBufferInit(RingBuffer *rb);

/**
 * @brief Ring buffer'a veri yazar.
 * 
 * Eðer buffer doluysa, en eski veri silinir (overwrite).
 * 
 * @param rb RingBuffer pointer'ý
 * @param data Yazýlacak karakter
 */
void RingBufferWrite(RingBuffer *rb, char data);

/**
 * @brief Ring buffer'dan veri okur.
 * @param rb RingBuffer pointer'ý
 * @return Okunan karakter
 */
char RingBufferRead(RingBuffer *rb);

/**
 * @brief Buffer dolu mu kontrol eder.
 * @param rb RingBuffer pointer'ý
 * @return true Doluysa, false deðilse
 */
bool RingBufferIsFull(RingBuffer *rb);

/**
 * @brief Buffer boþ mu kontrol eder.
 * @param rb RingBuffer pointer'ý
 * @return true Boþsa, false deðilse
 */
bool RingBufferIsEmpty(RingBuffer *rb);

int main() {
    RingBuffer rb;
    RingBufferInit(&rb);
    
    char transmitted_data[] = "eclipse";
    int length = strlen(transmitted_data);
    
    printf("Yazilacak veri: %s\n", transmitted_data);
    printf("Buffer boyutu: %d\n\n", MAX_BUFFER_SIZE);
    
    // Veriyi karakter karakter buffer'a yaz
    for(int i = 0; i < length; i++) {
        printf("%c yaziliyor... ", transmitted_data[i]);
        
        if (RingBufferIsFull(&rb)) {
            // Doluysa üzerine yazýlacak karakteri bildir
            char overwritten = rb.buffer[rb.head];
            printf("('%c' yerine gecti)", overwritten);
        }
        
        RingBufferWrite(&rb, transmitted_data[i]);
        
        // Anlýk buffer içeriðini göster
        printf(" -> ");
        for(int k = 0; k < rb.count; k++) {
            int index = (rb.tail + k) % MAX_BUFFER_SIZE;
            printf("[%c]", rb.buffer[index]);
        }
        printf("\n");
    }
    
    // Buffer'daki veriyi sýrayla oku
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

    // Buffer içeriðini temizle (isteðe baðlý)
    for(int i = 0; i < MAX_BUFFER_SIZE; i++) {
        rb->buffer[i] = '\0';
    }
}

void RingBufferWrite(RingBuffer *rb, char data) {
    if (rb->count == MAX_BUFFER_SIZE) {
        // Doluysa en eski verinin üstüne yazýlacak
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
```

---
