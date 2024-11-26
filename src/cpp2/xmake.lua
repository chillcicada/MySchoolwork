add_rules("mode.debug", "mode.release")
add_requires("eigen", "utest.h")

target("t2")
  set_kind("binary")
  set_languages("c++17")
  add_files("HW04/t2.cpp")
  add_packages("eigen")

target("tests")
  set_languages("c++17")
  add_includedirs("mystl")
  -- add the main entry file
  add_files("tests/main.cpp")
  -- source files will automatically be added and bundled to the target
  add_files("tests/*_test.cpp")
  add_packages("utest.h")
