# libSceWeb technical debt

### Unknown function info

The 12 exports in [Export.cpp](../../../core/libs/prx/libSceWeb/Export.cpp) come from the `libSceWeb` export list of [idc/ps4libdoc](https://github.com/idc/ps4libdoc/tree/9.00) (PS4 firmware 9.00, commit a71315e7f36e312ae71e9e3a92982e9ffbfc725f); a PS5 export inventory of this module is not available to the project, so the PS5 module may export more, fewer or different symbols. A name is listed only when its hash equals the recorded NID; the others are exported by NID alone. Prototypes and behaviour are unverified: every function takes no parameters in the import-resolution convention and throws through `NotImplemented_nid_no_patch`.

- [sceWebInitialize](../../../core/libs/prx/libSceWeb/Export.cpp) (libSceWeb) - unknown signature (NID GE9UpqJPdFs)
- [sceWebTerminate](../../../core/libs/prx/libSceWeb/Export.cpp) (libSceWeb) - unknown signature (NID uA2V1TG78p0)
- [U0WWVy+WEzc](../../../core/libs/prx/libSceWeb/Export.cpp) (libSceWeb) - unknown name, signature
- [cCuFvsQw0Ts](../../../core/libs/prx/libSceWeb/Export.cpp) (libSceWeb) - unknown name, signature
- [ck2JqODsGqo](../../../core/libs/prx/libSceWeb/Export.cpp) (libSceWeb) - unknown name, signature
- [dk2zvVSwsoA](../../../core/libs/prx/libSceWeb/Export.cpp) (libSceWeb) - unknown name, signature
- [m0GycBUK+BA](../../../core/libs/prx/libSceWeb/Export.cpp) (libSceWeb) - unknown name, signature
- [spoQscGt3EA](../../../core/libs/prx/libSceWeb/Export.cpp) (libSceWeb) - unknown name, signature
- [w1N9bHY7tbM](../../../core/libs/prx/libSceWeb/Export.cpp) (libSceWeb) - unknown name, signature
- [ycjgSo4QJ58](../../../core/libs/prx/libSceWeb/Export.cpp) (libSceWeb) - unknown name, signature
- [9OhfHLBAiCo](../../../core/libs/prx/libSceWeb/Export.cpp) (libSceWeb) - unknown name, signature
- [-0PAZRBRNNI](../../../core/libs/prx/libSceWeb/Export.cpp) (libSceWeb) - unknown name, signature
