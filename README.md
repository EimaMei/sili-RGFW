# sili RGFW
## Original project
You can find the original project [here](https://github.com/ColleagueRiley/RGFW).

## Description
sili RGFW is meant to be a "sili port" of the RGFW library to make it much easier 
to use sili alongside RGFW, whilst addding improvements to it that are only possible 
with sili.

## Rationale
### Modify the internals of RGFW to make it easy and comfortable to use with sili.
- Using `siString` instead of NULL-terminated C-strings.
- Using sili types, functions, macros, etc instead of equivalent C/RGFW ones.
- Breaking RGFW's conventions in favour of sili design choices.
- and so on...

### Submit changes to the original RGFW
Working on sili RGFW also means reviewing each part of the library and question 
any parts that may fall under certain poor quality.

Current review progress:
- [ ] RGFW allocator:
    - [ ] RGFW_window_setBufferPtr
- [ ] RGFW X11:
    - [ ] General:
        - [x] RGFW_setClassName
        - [x] RGFW_setBufferSize
        - [x] RGFW_getScreenSize
    - [ ] Window functions:
        - [x] RGFW_createWindow/RGFW_createWindowPtr
        - [ ] RGFW_window_checkEvent
        - [ ] RGFW_window_eventWait
        - [ ] RGFW_window_checkEvents
        - [ ] RGFW_stopCheckEvents
        - [ ] RGFW_window_close
        - [ ] RGFW_window_move
        - [ ] RGFW_window_moveToMonitor
        - [ ] RGFW_window_resize
        - [ ] RGFW_window_setMinSize/RGFW_window_setMaxSize
        - [ ] RGFW_window_maximize/RGFW_window_minimize/RGFW_window_restore
        - [ ] RGFW_window_setBorder
        - [ ] RGFW_window_setDND
        - [ ] RGFW_window_setMousePassthrough
        - [x] RGFW_window_setName
        - [x] RGFW_window_setIcon
        - [x] RGFW_window_setMouse
        - [x] RGFW_window_setMouseStandard
        - [x] RGFW_window_setMouseDefault 
        - [ ] RGFW_window_mouseHold
        - [ ] RGFW_window_mouseUnhold
        - [ ] RGFW_window_hide
        - [ ] RGFW_window_show
        - [ ] RGFW_window_setShouldClose
        - [ ] RGFW_getGlobalMousePoint
        - [ ] RGFW_window_getMousePoint
        - [ ] RGFW_window_showMouse
        - [ ] RGFW_window_moveMouse
        - [ ] RGFW_window_shouldClose
        - [ ] RGFW_window_isFullscreen 
        - [ ] RGFW_window_isHidden
        - [ ] RGFW_window_isMinimized
        - [ ] RGFW_window_isMaximized