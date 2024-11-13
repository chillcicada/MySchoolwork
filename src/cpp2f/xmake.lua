add_rules("mode.debug", "mode.release")

target("qode")
    add_rules("qt.widgetapp")
    set_languages("c++17")
    -- add ui & core header files
    add_headerfiles("src/ui/*.h", "src/core/*.h")
    -- add main source file
    add_files("src/main.cpp")
    add_files("src/ui/*.cpp", "src/core/*.cpp")
    -- add header files with Q_OBJECT macro
    add_files("src/ui/*.h")
