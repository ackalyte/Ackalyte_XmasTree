/*!
* @file        AckaXmasTree.cpp
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
#include "AckaXmasTree.h"

byte neopix_fade[128] = {0};
byte neopix_TreeGreen[NUM_LEDS] = {0};
byte neopix_TreeRed[NUM_LEDS]={0};
byte neopix_TreeBlue[NUM_LEDS]={0};
byte neopix_TreeWhite[NUM_LEDS]={0};
byte TreeTop[NUM_TREE_TOPLEDS]={210,209,208,207,233,232,231,230,229,228,227,226,225,224,223,222,221,220,219,218,217,216,215,214,213};
byte TreeMiddle[NUM_TREE_MIDDLELEDS]={168,167,166,165,164,163,162,206,205,204,203,202,201,200,199,198,186,185,184,183,182,181,180,179,178,177,176,175,174,173,172,171};
byte TreeBottom[NUM_TREE_BOTTOMLEDS]={122,121,120,119,118,117,161,160,159,158,157,156,155,154,153,152,151,143,142,141,140,139,138,137,136,135,134,133,132,131,130,129,128,127};
byte TreeRoot[NUM_ROOTLEDS]={9,10,11,12,71,72,73,123,124,125,126};
byte Tree[NUM_TREELEDS]={0};

const int config = SK6812_GRBW | SK6812_800kHz;
DMAMEM TreeDisplayBuffer buff;
byte Tree_gamma[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

XmasTree::XmasTree(TreeDisplayBuffer& buff, uint8_t channel, uint8_t random_seed_pin):tree(NUM_LEDS, buff.displayMemory, buff.drawingMemory, config),m_channel(channel){
    randomSeed(analogRead(random_seed_pin));
}

XmasTree::~XmasTree(){
}

void XmasTree::init(){
  this->setTreeArray();
  this->setTreeGreen(neopix_TreeGreen);
  this->setTreeRed(neopix_TreeRed);
  this->setTreeWhite(neopix_TreeWhite);
  this->setFade(neopix_fade);
  tree.begin();
  this->show(); // Initialize all pixels to 'off'
}

void XmasTree::show(){
    tree.show();
}

uint32_t XmasTree::color(uint8_t r, uint8_t g, uint8_t b) {
  return (r << 16) | (g << 8) | b;
}

// Convert separate R,G,B,W into packed 32-bit WRGB color.
// Packed format is always WRGB, regardless of LED strand color order.
uint32_t XmasTree::color(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  return (w << 24) | (r << 16) | (g << 8) | b;
}

void XmasTree::setTreeArray(void){
    byte i=0;
    for (i=0; i<NUM_ROOTLEDS; i++) {
      Tree[i]=TreeRoot[i];
    }
    for (i=0; i<17; i++) {
      Tree[NUM_ROOTLEDS+i]=TreeBottom[i];
    }
    for (i=0; i<16; i++) {
      Tree[28+i]=TreeMiddle[i];
      }
    for (i=0; i<13; i++) {
      Tree[44+i]=TreeTop[i];
      }
    for (i=13; i<NUM_TREE_TOPLEDS; i++) {
      Tree[44+i]=TreeTop[i];
      }
    for (i=16; i<NUM_TREE_MIDDLELEDS; i++) {
      Tree[53+i]=TreeMiddle[i];
      }
    for (i=17; i<NUM_TREE_BOTTOMLEDS; i++) {
      Tree[68+i]=TreeBottom[i];
      }
 }

 
void XmasTree::snowing(void) {
      
      long snowpoints[24] = {0};
      for(byte i=0;i<4;i++){
        snowpoints[i]= random(23,62);
        }
      for(byte i=4;i<16;i++){
        snowpoints[i]= random(82,162);
        }
       for(byte i=16;i<24;i++){
        snowpoints[i]= random(162,235);
        }  
      for(int j = 0; j <128 ; j++){
          for(byte i=0;i<24;i++){
              tree.setPixel(snowpoints[i], this->color(neopix_TreeRed[snowpoints[i]],neopix_TreeGreen[snowpoints[i]],0,neopix_fade[j]));
              }
          this->show();
      }
      for(int j = 127; j >= 0 ; j--){
          for(byte i=0;i<24;i++){
              tree.setPixel(snowpoints[i], this->color(neopix_TreeRed[snowpoints[i]],neopix_TreeGreen[snowpoints[i]],0,neopix_fade[j]-1));
              }
          this->show();
      }
}
   
void XmasTree::setTreeGreen(byte *Greenpoints) {
   for(byte i=0; i<NUM_TREE_TOPLEDS; i++) {
          Greenpoints[TreeTop[i]]=255;
        }
   for(byte i=0; i<NUM_TREE_MIDDLELEDS; i++) {
          Greenpoints[TreeMiddle[i]]=255;
        }
   for(byte i=0; i<NUM_TREE_BOTTOMLEDS; i++) {
          Greenpoints[TreeBottom[i]]=255;
        }
   for(byte i=0; i<NUM_ROOTLEDS; i++) {
          Greenpoints[TreeRoot[i]]=ORANGE_green;
        }
}
void XmasTree::setTreeRed(byte *Red) {
  for(byte i=0; i<NUM_ROOTLEDS; i++) {
          Red[TreeRoot[i]]=ORANGE_red;
        }
}
void XmasTree::setTreeWhite(byte *White) {
   for(uint16_t i=0; i<9; i++) {
          White[i]=225;
        }
   for(uint16_t i=13; i<23; i++) {
          White[i]=225;
        }
   for(uint16_t i=62; i<71; i++) {
          White[i]=225;
        }
   for(uint16_t i=74; i<82; i++) {
          White[i]=225;
        }
}

void XmasTree::allwhite(void) {
  for (byte i=0; i<NUM_LEDS; i++) {
    tree.setPixel(i, this->color(0,0,0,255));
  }
  this->show();
}
void XmasTree::setTree0(void) {
 for (byte i=0; i<NUM_LEDS; i++) {
    tree.setPixel(i, this->color(neopix_TreeRed[i],neopix_TreeGreen[i],0,0));
  }
}

void XmasTree::setTree1random(void) {
 for (byte i=0; i<NUM_LEDS; i++) {
    tree.setPixel(i, this->color(neopix_TreeRed[i],neopix_TreeGreen[i],0,0));
  }
 
 long leftspot[4] = {0};
 long rightspot[4] = {0};
 for (byte i=0; i<4; i++) {
    leftspot[i] = random(0,9);
    rightspot[i] = random(13,22);
    tree.setPixel(leftspot[i], this->color(neopix_TreeRed[leftspot[i]],neopix_TreeGreen[leftspot[i]],0,255));
    tree.setPixel(rightspot[i], this->color(neopix_TreeRed[rightspot[i]],neopix_TreeGreen[rightspot[i]],0,255));
  }
 snowing();
 for (byte i=0; i<4; i++) {
    leftspot[i] = random(0,9);
    rightspot[i] = random(13,22);
    tree.setPixel(leftspot[i], this->color(neopix_TreeRed[leftspot[i]],neopix_TreeGreen[leftspot[i]],0,255));
    tree.setPixel(rightspot[i], this->color(neopix_TreeRed[rightspot[i]],neopix_TreeGreen[rightspot[i]],0,255));
  }
}

void XmasTree::setTree1(void) {
  for (byte i=0; i<22; i++) {
    tree.setPixel(i, this->color(neopix_TreeRed[i],neopix_TreeGreen[i],0,neopix_TreeWhite[i]));
  }
  for (byte i=22; i<NUM_LEDS; i++) {
    tree.setPixel(i, this->color(neopix_TreeRed[i],neopix_TreeGreen[i],0,0));
  }
}
void XmasTree::setTree2random(void) {
  for (byte i=0; i<22; i++) {
    tree.setPixel(i, this->color(neopix_TreeRed[i],neopix_TreeGreen[i],0,neopix_TreeWhite[i]));
  }
  for (byte i=22; i<NUM_LEDS; i++) {
    tree.setPixel(i, this->color(neopix_TreeRed[i],neopix_TreeGreen[i],0,0));
  }
 
 long leftspot[4] = {0};
 long rightspot[4] = {0};
 for (byte i=0; i<4; i++) {
    leftspot[i] = random(62,71);
    rightspot[i] = random(74,82);
    tree.setPixel(leftspot[i], this->color(neopix_TreeRed[leftspot[i]],neopix_TreeGreen[leftspot[i]],0,255));
    tree.setPixel(rightspot[i], this->color(neopix_TreeRed[rightspot[i]],neopix_TreeGreen[rightspot[i]],0,255));
  }
 snowing();
 for (byte i=0; i<4; i++) {
    leftspot[i] = random(62,71);
    rightspot[i] = random(74,82);
    tree.setPixel(leftspot[i], this->color(neopix_TreeRed[leftspot[i]],neopix_TreeGreen[leftspot[i]],0,255));
    tree.setPixel(rightspot[i], this->color(neopix_TreeRed[rightspot[i]],neopix_TreeGreen[rightspot[i]],0,255));
  }
}

void XmasTree::setTree2(void) {
  for (byte i=0; i<NUM_LEDS; i++) {
    tree.setPixel(i, this->color(neopix_TreeRed[i],neopix_TreeGreen[i],0,neopix_TreeWhite[i]));
  }
}

void XmasTree::setFade(byte *fade){
  for(uint16_t i=0; i<128; i++) {
          fade[i]=i*2+1;
        }
  }


void XmasTree::rainbowTree(uint8_t wait) {
  uint16_t i, j;
    for(j=0; j<256; j++) {
      for(i=NUM_ROOTLEDS; i<NUM_TREELEDS; i++) {
        tree.setPixel(Tree[i], Wheel((i+j) & 255));
        this->show();
      }
      delay(wait);
    }
}

void XmasTree::rainbowFade2White(uint8_t wait, int rainbowLoops, int whiteLoops) {
  float fadeMax = 100.0;
  int fadeVal = 0;
  uint32_t wheelVal;
  int redVal, greenVal, blueVal;

  for(int k = 0 ; k < rainbowLoops ; k ++){
    
    for(int j=0; j<256; j++) { // 5 cycles of all colors on wheel

      for(int i=NUM_ROOTLEDS; i< NUM_TREELEDS; i++) {

        wheelVal = Wheel(((i * 256 / 91) + j) & 255);

        redVal = red(wheelVal) * float(fadeVal/fadeMax);
        greenVal = green(wheelVal) * float(fadeVal/fadeMax);
        blueVal = blue(wheelVal) * float(fadeVal/fadeMax);

        tree.setPixel( Tree[i], this->color( redVal, greenVal, blueVal ) );

      }
       for(int i=0; i< NUM_ROOTLEDS; i++) {

        redVal = ORANGE_red * float(fadeVal/fadeMax);
        greenVal = ORANGE_green * float(fadeVal/fadeMax);
        blueVal = 0 * float(fadeVal/fadeMax);

        tree.setPixel( Tree[i], this->color( redVal, greenVal, blueVal ) );

      }

      //First loop, fade in!
      if(k == 0 && fadeVal < fadeMax-1) {
          fadeVal++;
      }

      //Last loop, fade out!
      else if(k == rainbowLoops - 1 && j > 255 - fadeMax ){
          fadeVal--;
      }
        this->show();
        delay(wait);
    }
  }

  delay(500);

}

void XmasTree::rainbowCycleTree(uint8_t wait, byte cycle) {
  uint16_t i, j;
  for(j=0; j<256 * cycle; j++) { // 5 cycles of all colors on wheel
    for(i=NUM_ROOTLEDS; i< NUM_TREELEDS; i++) {
      tree.setPixel(Tree[i], Wheel(((i * 256 / 91) + j) & 255));
    } 
  for(i = NUM_ROOTLEDS; i<NUM_TREELEDS;i++){
    }
    this->show();
    delay(wait);
  }
}
uint32_t XmasTree::Wheel(int WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return this->color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return this->color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return this->color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}

uint8_t XmasTree::red(uint32_t c) {
  return (c >> 16);
}
uint8_t XmasTree::green(uint32_t c) {
  return (c >> 8);
}
uint8_t XmasTree::blue(uint32_t c) {
  return (c);
}
void XmasTree::colorWipe(uint32_t root_c,uint32_t leaf_c, uint8_t wait) {
  for(uint16_t i=0; i<12; i++) {
    tree.setPixel(Tree[i], root_c);
    this->show();
    delay(wait);
  }
  for(uint16_t i=NUM_ROOTLEDS; i<NUM_TREELEDS; i++) {
    tree.setPixel(Tree[i], leaf_c);
    this->show();
    delay(wait);
  }
}

void XmasTree::TreeGrowing(uint32_t root_c,uint32_t leaf_c,uint8_t wait) {
  for(uint16_t i=0; i<4; i++) {
    tree.setPixel(Tree[i], root_c);
  }
  this->show();
  delay(wait);
  for(uint16_t i=4; i<7; i++) {
    tree.setPixel(Tree[i], root_c);
  }
  this->show();
  delay(wait);
  for(uint16_t i=7; i<11; i++) {
    tree.setPixel(Tree[i], root_c);
  }
  this->show();
  delay(wait);
  for(uint16_t i=11; i<17; i++) {
    tree.setPixel(Tree[i], leaf_c);
    tree.setPixel(Tree[112-i], leaf_c);
  }
  this->show();
  delay(wait);
  for(uint16_t i=17; i<57; i++) {
    tree.setPixel(Tree[i], leaf_c);
    tree.setPixel(Tree[112-i], leaf_c);
    this->show();
    delay(wait);
  }
}

void XmasTree::SnowOnTreeCycle(byte wait,byte cycle){
   for(int j = 0; j <256 ; j++){
          for(byte i=0;i<NUM_ROOTLEDS;i++){
              tree.setPixel(Tree[i], this->color(float(Tree_gamma[j]*ORANGE_red/255),float(Tree_gamma[j]*ORANGE_green/255),0,0));
              }
          for(byte i=0;i<30;i++){
              tree.setPixel(Tree[3*i+11], this->color(0,0,0,Tree_gamma[j]));
              tree.setPixel(Tree[3*i+12], this->color(0,Tree_gamma[j],0,0));
              tree.setPixel(Tree[3*i+13], this->color(0,Tree_gamma[j],0,0));
              }
          tree.setPixel(Tree[101], this->color(0,0,0,Tree_gamma[j]));
          this->show();
          delay(wait);
      }
      delay(500);
       for (byte l=0;l<cycle;l++){
          for(byte i=0;i<30;i++){
              tree.setPixel(Tree[3*i+11],WARM_WHITE);
              tree.setPixel(Tree[3*i+13], GREEN);
              }
          tree.setPixel(Tree[101], WARM_WHITE);
          this->show();
          delay(500);
           for(byte i=0;i<30;i++){
              tree.setPixel(Tree[3*i+11],GREEN);
              tree.setPixel(Tree[3*i+12], WARM_WHITE);
              }
          tree.setPixel(Tree[101], GREEN);
          this->show();
          delay(500);
           for(byte i=0;i<30;i++){
              tree.setPixel(Tree[3*i+12], GREEN);
              tree.setPixel(Tree[3*i+13], WARM_WHITE);
              }
          this->show();
          delay(500);
       }
      for(int j = 255; j >= 0 ; j--){
         for(byte i=0;i<NUM_ROOTLEDS;i++){
              tree.setPixel(Tree[i], this->color(float(Tree_gamma[j]*ORANGE_red/255),float(Tree_gamma[j]*ORANGE_green/255),0,0));
              }
          for(byte i=0;i<30;i++){
              tree.setPixel(Tree[3*i+11], this->color(0,Tree_gamma[j],0,0));
              tree.setPixel(Tree[3*i+12], this->color(0,Tree_gamma[j],0,0));
              tree.setPixel(Tree[3*i+13], this->color(0,0,0,Tree_gamma[j]));
              }
          tree.setPixel(Tree[101], this->color(0,Tree_gamma[j],0,0));
          this->show();
          delay(wait);
      }
  }
  void XmasTree::SnowOnTree(byte wait){
   for(int j = 0; j <256 ; j++){
          for(byte i=0;i<NUM_ROOTLEDS;i++){
              tree.setPixel(Tree[i], this->color(float(Tree_gamma[j]*ORANGE_red/255),float(Tree_gamma[j]*ORANGE_green/255),0,0));
              }
          for(byte i=0;i<45;i++){
              tree.setPixel(Tree[2*i+11], this->color(0,0,0,Tree_gamma[j]));
              tree.setPixel(Tree[2*i+12], this->color(0,Tree_gamma[j],0,0));
              }
          tree.setPixel(Tree[101], this->color(0,0,0,Tree_gamma[j]));
          this->show();
          delay(wait);
      }
      delay(1000);
      for(int j = 255; j >= 0 ; j--){
         for(byte i=0;i<NUM_ROOTLEDS;i++){
              tree.setPixel(Tree[i], this->color(float(Tree_gamma[j]*ORANGE_red/255),float(Tree_gamma[j]*ORANGE_green/255),0,0));
              }
          for(byte i=0;i<45;i++){
              tree.setPixel(Tree[2*i+11], this->color(0,0,0,Tree_gamma[j]));
              tree.setPixel(Tree[2*i+12], this->color(0,Tree_gamma[j],0,0));
              }
          tree.setPixel(Tree[101], this->color(0,0,0,Tree_gamma[j]));
          this->show();
          delay(wait);
      }
  }
void XmasTree::RedOnTree(byte wait){
   for(int j = 0; j <256 ; j++){
          for(byte i=0;i<NUM_ROOTLEDS;i++){
              tree.setPixel(Tree[i], this->color(float(Tree_gamma[j]*ORANGE_red/255),float(Tree_gamma[j]*ORANGE_green/255),0,0));
              }
          for(byte i=0;i<45;i++){
            tree.setPixel(Tree[2*i+11], this->color(0,Tree_gamma[j],0,0));
            tree.setPixel(Tree[2*i+12], this->color(Tree_gamma[j],0,0,0));
              }
          tree.setPixel(Tree[101], this->color(0,Tree_gamma[j],0,0));
          this->show();
          delay(wait);
      }
    delay(1000);
    for(int j = 255; j >= 0 ; j--){
        for(byte i=0;i<NUM_ROOTLEDS;i++){
            tree.setPixel(Tree[i], this->color(float(Tree_gamma[j]*ORANGE_red/255),float(Tree_gamma[j]*ORANGE_green/255),0,0));
            }
        for(byte i=0;i<45;i++){
            tree.setPixel(Tree[2*i+11], this->color(0,Tree_gamma[j],0,0));
            tree.setPixel(Tree[2*i+12], this->color(Tree_gamma[j],0,0,0));
            }
        tree.setPixel(Tree[101], this->color(0,Tree_gamma[j],0,0));
        this->show();
        delay(wait); 
        }
  }
  
void XmasTree::WhiteRedOnTree(byte wait,byte cycle){
   for(int j = 0; j <256 ; j++){
       for(byte i=0;i<NUM_ROOTLEDS;i++){
           tree.setPixel(Tree[i], this->color(float(Tree_gamma[j]*ORANGE_red/255),float(Tree_gamma[j]*ORANGE_green/255),0,0));
           }
       for(byte i=0;i<30;i++){
           tree.setPixel(Tree[3*i+11], this->color(0,Tree_gamma[j],0,0));        
           tree.setPixel(Tree[3*i+12], this->color(0,0,0,Tree_gamma[j]));
           tree.setPixel(Tree[3*i+13], this->color(Tree_gamma[j],0,0,0));
           }
       tree.setPixel(Tree[101], this->color(0,Tree_gamma[j],0,0));  
       this->show();
       delay(wait);
       }
    delay(500);
    for (byte l=0;l<cycle;l++){
         for(byte i=0;i<30;i++){
             //tree.setPixel(Tree[3*i+11], this->color(0,Tree_gamma[j],0,0));        
             tree.setPixel(Tree[3*i+12], RED);
             tree.setPixel(Tree[3*i+13], WARM_WHITE);
             }
         this->show();
         delay(500);
         for(byte i=0;i<30;i++){
             //tree.setPixel(Tree[3*i+11], this->color(0,Tree_gamma[j],0,0));        
             tree.setPixel(Tree[3*i+12], WARM_WHITE);
             tree.setPixel(Tree[3*i+13], RED);
             }
         this->show();
         delay(500);
         }
     for(int j = 255; j >= 0 ; j--){
         for(byte i=0;i<9;i++){
             tree.setPixel(i, this->color(0,0,0,Tree_gamma[j]) );
            }
         for(byte i=13;i<23;i++){
             tree.setPixel(i, this->color(0,0,0,Tree_gamma[j]) );
            }
         for(byte i=62;i<71;i++){
            tree.setPixel(i, this->color(0,0,0,Tree_gamma[j]) );
            }
         for(byte i=74;i<82;i++){
            tree.setPixel(i, this->color(0,0,0,Tree_gamma[j]) );
            }
         for(byte i=0;i<NUM_ROOTLEDS;i++){
              tree.setPixel(Tree[i], this->color(float(Tree_gamma[j]*ORANGE_red/255),float(Tree_gamma[j]*ORANGE_green/255),0,0));
              }
         for(byte i=0;i<30;i++){
            tree.setPixel(Tree[3*i+11], this->color(0,Tree_gamma[j],0,0));
            tree.setPixel(Tree[3*i+12], this->color(0,0,0,Tree_gamma[j]));
            tree.setPixel(Tree[3*i+13], this->color(Tree_gamma[j],0,0,0));
            }
         tree.setPixel(Tree[101], this->color(0,Tree_gamma[j],0,0));
         this->show();
         delay(wait);
      }
  }

void XmasTree::pulseWhite(uint8_t wait) {
  for(int j = 0; j < 256 ; j++){
      for(uint16_t i=NUM_ROOTLEDS; i<NUM_TREELEDS; i++) {
          tree.setPixel(Tree[i], this->color(0,0,0, Tree_gamma[j] ) );
        }
        delay(wait);
        this->show();
      }    
  for(int j = 255; j >= 0 ; j--){
      for(uint16_t i=NUM_ROOTLEDS; i<NUM_TREELEDS; i++) {
          tree.setPixel(Tree[i], this->color(0,0,0, Tree_gamma[j] ) );
        }
        delay(wait);
        this->show();
      }
  }

void XmasTree::WhiteTreeFadeOut(uint8_t wait){
  for(int j = 255; j >= 0 ; j--){
      for(uint16_t i=NUM_ROOTLEDS; i<NUM_TREELEDS; i++) {
          tree.setPixel(Tree[i], this->color(0,0,0,Tree_gamma[j]) );
        }
      for(uint16_t i=0; i<NUM_ROOTLEDS; i++) {
          tree.setPixel(Tree[i], this->color(float(Tree_gamma[j]*ORANGE_red/255),float(Tree_gamma[j]*ORANGE_green/255),0,0) );
        }
        delay(wait);
        this->show();
      }
  }

void XmasTree::GreenTreeSnowFadeOut(uint8_t wait){
  for(int j = 255; j >= 0 ; j--){
      for(uint16_t i=NUM_ROOTLEDS; i<NUM_TREELEDS; i++) {
          tree.setPixel(Tree[i], this->color(0,Tree_gamma[j],0,0) );
        }
      for(uint16_t i=0; i<NUM_ROOTLEDS; i++) {
          tree.setPixel(Tree[i], this->color(float(Tree_gamma[j]*ORANGE_red/255),float(Tree_gamma[j]*ORANGE_green/255),0,0) );
        }
        delay(wait);
        this->show();
      }
  }

void XmasTree::PlayChristmasPattern(void){
  this->setTree0();
  this->snowing();
  this->setTree1random();
  this->snowing();
  this->setTree1();
  this->snowing();
  this->setTree2random();
  this->snowing();
  this->setTree2();
  this->snowing();
  this->setTree2();
  this->GreenTreeSnowFadeOut(5);
  this->SnowOnTree(1);
  this->RedOnTree(1);
  this->WhiteRedOnTree(1,6);
}
