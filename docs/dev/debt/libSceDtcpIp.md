# libSceDtcpIp technical debt

### Unknown function info

The 22 exports in [Export.cpp](../../../core/libs/prx/libSceDtcpIp/Export.cpp) come from the `libSceDtcpIp` export list of [idc/ps4libdoc](https://github.com/idc/ps4libdoc/tree/9.00) (PS4 firmware 9.00, commit a71315e7f36e312ae71e9e3a92982e9ffbfc725f); a PS5 export inventory of this module is not available to the project, so the PS5 module may export more, fewer or different symbols. A name is listed only when its hash equals the recorded NID; the others are exported by NID alone. Prototypes and behaviour are unverified: every function takes no parameters in the import-resolution convention and throws through `NotImplemented_nid_no_patch`.

- [sceDtcpIpActivateAsync](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID iA5fgZroSXQ)
- [sceDtcpIpAddHeader](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID w8gdCsz9E5g)
- [sceDtcpIpByteSeekAsync](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID QXd85nHKgTc)
- [sceDtcpIpCancelActivate](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID 45gE-Md7pGc)
- [sceDtcpIpCheckActivationAsync](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID fpMtgjbfR28)
- [sceDtcpIpCloseContentAsync](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID wB7VXMN6d7Y)
- [sceDtcpIpGetErrorCode](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID 7YmdciXqdyw)
- [sceDtcpIpGetHttpStatusCode](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID YUMJ3Foe2ds)
- [sceDtcpIpInit](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID -8ArXjBU6qg)
- [sceDtcpIpInitAuthAsync](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID vtBruB+RWUw)
- [sceDtcpIpOpenContentAsync](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID 47jR75uXOFs)
- [sceDtcpIpPollAsync](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID +2bYveDZRzU)
- [sceDtcpIpReadAsync](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID SZSvjyBqJ3A)
- [sceDtcpIpRemoveHeader](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID -BReK8o1vzQ)
- [sceDtcpIpStartAuthAsync](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID D0cPLPTMMsM)
- [sceDtcpIpStartSeq](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID 4bT02EA5CF0)
- [sceDtcpIpStopAuthAsync](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID nZZ-9S5sscs)
- [sceDtcpIpStopSeq](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID icx5rQ00bpY)
- [sceDtcpIpTerm](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID 2i0OGsRbIUA)
- [sceDtcpIpTermAuthAsync](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID dUHO5qR+hkw)
- [sceDtcpIpTimeSeekAsync](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID wBWjyBqYees)
- [sceDtcpIpWaitAsync](../../../core/libs/prx/libSceDtcpIp/Export.cpp) (libSceDtcpIp) - unknown signature (NID pSUTufzQ4og)
