cmd_arch/arm/mach-nxp4330/prototype/module/nx_i2c.o := arm-eabi-gcc -Wp,-MD,arch/arm/mach-nxp4330/prototype/module/.nx_i2c.o.d  -nostdinc -isystem /home/swpark/ws/jb-mr1.1-test/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/../lib/gcc/arm-eabi/4.6.x-google/include -I/home/swpark/ws/jb-mr1.1-test/kernel/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include /home/swpark/ws/jb-mr1.1-test/kernel/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-nxp4330/include -Iarch/arm/plat-nxp4330/include -I/home/swpark/ws/jb-mr1.1-test/kernel/arch/arm/plat-nxp4330/common -I/home/swpark/ws/jb-mr1.1-test/kernel/arch/arm/plat-nxp4330/lynx/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -O2 -marm -fno-dwarf2-cfi-asm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -mabi=aapcs-linux -mno-thumb-interwork -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -I/home/swpark/ws/jb-mr1.1-test/kernel/arch/arm/mach-nxp4330/prototype/base -I/home/swpark/ws/jb-mr1.1-test/kernel/arch/arm/mach-nxp4330/prototype/module -I/home/swpark/ws/jb-mr1.1-test/kernel/arch/arm/mach-nxp4330/prototype/module -D__LINUX__ -D__PRINTK__ -DNX_RELEASE -mtune=cortex-a9 -mfpu=vfp -mfloat-abi=softfp -I/home/swpark/ws/jb-mr1.1-test/kernel/arch/arm/plat-nxp4330/common -I/home/swpark/ws/jb-mr1.1-test/kernel/arch/arm/plat-nxp4330/lynx/include -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -I/home/swpark/ws/jb-mr1.1-test/kernel/prototype/base -I/home/swpark/ws/jb-mr1.1-test/kernel/prototype/module -I/home/swpark/ws/jb-mr1.1-test/kernel/prototype/module -D__LINUX__ -D__PRINTK__ -DNX_RELEASE -mtune=cortex-a9 -mfpu=vfp -mfloat-abi=softfp    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(nx_i2c)"  -D"KBUILD_MODNAME=KBUILD_STR(nx_i2c)" -c -o arch/arm/mach-nxp4330/prototype/module/nx_i2c.o arch/arm/mach-nxp4330/prototype/module/nx_i2c.c

source_arch/arm/mach-nxp4330/prototype/module/nx_i2c.o := arch/arm/mach-nxp4330/prototype/module/nx_i2c.c

deps_arch/arm/mach-nxp4330/prototype/module/nx_i2c.o := \
  /home/swpark/ws/jb-mr1.1-test/kernel/arch/arm/mach-nxp4330/prototype/base/nx_chip.h \
  arch/arm/mach-nxp4330/prototype/module/nx_i2c.h \
  arch/arm/mach-nxp4330/prototype/module/../base/nx_prototype.h \
  arch/arm/mach-nxp4330/prototype/module/../base/nx_type.h \
  arch/arm/mach-nxp4330/prototype/module/../base/nx_debug.h \
  arch/arm/mach-nxp4330/prototype/module/../base/nx_chip.h \
  arch/arm/mach-nxp4330/prototype/module/../base/nx_clockcontrol.h \
  arch/arm/mach-nxp4330/prototype/module/../base/nx_bit_accessor.h \
  /home/swpark/ws/jb-mr1.1-test/kernel/arch/arm/mach-nxp4330/prototype/base/nx_type.h \

arch/arm/mach-nxp4330/prototype/module/nx_i2c.o: $(deps_arch/arm/mach-nxp4330/prototype/module/nx_i2c.o)

$(deps_arch/arm/mach-nxp4330/prototype/module/nx_i2c.o):
