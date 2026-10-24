# libSceAsyncStorageInternal technical debt

### Unknown function info

The 19 exports in [Export.cpp](../../../core/libs/prx/libSceAsyncStorageInternal/Export.cpp) come from the `libSceAsyncStorageInternal` export list of [idc/ps4libdoc](https://github.com/idc/ps4libdoc/tree/9.00) (PS4 firmware 9.00, commit a71315e7f36e312ae71e9e3a92982e9ffbfc725f); a PS5 export inventory of this module is not available to the project, so the PS5 module may export more, fewer or different symbols. A name is listed only when its hash equals the recorded NID; the others are exported by NID alone. Prototypes and behaviour are unverified: every function takes no parameters in the import-resolution convention and throws through `NotImplemented_nid_no_patch`.

- [AtEWh5hZJAI](../../../core/libs/prx/libSceAsyncStorageInternal/Export.cpp) (libSceAsyncStorageInternal) - unknown name, signature
- [EKjWxMVMPzY](../../../core/libs/prx/libSceAsyncStorageInternal/Export.cpp) (libSceAsyncStorageInternal) - unknown name, signature
- [GETCq+kyXcA](../../../core/libs/prx/libSceAsyncStorageInternal/Export.cpp) (libSceAsyncStorageInternal) - unknown name, signature
- [J-cJO5MPuwo](../../../core/libs/prx/libSceAsyncStorageInternal/Export.cpp) (libSceAsyncStorageInternal) - unknown name, signature
- [Knldkc0w9lI](../../../core/libs/prx/libSceAsyncStorageInternal/Export.cpp) (libSceAsyncStorageInternal) - unknown name, signature
- [QM3-5jVrNHg](../../../core/libs/prx/libSceAsyncStorageInternal/Export.cpp) (libSceAsyncStorageInternal) - unknown name, signature
- [TN9xRCVggRw](../../../core/libs/prx/libSceAsyncStorageInternal/Export.cpp) (libSceAsyncStorageInternal) - unknown name, signature
- [hP+HenjaOi8](../../../core/libs/prx/libSceAsyncStorageInternal/Export.cpp) (libSceAsyncStorageInternal) - unknown name, signature
- [iYDbqYNVajM](../../../core/libs/prx/libSceAsyncStorageInternal/Export.cpp) (libSceAsyncStorageInternal) - unknown name, signature
- [mvZ-UdW+Z-Q](../../../core/libs/prx/libSceAsyncStorageInternal/Export.cpp) (libSceAsyncStorageInternal) - unknown name, signature
- [smItNfY3yHA](../../../core/libs/prx/libSceAsyncStorageInternal/Export.cpp) (libSceAsyncStorageInternal) - unknown name, signature
- [65H7-ohmD9c](../../../core/libs/prx/libSceAsyncStorageInternal/Export.cpp) (libSceAsyncStorageInternal) - unknown name, signature
- [9zqbh2tZtZg](../../../core/libs/prx/libSceAsyncStorageInternal/Export.cpp) (libSceAsyncStorageInternal) - unknown name, signature
- [93CwGWrhf+w](../../../core/libs/prx/libSceAsyncStorageInternal/Export.cpp) (libSceAsyncStorageInternal) - unknown name, signature
- [+YiZLBbdEy8](../../../core/libs/prx/libSceAsyncStorageInternal/Export.cpp) (libSceAsyncStorageInternal) - unknown name, signature
- [AdTjrblPbkA](../../../core/libs/prx/libSceAsyncStorageInternal/Export.cpp) (libSceAsyncStorageInternal) - unknown name, signature
- [FlnrIbnUvyI](../../../core/libs/prx/libSceAsyncStorageInternal/Export.cpp) (libSceAsyncStorageInternal) - unknown name, signature
- [qenXW57P9rU](../../../core/libs/prx/libSceAsyncStorageInternal/Export.cpp) (libSceAsyncStorageInternal) - unknown name, signature
- [yLYSOLZmYso](../../../core/libs/prx/libSceAsyncStorageInternal/Export.cpp) (libSceAsyncStorageInternal) - unknown name, signature
