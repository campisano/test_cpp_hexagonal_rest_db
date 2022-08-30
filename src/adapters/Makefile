binary_name			:= adapters.so
type				:= lib

include_paths			:= inc ../domain/inc ../application/inc \
                                   ../../lib/json/install/include ../../lib/httplib/install/include
library_paths			:= ../domain/build/lib ../application/build/lib
libs_to_link			:=
test_libs_to_link		:= stdc++ pthread \
                                   spdlog fmt yaml-cpp pqxx \
                                   CppUTest CppUTestExt \
                                   :application.so :domain.so

base_source_paths		:= src src/repositories src/controllers src/drivers/logger src/drivers/persistence src/drivers/http src/drivers/config
test_source_paths		:= test

include ../../lib/generic_makefile/modular_makefile.mk
