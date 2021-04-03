TARGET	:= target
#TARGET	:= native
#TARGET	:= android

ifeq ($(TARGET),target)
CC		:= arm-starfishmllib32-linux-gnueabi-gcc
CFLAGS	:= --sysroot=$(shell echo $$SYSROOT)
else ifeq ($(TARGET), android)
CC		:= clang
ANDROID_ROOT	:= /system
ANDROID_VENDOR_PATH	:= ${ANDROID_ROOT}/vendor/lib64
LDFLAGS	+= -L${ANDROID_VENDOR_PATH} -L${ANDROID_VENDOR_PATH}/egl
endif


CC		?= gcc
LDFLAGS	+=
LIBS	?= 
CFLAGS	+= -o2
SOURCE	:= getCpuUtil.c
SOURCES	:= $(patsubst %.c, %.c, $(SOURCE))
OBJS	:= $(SOURCES:%.c=%.o)

all: clean $(TARGET)

$(TARGET): $(OBJS)
	@echo $(OBJS)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) -o getCpuUtil


clean:
	@rm -f $(OBJS)
