binary_name			:= example
type				:= exec

include_paths			:= src/domain/inc src/application/inc src/adapters/inc
library_paths			:= src/domain/build/lib src/application/build/lib src/adapters/build/lib
libs_to_link			:= stdc++ pthread \
                                   spdlog fmt yaml-cpp pqxx \
                                   :adapters.so :application.so :domain.so
test_libs_to_link		:= CppUTest CppUTestExt

main_source_paths		:= src/main
test_source_paths		:= src/test

subcomponent_paths		:= src/domain src/application src/adapters

PREFIX				:= $(CURDIR)/install

include lib/generic_makefile/modular_makefile.mk
