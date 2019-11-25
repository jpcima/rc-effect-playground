#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX, Christopher Arndt, and Patrick Desaulniers
#

include dpf/Makefile.base.mk

all: libs plugins gen

# --------------------------------------------------------------

submodules:
	git submodule update --init --recursive

libs:

plugins: libs
	$(MAKE) all -C plugins/Juno
	$(MAKE) all -C plugins/JunoAdvanced
	$(MAKE) all -C plugins/JunoAdvancedStereo

ifneq ($(CROSS_COMPILING),true)
gen: plugins dpf/utils/lv2_ttl_generator
	@$(CURDIR)/dpf/utils/generate-ttl.sh
ifeq ($(MACOS),true)
	@$(CURDIR)/dpf/utils/generate-vst-bundles.sh
endif

dpf/utils/lv2_ttl_generator:
	$(MAKE) -C dpf/utils/lv2-ttl-generator
else
gen: plugins dpf/utils/lv2_ttl_generator.exe
	@$(CURDIR)/dpf/utils/generate-ttl.sh

dpf/utils/lv2_ttl_generator.exe:
	$(MAKE) -C dpf/utils/lv2-ttl-generator WINDOWS=true
endif

# --------------------------------------------------------------

clean:
	$(MAKE) clean -C dpf/utils/lv2-ttl-generator
	$(MAKE) clean -C plugins/Juno
	$(MAKE) clean -C plugins/JunoAdvanced
	$(MAKE) clean -C plugins/JunoAdvancedStereo
	rm -rf bin build

install: all
	$(MAKE) install -C plugins/Juno
	$(MAKE) install -C plugins/JunoAdvanced
	$(MAKE) install -C plugins/JunoAdvancedStereo

install-user: all
	$(MAKE) install-user -C plugins/Juno
	$(MAKE) install-user -C plugins/JunoAdvanced
	$(MAKE) install-user -C plugins/JunoAdvancedStereo

# --------------------------------------------------------------

.PHONY: all clean install install-user submodule libs plugins gen

# --------------------------------------------------------------

dsp:
	faust -cn faustChorusImpl -scn faustObject -o sources/chorus.dsp.cxx sources/chorus.dsp
	faust -cn faustChorusAdvancedImpl -scn faustObject -o sources/chorus_advanced.dsp.cxx sources/chorus_advanced.dsp
	faust -cn faustChorusAdvancedStereoImpl -scn faustObject -o sources/chorus_advanced_stereo.dsp.cxx sources/chorus_advanced_stereo.dsp

.PHONY: dsp
