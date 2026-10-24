# libSceVnaInternal technical debt

### Unknown function info

The 27 exports in [Export.cpp](../../../core/libs/prx/libSceVnaInternal/Export.cpp) come from the `libSceVnaInternal` export list of [idc/ps4libdoc](https://github.com/idc/ps4libdoc/tree/9.00) (PS4 firmware 9.00, commit a71315e7f36e312ae71e9e3a92982e9ffbfc725f); a PS5 export inventory of this module is not available to the project, so the PS5 module may export more, fewer or different symbols. A name is listed only when its hash equals the recorded NID; the others are exported by NID alone. Prototypes and behaviour are unverified: every function takes no parameters in the import-resolution convention and throws through `NotImplemented_nid_no_patch`.

- [sceVnaCancelDownloadTts](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID UUwnVHwsEzc)
- [sceVnaCancelTts](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID 8PF0W+Q47rM)
- [sceVnaCheckCallback](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID KFez0hNxLvY)
- [sceVnaCloseTtsStream](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID np2cGvsjqvY)
- [sceVnaGetFeedbackStatus](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID QI6ArERn7Tk)
- [sceVnaGetMicStatus](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID -R7CpLCLHe8)
- [sceVnaGetVadState](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID a8lad-APGOY)
- [sceVnaGetWakeupPhraseInfo](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID Yjkpnrnkgpw)
- [sceVnaGetWakeupPhraseInfoCount](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID TA4NTYpt0uU)
- [sceVnaInitialize](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID XCD6zBOkiIM)
- [sceVnaInitializeForParty](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID Xgsi0nAQvNU)
- [sceVnaNotify](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID LSt2Pfp9GRw)
- [sceVnaNotifyStatus](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID PKW7W-yst78)
- [sceVnaOpenTtsStream](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID z-Vz1l8rYNg)
- [sceVnaReadTtsStream](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID pR2Ae3d5-6s)
- [sceVnaRegisterCallback](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID eMerT8QXYeM)
- [sceVnaRequestDownloadTts](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID aCIECfxBuBY)
- [sceVnaRequestTts](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID 6b8nZuvZxpQ)
- [sceVnaSetDucking](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID CenzYgIUIIw)
- [sceVnaSetInputDevice](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID LxfVKLcwdtE)
- [sceVnaSetWakeupPhrase](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID FT07o-hAwrw)
- [sceVnaStartAnalyze](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID P02oAVAxens)
- [sceVnaStartKeywordDetection](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID wV04-VveLpE)
- [sceVnaStopAnalyze](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID OqICoewmNZA)
- [sceVnaStopKeywordDetection](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID d3aALUluqfs)
- [sceVnaTerminate](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID qLIzHK7b8ow)
- [sceVnaUnregisterCallback](../../../core/libs/prx/libSceVnaInternal/Export.cpp) (libSceVnaInternal) - unknown signature (NID A3TNKhREamw)
