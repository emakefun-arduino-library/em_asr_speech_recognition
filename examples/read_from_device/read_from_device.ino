/**
 * @~Chinese
 * @file read_from_device.ino
 * @brief 读取设备数据。
 * @example read_from_device.ino
 * 读取设备数据。
 */
/**
 * @~English
 * @file read_from_device.ino
 * @brief Read data from the device.
 * @example read_from_device.ino
 * Read data from the device.
 */
#include "asr_speech_recognition.h"
#include "asr_speech_recognition_lib.h"
#ifndef ESP32
SoftwareSerial myserial(12, 13);  // RX, TX           // 9600bps}
#else
HardwareSerial myserial(1);  // RX, TX
#endif
em::AsrSpeechRecognition myASR(myserial);
void setup() {
  Serial.begin(9600);  // 9600bps
#ifndef ESP32
  // 对于Arduino平台
  myserial.begin(9600);
#else
  // 对于ESP32平台，可能需要特定的配置,RX:15 ,TX:14
  myserial.begin(9600, SERIAL_8N1, 15, 14, false);
#endif
  Serial.println(String("asr speech recognition_lib version: ") + em::asr_speech_recognition_lib::Version());
}

void loop() {
  if (myserial.available() > 0) {
    uint8_t buffer[8], read_buffer[3][8] = {0};
    // 读取3个协议数据
    for (uint8_t i = 0; i < 3; i++) {
      myASR.read_protocol(read_buffer[i], ASR_READ_GENERAL_COMMAND, i + 1);
    }
    // 读取设备数据
    myserial.readBytes(buffer, 8);
    // 比较协议数据和设备数据是否一致
    for (uint8_t i = 0; i < 3; i++) {
      if (memcmp(buffer, read_buffer[i], 8) == 0) {
        switch (i) {
          case 0:
            Serial.println("收到来自智能管家的指令: 打开智能管家");
            break;
          case 1:
            Serial.println("收到来自智能管家的指令: 打开空调");
            break;
          case 2:
            Serial.println("收到来自智能管家的指令: 关掉空调");
            break;
          default:
            break;
        }
      }
    }
  }
}