import keycodes

## https://github.com/nim-lang/sdl2/blob/master/src/sdl2.nim
# type
#   KeySym* {.pure.} = object
#     scancode*: ScanCode
#     modstate*: int16
#     sym*     : cint
#     unicode* : cint
#   EventType {.header: "eventmanager.h", importc.} = enum
#     KeyEvent, MouseEvent #{.importc: "EVENT_KEY".}
#     # MouseEvent {.importc: "EVENT_MOUSE".}
#   # EventType {.size: sizeof(cint).} = enum
#   #   EVENT_KEY, EVENT_MOUSE, EVENT_MOUSEMOVE, EVENT_TIME,

# type Callback(event: void, kdown: bool) {.cdecl, importc: "Callback".}

# proc register_key(key: KeySym, etype: EventType) {.cdecl, importc: "em_register_key".}
# proc callback_none() {.cdecl, importc: "".}

proc init() {.exportc.} =
  echo "init"
  # register_key(K_ESCAPE, em_callback, NULL, 0, 0, 0)

proc update(dt: cdouble) {.exportc.} = 
  discard 1
