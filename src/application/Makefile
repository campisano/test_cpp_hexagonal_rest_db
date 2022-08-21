binary_name			:= application.so
type				:= lib

include_paths			:= inc ../domain/inc ../../lib/cpputest/install/include
library_paths			:= ../domain/build/lib \
                                   ../../lib/cpputest/install/lib
libs_to_link			:=
test_libs_to_link		:= stdc++ pthread :domain.so \
                                   :libCppUTest.a :libCppUTestExt.a

base_source_paths		:= src src/usecases
test_source_paths		:= test

include ../../lib/generic_makefile/modular_makefile.mk
