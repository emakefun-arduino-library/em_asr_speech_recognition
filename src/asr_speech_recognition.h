/**
 * @file asr_speech_recognition.h
 */
#pragma once

#ifndef _EM_ASR_SPEECH_RECOGNITION_H_
#define _EM_ASR_SPEECH_RECOGNITION_H_

#include <SoftwareSerial.h>
#include <WString.h>
#include <stdint.h>

namespace em {
/**
 * @~Chinese
 * @brief 定义常量。
 */
/**
 * @~English
 * @brief Define constants.
 */
#define ASR_SERIAL_BAUD_RATE (9600)

#define ASR_READ_GENERAL_COMMAND (0x81)
#define ASR_GREETING__COMMAND (0x82)

#define ASR_ECHO_COMMAND (0x01)
#define ASR_VERIFY_COMMAND (0x02)
#define ASR_BROADCAST_SOUND_COMMAND (0x03)
#define ASR_RESET_COMMAND (0x04)
#define ASR_EXIT_WAKEUP_COMMAND (0x05)
#define ASR_PLAY_SOUND_COMMAND (0x06)
#define ASR_SET_VOLUME_COMMAND (0x07)
#define ASR_GET_VERSION_COMMAND (0x08)

/**
 * @~Chinese
 * @class AsrSpeechRecognition
 * @brief AsrSpeechRecognition是语音识别模块的驱动类，用于与语音识别模块进行通信。
 * @example read_from_device.ino 从设备中读取数据。
 */
/**
 * @~English
 * @class AsrSpeechRecognition
 * @brief AsrSpeechRecognition is a driver class for communication with the speech recognition module.
 * @example read_from_device.ino Read data from the device.
 */
class AsrSpeechRecognition {
 public:
/**
 * @~Chinese
 * @brief 构造函数。
 * @param mySerial 软件串口对象。
 */
/**
 * @~English
 * @brief Constructor.
 * @param mySerial Software serial object.
 */
#ifndef ESP32
  explicit AsrSpeechRecognition(SoftwareSerial& mySerial);
#else
  explicit AsrSpeechRecognition(HardwareSerial& mySerial);
#endif

  /**
   * @~Chinese
   * @brief 数据解码。
   * @param[in] buffer 指令解码后的缓冲区。
   * @param[in] cmd 指令类型。
   * @param[in] id 命令词ID。
   */
  /**
   * @~English
   * @brief Data decoding.
   * @param[in] buffer Decoded buffer.
   * @param[in] cmd Command type.
   * @param[in] id Command ID.
   */
  void read_protocol(uint8_t* buffer, const uint8_t cmd, const uint8_t id);
  void send_protocol(const uint8_t cmd, const uint8_t id);
  void echo_operation(const uint8_t cmd);
  void verify_operation(const uint8_t cmd);
  void broadcast_sound_operation(const uint8_t id);
  void reset_operation();
  void exit_wakeup_operation();
  void play_sound_operation(const uint8_t cmd);
  void set_volume_operation(const uint8_t volume);
  void get_version_operation();

 private:
#ifndef ESP32
  SoftwareSerial mySerial_;
#else
  HardwareSerial mySerial_;
#endif
  struct asr_protocol_v1 {
    const uint8_t head[2] = {0xA5, 0xFA};
    const uint8_t id = 0x00;
    uint8_t cmd;
    uint8_t data[2];
    uint8_t chksum;
    const uint8_t end = 0xFB;
  };
};
}  // namespace em
#endif