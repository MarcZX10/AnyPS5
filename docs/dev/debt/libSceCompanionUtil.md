# libSceCompanionUtil technical debt

### Unknown function info

- [sceCompanionUtilGetEvent](../../../core/libs/prx/libSceCompanionUtil/Export.cpp) - throws through `NotImplemented_nid_no_patch`; behaviour and the PS5 prototypes are unmeasured. The only source of the parameter lists is shadPS4's PS4-derived prototypes (GPLv2, used as a reference only), with no second reference; structure pointers are `void*` because no layout is known.
- [sceCompanionUtilGetRemoteOskEvent, sceCompanionUtilInitialize, sceCompanionUtilOptParamInitialize and sceCompanionUtilTerminate](../../../core/libs/prx/libSceCompanionUtil/Export.cpp) (libSceCompanionUtil) - names and NIDs are present in the [PS5 3.20 export inventory](https://github.com/DNNDHH/PS5-3.20_Libs/blob/b2a77c09cd71c01f34c790cfbe98c751a13262ad/libSceCompanionUtil.c), but no credible prototypes were found. The declarations have no parameters solely to resolve known imports; this is not an ABI claim and callers must not call them until signatures are verified
