#pragma once

#ifndef _EM_TTS20_H_
#define _EM_TTS20_H_

#include <Arduino.h>
#include <Wire.h>

#include "em_check.h"

/**
 * @file tts20.h
 */

namespace em {

/**
 * @~Chinese
 * @brief TTS20 文本转语音模块驱动类
 * @details 该类提供了与TTS20文本转语音模块通信的接口，支持通过I2C协议
 *          发送文本、控制播放状态、查询设备信息等功能
 */
/**
 * @~English
 * @brief TTS20 Text-to-Speech Module Driver Class
 * @details This class provides the interface for communicating with the TTS20
 *          text-to-speech module, supporting functions such as sending text via
 *          I2C protocol, controlling playback status, and querying device information
 */
class Tts20 {
 public:
  /**
   * @~Chinese
   * @brief 默认I2C地址。
   */
  /**
   * @~English
   * @brief Default I2C address.
   */
  static constexpr uint8_t kDefaultI2cAddress = 0x40;

  /**
   * @~Chinese
   * @brief 构造函数。
   * @param[in] i2c_address I2C地址。
   * @param[in] wire TwoWire 对象引用。
   */
  /**
   * @~English
   * @brief Constructor.
   * @param[in] i2c_address I2C address.
   * @param[in] wire TwoWire object reference.
   */
  Tts20(const uint8_t i2c_address, TwoWire &wire);

  /**
   * @~Chinese
   * @brief 初始化。
   */
  /**
   * @~English
   * @brief Initialize.
   */
  void Init();

  /**
   * @~Chinese
   * @brief 获取固件版本。
   * @return 固件版本。
   */
  /**
   * @~English
   * @brief Get firmware version.
   * @return Firmware version.
   */
  String firmware_version();

  /**
   * @~Chinese
   * @brief 获取设备ID。
   * @return 设备ID。
   */
  /**
   * @~English
   * @brief Get device ID.
   * @return Device ID.
   */
  uint8_t device_id();

  /**
   * @~Chinese
   * @brief 获取设备名称。
   * @return 设备名称。
   */
  /**
   * @~English
   * @brief Get device name.
   * @return Device name.
   */
  String name();

  /**
   * @~Chinese
   * @brief 文本转语音并播放。
   * @param[in] text 要播放的文本数据，数据长度不大于4K个字节。
   * @return 是否成功合成并开始播放。
   * @details 文本长度限制：单次合成文本量最多4K字节。如果文本超过此限制，播放将失败。
   *          - 建议在发送前检查文本长度，避免因文本过长导致的播放失败。
   */
  /**
   * @~English
   * @brief Convert text to speech and play.
   * @param[in] text The text data to be played should not exceed a length of 4K bytes.
   * @return Has it been successfully synthesized and started playing.
   * @details Text length limit: Maximum 4K bytes per synthesis. Playback will fail if text exceeds this limit.
   *          - It is recommended to check text length before sending to avoid playback failure due to excessive text length.
   */
  bool Play(const String &text);

  /**
   * @~Chinese
   * @brief 检查模块是否处于忙碌状态。
   * @return true 表示模块处于忙碌状态，false 表示模块空闲。
   */
  /**
   * @~English
   * @brief Check if the module is in busy state.
   * @return true indicates the module is busy, false indicates the module is idle.
   */
  bool IsBusy();

  /**
   * @~Chinese
   * @brief 终止播放。
   * @return 是否成功终止播放。
   */
  /**
   * @~English
   * @brief Stop playback.
   * @return Has the playback been successfully stopped.
   */
  bool Stop();

  /**
   * @~Chinese
   * @brief 暂停播放，后续可以继续播放。
   * @return 是否成功暂停播放。
   */
  /**
   * @~English
   * @brief Pause playback, you can continue playing in the future.
   * @return Has the playback been successfully stopped..
   */
  bool Pause();

  /**
   * @~Chinese
   * @brief 恢复播放（暂停后继续播放）。
   * @return 是否成功恢复播放。
   */
  /**
   * @~English
   * @brief Resume playback (pause and resume playback).
   * @return Whether the playback has been successfully restored.
   */
  bool Resume();

 private:
  Tts20(const Tts20 &) = delete;
  Tts20 &operator=(const Tts20 &) = delete;

  void ClearRxBuffer();
  void I2cWrite(const uint8_t *data, const uint16_t size);
  uint16_t I2cRead(uint8_t *buffer, const uint16_t expected_length, const uint32_t timeout_ms);
  bool ReadUntil(const uint8_t target_byte, const uint32_t timeout_ms);

  const uint8_t i2c_address_ = kDefaultI2cAddress;
  TwoWire &wire_ = Wire;
  uint8_t rx_buffer_capacity_ = 0;
};

}  // namespace em
#endif