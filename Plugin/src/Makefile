#
#
# (C) Yuri Ingultsov (yuri@softlab.in.ua) 2014
#
#
#
# Builds 32bit & 64bit vrsions of plugin for linux. 
# 
# NOTE: 
#     Before compiling make sure the latest SDK unpacked to ./src/sdk/SDK/*
#
# usage:
#    make linux           - builds both 32 & 64 bit plugins
#    make linux32         - 32 bit only
#    make linux64         - 64 bit only
#
# output:
# build            <- .o .d (in dependence of OS/arch)
#   $(os)
#       64
#       32
	
# inst            
#   $(PLUGIN)
#       64        <- lin.xpl
#       32        <- lin.xpl
#
# 
# License: GNU GPL v2

# 
# the plugin name
#
PLUGIN=an2plugin.xpl

#
#
#
inst_base = inst
build_base = build
src_base = .

#
#
#
INCLUDES = -Isdk/SDK/CHeaders/XPLM
DEFINES = -DXPLM200=1 -DAPL=0 -DIBM=0 -DLIN=1

#OS from environemnt
OS := $(OS)

#
#
CXXFLAGS:=$(CXXFLAGS) $(INCLUDES) $(DEFINES) -fPIC -fvisibility=hidden -Wall 
CFLAGS:=$(CFLAGS) $(INCLUDES) $(DEFINES) -fPIC -fvisibility=hidden -Wall
LFLAGS:=$(LFLAGS)
LIBS:=$(LIBS)

#
#
#
CC=gcc
CXX=g++
LINK=gcc


#
#
source_dirs  = ./
source_files_cpp = ./an2pluginLin.cpp ./EngineModel.cpp ./FlyWheelModel.cpp ./GeneralModel.cpp ./GyroModel.cpp ./XpData.cpp

#
# this make file will autogenerate include dependences... and store it as .d files along with .o's 
#
dep_files = $(wildcard $(addsuffix /*.d, $(source_dirs)))



#
#
build := $(build_base)/$(OS)
inst := $(inst_base)/$(PLUGIN)

#
# build
#	$(os)
#		64
#		32
#
# build = ./build/$(os)/64/*
# build = ./build/$(os)/32/*
#
object_files_32 = $(patsubst %.cpp, $(build)/32/%.o, $(source_files_cpp))
object_files_64 = $(patsubst %.cpp, $(build)/64/%.o, $(source_files_cpp))


.PHONY: clean linux
.SUFFIXES:


#
#
#
#
linux: export CXXFLAGS=-g -O0
linux: export OS=lin
linux: 
	$(MAKE) $(PLUGIN)

linux32: export CXXFLAGS=-g -O0
linux32: export OS=lin
linux32: 
	$(MAKE) $(PLUGIN)32

linux64: export CXXFLAGS=-g -O0
linux64: export OS=lin
linux64: 
	$(MAKE) $(PLUGIN)64


t:
	@echo "-$(build)-"
	@echo "-$(inst)-"
	@echo "-$(source_files_cpp)-"
	@echo "-$(dep_files)-"
	@echo "-$(object_files_32)-"
	@echo "-$(object_files_64)-"

#
#
# ./inst/$(plugin)/32/lin.xpl
# ./inst/$(plugin)/64/lin.xpl
#
$(PLUGIN)32: $(inst)/32/$(OS).xpl
$(PLUGIN)64: $(inst)/64/$(OS).xpl
$(PLUGIN): $(PLUGIN)64 $(PLUGIN)32


#
#
#
#
#$(LINK) $^ -o $@ $(LFLAGS) $(LIBS)
#
$(inst)/64/$(OS).xpl: $(object_files_64) exports.txt
	@echo Linking $@
	mkdir -p $(dir $@)
	$(LINK) -m64 -static-libgcc -shared -Wl,--version-script=exports.txt -o $@ $(object_files_64) $(LIBS)

$(inst)/32/$(OS).xpl: $(object_files_32) exports.txt
	@echo Linking $@
	mkdir -p $(dir $@)
	$(LINK) -m32 -static-libgcc -shared -Wl,--version-script=exports.txt -o $@ $(object_files_32) $(LIBS)

#
# compile
#
$(build)/64/%.o: ./%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -m64 -c -o $@ -MD -MT $@ $<

$(build)/64/%.o: ./%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -m64 -o $@ -MD -MT $@ $<

$(build)/32/%.o: ./%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -m32 -o $@ -MD -MT $@ $<

$(build)/32/%.o: ./%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -m32 -o $@ -MD -MT $@ $<

#
# dependences
#
include $(patsubst ./%, $(build)/64/%, $(dep_files))
include $(patsubst ./%, $(build)/32/%, $(dep_files))

clean:
	rm -rf $(build_base)/*
	rm -rf $(inst_base)/*

