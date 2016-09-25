## 
## Simple makefile for decaf programming projects
##


.PHONY: clean strip

# Set the default target. When you make with no arguments,
# this will be the target built.
COMPILER = dcc
PRODUCTS = $(COMPILER) 
default: $(PRODUCTS)

# Set up the list of source and object files
SRCS = $(wildcard *.cc)

# OBJS can deal with either .cc or .c files listed in SRCS
OBJS = y.tab.o lex.yy.o $(patsubst %.cc, %.o, $(filter %.cc,$(SRCS))) $(patsubst %.c, %.o, $(filter %.c, $(SRCS)))

JUNK =  *.o lex.yy.c dpp.yy.c y.tab.c y.tab.h *.core core $(COMPILER).purify purify.log 

# Define the tools we are going to use
CC= g++
LD = g++
LEX = flex
YACC = bison

# Set up the necessary flags for the tools

# We want debugging and most warnings, but lex/yacc generate some
# static symbols we don't use, so turn off unused warnings to avoid clutter
# STL has some signed/unsigned comparisons we want to suppress
CFLAGS = -g -std=c++11 -Wall -Wno-unused -Wno-sign-compare 

# The -d flag tells lex to set up for debugging. Can turn on/off by
# setting value of global yy_flex_debug inside the scanner itself
LEXFLAGS = -d

# The -d flag tells yacc to generate header with token types
# The -v flag writes out a verbose description of the states and conflicts
# The -t flag turns on debugging capability
# The -y flag means imitate yacc's output file naming conventions
YACCFLAGS = -dvty

# Link with standard c library, math library, and lex library
LIBS = -lc -lm

# Rules for various parts of the target

.yy.o: $*.yy.c
	$(CC) $(CFLAGS) -c -o $@ $*.cc

lex.yy.c: scanner.l  parser.y y.tab.h 
	$(LEX) $(LEXFLAGS) scanner.l

y.tab.o: y.tab.c
	$(CC) $(CFLAGS) -c -o y.tab.o y.tab.c

y.tab.h y.tab.c: parser.y
	$(YACC) $(YACCFLAGS) parser.y
.cc.o: $*.cc
	$(CC) $(CFLAGS) -c -o $@ $*.cc

# rules to build compiler (dcc)

$(COMPILER) :  $(OBJS)
	$(LD) -o $@ $(OBJS) $(LIBS)

$(COMPILER).purify : $(OBJS)
	purify -log-file=purify.log -cache-dir=/tmp/$(USER) -leaks-at-exit=no $(LD) -o $@ $(OBJS) $(LIBS)


# This target is to build small for testing (no debugging info), removes
# all intermediate products, too
strip : $(PRODUCTS)
	strip $(PRODUCTS)
	rm -rf $(JUNK)


# make depend will set up the header file dependencies for the 
# assignment.  You should make depend whenever you add a new header
# file to the project or move the project between machines
#
depend:
	makedepend -- $(CFLAGS) -- $(SRCS)

.PHONY: test
test: test-syntax test-scope

test-scope: $(COMPILER)
	@./test.sh scope

test-syntax: $(COMPILER)
	@./test.sh syntax

clean:
	rm -f $(JUNK) y.output $(PRODUCTS)

# DO NOT DELETE

symbol_table.o: symbol_table.hh ast_decl.hh ast.hh /usr/include/stdlib.h
symbol_table.o: /usr/include/features.h /usr/include/stdc-predef.h
symbol_table.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
symbol_table.o: /usr/include/gnu/stubs.h /usr/include/bits/waitflags.h
symbol_table.o: /usr/include/bits/waitstatus.h /usr/include/sys/types.h
symbol_table.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
symbol_table.o: /usr/include/time.h /usr/include/endian.h
symbol_table.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
symbol_table.o: /usr/include/bits/byteswap-16.h /usr/include/sys/select.h
symbol_table.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
symbol_table.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
symbol_table.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
symbol_table.o: /usr/include/bits/stdlib-float.h analyzable.hh scope_stack.hh
symbol_table.o: scope.hh errors.hh location.hh closeable.hh list.hh
symbol_table.o: utility.hh /usr/include/stdio.h /usr/include/libio.h
symbol_table.o: /usr/include/_G_config.h /usr/include/wchar.h
symbol_table.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
scope.o: scope.hh ast_decl.hh ast.hh /usr/include/stdlib.h
scope.o: /usr/include/features.h /usr/include/stdc-predef.h
scope.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
scope.o: /usr/include/gnu/stubs.h /usr/include/bits/waitflags.h
scope.o: /usr/include/bits/waitstatus.h /usr/include/sys/types.h
scope.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
scope.o: /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h
scope.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
scope.o: /usr/include/sys/select.h /usr/include/bits/select.h
scope.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
scope.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
scope.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h analyzable.hh
scope.o: scope_stack.hh errors.hh location.hh closeable.hh list.hh utility.hh
scope.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
scope.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
scope.o: /usr/include/bits/sys_errlist.h
ast_expr.o: ast_expr.hh ast.hh /usr/include/stdlib.h /usr/include/features.h
ast_expr.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
ast_expr.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
ast_expr.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
ast_expr.o: /usr/include/sys/types.h /usr/include/bits/types.h
ast_expr.o: /usr/include/bits/typesizes.h /usr/include/time.h
ast_expr.o: /usr/include/endian.h /usr/include/bits/endian.h
ast_expr.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
ast_expr.o: /usr/include/sys/select.h /usr/include/bits/select.h
ast_expr.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
ast_expr.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
ast_expr.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h
ast_expr.o: analyzable.hh scope_stack.hh scope.hh errors.hh location.hh
ast_expr.o: ast_stmt.hh list.hh utility.hh /usr/include/stdio.h
ast_expr.o: /usr/include/libio.h /usr/include/_G_config.h
ast_expr.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
ast_expr.o: /usr/include/bits/sys_errlist.h closeable.hh symbol_table.hh
ast_expr.o: ast_type.hh ast_decl.hh /usr/include/string.h
ast_expr.o: /usr/include/xlocale.h
ast_stmt.o: ast_stmt.hh list.hh utility.hh /usr/include/stdlib.h
ast_stmt.o: /usr/include/features.h /usr/include/stdc-predef.h
ast_stmt.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
ast_stmt.o: /usr/include/gnu/stubs.h /usr/include/bits/waitflags.h
ast_stmt.o: /usr/include/bits/waitstatus.h /usr/include/sys/types.h
ast_stmt.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
ast_stmt.o: /usr/include/time.h /usr/include/endian.h
ast_stmt.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
ast_stmt.o: /usr/include/bits/byteswap-16.h /usr/include/sys/select.h
ast_stmt.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
ast_stmt.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
ast_stmt.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
ast_stmt.o: /usr/include/bits/stdlib-float.h /usr/include/stdio.h
ast_stmt.o: /usr/include/libio.h /usr/include/_G_config.h
ast_stmt.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
ast_stmt.o: /usr/include/bits/sys_errlist.h analyzable.hh scope_stack.hh
ast_stmt.o: scope.hh ast.hh errors.hh location.hh closeable.hh
ast_stmt.o: symbol_table.hh ast_type.hh ast_decl.hh ast_expr.hh
utility.o: utility.hh /usr/include/stdlib.h /usr/include/features.h
utility.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
utility.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
utility.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
utility.o: /usr/include/sys/types.h /usr/include/bits/types.h
utility.o: /usr/include/bits/typesizes.h /usr/include/time.h
utility.o: /usr/include/endian.h /usr/include/bits/endian.h
utility.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
utility.o: /usr/include/sys/select.h /usr/include/bits/select.h
utility.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
utility.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
utility.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h
utility.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
utility.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
utility.o: /usr/include/bits/sys_errlist.h list.hh /usr/include/string.h
utility.o: /usr/include/xlocale.h
main.o: /usr/include/string.h /usr/include/features.h
main.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
main.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
main.o: /usr/include/xlocale.h /usr/include/stdio.h /usr/include/bits/types.h
main.o: /usr/include/bits/typesizes.h /usr/include/libio.h
main.o: /usr/include/_G_config.h /usr/include/wchar.h
main.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
main.o: utility.hh /usr/include/stdlib.h /usr/include/bits/waitflags.h
main.o: /usr/include/bits/waitstatus.h /usr/include/sys/types.h
main.o: /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h
main.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
main.o: /usr/include/sys/select.h /usr/include/bits/select.h
main.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
main.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
main.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h errors.hh
main.o: location.hh parser.hh scanner.hh list.hh ast.hh analyzable.hh
main.o: scope_stack.hh scope.hh ast_type.hh ast_stmt.hh closeable.hh
main.o: symbol_table.hh ast_decl.hh ast_expr.hh y.tab.h
ast_decl.o: ast_decl.hh ast.hh /usr/include/stdlib.h /usr/include/features.h
ast_decl.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
ast_decl.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
ast_decl.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
ast_decl.o: /usr/include/sys/types.h /usr/include/bits/types.h
ast_decl.o: /usr/include/bits/typesizes.h /usr/include/time.h
ast_decl.o: /usr/include/endian.h /usr/include/bits/endian.h
ast_decl.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
ast_decl.o: /usr/include/sys/select.h /usr/include/bits/select.h
ast_decl.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
ast_decl.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
ast_decl.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h
ast_decl.o: analyzable.hh scope_stack.hh scope.hh errors.hh location.hh
ast_decl.o: closeable.hh list.hh utility.hh /usr/include/stdio.h
ast_decl.o: /usr/include/libio.h /usr/include/_G_config.h
ast_decl.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
ast_decl.o: /usr/include/bits/sys_errlist.h ast_type.hh ast_stmt.hh
ast_decl.o: symbol_table.hh
ast.o: ast.hh /usr/include/stdlib.h /usr/include/features.h
ast.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
ast.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
ast.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
ast.o: /usr/include/sys/types.h /usr/include/bits/types.h
ast.o: /usr/include/bits/typesizes.h /usr/include/time.h
ast.o: /usr/include/endian.h /usr/include/bits/endian.h
ast.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
ast.o: /usr/include/sys/select.h /usr/include/bits/select.h
ast.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
ast.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
ast.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h analyzable.hh
ast.o: scope_stack.hh scope.hh errors.hh location.hh ast_type.hh list.hh
ast.o: utility.hh /usr/include/stdio.h /usr/include/libio.h
ast.o: /usr/include/_G_config.h /usr/include/wchar.h
ast.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
ast.o: ast_stmt.hh closeable.hh symbol_table.hh ast_decl.hh
ast.o: /usr/include/string.h /usr/include/xlocale.h
errors.o: errors.hh location.hh /usr/include/stdio.h /usr/include/features.h
errors.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
errors.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
errors.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
errors.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
errors.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
errors.o: scanner.hh ast_type.hh ast.hh /usr/include/stdlib.h
errors.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
errors.o: /usr/include/sys/types.h /usr/include/time.h /usr/include/endian.h
errors.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
errors.o: /usr/include/bits/byteswap-16.h /usr/include/sys/select.h
errors.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
errors.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
errors.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
errors.o: /usr/include/bits/stdlib-float.h analyzable.hh scope_stack.hh
errors.o: scope.hh list.hh utility.hh ast_stmt.hh closeable.hh
errors.o: symbol_table.hh ast_expr.hh ast_decl.hh
ast_type.o: ast_type.hh ast.hh /usr/include/stdlib.h /usr/include/features.h
ast_type.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
ast_type.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
ast_type.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
ast_type.o: /usr/include/sys/types.h /usr/include/bits/types.h
ast_type.o: /usr/include/bits/typesizes.h /usr/include/time.h
ast_type.o: /usr/include/endian.h /usr/include/bits/endian.h
ast_type.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
ast_type.o: /usr/include/sys/select.h /usr/include/bits/select.h
ast_type.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
ast_type.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
ast_type.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h
ast_type.o: analyzable.hh scope_stack.hh scope.hh errors.hh location.hh
ast_type.o: list.hh utility.hh /usr/include/stdio.h /usr/include/libio.h
ast_type.o: /usr/include/_G_config.h /usr/include/wchar.h
ast_type.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
ast_type.o: ast_stmt.hh closeable.hh symbol_table.hh ast_decl.hh
ast_type.o: /usr/include/string.h /usr/include/xlocale.h
scope_stack.o: scope_stack.hh scope.hh
