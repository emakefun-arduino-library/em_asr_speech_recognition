/**
 * @file asr_speech_recognition.cpp
 */

#include "asr_speech_recognition.h"

#include <Arduino.h>
namespace em {
#ifndef ESP32
AsrSpeechRecognition::AsrSpeechRecognition(SoftwareSerial& mySerial) : mySerial_(mySerial) {
}
#else
AsrSpeechRecognition::AsrSpeechRecognition(HardwareSerial& mySerial) : mySerial_(mySerial) {
}
#endif

void AsrSpeechRecognition::read_protocol(uint8_t* buffer, const uint8_t cmd, const uint8_t id) {
  asr_protocol_v1 temp_protocol;
  temp_protocol.cmd = cmd;
  temp_protocol.data[0] = id % 256;
  temp_protocol.data[1] = id / 256;
  temp_protocol.chksum = (temp_protocol.head[0] + temp_protocol.head[1] + temp_protocol.id + temp_protocol.cmd +
                          temp_protocol.data[0] + temp_protocol.data[1]) &
                         0xFF;
  buffer[0] = temp_protocol.head[0];
  buffer[1] = temp_protocol.head[1];
  buffer[2] = temp_protocol.id;
  buffer[3] = temp_protocol.cmd;
  buffer[4] = temp_protocol.data[0];
  buffer[5] = temp_protocol.data[1];
  buffer[6] = temp_protocol.chksum;
  buffer[7] = temp_protocol.end;
}
void AsrSpeechRecognition::send_protocol(const uint8_t cmd, const uint8_t id) {
  static uint8_t buffer[8];
  read_protocol(buffer, cmd, id);
  mySerial_.write(buffer, 8);
}
void AsrSpeechRecognition::echo_operation(const uint8_t cmd) {
  send_protocol(ASR_ECHO_COMMAND, cmd);
}
void AsrSpeechRecognition::verify_operation(const uint8_t cmd) {
  send_protocol(ASR_VERIFY_COMMAND, cmd);
}
void AsrSpeechRecognition::broadcast_sound_operation(const uint8_t id) {
  send_protocol(ASR_BROADCAST_SOUND_COMMAND, id);
}
void AsrSpeechRecognition::reset_operation() {
  send_protocol(ASR_RESET_COMMAND, 0x01);
}
void AsrSpeechRecognition::exit_wakeup_operation() {
  send_protocol(ASR_EXIT_WAKEUP_COMMAND, 0x01);
}
void AsrSpeechRecognition::play_sound_operation(const uint8_t cmd) {
  send_protocol(ASR_PLAY_SOUND_COMMAND, cmd);
}
void AsrSpeechRecognition::set_volume_operation(const uint8_t volume) {
  send_protocol(ASR_SET_VOLUME_COMMAND, volume);
}
void AsrSpeechRecognition::get_version_operation() {
  send_protocol(ASR_GET_VERSION_COMMAND, 0x01);
}
}  // namespace em