add_rules("mode.debug", "mode.release")
add_requires("eigen")
target("t2")
  set_kind("binary")
  set_languages("c++17")
  add_files("HW04/t2.cpp")
  add_packages("eigen")