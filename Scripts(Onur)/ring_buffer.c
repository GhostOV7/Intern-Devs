
---

```c
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_BUFFER_SIZE 5  ///< Ring buffer'�n maksimum kapasitesi

/**
 * @brief Ring buffer yap�s�
 */
typedef struct {
    char buffer[MAX_BUFFER_SIZE];  ///< Verilerin tutuldu�u dizi
    int head;                      ///< Son yaz�lan konum
    int tail;                      ///< Son okunan konum
    int count;                     ///< Mevcut eleman say�s�
} RingBuffer;

/**
 * @brief Ring buffer'� ba�lat�r (s�f�rlar).
 * @param rb RingBuffer pointer'�
 */
void RingBufferInit(RingBuffer *rb);

/**
 * @brief Ring buffer'a veri yazar.
 * 
 * E�er buffer doluysa, en eski veri silinir (overwrite).
 * 
 * @param rb RingBuffer pointer'�
 * @param data Yaz�lacak karakter
 */
void RingBufferWrite(RingBuffer *rb, char data);

/**
 * @brief Ring buffer'dan veri okur.
 * @param rb RingBuffer pointer'�
 * @return Okunan karakter
 */
char RingBufferRead(RingBuffer *rb);

/**
 * @brief Buffer dolu mu kontrol eder.
 * @param rb RingBuffer pointer'�
 * @return true Doluysa, false de�ilse
 */
bool RingBufferIsFull(RingBuffer *rb);

/**
 * @brief Buffer bo� mu kontrol eder.
 * @param rb RingBuffer pointer'�
 * @return true Bo�sa, false de�ilse
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
            // Doluysa �zerine yaz�lacak karakteri bildir
            char overwritten = rb.buffer[rb.head];
            printf("('%c' yerine gecti)", overwritten);
        }
        
        RingBufferWrite(&rb, transmitted_data[i]);
        
        // Anl�k buffer i�eri�ini g�ster
        printf(" -> ");
        for(int k = 0; k < rb.count; k++) {
            int index = (rb.tail + k) % MAX_BUFFER_SIZE;
            printf("[%c]", rb.buffer[index]);
        }
        printf("\n");
    }
    
    // Buffer'daki veriyi s�rayla oku
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

    // Buffer i�eri�ini temizle (iste�e ba�l�)
    for(int i = 0; i < MAX_BUFFER_SIZE; i++) {
        rb->buffer[i] = '\0';
    }
}

void RingBufferWrite(RingBuffer *rb, char data) {
    if (rb->count == MAX_BUFFER_SIZE) {
        // Doluysa en eski verinin �st�ne yaz�lacak
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
