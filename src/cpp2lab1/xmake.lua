add_rules("mode.debug", "mode.release")

target("lab1")
    add_rules("qt.widgetapp")
    -- add ui & core header files
    add_headerfiles("src/ui/*.h", "src/core/*.h")
    -- add main source file
    add_files("src/main.cpp")
    add_files("src/ui/*.cpp", "src/core/*.cpp")
    -- add header files with Q_OBJECT macro
    add_files("src/ui/*.h")

    -- for test
    -- the `testUndo.cpp` is not a standard test file, so i just add header files without handling it
    -- if you want to compile it, you should follow the qmake guide in README.md
    -- here didn't add `src/core/Undo.cpp` and provide no target for it
    add_frameworks("QtTest", "QSignalSpy")
