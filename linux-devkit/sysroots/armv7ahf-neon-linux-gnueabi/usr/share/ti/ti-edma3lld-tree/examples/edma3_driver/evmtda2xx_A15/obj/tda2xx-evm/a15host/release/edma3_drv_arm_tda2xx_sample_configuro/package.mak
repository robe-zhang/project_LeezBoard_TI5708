#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#

unexport MAKEFILE_LIST
MK_NOGENDEPS := $(filter clean,$(MAKECMDGOALS))
override PKGDIR = edma3_drv_arm_tda2xx_sample_configuro
XDCINCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(XPKGPATH))))
XDCCFGDIR = package/cfg/

#
# The following dependencies ensure package.mak is rebuilt
# in the event that some included BOM script changes.
#
ifneq (clean,$(MAKECMDGOALS))
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/utils.js:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/utils.js
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/xdc.tci:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/xdc.tci
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/template.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/template.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/om2.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/om2.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/xmlgen.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/xmlgen.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/xmlgen2.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/xmlgen2.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/Warnings.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/Warnings.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/IPackage.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/IPackage.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/package.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/package.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/services/global/Clock.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/services/global/Clock.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/services/global/Trace.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/services/global/Trace.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/bld.js:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/bld.js
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/BuildEnvironment.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/BuildEnvironment.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/PackageContents.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/PackageContents.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/_gen.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/_gen.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/Library.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/Library.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/Executable.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/Executable.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/Repository.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/Repository.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/Configuration.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/Configuration.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/Script.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/Script.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/Manifest.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/Manifest.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/Utils.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/Utils.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/ITarget.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/ITarget.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/ITarget2.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/ITarget2.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/ITarget3.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/ITarget3.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/ITargetFilter.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/ITargetFilter.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/package.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/bld/package.xs
package.mak: config.bld
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/work/am57xx_evm-linux-gnueabi/edma3-lld-rtos/2.12.05.30C-r0.1/git/packages/config.bld:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/work/am57xx_evm-linux-gnueabi/edma3-lld-rtos/2.12.05.30C-r0.1/git/packages/config.bld
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/ti/targets/ITarget.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/ti/targets/ITarget.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/ti/targets/C28_large.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/ti/targets/C28_large.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/ti/targets/C28_float.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/ti/targets/C28_float.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/ti/targets/package.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/ti/targets/package.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/ti/targets/elf/ITarget.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/ti/targets/elf/ITarget.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/ti/targets/elf/C28_float.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/ti/targets/elf/C28_float.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/ti/targets/elf/package.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/ti/targets/elf/package.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/ti/targets/arm/elf/IArm.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/ti/targets/arm/elf/IArm.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/ti/targets/arm/elf/package.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/ti/targets/arm/elf/package.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/ITarget.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/ITarget.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/_utils.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/_utils.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/Linux86.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/Linux86.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/Mingw.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/Mingw.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/package.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/package.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/ITarget.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/ITarget.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/GCArmv6.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/GCArmv6.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/GCArmv7A.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/GCArmv7A.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/IM.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/IM.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/M3.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/M3.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/M4.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/M4.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/M4F.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/M4F.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/A8F.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/A8F.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/A9F.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/A9F.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/A15F.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/A15F.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/A53F.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/A53F.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/package.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/package.xs
package.mak: package.bld
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/tools/configuro/template/compiler.opt.xdt:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/tools/configuro/template/compiler.opt.xdt
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/services/io/File.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/services/io/File.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/services/io/package.xs:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/services/io/package.xs
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/tools/configuro/template/compiler.defs.xdt:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/tools/configuro/template/compiler.defs.xdt
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/tools/configuro/template/custom.mak.exe.xdt:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/tools/configuro/template/custom.mak.exe.xdt
/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/tools/configuro/template/package.xs.xdt:
package.mak: /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/ti-xdctools-tree/packages/xdc/tools/configuro/template/package.xs.xdt
endif

gnu.targets.arm.A15F.rootDir ?= /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux/usr/share/ti/gcc-arm-none-eabi
gnu.targets.arm.packageBase ?= /oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm/
.PRECIOUS: $(XDCCFGDIR)/%.oa15fg
.PHONY: all,a15fg .dlls,a15fg .executables,a15fg test,a15fg
all,a15fg: .executables,a15fg
.executables,a15fg: .libraries,a15fg
.executables,a15fg: .dlls,a15fg
.dlls,a15fg: .libraries,a15fg
.libraries,a15fg: .interfaces
	@$(RM) $@
	@$(TOUCH) "$@"

.help::
	@$(ECHO) xdc test,a15fg
	@$(ECHO) xdc .executables,a15fg
	@$(ECHO) xdc .libraries,a15fg
	@$(ECHO) xdc .dlls,a15fg


all: .executables 
.executables: .libraries .dlls
.libraries: .interfaces

PKGCFGS := $(wildcard package.xs) package/build.cfg
.interfaces: package/package.xdc.inc package/package.defs.h package.xdc $(PKGCFGS)

-include package/package.xdc.dep
package/%.xdc.inc package/%_edma3_drv_arm_tda2xx_sample_configuro.c package/%.defs.h: %.xdc $(PKGCFGS)
	@$(MSG) generating interfaces for package edma3_drv_arm_tda2xx_sample_configuro" (because $@ is older than $(firstword $?))" ...
	$(XSRUN) -f xdc/services/intern/cmd/build.xs $(MK_IDLOPTS) -m package/package.xdc.dep -i package/package.xdc.inc package.xdc

.dlls,a15fg .dlls: edma3_drv_bios6_tda2xx_a15_st_sample.pa15fg

-include package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.mak
-include package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.cfg.mak
ifeq (,$(MK_NOGENDEPS))
-include package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.dep
endif
edma3_drv_bios6_tda2xx_a15_st_sample.pa15fg: package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.xdl
	@


ifeq (,$(wildcard .libraries,a15fg))
edma3_drv_bios6_tda2xx_a15_st_sample.pa15fg package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.c: .libraries,a15fg
endif

package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.c package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.h package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.xdl: override _PROG_NAME := edma3_drv_bios6_tda2xx_a15_st_sample.xa15fg
package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.c: package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.cfg
package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.xdc.inc: package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.xdl
package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.xdl package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.c: .interfaces

clean:: clean,a15fg
	-$(RM) package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.cfg
	-$(RM) package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.dep
	-$(RM) package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.c
	-$(RM) package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.xdc.inc

clean,a15fg::
	-$(RM) edma3_drv_bios6_tda2xx_a15_st_sample.pa15fg
.executables,a15fg .executables: edma3_drv_bios6_tda2xx_a15_st_sample.xa15fg

edma3_drv_bios6_tda2xx_a15_st_sample.xa15fg: |edma3_drv_bios6_tda2xx_a15_st_sample.pa15fg

-include package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample.xa15fg.mak
edma3_drv_bios6_tda2xx_a15_st_sample.xa15fg: package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.oa15fg 
	$(RM) $@
	@$(MSG) lnka15fg $@ ...
	$(RM) $(XDCCFGDIR)$@.map
	$(gnu.targets.arm.A15F.rootDir)/bin/arm-none-eabi-gcc -mfloat-abi=hard -nostartfiles -Wl,-static -Wl,--gc-sections    -L/oe/bld/build-CORTEX_1/arago-tmp-external-linaro-toolchain/sysroots/am57xx-evm/usr/share/ti/ti-sysbios-tree/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/lib/hard  -o $@ package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.oa15fg -Wl,-T,package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.xdl   -Wl,--start-group -lgcc -lc -lm -Wl,--end-group --specs=nano.specs -Wl,-Map=$(XDCCFGDIR)/$@.map -Wl,--start-group -lnosys -Wl,--end-group
	
edma3_drv_bios6_tda2xx_a15_st_sample.xa15fg: export LD_LIBRARY_PATH=

edma3_drv_bios6_tda2xx_a15_st_sample.test test,a15fg test: edma3_drv_bios6_tda2xx_a15_st_sample.xa15fg.test

edma3_drv_bios6_tda2xx_a15_st_sample.xa15fg.test:: edma3_drv_bios6_tda2xx_a15_st_sample.xa15fg
ifeq (,$(_TESTLEVEL))
	@$(MAKE) -R -r --no-print-directory -f $(XDCROOT)/packages/xdc/bld/xdc.mak _TESTLEVEL=1 edma3_drv_bios6_tda2xx_a15_st_sample.xa15fg.test
else
	@$(MSG) running $<  ...
	$(call EXEC.edma3_drv_bios6_tda2xx_a15_st_sample.xa15fg, ) 
endif

clean,a15fg::
	-$(RM) $(wildcard .tmp,edma3_drv_bios6_tda2xx_a15_st_sample.xa15fg,*)


clean:: clean,a15fg

clean,a15fg::
	-$(RM) edma3_drv_bios6_tda2xx_a15_st_sample.xa15fg
%,copy:
	@$(if $<,,$(MSG) don\'t know how to build $*; exit 1)
	@$(MSG) cp $< $@
	$(RM) $@
	$(CP) $< $@
edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.oa15fg,copy : package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.oa15fg
edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.sa15fg,copy : package/cfg/edma3_drv_bios6_tda2xx_a15_st_sample_pa15fg.sa15fg

$(XDCCFGDIR)%.c $(XDCCFGDIR)%.h $(XDCCFGDIR)%.xdl: $(XDCCFGDIR)%.cfg $(XDCROOT)/packages/xdc/cfg/Main.xs | .interfaces
	@$(MSG) "configuring $(_PROG_NAME) from $< ..."
	$(CONFIG) $(_PROG_XSOPTS) xdc.cfg $(_PROG_NAME) $(XDCCFGDIR)$*.cfg $(XDCCFGDIR)$*

.PHONY: release,edma3_drv_arm_tda2xx_sample_configuro
ifeq (,$(MK_NOGENDEPS))
-include package/rel/edma3_drv_arm_tda2xx_sample_configuro.tar.dep
endif
package/rel/edma3_drv_arm_tda2xx_sample_configuro/edma3_drv_arm_tda2xx_sample_configuro/package/package.rel.xml: package/package.bld.xml
package/rel/edma3_drv_arm_tda2xx_sample_configuro/edma3_drv_arm_tda2xx_sample_configuro/package/package.rel.xml: package/build.cfg
package/rel/edma3_drv_arm_tda2xx_sample_configuro/edma3_drv_arm_tda2xx_sample_configuro/package/package.rel.xml: package/package.xdc.inc
package/rel/edma3_drv_arm_tda2xx_sample_configuro/edma3_drv_arm_tda2xx_sample_configuro/package/package.rel.xml: .force
	@$(MSG) generating external release references $@ ...
	$(XS) $(JSENV) -f $(XDCROOT)/packages/xdc/bld/rel.js $(MK_RELOPTS) . $@

edma3_drv_arm_tda2xx_sample_configuro.tar: package/rel/edma3_drv_arm_tda2xx_sample_configuro.xdc.inc package/rel/edma3_drv_arm_tda2xx_sample_configuro/edma3_drv_arm_tda2xx_sample_configuro/package/package.rel.xml
	@$(MSG) making release file $@ "(because of $(firstword $?))" ...
	-$(RM) $@
	$(call MKRELTAR,package/rel/edma3_drv_arm_tda2xx_sample_configuro.xdc.inc,package/rel/edma3_drv_arm_tda2xx_sample_configuro.tar.dep)


release release,edma3_drv_arm_tda2xx_sample_configuro: all edma3_drv_arm_tda2xx_sample_configuro.tar
clean:: .clean
	-$(RM) edma3_drv_arm_tda2xx_sample_configuro.tar
	-$(RM) package/rel/edma3_drv_arm_tda2xx_sample_configuro.xdc.inc
	-$(RM) package/rel/edma3_drv_arm_tda2xx_sample_configuro.tar.dep

clean:: .clean
	-$(RM) .libraries $(wildcard .libraries,*)
clean:: 
	-$(RM) .dlls $(wildcard .dlls,*)
#
# The following clean rule removes user specified
# generated files or directories.
#

ifneq (clean,$(MAKECMDGOALS))
ifeq (,$(wildcard package))
    $(shell $(MKDIR) package)
endif
ifeq (,$(wildcard package/cfg))
    $(shell $(MKDIR) package/cfg)
endif
ifeq (,$(wildcard package/lib))
    $(shell $(MKDIR) package/lib)
endif
ifeq (,$(wildcard package/rel))
    $(shell $(MKDIR) package/rel)
endif
ifeq (,$(wildcard package/internal))
    $(shell $(MKDIR) package/internal)
endif
endif
clean::
	-$(RMDIR) package

include custom.mak