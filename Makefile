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

libs: artwork
	$(MAKE) -C dpf/dgl ../build/libdgl-opengl.a

plugins: libs
	$(MAKE) all -C plugins/Hera
	$(MAKE) all -C plugins/HeraAdvanced
	$(MAKE) all -C plugins/HeraAdvancedStereo

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

dsp:
	faust -cn faustChorusImpl -scn faustObject -o sources/chorus.dsp.cxx sources/chorus.dsp
	faust -cn faustChorusAdvancedImpl -scn faustObject -o sources/chorus_advanced.dsp.cxx sources/chorus_advanced.dsp
	faust -cn faustChorusAdvancedStereoImpl -scn faustObject -o sources/chorus_advanced_stereo.dsp.cxx sources/chorus_advanced_stereo.dsp

# --------------------------------------------------------------

artwork:
	$(MAKE) artwork -C plugins/Hera

# --------------------------------------------------------------

clean:
	$(MAKE) clean -C dpf/dgl
	$(MAKE) clean -C dpf/utils/lv2-ttl-generator
	$(MAKE) clean -C plugins/Hera
	$(MAKE) clean -C plugins/HeraAdvanced
	$(MAKE) clean -C plugins/HeraAdvancedStereo
	rm -rf bin build

dist-clean: clean
	$(MAKE) dist-clean -C plugins/Hera

install: all
	$(MAKE) install -C plugins/Hera
	$(MAKE) install -C plugins/HeraAdvanced
	$(MAKE) install -C plugins/HeraAdvancedStereo

install-user: all
	$(MAKE) install-user -C plugins/Hera
	$(MAKE) install-user -C plugins/HeraAdvanced
	$(MAKE) install-user -C plugins/HeraAdvancedStereo

# --------------------------------------------------------------

.PHONY: all artwork clean dist-clean dsp install install-user submodule libs plugins gen
