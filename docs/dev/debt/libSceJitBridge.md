# libSceJitBridge technical debt

### Unknown function info

The 23 exports in [Export.cpp](../../../core/libs/prx/libSceJitBridge/Export.cpp) come from the `libSceJitBridge` export list of [idc/ps4libdoc](https://github.com/idc/ps4libdoc/tree/9.00) (PS4 firmware 9.00, commit a71315e7f36e312ae71e9e3a92982e9ffbfc725f); a PS5 export inventory of this module is not available to the project, so the PS5 module may export more, fewer or different symbols. A name is listed only when its hash equals the recorded NID; the others are exported by NID alone. Prototypes and behaviour are unverified: every function takes no parameters in the import-resolution convention and throws through `NotImplemented_nid_no_patch`.

- [_ZN19JITSharedDataMemory11shared_freeEPv](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown signature (NID aNkfdBX+wu8)
- [_ZN19JITSharedDataMemory13shared_callocEmm](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown signature (NID dsomX1PvEyw)
- [_ZN19JITSharedDataMemory13shared_mallocEm](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown signature (NID 0MqrCZ2CMWk)
- [_ZN19JITSharedDataMemory14shared_reallocEPvm](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown signature (NID juTxptKt0gE)
- [_ZN19JITSharedDataMemory15shared_mallinfoEv](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown signature (NID FWuKSBWcWpY)
- [_ZN19JITSharedDataMemory15shared_memalignEmm](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown signature (NID chi2eH8ZMWw)
- [_ZN19JITSharedDataMemory27shared_malloc_max_footprintEv](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown signature (NID KMsFaZJ94s0)
- [_ZN19JITSharedDataMemory9sbrk_infoE](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown signature (NID 1yYzosuMlRQ)
- [_ZN19JITSharedTextMemory11shared_freeEPv](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown signature (NID nJLHw-RLy04)
- [_ZN19JITSharedTextMemory15shared_mallinfoEv](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown signature (NID HtBKMIkuZes)
- [_ZN19JITSharedTextMemory15shared_memalignEmm](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown signature (NID Jf2IlBrVPJw)
- [_ZN19JITSharedTextMemory27shared_malloc_max_footprintEv](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown signature (NID zqEvgYYZ7yw)
- [_ZN19JITSharedTextMemory9sbrk_infoE](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown signature (NID gIc9KgCsbRg)
- [_ZN9JITBridge12ringDoorbellEiNS_8DoorbellE](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown signature (NID SIV74lgzM60)
- [_ZN9JITBridge12waitDoorbellEi](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown signature (NID Db6xmY7At2g)
- [_ZN9JITBridge14shutdownFromVMEPS_b](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown signature (NID ISUUjW5I+7Q)
- [_ZN9JITBridge16initializeFromVMEPKcPPcPKNS_11RestartDataE](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown signature (NID PYqhIaBQ4T4)
- [_ZN9JITBridge20shutdownFromCompilerEPS_b](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown signature (NID HQgBJvkdrfA)
- [_ZN9JITBridge22initializeFromCompilerEPKcPPcPKNS_11RestartDataE](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown signature (NID aBOzlIVp16k)
- [_ZN9JITBridge8shutdownEb](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown signature (NID JRQIZdQ5VRs)
- [_ZNK9JITBridge20sharedMemoryAreaSizeEv](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown signature (NID lWDHF6V72lk)
- [KvaTJ9sSwMY](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown name, signature
- [SjL1STUBoaw](../../../core/libs/prx/libSceJitBridge/Export.cpp) (libSceJitBridge) - unknown name, signature
