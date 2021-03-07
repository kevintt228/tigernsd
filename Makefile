#
# Makefile -- one file to make them all, nsd(8)
#
# Copyright (c) 2001-2006, NLnet Labs. All rights reserved.
#
# See LICENSE for the license.
#

# Standard installation pathnames
SHELL = /bin/sh
srcdir = .
prefix	= /usr/local
exec_prefix = ${prefix}
sbindir	= ${exec_prefix}/sbin
mandir = ${datarootdir}/man
datarootdir = ${prefix}/share

# NSD specific pathnames
configdir = /etc/nsd
piddir = /var/run
dbdir = /var/db/nsd
pidfile = /var/run/nsd.pid
logfile = /var/log/nsd.log
dbfile = /var/db/nsd/nsd.db
xfrdir = /tmp
xfrdfile = /var/db/nsd/xfrd.state
zonelistfile = /var/db/nsd/zone.list
nsdconfigfile = /etc/nsd/nsd.conf
zonesdir = /etc/nsd
chrootdir= 
user = nsd

# override $U variable which is used by autotools for deansification (for
# K&R C compilers), but causes problems if $U is defined in the env).
U=

CC		= gcc
CPPFLAGS	= -I.
CFLAGS		= -g -I include/
LDFLAGS		= 
LIBS		= -lcrypto -levent -lrt 
SSL_LIBS	= -lssl
LIBOBJS		=  ${LIBOBJDIR}strlcat$U.o ${LIBOBJDIR}strlcpy$U.o ${LIBOBJDIR}b64_pton$U.o ${LIBOBJDIR}b64_ntop$U.o
INSTALL		= $(srcdir)/install-sh -c
INSTALL_PROGRAM	= $(INSTALL)
INSTALL_DATA	= $(INSTALL) -m 644

YACC		= byacc
LEX		= flex

COMPILE		= $(CC) $(CPPFLAGS) $(CFLAGS)
LINK		= $(CC) $(CFLAGS) $(LDFLAGS)
EDIT		= sed \
			-e 's,@prefix\@,$(prefix),g' \
			-e 's,@exec_prefix\@,$(exec_prefix),g' \
			-e 's,@sbindir\@,$(sbindir),g' \
			-e 's,@configdir\@,$(configdir),g' \
			-e 's,@zonesdir\@,$(zonesdir),g' \
			-e 's,@chrootdir\@,$(chrootdir),g' \
			-e 's,@pidfile\@,$(pidfile),g' \
			-e 's,@logfile\@,$(logfile),g' \
			-e 's,@dbfile\@,$(dbfile),g' \
			-e 's,@xfrdir\@,$(xfrdir),g' \
			-e 's,@xfrdfile\@,$(xfrdfile),g' \
			-e 's,@zonelistfile\@,$(zonelistfile),g' \
			-e 's,@nsdconfigfile\@,$(nsdconfigfile),g' \
			-e 's,@shell\@,$(SHELL),g' \
			-e 's,@user\@,$(user),g'

TARGETS=nsd nsd-checkconf nsd-checkzone nsd-control nsd.conf.sample nsd-control-setup.sh
MANUALS=nsd.8 nsd-checkconf.8 nsd-checkzone.8 nsd-control.8 nsd.conf.5

COMMON_OBJ=answer.o axfr.o buffer.o configlexer.o configparser.o dname.o dns.o edns.o iterated_hash.o lookup3.o namedb.o nsec3.o options.o packet.o query.o rbtree.o radtree.o rdata.o region-allocator.o rrl.o tsig.o tsig-openssl.o udb.o udbradtree.o udbzone.o util.o geo_radix_tree.o dnsx_hash.o geo_core.o
XFRD_OBJ=xfrd-disk.o xfrd-notify.o xfrd-tcp.o xfrd.o remote.o
NSD_OBJ=$(COMMON_OBJ) $(XFRD_OBJ) difffile.o ipc.o mini_event.o netio.o nsd.o server.o dbaccess.o dbcreate.o zlexer.o zonec.o zparser.o
ALL_OBJ=$(NSD_OBJ) nsd-checkconf.o nsd-checkzone.o nsd-control.o nsd-mem.o
NSD_CHECKCONF_OBJ=$(COMMON_OBJ) nsd-checkconf.o
NSD_CHECKZONE_OBJ=$(COMMON_OBJ) $(XFRD_OBJ) dbaccess.o dbcreate.o difffile.o ipc.o mini_event.o netio.o server.o zonec.o zparser.o zlexer.o nsd-checkzone.o
NSD_CONTROL_OBJ=$(COMMON_OBJ) nsd-control.o
CUTEST_OBJ=$(COMMON_OBJ) $(XFRD_OBJ) dbaccess.o dbcreate.o difffile.o ipc.o mini_event.o netio.o server.o zonec.o zparser.o zlexer.o cutest_dname.o cutest_dns.o cutest_iterated_hash.o cutest_run.o cutest_radtree.o cutest_rbtree.o cutest_namedb.o cutest_options.o cutest_region.o cutest_rrl.o cutest_udb.o cutest_udbrad.o cutest_util.o cutest.o qtest.o
NSD_MEM_OBJ=$(COMMON_OBJ) $(XFRD_OBJ) dbaccess.o dbcreate.o difffile.o ipc.o mini_event.o netio.o server.o zonec.o zparser.o zlexer.o nsd-mem.o
all:	$(TARGETS) $(MANUALS)

$(ALL_OBJ):
	$(COMPILE) -c $<

nsd-control-setup.sh:	$(srcdir)/nsd-control-setup.sh.in config.h
	rm -f nsd-control-setup.sh
	$(EDIT) $(srcdir)/nsd-control-setup.sh.in > nsd-control-setup.sh
	chmod +x nsd-control-setup.sh

nsd.conf.sample:	$(srcdir)/nsd.conf.sample.in config.h
	rm -f nsd.conf.sample
	$(EDIT) $(srcdir)/nsd.conf.sample.in | awk '/RRLconfig'xx'/ { while($$0 !~ /.*RRLend.*/) { getline; } getline; } {print} ' > nsd.conf.sample

nsd.conf.5:	$(srcdir)/nsd.conf.5.in config.h
	rm -f nsd.conf.5
	$(EDIT) $(srcdir)/nsd.conf.5.in | awk '/rrlstart'xx'/ { while($$0 !~ /.*rrlend.*/) { getline; } getline; } {print} ' > nsd.conf.5

nsd.8:	$(srcdir)/nsd.8.in config.h
	rm -f nsd.8
	$(EDIT) $(srcdir)/nsd.8.in > nsd.8

nsd-checkconf.8:	$(srcdir)/nsd-checkconf.8.in config.h
	rm -f nsd-checkconf.8
	$(EDIT) $(srcdir)/nsd-checkconf.8.in > nsd-checkconf.8

nsd-checkzone.8:	$(srcdir)/nsd-checkzone.8.in config.h
	rm -f nsd-checkzone.8
	$(EDIT) $(srcdir)/nsd-checkzone.8.in > nsd-checkzone.8

nsd-control.8:	$(srcdir)/nsd-control.8.in config.h
	rm -f nsd-control.8
	$(EDIT) $(srcdir)/nsd-control.8.in > nsd-control.8

install: all
	$(INSTALL) -d $(DESTDIR)$(sbindir)
	$(INSTALL) -d $(DESTDIR)$(configdir)
	$(INSTALL) -d $(DESTDIR)$(piddir)
	$(INSTALL) -d $(DESTDIR)$(xfrdir)
	$(INSTALL) -d $(DESTDIR)$(dbdir)
	$(INSTALL) -d $(DESTDIR)$(mandir)
	$(INSTALL) -d $(DESTDIR)$(mandir)/man8
	$(INSTALL) -d $(DESTDIR)$(mandir)/man5
	$(INSTALL) nsd $(DESTDIR)$(sbindir)/nsd
	$(INSTALL) nsd-control-setup.sh $(DESTDIR)$(sbindir)/nsd-control-setup
	$(INSTALL) nsd-checkconf $(DESTDIR)$(sbindir)/nsd-checkconf
	$(INSTALL) nsd-checkzone $(DESTDIR)$(sbindir)/nsd-checkzone
	$(INSTALL) nsd-control $(DESTDIR)$(sbindir)/nsd-control
	$(INSTALL_DATA) nsd.8 $(DESTDIR)$(mandir)/man8
	$(INSTALL_DATA) nsd-checkconf.8 $(DESTDIR)$(mandir)/man8/nsd-checkconf.8
	$(INSTALL_DATA) nsd-checkzone.8 $(DESTDIR)$(mandir)/man8/nsd-checkzone.8
	$(INSTALL_DATA) nsd-control.8 $(DESTDIR)$(mandir)/man8/nsd-control.8
	$(INSTALL_DATA) nsd.conf.5 $(DESTDIR)$(mandir)/man5/nsd.conf.5
	$(INSTALL_DATA) nsd.conf.sample $(DESTDIR)$(nsdconfigfile).sample

uninstall:
	@echo
	rm -f -- $(DESTDIR)$(sbindir)/nsd $(DESTDIR)$(sbindir)/nsd-control-setup $(DESTDIR)$(sbindir)/nsd-checkconf $(DESTDIR)$(sbindir)/nsd-checkzone $(DESTDIR)$(sbindir)/nsd-control
	rm -f -- $(DESTDIR)$(mandir)/man8/nsd.8 $(DESTDIR)$(mandir)/man5/nsd.conf.5
	rm -f -- $(DESTDIR)$(mandir)/man8/nsd-checkconf.8 $(DESTDIR)$(mandir)/man8/nsd-checkzone.8 $(DESTDIR)$(mandir)/man8/nsd-control.8
	rm -f -- $(DESTDIR)$(pidfile)
	@echo
	@echo "You still need to remove $(DESTDIR)$(configdir), $(DESTDIR)$(piddir), $(DESTDIR)$(dbfile) directory by hand."

test: 

nsd:	$(NSD_OBJ) $(LIBOBJS)
	$(LINK) -o $@ $(NSD_OBJ) $(LIBOBJS) $(SSL_LIBS) $(LIBS)

nsd-checkconf:	$(NSD_CHECKCONF_OBJ) $(LIBOBJS)
	$(LINK) -o $@ $(NSD_CHECKCONF_OBJ) $(LIBOBJS) $(LIBS)

nsd-checkzone:	$(NSD_CHECKZONE_OBJ) $(LIBOBJS)
	$(LINK) -o $@ $(NSD_CHECKZONE_OBJ) $(LIBOBJS) $(SSL_LIBS) $(LIBS)

nsd-control:	$(NSD_CONTROL_OBJ) $(LIBOBJS)
	$(LINK) -o $@ $(NSD_CONTROL_OBJ) $(LIBOBJS) $(SSL_LIBS) $(LIBS)

nsd-mem:	$(NSD_MEM_OBJ) $(LIBOBJS)
	$(LINK) -o $@ $(NSD_MEM_OBJ) $(LIBOBJS) $(SSL_LIBS) $(LIBS)

cutest:	$(CUTEST_OBJ) $(LIBOBJS)
	$(LINK) -o $@ $(CUTEST_OBJ) $(LIBOBJS) $(SSL_LIBS) $(LIBS)

udb-inspect:	udb-inspect.o $(COMMON_OBJ) $(LIBOBJS)
	$(LINK) -o $@ udb-inspect.o $(COMMON_OBJ) $(LIBOBJS) $(LIBS)

clean:
	rm -f *.o $(TARGETS) $(MANUALS) cutest udb-inspect nsd-mem

realclean: clean
	rm -f Makefile config.h config.log config.status
	rm -rf autom4te*
	rm -f zlexer.c zparser.h zparser.c zparser.stamp
	rm -f configlexer.c configparser.h configparser.c configparser.stamp

devclean: realclean
	rm -f config.h.in configure

basename.o:	$(srcdir)/compat/basename.c
	$(COMPILE) -c $(srcdir)/compat/basename.c

inet_pton.o:	$(srcdir)/compat/inet_pton.c
	$(COMPILE) -c $(srcdir)/compat/inet_pton.c

inet_ntop.o:	$(srcdir)/compat/inet_ntop.c
	$(COMPILE) -c $(srcdir)/compat/inet_ntop.c

inet_aton.o:	$(srcdir)/compat/inet_aton.c
	$(COMPILE) -c $(srcdir)/compat/inet_aton.c

b64_pton.o:	$(srcdir)/compat/b64_pton.c
	$(COMPILE) -c $(srcdir)/compat/b64_pton.c

b64_ntop.o:	$(srcdir)/compat/b64_ntop.c
	$(COMPILE) -c $(srcdir)/compat/b64_ntop.c

memcmp.o:	$(srcdir)/compat/memcmp.c
	$(COMPILE) -c $(srcdir)/compat/memcmp.c

memmove.o:	$(srcdir)/compat/memmove.c
	$(COMPILE) -c $(srcdir)/compat/memmove.c

snprintf.o:	$(srcdir)/compat/snprintf.c
	$(COMPILE) -c $(srcdir)/compat/snprintf.c

strlcat.o:	$(srcdir)/compat/strlcat.c
	$(COMPILE) -c $(srcdir)/compat/strlcat.c

strlcpy.o:	$(srcdir)/compat/strlcpy.c
	$(COMPILE) -c $(srcdir)/compat/strlcpy.c

strptime.o:	$(srcdir)/compat/strptime.c
	$(COMPILE) -c $(srcdir)/compat/strptime.c

vsnprintf.o:	$(srcdir)/compat/vsnprintf.c
	$(COMPILE) -c $(srcdir)/compat/vsnprintf.c

timegm.o:	$(srcdir)/compat/timegm.c
	$(COMPILE) -c $(srcdir)/compat/timegm.c

malloc.o:	$(srcdir)/compat/malloc.c
	$(COMPILE) -c $(srcdir)/compat/malloc.c

pselect.o:	$(srcdir)/compat/pselect.c
	$(COMPILE) -c $(srcdir)/compat/pselect.c

fake-rfc2553.o:	$(srcdir)/compat/fake-rfc2553.c
	$(COMPILE) -c $(srcdir)/compat/fake-rfc2553.c

cutest_dname.o:	$(srcdir)/tpkg/cutest/cutest_dname.c
	$(COMPILE) -c $(srcdir)/tpkg/cutest/cutest_dname.c

cutest_dns.o:	$(srcdir)/tpkg/cutest/cutest_dns.c
	$(COMPILE) -c $(srcdir)/tpkg/cutest/cutest_dns.c

cutest_iterated_hash.o:	$(srcdir)/tpkg/cutest/cutest_iterated_hash.c
	$(COMPILE) -c $(srcdir)/tpkg/cutest/cutest_iterated_hash.c

cutest_run.o:	$(srcdir)/tpkg/cutest/cutest_run.c
	$(COMPILE) -c $(srcdir)/tpkg/cutest/cutest_run.c

cutest_rbtree.o:	$(srcdir)/tpkg/cutest/cutest_rbtree.c
	$(COMPILE) -c $(srcdir)/tpkg/cutest/cutest_rbtree.c

cutest_radtree.o:	$(srcdir)/tpkg/cutest/cutest_radtree.c
	$(COMPILE) -c $(srcdir)/tpkg/cutest/cutest_radtree.c

cutest_namedb.o:	$(srcdir)/tpkg/cutest/cutest_namedb.c
	$(COMPILE) -c $(srcdir)/tpkg/cutest/cutest_namedb.c

cutest_options.o:	$(srcdir)/tpkg/cutest/cutest_options.c
	$(COMPILE) -c $(srcdir)/tpkg/cutest/cutest_options.c

cutest_region.o:	$(srcdir)/tpkg/cutest/cutest_region.c
	$(COMPILE) -c $(srcdir)/tpkg/cutest/cutest_region.c

cutest_rrl.o:	$(srcdir)/tpkg/cutest/cutest_rrl.c
	$(COMPILE) -c $(srcdir)/tpkg/cutest/cutest_rrl.c

cutest_udb.o:	$(srcdir)/tpkg/cutest/cutest_udb.c
	$(COMPILE) -c $(srcdir)/tpkg/cutest/cutest_udb.c

cutest_udbrad.o:	$(srcdir)/tpkg/cutest/cutest_udbrad.c
	$(COMPILE) -c $(srcdir)/tpkg/cutest/cutest_udbrad.c

cutest_util.o:	$(srcdir)/tpkg/cutest/cutest_util.c
	$(COMPILE) -c $(srcdir)/tpkg/cutest/cutest_util.c

cutest.o:	$(srcdir)/tpkg/cutest/cutest.c
	$(COMPILE) -c $(srcdir)/tpkg/cutest/cutest.c

qtest.o:	$(srcdir)/tpkg/cutest/qtest.c
	$(COMPILE) -c $(srcdir)/tpkg/cutest/qtest.c

udb-inspect.o:	$(srcdir)/tpkg/cutest/udb-inspect.c
	$(COMPILE) -c $(srcdir)/tpkg/cutest/udb-inspect.c

zlexer.c:	$(srcdir)/zlexer.lex
	if test "$(LEX)" != ":"; then rm -f $@ ;\
		echo '#include "config.h"' > $@ ;\
		$(LEX) -i -t $(srcdir)/zlexer.lex >> $@ ;\
	fi

zparser.c zparser.h: $(srcdir)/zparser.y
	$(YACC) -d -o zparser.c $(srcdir)/zparser.y

configlexer.c:	$(srcdir)/configlexer.lex
	if test "$(LEX)" != ":"; then rm -f $@ ;\
		echo '#include "configyyrename.h"' > $@ ;\
		$(LEX) -i -t $(srcdir)/configlexer.lex >> $@ ;\
	fi

configparser.c configparser.h:	$(srcdir)/configparser.y
	$(YACC) -d -o configparser.c $(srcdir)/configparser.y

# autoconf rules
config.h.in:	configure.ac
	autoheader

configure:	configure.ac
	autoconf

tags: 	
	ctags *.[ch]

# dependency generation
DEPEND_TMP=depend1073.tmp
DEPEND_TMP2=depend1074.tmp
DEPEND_TARGET=Makefile
DEPEND_TARGET2=Makefile.in
depend:
	(cd $(srcdir) ; $(CC) -MM $(CPPFLAGS) *.c compat/*.c tpkg/cutest/*.c) | \
		sed -e 's? *\([^ ]*\.[ch]\)? $$(srcdir)/\1?g' | \
		sed -e 's?$$(srcdir)/config.h?config.h?g' \
			-e 's?$$(srcdir)/configlexer.c?configlexer.c?g' \
			-e 's?$$(srcdir)/configparser.c?configparser.c?g' \
			-e 's?$$(srcdir)/configparser.h?configparser.h?g' \
			-e 's?$$(srcdir)/zlexer.c?zlexer.c?g' \
			-e 's?$$(srcdir)/zparser.c?zparser.c?g' \
			-e 's?$$(srcdir)/zparser.h?zparser.h?g' \
			> $(DEPEND_TMP)
	cp $(DEPEND_TARGET) $(DEPEND_TMP2)
	head -`egrep -n "# Dependencies" $(DEPEND_TARGET) | tail -1 | sed -e 's/:.*$$//'` $(DEPEND_TMP2) > $(DEPEND_TARGET)
	cat $(DEPEND_TMP) >> $(DEPEND_TARGET)
	@if diff $(DEPEND_TARGET) $(DEPEND_TMP2); then echo "	$(DEPEND_TARGET) unchanged"; else echo "	Updated $(DEPEND_TARGET))"; fi
	@if test -f $(DEPEND_TARGET2); then \
		cp $(DEPEND_TARGET2) $(DEPEND_TMP2); \
		head -`egrep -n "# Dependencies" $(DEPEND_TARGET2) | tail -1 | sed -e 's/:.*$$//'` $(DEPEND_TMP2) > $(DEPEND_TARGET2); \
		cat $(DEPEND_TMP) >> $(DEPEND_TARGET2); \
		if diff $(DEPEND_TARGET2) $(DEPEND_TMP2); then echo "	$(DEPEND_TARGET2) unchanged"; else echo "	Updated $(DEPEND_TARGET2))"; fi; \
	fi
	rm -f $(DEPEND_TMP) $(DEPEND_TMP2)

# Dependencies
answer.o: $(srcdir)/answer.c config.h $(srcdir)/answer.h $(srcdir)/dns.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/buffer.h \
 $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/radtree.h $(srcdir)/rbtree.h $(srcdir)/packet.h $(srcdir)/query.h $(srcdir)/nsd.h \
 $(srcdir)/edns.h $(srcdir)/tsig.h
axfr.o: $(srcdir)/axfr.c config.h $(srcdir)/axfr.h $(srcdir)/nsd.h $(srcdir)/dns.h $(srcdir)/edns.h $(srcdir)/buffer.h \
 $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/query.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/radtree.h $(srcdir)/rbtree.h \
 $(srcdir)/packet.h $(srcdir)/tsig.h $(srcdir)/options.h
buffer.o: $(srcdir)/buffer.c config.h $(srcdir)/buffer.h $(srcdir)/region-allocator.h $(srcdir)/util.h
configlexer.o: configlexer.c $(srcdir)/configyyrename.h config.h $(srcdir)/options.h \
 $(srcdir)/region-allocator.h $(srcdir)/rbtree.h configparser.h
configparser.o: configparser.c config.h $(srcdir)/options.h $(srcdir)/region-allocator.h \
 $(srcdir)/rbtree.h $(srcdir)/util.h $(srcdir)/dname.h $(srcdir)/buffer.h $(srcdir)/tsig.h $(srcdir)/rrl.h $(srcdir)/query.h $(srcdir)/namedb.h $(srcdir)/dns.h \
 $(srcdir)/radtree.h $(srcdir)/nsd.h $(srcdir)/edns.h $(srcdir)/packet.h $(srcdir)/configyyrename.h
dbaccess.o: $(srcdir)/dbaccess.c config.h $(srcdir)/dns.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/buffer.h \
 $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/radtree.h $(srcdir)/rbtree.h $(srcdir)/options.h $(srcdir)/rdata.h $(srcdir)/udb.h \
 $(srcdir)/udbradtree.h $(srcdir)/udbzone.h $(srcdir)/zonec.h $(srcdir)/nsec3.h $(srcdir)/difffile.h $(srcdir)/nsd.h $(srcdir)/edns.h
dbcreate.o: $(srcdir)/dbcreate.c config.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/buffer.h \
 $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/dns.h $(srcdir)/radtree.h $(srcdir)/rbtree.h $(srcdir)/udb.h $(srcdir)/udbradtree.h \
 $(srcdir)/udbzone.h $(srcdir)/options.h $(srcdir)/nsd.h $(srcdir)/edns.h
difffile.o: $(srcdir)/difffile.c config.h $(srcdir)/difffile.h $(srcdir)/rbtree.h $(srcdir)/region-allocator.h \
 $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/buffer.h $(srcdir)/util.h $(srcdir)/dns.h $(srcdir)/radtree.h $(srcdir)/options.h $(srcdir)/udb.h \
 $(srcdir)/xfrd-disk.h $(srcdir)/packet.h $(srcdir)/rdata.h $(srcdir)/udbzone.h $(srcdir)/udbradtree.h $(srcdir)/nsec3.h $(srcdir)/nsd.h $(srcdir)/edns.h \
 $(srcdir)/rrl.h $(srcdir)/query.h $(srcdir)/tsig.h
dname.o: $(srcdir)/dname.c config.h $(srcdir)/dns.h $(srcdir)/dname.h $(srcdir)/buffer.h $(srcdir)/region-allocator.h \
 $(srcdir)/util.h $(srcdir)/query.h $(srcdir)/namedb.h $(srcdir)/radtree.h $(srcdir)/rbtree.h $(srcdir)/nsd.h $(srcdir)/edns.h $(srcdir)/packet.h $(srcdir)/tsig.h
dns.o: $(srcdir)/dns.c config.h $(srcdir)/dns.h $(srcdir)/zonec.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/buffer.h \
 $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/radtree.h $(srcdir)/rbtree.h zparser.h
edns.o: $(srcdir)/edns.c config.h $(srcdir)/dns.h $(srcdir)/edns.h $(srcdir)/buffer.h $(srcdir)/region-allocator.h $(srcdir)/util.h
ipc.o: $(srcdir)/ipc.c config.h $(srcdir)/ipc.h $(srcdir)/netio.h $(srcdir)/region-allocator.h $(srcdir)/buffer.h $(srcdir)/util.h \
 $(srcdir)/xfrd-tcp.h $(srcdir)/xfrd.h $(srcdir)/rbtree.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/dns.h $(srcdir)/radtree.h $(srcdir)/options.h \
 $(srcdir)/tsig.h $(srcdir)/nsd.h $(srcdir)/edns.h $(srcdir)/xfrd-notify.h $(srcdir)/difffile.h $(srcdir)/udb.h
iterated_hash.o: $(srcdir)/iterated_hash.c config.h $(srcdir)/iterated_hash.h
lookup3.o: $(srcdir)/lookup3.c config.h $(srcdir)/lookup3.h
mini_event.o: $(srcdir)/mini_event.c config.h
namedb.o: $(srcdir)/namedb.c config.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/buffer.h $(srcdir)/region-allocator.h \
 $(srcdir)/util.h $(srcdir)/dns.h $(srcdir)/radtree.h $(srcdir)/rbtree.h $(srcdir)/nsec3.h
netio.o: $(srcdir)/netio.c config.h $(srcdir)/netio.h $(srcdir)/region-allocator.h $(srcdir)/util.h
nsd.o: $(srcdir)/nsd.c config.h $(srcdir)/nsd.h $(srcdir)/dns.h $(srcdir)/edns.h $(srcdir)/buffer.h $(srcdir)/region-allocator.h \
 $(srcdir)/util.h $(srcdir)/options.h $(srcdir)/rbtree.h $(srcdir)/tsig.h $(srcdir)/dname.h $(srcdir)/remote.h
nsd-checkconf.o: $(srcdir)/nsd-checkconf.c config.h $(srcdir)/tsig.h $(srcdir)/buffer.h \
 $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/dname.h $(srcdir)/options.h $(srcdir)/rbtree.h $(srcdir)/rrl.h $(srcdir)/query.h \
 $(srcdir)/namedb.h $(srcdir)/dns.h $(srcdir)/radtree.h $(srcdir)/nsd.h $(srcdir)/edns.h $(srcdir)/packet.h
nsd-checkzone.o: $(srcdir)/nsd-checkzone.c config.h $(srcdir)/nsd.h $(srcdir)/dns.h $(srcdir)/edns.h $(srcdir)/buffer.h \
 $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/options.h $(srcdir)/rbtree.h $(srcdir)/zonec.h $(srcdir)/namedb.h $(srcdir)/dname.h \
 $(srcdir)/radtree.h
nsd-control.o: $(srcdir)/nsd-control.c config.h $(srcdir)/util.h $(srcdir)/tsig.h $(srcdir)/buffer.h \
 $(srcdir)/region-allocator.h $(srcdir)/dname.h $(srcdir)/options.h $(srcdir)/rbtree.h
nsd-mem.o: $(srcdir)/nsd-mem.c config.h $(srcdir)/nsd.h $(srcdir)/dns.h $(srcdir)/edns.h $(srcdir)/buffer.h \
 $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/tsig.h $(srcdir)/dname.h $(srcdir)/options.h $(srcdir)/rbtree.h $(srcdir)/namedb.h \
 $(srcdir)/radtree.h $(srcdir)/udb.h $(srcdir)/udbzone.h $(srcdir)/udbradtree.h
nsec3.o: $(srcdir)/nsec3.c config.h $(srcdir)/nsec3.h $(srcdir)/iterated_hash.h $(srcdir)/namedb.h $(srcdir)/dname.h \
 $(srcdir)/buffer.h $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/dns.h $(srcdir)/radtree.h $(srcdir)/rbtree.h $(srcdir)/nsd.h $(srcdir)/edns.h \
 $(srcdir)/answer.h $(srcdir)/packet.h $(srcdir)/query.h $(srcdir)/tsig.h $(srcdir)/udbzone.h $(srcdir)/udb.h $(srcdir)/udbradtree.h $(srcdir)/options.h
options.o: $(srcdir)/options.c config.h $(srcdir)/options.h $(srcdir)/region-allocator.h $(srcdir)/rbtree.h \
 $(srcdir)/query.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/buffer.h $(srcdir)/util.h $(srcdir)/dns.h $(srcdir)/radtree.h $(srcdir)/nsd.h $(srcdir)/edns.h \
 $(srcdir)/packet.h $(srcdir)/tsig.h $(srcdir)/difffile.h $(srcdir)/udb.h $(srcdir)/rrl.h $(srcdir)/configyyrename.h configparser.h
packet.o: $(srcdir)/packet.c config.h $(srcdir)/packet.h $(srcdir)/dns.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/buffer.h \
 $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/radtree.h $(srcdir)/rbtree.h $(srcdir)/query.h $(srcdir)/nsd.h $(srcdir)/edns.h $(srcdir)/tsig.h \
 $(srcdir)/rdata.h
query.o: $(srcdir)/query.c config.h $(srcdir)/answer.h $(srcdir)/dns.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/buffer.h \
 $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/radtree.h $(srcdir)/rbtree.h $(srcdir)/packet.h $(srcdir)/query.h $(srcdir)/nsd.h \
 $(srcdir)/edns.h $(srcdir)/tsig.h $(srcdir)/axfr.h $(srcdir)/options.h $(srcdir)/nsec3.h
radtree.o: $(srcdir)/radtree.c config.h $(srcdir)/radtree.h $(srcdir)/util.h $(srcdir)/region-allocator.h
rbtree.o: $(srcdir)/rbtree.c config.h $(srcdir)/rbtree.h $(srcdir)/region-allocator.h
rdata.o: $(srcdir)/rdata.c config.h $(srcdir)/rdata.h $(srcdir)/dns.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/buffer.h \
 $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/radtree.h $(srcdir)/rbtree.h $(srcdir)/zonec.h
region-allocator.o: $(srcdir)/region-allocator.c config.h $(srcdir)/region-allocator.h $(srcdir)/util.h
remote.o: $(srcdir)/remote.c config.h $(srcdir)/remote.h $(srcdir)/util.h $(srcdir)/xfrd.h $(srcdir)/rbtree.h \
 $(srcdir)/region-allocator.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/buffer.h $(srcdir)/dns.h $(srcdir)/radtree.h $(srcdir)/options.h \
 $(srcdir)/tsig.h $(srcdir)/xfrd-notify.h $(srcdir)/xfrd-tcp.h $(srcdir)/nsd.h $(srcdir)/edns.h $(srcdir)/difffile.h $(srcdir)/udb.h $(srcdir)/ipc.h \
 $(srcdir)/netio.h
rrl.o: $(srcdir)/rrl.c config.h $(srcdir)/rrl.h $(srcdir)/query.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/buffer.h \
 $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/dns.h $(srcdir)/radtree.h $(srcdir)/rbtree.h $(srcdir)/nsd.h $(srcdir)/edns.h $(srcdir)/packet.h \
 $(srcdir)/tsig.h $(srcdir)/lookup3.h $(srcdir)/options.h
server.o: $(srcdir)/server.c config.h $(srcdir)/axfr.h $(srcdir)/nsd.h $(srcdir)/dns.h $(srcdir)/edns.h $(srcdir)/buffer.h \
 $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/query.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/radtree.h $(srcdir)/rbtree.h \
 $(srcdir)/packet.h $(srcdir)/tsig.h $(srcdir)/netio.h $(srcdir)/xfrd.h $(srcdir)/options.h $(srcdir)/xfrd-tcp.h $(srcdir)/xfrd-disk.h \
 $(srcdir)/difffile.h $(srcdir)/udb.h $(srcdir)/nsec3.h $(srcdir)/ipc.h $(srcdir)/remote.h $(srcdir)/lookup3.h $(srcdir)/rrl.h
tsig.o: $(srcdir)/tsig.c config.h $(srcdir)/tsig.h $(srcdir)/buffer.h $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/dname.h \
 $(srcdir)/tsig-openssl.h $(srcdir)/dns.h $(srcdir)/packet.h $(srcdir)/namedb.h $(srcdir)/radtree.h $(srcdir)/rbtree.h $(srcdir)/query.h $(srcdir)/nsd.h \
 $(srcdir)/edns.h
tsig-openssl.o: $(srcdir)/tsig-openssl.c config.h $(srcdir)/tsig-openssl.h $(srcdir)/region-allocator.h \
 $(srcdir)/tsig.h $(srcdir)/buffer.h $(srcdir)/util.h $(srcdir)/dname.h
udb.o: $(srcdir)/udb.c config.h $(srcdir)/udb.h $(srcdir)/lookup3.h $(srcdir)/util.h
udbradtree.o: $(srcdir)/udbradtree.c config.h $(srcdir)/udbradtree.h $(srcdir)/udb.h $(srcdir)/radtree.h
geo_radix_tree.o: $(srcdir)/geo_radix_tree.c config.h $(srcdir)/geo_radix_tree.h
dnsx_hash.o: $(srcdir)/lib/dnsx_hash.c config.h $(srcdir)/include/dnsx_hash.h
geo_core.o: $(srcdir)/geo_core.c $(srcdir)/geo_radix_tree.c config.h $(srcdir)/geo_radix_tree.h $(srcdir)/rrl.c $(srcdir)/rrl.h $(srcdir)/query.h
udbzone.o: $(srcdir)/udbzone.c config.h $(srcdir)/udbzone.h $(srcdir)/udb.h $(srcdir)/dns.h $(srcdir)/udbradtree.h $(srcdir)/util.h \
 $(srcdir)/iterated_hash.h $(srcdir)/dname.h $(srcdir)/buffer.h $(srcdir)/region-allocator.h $(srcdir)/difffile.h $(srcdir)/rbtree.h \
 $(srcdir)/namedb.h $(srcdir)/radtree.h $(srcdir)/options.h
util.o: $(srcdir)/util.c config.h $(srcdir)/util.h $(srcdir)/region-allocator.h $(srcdir)/dname.h $(srcdir)/buffer.h \
 $(srcdir)/namedb.h $(srcdir)/dns.h $(srcdir)/radtree.h $(srcdir)/rbtree.h $(srcdir)/rdata.h $(srcdir)/zonec.h
xfrd.o: $(srcdir)/xfrd.c config.h $(srcdir)/xfrd.h $(srcdir)/rbtree.h $(srcdir)/region-allocator.h $(srcdir)/namedb.h \
 $(srcdir)/dname.h $(srcdir)/buffer.h $(srcdir)/util.h $(srcdir)/dns.h $(srcdir)/radtree.h $(srcdir)/options.h $(srcdir)/tsig.h $(srcdir)/xfrd-tcp.h \
 $(srcdir)/xfrd-disk.h $(srcdir)/xfrd-notify.h $(srcdir)/netio.h $(srcdir)/nsd.h $(srcdir)/edns.h $(srcdir)/packet.h $(srcdir)/rdata.h \
 $(srcdir)/difffile.h $(srcdir)/udb.h $(srcdir)/ipc.h $(srcdir)/remote.h
xfrd-disk.o: $(srcdir)/xfrd-disk.c config.h $(srcdir)/xfrd-disk.h $(srcdir)/xfrd.h $(srcdir)/rbtree.h \
 $(srcdir)/region-allocator.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/buffer.h $(srcdir)/util.h $(srcdir)/dns.h $(srcdir)/radtree.h \
 $(srcdir)/options.h $(srcdir)/tsig.h $(srcdir)/nsd.h $(srcdir)/edns.h
xfrd-notify.o: $(srcdir)/xfrd-notify.c config.h $(srcdir)/xfrd-notify.h $(srcdir)/tsig.h $(srcdir)/buffer.h \
 $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/dname.h $(srcdir)/rbtree.h $(srcdir)/xfrd.h $(srcdir)/namedb.h $(srcdir)/dns.h \
 $(srcdir)/radtree.h $(srcdir)/options.h $(srcdir)/xfrd-tcp.h $(srcdir)/packet.h
xfrd-tcp.o: $(srcdir)/xfrd-tcp.c config.h $(srcdir)/xfrd-tcp.h $(srcdir)/xfrd.h $(srcdir)/rbtree.h \
 $(srcdir)/region-allocator.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/buffer.h $(srcdir)/util.h $(srcdir)/dns.h $(srcdir)/radtree.h \
 $(srcdir)/options.h $(srcdir)/tsig.h $(srcdir)/packet.h $(srcdir)/xfrd-disk.h
zlexer.o: zlexer.c config.h $(srcdir)/zonec.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/buffer.h \
 $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/dns.h $(srcdir)/radtree.h $(srcdir)/rbtree.h zparser.h
zonec.o: $(srcdir)/zonec.c config.h $(srcdir)/zonec.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/buffer.h \
 $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/dns.h $(srcdir)/radtree.h $(srcdir)/rbtree.h $(srcdir)/rdata.h zparser.h \
 $(srcdir)/options.h $(srcdir)/nsec3.h
zparser.o: zparser.c config.h $(srcdir)/dname.h $(srcdir)/buffer.h $(srcdir)/region-allocator.h $(srcdir)/util.h \
 $(srcdir)/namedb.h $(srcdir)/dns.h $(srcdir)/radtree.h $(srcdir)/rbtree.h $(srcdir)/zonec.h
b64_ntop.o: $(srcdir)/compat/b64_ntop.c config.h
b64_pton.o: $(srcdir)/compat/b64_pton.c config.h
basename.o: $(srcdir)/compat/basename.c
fake-rfc2553.o: $(srcdir)/compat/fake-rfc2553.c $(srcdir)/compat/fake-rfc2553.h config.h
inet_aton.o: $(srcdir)/compat/inet_aton.c config.h
inet_ntop.o: $(srcdir)/compat/inet_ntop.c config.h
inet_pton.o: $(srcdir)/compat/inet_pton.c config.h
malloc.o: $(srcdir)/compat/malloc.c
memcmp.o: $(srcdir)/compat/memcmp.c config.h
memmove.o: $(srcdir)/compat/memmove.c config.h
pselect.o: $(srcdir)/compat/pselect.c config.h
snprintf.o: $(srcdir)/compat/snprintf.c config.h
strlcat.o: $(srcdir)/compat/strlcat.c config.h
strlcpy.o: $(srcdir)/compat/strlcpy.c config.h
strptime.o: $(srcdir)/compat/strptime.c
cutest.o: $(srcdir)/tpkg/cutest/cutest.c config.h $(srcdir)/tpkg/cutest/cutest.h
cutest_dname.o: $(srcdir)/tpkg/cutest/cutest_dname.c config.h $(srcdir)/tpkg/cutest/cutest.h \
 $(srcdir)/region-allocator.h $(srcdir)/dname.h $(srcdir)/buffer.h $(srcdir)/region-allocator.h $(srcdir)/util.h
cutest_dns.o: $(srcdir)/tpkg/cutest/cutest_dns.c config.h $(srcdir)/tpkg/cutest/cutest.h \
 $(srcdir)/region-allocator.h $(srcdir)/dns.h
cutest_iterated_hash.o: $(srcdir)/tpkg/cutest/cutest_iterated_hash.c config.h \
 $(srcdir)/tpkg/cutest/cutest.h $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/iterated_hash.h $(srcdir)/dname.h \
 $(srcdir)/buffer.h $(srcdir)/region-allocator.h $(srcdir)/util.h
cutest_namedb.o: $(srcdir)/tpkg/cutest/cutest_namedb.c config.h \
 $(srcdir)/tpkg/cutest/cutest.h $(srcdir)/region-allocator.h $(srcdir)/options.h config.h \
 $(srcdir)/region-allocator.h $(srcdir)/rbtree.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/buffer.h $(srcdir)/util.h $(srcdir)/dns.h \
 $(srcdir)/radtree.h $(srcdir)/nsec3.h $(srcdir)/udb.h $(srcdir)/udbzone.h $(srcdir)/udb.h $(srcdir)/udbradtree.h $(srcdir)/difffile.h $(srcdir)/namedb.h \
 $(srcdir)/options.h $(srcdir)/zonec.h $(srcdir)/nsd.h $(srcdir)/edns.h
cutest_options.o: $(srcdir)/tpkg/cutest/cutest_options.c config.h \
 $(srcdir)/tpkg/cutest/cutest.h $(srcdir)/region-allocator.h $(srcdir)/options.h config.h \
 $(srcdir)/region-allocator.h $(srcdir)/rbtree.h $(srcdir)/util.h $(srcdir)/dname.h $(srcdir)/buffer.h $(srcdir)/util.h $(srcdir)/nsd.h $(srcdir)/dns.h \
 $(srcdir)/edns.h
cutest_radtree.o: $(srcdir)/tpkg/cutest/cutest_radtree.c config.h \
 $(srcdir)/tpkg/cutest/cutest.h $(srcdir)/radtree.h $(srcdir)/region-allocator.h $(srcdir)/util.h
cutest_rbtree.o: $(srcdir)/tpkg/cutest/cutest_rbtree.c config.h \
 $(srcdir)/tpkg/cutest/cutest.h $(srcdir)/region-allocator.h $(srcdir)/rbtree.h $(srcdir)/region-allocator.h
cutest_region.o: $(srcdir)/tpkg/cutest/cutest_region.c config.h \
 $(srcdir)/tpkg/cutest/cutest.h $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/rbtree.h \
 $(srcdir)/region-allocator.h
cutest_rrl.o: $(srcdir)/tpkg/cutest/cutest_rrl.c config.h $(srcdir)/tpkg/cutest/cutest.h \
 $(srcdir)/rrl.h $(srcdir)/query.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/buffer.h $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/dns.h \
 $(srcdir)/radtree.h $(srcdir)/rbtree.h $(srcdir)/nsd.h $(srcdir)/edns.h $(srcdir)/packet.h $(srcdir)/tsig.h
cutest_run.o: $(srcdir)/tpkg/cutest/cutest_run.c config.h $(srcdir)/tpkg/cutest/cutest.h \
 $(srcdir)/tpkg/cutest/qtest.h $(srcdir)/buffer.h $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/nsd.h $(srcdir)/dns.h \
 $(srcdir)/edns.h $(srcdir)/buffer.h
cutest_udb.o: $(srcdir)/tpkg/cutest/cutest_udb.c config.h $(srcdir)/tpkg/cutest/cutest.h \
 $(srcdir)/udb.h
cutest_udbrad.o: $(srcdir)/tpkg/cutest/cutest_udbrad.c config.h \
 $(srcdir)/tpkg/cutest/cutest.h $(srcdir)/udbradtree.h $(srcdir)/udb.h
cutest_util.o: $(srcdir)/tpkg/cutest/cutest_util.c config.h $(srcdir)/tpkg/cutest/cutest.h \
 $(srcdir)/region-allocator.h $(srcdir)/util.h
qtest.o: $(srcdir)/tpkg/cutest/qtest.c config.h $(srcdir)/tpkg/cutest/qtest.h $(srcdir)/buffer.h \
 $(srcdir)/region-allocator.h $(srcdir)/util.h $(srcdir)/query.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/buffer.h $(srcdir)/dns.h \
 $(srcdir)/radtree.h $(srcdir)/rbtree.h $(srcdir)/nsd.h $(srcdir)/edns.h $(srcdir)/packet.h $(srcdir)/tsig.h $(srcdir)/namedb.h $(srcdir)/util.h $(srcdir)/nsec3.h \
 $(srcdir)/options.h config.h $(srcdir)/packet.h $(srcdir)/dname.h $(srcdir)/rdata.h
udb-inspect.o: $(srcdir)/tpkg/cutest/udb-inspect.c config.h $(srcdir)/udb.h $(srcdir)/udbradtree.h \
 $(srcdir)/udb.h $(srcdir)/udbzone.h $(srcdir)/dns.h $(srcdir)/udbradtree.h $(srcdir)/util.h $(srcdir)/buffer.h $(srcdir)/region-allocator.h \
 $(srcdir)/util.h $(srcdir)/packet.h $(srcdir)/namedb.h $(srcdir)/dname.h $(srcdir)/buffer.h $(srcdir)/radtree.h $(srcdir)/rbtree.h $(srcdir)/rdata.h \
 $(srcdir)/namedb.h $(srcdir)/difffile.h $(srcdir)/options.h config.h
