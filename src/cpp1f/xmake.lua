add_rules("mode.debug", "mode.release")

target("maze")
    set_kind("binary")
    add_files("src/*.cpp")
