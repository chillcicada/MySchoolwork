add_rules("mode.debug", "mode.release")
add_requires("eigen", "utest.h")

target("t2")
  set_kind("binary")
  set_languages("c++17")
  add_files("HW04/t2.cpp")
  add_packages("eigen")

target("tests")
  set_languages("c++17")
  add_headerfiles("mystl/*.h")
  add_files("tests/*.cpp")
  add_packages("utest.h")
