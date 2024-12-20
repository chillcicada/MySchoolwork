-- @file xmake.lua
-- @author liukuan (liukuan22@mails.tsinghua.edu.cn)
-- @brief xmake build script for qode
-- @version 0.0.0
-- @date 2024-12-09
--
-- @copyright Copyright (c) 2024 GPLv3

-- Please check the `justfile` if you haven't use xmake before.

add_rules("mode.release", "mode.debug", "mode.coverage", "mode.profile")

add_requires("nlohmann_json", "utest.h")

target("qode")
    set_kind("binary")
    set_languages("c++20")
    add_rules("qt.widgetapp")
    add_includedirs("include", "src/core", "src/ui")
    add_headerfiles("src/*/*.h")
    add_files("src/*/*.cpp")
    add_files("src/main.cpp")
    add_files("src/ui/*.h", "src/core/*.h")
    add_packages("nlohmann_json")
    add_frameworks("QtWebEngineWidgets", "QtWebEngineCore")

target("mystl-test")
    set_kind("binary")
    set_languages("c++20")
    add_includedirs("include")
    add_files("tests/mystl/*.cpp")
    add_packages("utest.h")

target("lsp-test")
    set_kind("binary")
    set_languages("c++20")
    add_includedirs("include", "src/core")
    add_files("tests/lsp/*.cpp")
    add_packages("utest.h", "nlohmann_json")

target("lspclient-test")
    set_kind("binary")
    set_languages("c++20")
    add_rules("qt.console")
    add_includedirs("include", "src/core")
    add_files("src/core/Lsp*.h", "src/core/Lsp*.cpp", "tests/lspclient/*.cpp", "tests/lspclient/*.h")
    add_packages("nlohmann_json")
    add_frameworks("QtTest")

target("misc-test")
    set_kind("binary")
    add_rules("qt.console")
    set_languages("c++20")
    add_includedirs("include", "src/core")
    add_files("tests/misc/*.cpp")
    add_packages("nlohmann_json", "utest.h")
