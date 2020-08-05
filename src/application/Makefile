binary_name			:= application.so
type				:= lib

include_folders			:= inc ../domain/inc ../../lib/cpputest/install/include
library_folders			:= ../domain/build/debug/lib ../../lib/cpputest/install/lib
libs_to_link			:=
test_libs_to_link		:= stdc++ pthread :domain.so \
                                   :libCppUTest.a :libCppUTestExt.a

base_source_folders		:= src src/usecases
test_source_folders		:= test

include ../module.mk
