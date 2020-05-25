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

#ifndef UI_HERA_H
#define UI_HERA_H

#include "DistrhoUI.hpp"
#include "ImageWidgets.hpp"

#include "PluginHera.hpp"
#include "ArtworkHera.hpp"

START_NAMESPACE_DISTRHO

class UIHera : public UI,
               public ImageSwitch::Callback
{
public:
    UIHera();
    ~UIHera();

protected:
    void parameterChanged(uint32_t, float value) override;
    void programLoaded(uint32_t index) override;
    void sampleRateChanged(double newSampleRate) override;

    void uiIdle() override;

    void onDisplay() override;

    bool onKeyboard(const KeyboardEvent& ev) override;
    bool onSpecial(const SpecialEvent& ev) override;
    bool onMouse(const MouseEvent& ev) override;
    bool onMotion(const MotionEvent& ev) override;
    bool onScroll(const ScrollEvent& ev) override;

    void imageSwitchClicked(ImageSwitch* sw, bool down) override;

private:
    Image fImgBackground;
    ScopedPointer<ImageSwitch> fBtnTypeI, fBtnTypeII;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIHera)
};

END_NAMESPACE_DISTRHO

#endif
