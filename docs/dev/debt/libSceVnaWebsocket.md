# libSceVnaWebsocket technical debt

### Unknown function info

The 23 exports in [Export.cpp](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) come from the `libSceVnaWebsocket` export list of [idc/ps4libdoc](https://github.com/idc/ps4libdoc/tree/9.00) (PS4 firmware 9.00, commit a71315e7f36e312ae71e9e3a92982e9ffbfc725f); a PS5 export inventory of this module is not available to the project, so the PS5 module may export more, fewer or different symbols. A name is listed only when its hash equals the recorded NID; the others are exported by NID alone. Prototypes and behaviour are unverified: every function takes no parameters in the import-resolution convention and throws through `NotImplemented_nid_no_patch`.

- [Bw0-YBkPNm4](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [DP4477brt60](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [JiBSw3cBh2g](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [J3fL2giuM+0](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [J8-VXNQySz0](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [KGPZ+BZgXn0](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [K-logS9LtFw](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [MI6xIf-bHXs](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [NS+C+w391Aw](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [OUogBgTPp6E](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [PPt1uQ9zOb8](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [T4s2VWpD9-g](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [cbU-LTm7Mrg](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [es11O5Z1er4](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [fxgYzL5aGyw](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [hSnmIgcBCMk](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [jtTGYZXUOqE](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [obO4IYwAPtg](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [qUkQKyPORE8](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [t534VXlYZI8](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [8KzE01OyRog](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [94G0OCEujjA](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
- [-IDFERYOJPs](../../../core/libs/prx/libSceVnaWebsocket/Export.cpp) (libSceVnaWebsocket) - unknown name, signature
