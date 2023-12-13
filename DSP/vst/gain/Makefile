#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = pix_gain

# --------------------------------------------------------------
# Files to build

FILES_DSP = \
	main.cpp

# --------------------------------------------------------------
# Do some magic

include /home/arjun/Documents/DPF/Makefile.plugins.mk

# --------------------------------------------------------------
# Enable all possible plugin types

TARGETS += ladspa
TARGETS += lv2_sep
TARGETS += vst2
TARGETS += vst3
TARGETS += clap

all: $(TARGETS)

# --------------------------------------------------------------
