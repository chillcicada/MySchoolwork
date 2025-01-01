add_rules("mode.release", "mode.debug")

target("fw")
    set_kind("binary")
    set_languages("c++17")
    add_files("src/*.cpp")
