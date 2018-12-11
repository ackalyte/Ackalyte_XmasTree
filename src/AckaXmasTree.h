#ifndef ACKAXMASTREE_H
#define ACKAXMASTREE_H
#include <stdint.h>
#include <AckaLED.h>
#include "treeDisplayBuffer.h"

#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x000000FF
#define WARM_WHITE 0xFF000000
#define ORANGE_red 0x64
#define ORANGE_green 0x2D
#define ORANGE 0x00642D00

#define NUM_LEDS 234
#define NUM_TREELEDS 102
#define NUM_TREE_TOPLEDS 25
#define NUM_TREE_MIDDLELEDS 32
#define NUM_TREE_BOTTOMLEDS 34
#define NUM_ROOTLEDS 11
enum _channels{
    CHANNEL1=0,
    CHANNEL2,
    CHANNEL3,
    CHANNEL4,
    CHANNEL5,
    CHANNEL6,
    CHANNEL7,
    CHANNEL8,
    CHANNEL9,
    CHANNEL10,
    CHANNEL11,
    CHANNEL12,
    CHANNEL13,
    CHANNEL14,
    CHANNEL15,

    TOTAL_CHANNELS
};
class XmasTree{
    public:
        XmasTree(TreeDisplayBuffer& buff, uint8_t channel, uint8_t random_seed_pin);
        virtual ~XmasTree();
        void init();
        void show();
        uint32_t color(uint8_t r, uint8_t g, uint8_t b);
        uint32_t color(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
        void snowing(void);
        void setTreeGreen(byte *Greenpoints);
        void setTreeRed(byte *Red);
        void setTreeWhite(byte *White);
        void allwhite(void);
        void setTree0(void);
        void setTree1random(void);
        void setTree1(void);
        void setTree2random(void);
        void setTree2(void);
        void setFade(byte *fade);
        void setTreeArray(void);
        void rainbowTree(uint8_t wait);
        void rainbowFade2White(uint8_t wait, int rainbowLoops, int whiteLoops);
        void rainbowCycleTree(uint8_t wait, byte cycle);
        uint32_t Wheel(int WheelPos);
        uint8_t red(uint32_t c);
        uint8_t green(uint32_t c);
        uint8_t blue(uint32_t c);
        void colorWipe(uint32_t root_c,uint32_t leaf_c, uint8_t wait);
        void TreeGrowing(uint32_t root_c,uint32_t leaf_c,uint8_t wait);
        void SnowOnTreeCycle(byte wait,byte cycle);
        void SnowOnTree(byte wait);
        void RedOnTree(byte wait);
        void WhiteRedOnTree(byte wait,byte cycle);
        void whiteOverRainbow(uint8_t wait, uint8_t whiteSpeed, uint8_t whiteLength );
        void pulseWhite(uint8_t wait);
        void WhiteTreeFadeOut(uint8_t wait);
        void GreenTreeSnowFadeOut(uint8_t wait);
        void PlayChristmasPattern(void);

    private:
        AckaLED tree;
        uint8_t m_channel;
};
#endif