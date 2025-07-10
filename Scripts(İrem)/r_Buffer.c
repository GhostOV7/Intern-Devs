#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_BUFFER_SIZE 5

typedef struct {
    char buffer[MAX_BUFFER_SIZE];
    int read_index;
    int write_index;
} circular_buffer;

void cbuffer_init(circular_buffer *cbuffer)
{
    cbuffer->read_index = 0;
    cbuffer->write_index = 0;
    // Buffer'ı temizle
    for(int i = 0; i < MAX_BUFFER_SIZE; i++) {
        cbuffer->buffer[i] = 0;
    }
}

void cbuffer_push(circular_buffer *cbuffer, char data)
{
    cbuffer->buffer[cbuffer->write_index] = data;
    cbuffer->write_index = (cbuffer->write_index + 1) % MAX_BUFFER_SIZE;
    
    // Buffer dolu mu kontrol et (circular davranış)
    if(cbuffer->write_index == cbuffer->read_index) {
        cbuffer->read_index = (cbuffer->read_index + 1) % MAX_BUFFER_SIZE;
    }
}

char cbuffer_get(circular_buffer *cbuffer)
{
    // Buffer boş mu kontrol et
    if(cbuffer->read_index == cbuffer->write_index) {
        return '\0'; // Buffer boş
    }
    
    char data = cbuffer->buffer[cbuffer->read_index];
    cbuffer->read_index = (cbuffer->read_index + 1) % MAX_BUFFER_SIZE;
    return data;
}

int cbuffer_available(circular_buffer *cbuffer)
{
    int count = cbuffer->write_index - cbuffer->read_index;
    
    // Negatif olursa circular durumu düzelt
    if(count < 0) {
        count += MAX_BUFFER_SIZE;
    }
    
    return count;
}

void cbuffer_print(circular_buffer *cbuffer)
{
    printf("Buffer durumu: ");
    printf("read_index=%d, write_index=%d, available=%d\n", 
           cbuffer->read_index, cbuffer->write_index, cbuffer_available(cbuffer));
    
    printf("Buffer içeriği: [");
    for(int i = 0; i < MAX_BUFFER_SIZE; i++) {
        if(cbuffer->buffer[i] != 0) {
            printf("'%c'", cbuffer->buffer[i]);
        } else {
            printf("_");
        }
        if(i < MAX_BUFFER_SIZE - 1) printf(", ");
    }
    printf("]\n");
    
    printf("Okunabilir veriler: ");
    if(cbuffer_available(cbuffer) == 0) {
        printf("Buffer boş\n");
    } else {
        int temp_read = cbuffer->read_index;
        int count = cbuffer_available(cbuffer);
        for(int i = 0; i < count; i++) {
            printf("'%c' ", cbuffer->buffer[temp_read]);
            temp_read = (temp_read + 1) % MAX_BUFFER_SIZE;
        }
        printf("\n");
    }
    printf("---\n");
}

int main() 
{
    circular_buffer test_buffer;
    char data = 0;
    cbuffer_init(&test_buffer);
    
    printf("=== Circular Buffer Test ===\n");
    cbuffer_print(&test_buffer);
    
    printf("'i' ekleniyor...\n");
    cbuffer_push(&test_buffer, 'i');
    cbuffer_print(&test_buffer);
    
    printf("'r' ekleniyor...\n");
    cbuffer_push(&test_buffer, 'r');
    cbuffer_print(&test_buffer);
    
    printf("'e' ekleniyor...\n");
    cbuffer_push(&test_buffer, 'e');
    cbuffer_print(&test_buffer);
    
    printf("Bir karakter okunuyor...\n");
    data = cbuffer_get(&test_buffer);
    printf("Okunan karakter: '%c'\n", data);
    cbuffer_print(&test_buffer);
    
    printf("'m' ekleniyor...\n");
    cbuffer_push(&test_buffer, 'm');
    cbuffer_print(&test_buffer);
    
    // Buffer'ı doldur (circular davranış testi)
    printf("Buffer'ı doldurma testi...\n");
    cbuffer_push(&test_buffer, 'x');
    cbuffer_print(&test_buffer);
    
    cbuffer_push(&test_buffer, 'y');
    cbuffer_print(&test_buffer);
    
    cbuffer_push(&test_buffer, 'z');
    cbuffer_print(&test_buffer);
    
    // Tüm veriyi oku
    printf("\n=== Tüm veriyi okuma ===\n");
    while(cbuffer_available(&test_buffer) > 0) {
        data = cbuffer_get(&test_buffer);
        printf("Okunan: '%c'\n", data);
        cbuffer_print(&test_buffer);
    }
    
    return 0;
}