cmake_minimum_required (VERSION 2.6)
project (SGui)

ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
)

# add the executables
add_library(SGui
  macros.cpp
  basic.cpp
  basic_converters.cpp
  functions.cpp
  Box.cpp
  ConcreteWRectIfc.cpp
  ActionSurface.cpp
  State.cpp
  GraphState.cpp
  StateHndlr.cpp
  Txtr.cpp
  Image.cpp
  Font.cpp
  Text.cpp
  Txtr.cpp
  Rect.cpp
  TextBox.cpp
  SGui.cpp
  )