/*
 * Hera audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier: MIT
 *
 * Copyright (C) 2019-2020 J.P. Cimalando <https://jpcima.sfd1.org/>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "UIHera.hpp"
#include "Window.hpp"

START_NAMESPACE_DISTRHO

namespace Art = ArtworkHera;

// -----------------------------------------------------------------------
// Init / Deinit

UIHera::UIHera()
  : UI(Art::backgroundWidth, Art::backgroundHeight),
    fImgBackground(Art::backgroundData, Art::backgroundWidth, Art::backgroundHeight, GL_BGRA)
{
    // Buttons

    // Button Chorus Type 1 On/Off
    Image btn1ImgOff(Art::button1OffData, Art::button1OffWidth, Art::button1OffHeight);
    Image btn1ImgOn(Art::button1OnData, Art::button1OnWidth, Art::button1OnHeight);
    fBtnTypeI = new ImageSwitch(this, btn1ImgOff, btn1ImgOn);
    fBtnTypeI->setId(paramTypeI);
    fBtnTypeI->setAbsolutePos(94, 185);
    fBtnTypeI->setCallback(this);

    // Button Chorus Type 2 On/Off
    Image btn2ImgOff(Art::button2OffData, Art::button2OffWidth, Art::button2OffHeight);
    Image btn2ImgOn(Art::button2OnData, Art::button2OnWidth, Art::button2OnHeight);
    fBtnTypeII = new ImageSwitch(this, btn2ImgOff, btn2ImgOn);
    fBtnTypeII->setId(paramTypeII);
    fBtnTypeII->setAbsolutePos(152, 185);
    fBtnTypeII->setCallback(this);
}

UIHera::~UIHera() {

}

// -----------------------------------------------------------------------
// DSP/Plugin callbacks

/**
  A parameter has changed on the plugin side.
  This is called by the host to inform the UI about parameter changes.
*/
void UIHera::parameterChanged(uint32_t index, float value) {
    switch (index) {
        case paramTypeI:
            fBtnTypeI->setDown(value);
            break;
        case paramTypeII:
            fBtnTypeII->setDown(value);
            break;
    }

    (void)value;
}

/**
  A program has been loaded on the plugin side.
  This is called by the host to inform the UI about program changes.
*/
void UIHera::programLoaded(uint32_t index) {
    if (index < presetCount) {
        for (int i=0; i < paramCount; i++) {
            // set values for each parameter and update their widgets
            parameterChanged(i, factoryPresets[index].params[i]);
        }
    }
}

/**
  Optional callback to inform the UI about a sample rate change on the plugin side.
*/
void UIHera::sampleRateChanged(double newSampleRate) {
    (void)newSampleRate;
}

// -----------------------------------------------------------------------
// Optional UI callbacks

/**
  Idle callback.
  This function is called at regular intervals.
*/
void UIHera::uiIdle() {

}

// -----------------------------------------------------------------------
// Widget callbacks


/**
  A function called to draw the view contents.
*/
void UIHera::onDisplay() {
    fImgBackground.draw();
}

void UIHera::imageSwitchClicked(ImageSwitch* sw, bool down) {
    if (sw == fBtnTypeI || sw == fBtnTypeII) {
        sw->setDown(down);
        setParameterValue(sw->getId(), down);
    }
}

// -----------------------------------------------------------------------
// Optional widget callbacks; return true to stop event propagation, false otherwise.

/**
  A function called when a key is pressed or released.
*/
bool UIHera::onKeyboard(const KeyboardEvent& ev) {
    return false;
    (void)ev;
}

/**
  A function called when a special key is pressed or released.
*/
bool UIHera::onSpecial(const SpecialEvent& ev) {
    return false;
    (void)ev;
}

/**
  A function called when a mouse button is pressed or released.
*/
bool UIHera::onMouse(const MouseEvent& ev) {
    return false;
    (void)ev;
}

/**
  A function called when the mouse pointer moves.
*/
bool UIHera::onMotion(const MotionEvent& ev) {
    return false;
    (void)ev;
}

/**
  A function called on scrolling (e.g. mouse wheel or track pad).
*/
bool UIHera::onScroll(const ScrollEvent& ev) {
    return false;
    (void)ev;
}

// -----------------------------------------------------------------------

UI* createUI() {
    return new UIHera();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
