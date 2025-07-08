# 🛡️ HISMOD – Akıllı Ev Güvenlik ve Afet Simülasyon Sistemi 

**HISMOD**, Deneyap Kart 1A ile geliştirilen, çoklu sensör destekli bir **akıllı ev güvenlik ve afet farkındalık sistemidir**. Yangın, gaz kaçağı, deprem gibi tehlikeleri erken aşamada tespit ederek kullanıcıyı uyarır. Sistem aynı zamanda **simülasyon temelli farkındalık yaratmayı** amaçlayarak, kullanıcıların bu tehlikelere karşı hazırlıklı olmasını sağlar.

---

## 🎯 Proje Amacı

Türkiye gibi afet riski yüksek ülkelerde, bireysel farkındalık ve önlem alma alışkanlığı oldukça düşüktür. HISMOD bu soruna düşük maliyetli, yerel üretimle geliştirilen, kolay kurulabilen bir donanım çözümü sunar:

- Gerçek zamanlı **tehlike algılama**
- Kullanıcıyı **görsel ve işitsel** olarak bilgilendirme
- Bireylerde **afet bilinci** oluşturma
- Eğitim ve tatbikat amacıyla **simülasyon yapabilme**

---

## 🔩 Donanım Bileşenleri

| Bileşen | Açıklama |
|--------|----------|
| **Deneyap Kart 1A** | ESP32 tabanlı, yerli geliştirilmiş mikrodenetleyici kart |
| **Gaz Sensörü (MQ-9)** | LPG, metan ve karbon monoksit tespiti |
| **Alev Sensörü** | Yangın kaynaklı alevin optik algılanması |
| **Deprem Sensörü (SW-420)** | Titreşim ve sarsıntı algılama |
| **Ultrasonik Sensör (HC-SR04)** | Hareket, yaklaşma ve mesafe algılama |
| **Buzzer** | Tehlike durumlarında sesli uyarı |

---

## 🧰 Sistem Özellikleri
- ✅ **Çoklu Sensör İzleme: Sensör verileri belirli aralıklarla okunur**
- ✅ **Durum Algılama Mantığı: Eşik değerleri aşıldığında tehlike tipi belirlenir.**
- ✅ **Interrupt Tabanlı Algılama: SW-420 deprem sensörü için hızlı tepki.**
- ✅ **Seri Port Gözlem: Tüm olaylar Arduino IDE üzerinden anlık olarak takip edilir.**
- ✅ **Dinamik Uyarı Sistemi: Her tehlike tipi için farklı sesli uyarı ve konsol çıktısı.**


---

## 🧠 Sistem Mantığı

Sistem, belirli bir döngüde sensörlerden veri alır. Eşik değerler aşıldığında aşağıdaki mantık çalışır:

```cpp
if (gazDegeri > gazEsik) {
  Serial.println("🚨 GAZ KAÇAĞI ALGILANDI!");
  buzzerUyar();
}
if (alevAlgilandi()) {
  Serial.println("🔥 ALEV ALGILANDI!");
  buzzerUyar();
}
if (depremAlgilandi()) {
  Serial.println("🌍 DEPREM ALGILANDI!");
  buzzerUyar();
}
``` 
## 🔌 Bağlantı Şeması
![Image](https://github.com/user-attachments/assets/191f9244-38b0-4155-8f54-50c58dfa7fd5)

>  Giriş/çıkış pinleri ve bağlantılar Fritzing şemasında detaylıca gösterilmiştir.  
> 💡 **Not:** Deneyap Kart 1A, ESP32 tabanlıdır ve 3.3V çalışma voltajına sahiptir. 5V beslemeli sensörlerde dikkatli olun.


## 💻 Yazılım Kurulumu (Arduino IDE)

### Gerekli Adımlar:

1. Arduino IDE (**1.8.x** veya **2.x**) sürümünü indirin.  
2. **ESP32** kart tanımını ekleyin:  
   - Board Manager → **esp32** → **Espressif Systems**
3. Araçlar > Kart > **Deneyap Kart 1A** seçin.  
4. `hismod.ino` dosyasını açın.  
5. Uygun **portu seçin** ve karta **yükleyin**.  
6. **Serial Monitor** üzerinden 9600 baud ile çalıştırın.

---


