# libSceAudiodReport technical debt

### Unknown function info

The 8 exports in [Export.cpp](../../../core/libs/prx/libSceAudiodReport/Export.cpp) come from the `libSceAudiodReport` export list of [idc/ps4libdoc](https://github.com/idc/ps4libdoc/tree/9.00) (PS4 firmware 9.00, commit a71315e7f36e312ae71e9e3a92982e9ffbfc725f); a PS5 export inventory of this module is not available to the project, so the PS5 module may export more, fewer or different symbols. A name is listed only when its hash equals the recorded NID; the others are exported by NID alone. Prototypes and behaviour are unverified: every function takes no parameters in the import-resolution convention and throws through `NotImplemented_nid_no_patch`.

- [sceAudiodReportLoudness](../../../core/libs/prx/libSceAudiodReport/Export.cpp) (libSceAudiodReport) - unknown signature (NID WQhzwyaq4i8)
- [sceAudiodReportMasteringGetParams](../../../core/libs/prx/libSceAudiodReport/Export.cpp) (libSceAudiodReport) - unknown signature (NID zs1b1Y6IBdI)
- [sceAudiodReportMasteringSetParams](../../../core/libs/prx/libSceAudiodReport/Export.cpp) (libSceAudiodReport) - unknown signature (NID l-cZLdtVXds)
- [sceAudiodReportMasteringStates](../../../core/libs/prx/libSceAudiodReport/Export.cpp) (libSceAudiodReport) - unknown signature (NID oTBVBlVW9PU)
- [sceAudiodReportOutput](../../../core/libs/prx/libSceAudiodReport/Export.cpp) (libSceAudiodReport) - unknown signature (NID Db6G2wnBgp0)
- [sceAudiodReportRegisterHandler](../../../core/libs/prx/libSceAudiodReport/Export.cpp) (libSceAudiodReport) - unknown signature (NID N-t6bvimom4)
- [sceAudiodReportSetEnableFlag](../../../core/libs/prx/libSceAudiodReport/Export.cpp) (libSceAudiodReport) - unknown signature (NID 0v4UVCO4AXs)
- [sceAudiodReportUnregisterHandler](../../../core/libs/prx/libSceAudiodReport/Export.cpp) (libSceAudiodReport) - unknown signature (NID 6vGNjK1X5iU)
