/**
 * @~Chinese
 * @file play_with_encodings.ino
 * @brief 示例：TTS20模块不同编码方式播放演示。
 * @example play_with_encodings.ino
 * @details 演示TTS20模块使用GB2312和UTF-8两种编码方式播放文本的功能。
 */
/**
 * @~English
 * @file play_with_encodings.ino
 * @brief Example: TTS20 module playback with different encodings demonstration.
 * @example play_with_encodings.ino
 * @details Demonstrate the TTS20 module's ability to play text using both GB2312 and UTF-8 encoding methods.
 */

#include "tts20.h"

namespace {
em::Tts20 g_tts20(em::Tts20::kDefaultI2cAddress, Wire);

}  // namespace

void setup() {
  Serial.begin(115200);

  Wire.begin();

  g_tts20.Init();

  Serial.print(F("Device ID: 0x"));
  Serial.println(g_tts20.device_id(), HEX);
  Serial.print(F("Name: "));
  Serial.println(g_tts20.name());
  Serial.print(F("Firmware Version: "));
  Serial.println(g_tts20.firmware_version());
}

void loop() {
  Serial.println(F("Using GB2312 Encoding, playing: \"欢迎使用语音合成模块\""));
  if (g_tts20.Play(F("欢迎使用语音合成模块"), em::Tts20::TextEncodingType::kGb2312)) {
    Serial.println(F("GB2312 playback successful"));
  } else {
    Serial.println(F("GB2312 playback failed"));
  }

  while (g_tts20.IsBusy());

  delay(2000);

  Serial.println(F("Using UTF-8 encoding, playing: \"欢迎使用语音合成模块\""));
  if (g_tts20.Play(F("欢迎使用语音合成模块"), em::Tts20::TextEncodingType::kUtf8)) {
    Serial.println(F("UTF-8 playback successful"));
  } else {
    Serial.println(F("UTF-8 playback failed"));
  }

  while (g_tts20.IsBusy());

  delay(2000);
}