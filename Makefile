binary_name			:= example
type				:= exec

include_paths			:= src/domain/inc src/application/inc src/adapters/inc lib/cpputest/install/include
library_paths			:= src/domain/build/lib src/application/build/lib src/adapters/build/lib \
				   lib/spdlog/install/lib lib/yaml/install/lib lib/pq/install/lib lib/pqxx/install/lib lib/cpputest/install/lib
libs_to_link			:= stdc++ pthread :domain.so :application.so :adapters.so \
                                   :libspdlog.a :libyaml-cpp.a :libpqxx.so :libpq.so
test_libs_to_link		:= :libCppUTest.a :libCppUTestExt.a

main_source_paths		:= src/main
test_source_paths		:= src/test

subcomponent_paths		:= src/domain src/application src/adapters

PREFIX				:= $(CURDIR)/install

include lib/generic_makefile/modular_makefile.mk
