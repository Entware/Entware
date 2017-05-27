#
# Copyright (C) 2006-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# Main makefile for the host tools
#
# Entware note: some tools (image and kernel related) that we do not need are removed
#               other tools go 
curdir:=tools

# subdirectories to descend into
tools-y :=

ifeq ($(CONFIG_EXTERNAL_TOOLCHAIN),)
  BUILD_TOOLCHAIN := y
  ifdef CONFIG_GCC_USE_GRAPHITE
    BUILD_ISL = y
  endif
endif

tools-$(BUILD_TOOLCHAIN) += gmp mpfr mpc libelf expat
tools-y += m4 libtool autoconf automake flex bison pkg-config mklibs
tools-y += sstrip
tools-y += quilt
tools-y += mm-macros missing-macros cmake scons bc findutils gengetopt patchelf
tools-y += mtools
tools-y += lzma
tools-$(BUILD_ISL) += isl
tools-y += go-src
tools-y += go-bootstrap

# builddir dependencies
$(curdir)/bison/compile := $(curdir)/flex/compile
$(curdir)/flex/compile := $(curdir)/libtool/compile
$(curdir)/libtool/compile := $(curdir)/m4/compile $(curdir)/autoconf/compile $(curdir)/automake/compile $(curdir)/missing-macros/compile
$(curdir)/quilt/compile := $(curdir)/autoconf/compile $(curdir)/findutils/compile
$(curdir)/autoconf/compile := $(curdir)/m4/compile
$(curdir)/automake/compile := $(curdir)/m4/compile $(curdir)/autoconf/compile $(curdir)/pkg-config/compile $(curdir)/xz/compile
$(curdir)/gmp/compile := $(curdir)/libtool/compile
$(curdir)/mpc/compile := $(curdir)/mpfr/compile $(curdir)/gmp/compile
$(curdir)/mpfr/compile := $(curdir)/gmp/compile
$(curdir)/mklibs/compile := $(curdir)/libtool/compile
$(curdir)/mm-macros/compile := $(curdir)/libtool/compile
$(curdir)/missing-macros/compile := $(curdir)/autoconf/compile
$(curdir)/libelf/compile := $(curdir)/libtool/compile
$(curdir)/isl/compile := $(curdir)/gmp/compile
$(curdir)/bc/compile := $(curdir)/bison/compile
$(curdir)/findutils/compile := $(curdir)/bison/compile
$(curdir)/gengetopt/compile := $(curdir)/libtool/compile
$(curdir)/patchelf/compile := $(curdir)/libtool/compile
$(curdir)/go-src/compile := $(curdir)/go-bootstrap/compile

tools-y += coreutils

ifneq ($(CONFIG_CCACHE)$(CONFIG_SDK),)
$(foreach tool, $(filter-out xz patch,$(tools-y)), $(eval $(curdir)/$(tool)/compile += $(curdir)/ccache/compile))
tools-y += ccache
endif

# in case there is no patch tool on the host we need to make patch tool a
# dependency for tools which have patches directory
$(foreach tool, $(tools-y), $(if $(wildcard $(curdir)/$(tool)/patches),$(eval $(curdir)/$(tool)/compile += $(curdir)/patch/compile)))

$(foreach tool, $(filter-out xz,$(tools-y)), $(eval $(curdir)/$(tool)/compile += $(curdir)/xz/compile))

# make any tool depend on tar, xz and patch to ensure that archives can be unpacked and patched properly
tools-core := tar xz patch

$(foreach tool, $(tools-y), $(eval $(curdir)/$(tool)/compile += $(patsubst %,$(curdir)/%/compile,$(tools-core))))
tools-y += $(tools-core)

# make core tools depend on sed and flock
$(foreach tool, $(tools-core), $(eval $(curdir)/$(tool)/compile += $(curdir)/sed/compile))

$(curdir)/sed/compile := $(curdir)/flock/compile
tools-y += flock sed

$(curdir)/autoremove := 1
$(curdir)/builddirs := $(tools-y) $(tools-dep) $(tools-)
$(curdir)/builddirs-default := $(tools-y)

ifdef CHECK_ALL
$(curdir)/builddirs-check:=$($(curdir)/builddirs)
$(curdir)/builddirs-download:=$($(curdir)/builddirs)
endif

ifndef DUMP_TARGET_DB
define PrepareStaging
	@for dir in $(1); do ( \
		$(if $(QUIET),,set -x;) \
		mkdir -p "$$dir"; \
		cd "$$dir"; \
		mkdir -p bin lib include stamp; \
	); done
endef

# preparatory work
$(STAGING_DIR)/.prepared: $(TMP_DIR)/.build
	$(call PrepareStaging,$(STAGING_DIR))
	mkdir -p $(BUILD_DIR)/stamp
	touch $@

$(STAGING_DIR_HOST)/.prepared: $(TMP_DIR)/.build
	$(call PrepareStaging,$(STAGING_DIR_HOST))
	mkdir -p $(BUILD_DIR_HOST)/stamp $(STAGING_DIR_HOST)/include/sys
	$(INSTALL_DATA) $(TOPDIR)/tools/include/*.h $(STAGING_DIR_HOST)/include/
	$(INSTALL_DATA) $(TOPDIR)/tools/include/sys/*.h $(STAGING_DIR_HOST)/include/sys/
	ln -sf lib $(STAGING_DIR_HOST)/lib64
	touch $@

endif

$(curdir)//prepare = $(STAGING_DIR)/.prepared $(STAGING_DIR_HOST)/.prepared
$(curdir)//compile = $(STAGING_DIR)/.prepared $(STAGING_DIR_HOST)/.prepared

# prerequisites for the individual targets
$(curdir)/ := .config prereq

$(curdir)/install: $(curdir)/compile

tools_enabled = $(foreach tool,$(sort $(tools-y) $(tools-)),$(if $(filter $(tool),$(tools-y)),y,n))
$(eval $(call stampfile,$(curdir),tools,compile,,_$(subst $(space),,$(tools_enabled))))
$(eval $(call stampfile,$(curdir),tools,check,$(TMP_DIR)/.build))
$(eval $(call subdir,$(curdir)))
