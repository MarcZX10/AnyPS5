# libSceScm technical debt

### Unknown function info

The 4 exports in [Export.cpp](../../../core/libs/prx/libSceScm/Export.cpp) come from the `libSceScm` export list of [idc/ps4libdoc](https://github.com/idc/ps4libdoc/tree/9.00) (PS4 firmware 9.00, commit a71315e7f36e312ae71e9e3a92982e9ffbfc725f); a PS5 export inventory of this module is not available to the project, so the PS5 module may export more, fewer or different symbols. A name is listed only when its hash equals the recorded NID; the others are exported by NID alone. Prototypes and behaviour are unverified: every function takes no parameters in the import-resolution convention and throws through `NotImplemented_nid_no_patch`.

- [sceSblACMgrCheckPlatformDLL](../../../core/libs/prx/libSceScm/Export.cpp) (libSceScm) - unknown signature (NID 504MPu5OUbg)
- [sceSblACMgrIsPlatformDLL](../../../core/libs/prx/libSceScm/Export.cpp) (libSceScm) - unknown signature (NID k+dk+pYjIac)
- [sceSblRcMgrIsAllowLimitedUiInspector](../../../core/libs/prx/libSceScm/Export.cpp) (libSceScm) - unknown signature (NID yfn+OUTExgM)
- [sceSblRcMgrIsIntdevForPSM](../../../core/libs/prx/libSceScm/Export.cpp) (libSceScm) - unknown signature (NID bkz3jG-RlGA)
