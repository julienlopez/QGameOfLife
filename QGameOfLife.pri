QGAMEOFLIFE_ROOT = $$PWD

QGAMEOFLIFE_BIN = $$QGAMEOFLIFE_ROOT/bin

#QGAMEOFLIFE_INCLUDE = $$QGAMEOFLIFE_ROOT/include

QGAMEOFLIFE_LIB = $$QGAMEOFLIFE_ROOT/lib

QGAMEOFLIFE_OBJ_LIB = $$QGAMEOFLIFE_ROOT/obj_lib

QGAMEOFLIFE_MOC_LIB = $$QGAMEOFLIFE_ROOT/moc_lib

#QGAMEOFLIFE_OBJ_GUI = $$QGAMEOFLIFE_ROOT/obj_gui

#QGAMEOFLIFE_MOC_GUI = $$QGAMEOFLIFE_ROOT/moc_gui

QGAMEOFLIFE_OBJ_TESTS = $$QGAMEOFLIFE_ROOT/obj_tests

QGAMEOFLIFE_MOC_TESTS = $$QGAMEOFLIFE_ROOT/moc_tests

#QGAMEOFLIFE_SRC = $$QGAMEOFLIFE_ROOT/src

DESTDIR = $$QGAMEOFLIFE_BIN

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-declarations -Wredundant-decls -Wno-long-long -Wuninitialized
# -Wconversion -Winline
