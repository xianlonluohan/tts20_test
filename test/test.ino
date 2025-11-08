/**
 * @~Chinese
 * @file play.ino
 * @brief 示例：TTS20模块播放演示。
 * @example play.ino
 * @details TTS20模块播放演示。
 */
/**
 * @~English
 * @file play.ino
 * @brief Example: TTS20 module playback demonstration.
 * @example play.ino
 * @details module playback demonstration.
 */

#include "tts20.h"

namespace
{
    em::Tts20 g_tts20(em::Tts20::kDefaultI2cAddress, Wire);

} // namespace

void setup()
{
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

void loop()
{
    String test = F(
        "[v1]我四岁的时候，对这世界一无所知，以为它只是一些故事。我五岁的时候，“妈”对我吐露真相，说真实的世界大到你无法相信，而房间只是它一个又小又臭的碎片。对五岁的杰克而言，房间就是全世界。这是他出生和成长的地方，他跟妈住在这里，学习、阅读、吃饭、睡觉、游戏。但对妈而言，房间却是老尼克囚禁她七年的监狱。她在不可能的禁闭环境里尽量让杰克健康成长。每晚，她让杰克睡在衣橱里，不让他看到恶男子强暴她的恐怖画面；她也不让杰克沉溺在电视中，规定他每天看电视的时间。然而，她终究只是一个母亲，而非圣母，她会不耐烦，她会生气地对着杰克大吼，她甚至间或性情绪低落到一整天不肯起床，也不给杰克做饭。正是这复杂而不完美的母性，让人纠结不已。靠着决心、机智和强大的母爱，妈为杰克创造了人生。但她知道这样是不够的……对她不够，对杰克也不够。她想出一个大胆的脱逃计划，需要仰赖她儿子的勇气，以及大量的运气。她没想到的是，对这计划一旦成功会产生什么样的后果，自己竟然没有充分的准备。文章讲述了作者作为一名在外求学的游子，搬入一间新租的房间。他/她通过亲手打扫、布置这个空间，不仅清理了物理上的尘埃，也进行了一场内心的洗礼。最终作者在这个属于自己的“房间”里，找到了精神的栖息地，学会了与孤独共处，并确认了自我的存在。总而言之，《房间》讲述的是一个关于 “安顿” 的现代寓言——我们如何在一个陌生的城市里，通过经营一个微小的物理空间，最终为自己漂泊的心灵找到一个可以停靠的港湾。"

    );
    if (g_tts20.Play(test))
    {
        Serial.println(F("Play successful"));
    }
    else
    {
        Serial.println(F("Play failed"));
    }

    while (g_tts20.IsBusy())
        ;

    delay(20000);
}