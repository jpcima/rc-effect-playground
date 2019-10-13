//
// A generic and somewhat minimal superclass for Faust-generated classes.
// Pass faust `-scn faustObject` in order to use it.
//

#pragma once

class faustObject {
public:
    virtual ~faustObject() {}

    class Meta {
    public:
        virtual ~Meta() {}
        virtual void declare(const char *property, const char *value) {}
    };

    class UI {
    public:
        virtual ~UI() {}
        virtual void declare(float *control, const char *property, const char *value) {}

        void openTabBox(...) {}
        void openHorizontalBox(...) {}
        void openVerticalBox(...) {}
        void closeBox() {}

        void addButton(...) {}
        void addCheckButton(...) {}
        void addVerticalSlider(...) {}
        void addHorizontalSlider(...) {}
        void addNumEntry(...) {}

        void addHorizontalBargraph(...) {}
        void addVerticalBargraph(...) {}

        void addSoundfile(...) {}
    };
};
