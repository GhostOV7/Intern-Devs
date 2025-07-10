# Ring Buffer - Doxygen Açıklama Dosyası

Bu proje, sabit boyutlu bir **ring buffer (halka tampon)** yapısının C diliyle implementasyonudur.

## Özellikler
- FIFO (First-In First-Out) yapısı
- Otomatik veri üzerine yazma özelliği (overwriting)
- Tampon dolu/boş kontrolü
- Temiz ve basit kullanım

## Kullanım Örneği

Aşağıdaki örnekte "eclipse" kelimesi tek tek yazılıyor ve ring buffer'a ekleniyor. 
Tampon dolduğunda eski veri üzerine yazılıyor.