/*!
* @file        XMAS-Tree.ino
* @copyright   Copyright (c) 2018 Ackalyte
*
*              Permission is hereby granted, free of charge, to any person obtaining a copy
*              of this software and associated documentation files (the "Software"), to deal
*              in the Software without restriction, including without limitation the rights
*              to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*              copies of the Software, and to permit persons to whom the Software is
*              furnished to do so, subject to the following conditions:
*
*              The above copyright notice and this permission notice shall be included in all
*              copies or substantial portions of the Software.
*
*              THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*              IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*              FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*              AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*              LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*              OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*              SOFTWARE.
*
*
* @author      Chenxu Gong <c.gong@tektindustries.com>
* @co-author   Sahil Khanna <s.khanna@tektindustries.com>
* @date        10 Dec 2018
* @brief       Christmas Tree LED for RGBW Triangle strips
*/

#include <AckaXmasTree.h>

#define ROOT_COLOR ORANGE
#define LEAF_COLOR GREEN
#define SNOW_COLOR WARM_WHITE
#define RANDOM_SEED_PIN 0
DMAMEM TreeDisplayBuffer dmaMemory;
XmasTree tree(dmaMemory,CHANNEL1,RANDOM_SEED_PIN);

void setup() {
  tree.init();
}

void loop() {
  tree.PlayChristmasPattern();
}
