binary_name			:= example
type				:= exec

include_folders			:= src/domain/inc src/application/inc src/adapters/inc lib/cpputest/install/include
library_folders			:= src/domain/build/debug/lib src/application/build/debug/lib src/adapters/build/debug/lib \
                                   lib/spdlog/install/lib lib/yaml/install/lib lib/pq/install/lib lib/pqxx/install/lib lib/restbed/install/library lib/cpputest/install/lib
libs_to_link			:= stdc++ pthread :domain.so :application.so :adapters.so \
                                   :libspdlog.a :libyaml-cpp.a :libpqxx.so :libpq.so :librestbed.so
test_libs_to_link		:= :libCppUTest.a :libCppUTestExt.a

main_source_folders		:= src/main
test_source_folders		:= src/test

subcomponent_folders		:= src/domain src/application src/adapters

include src/module.mk
