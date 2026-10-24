# libSceInvitationDialog technical debt

### Unknown function info

- [sceInvitationDialogGetResult](../../../core/libs/prx/libSceInvitationDialog/Export.cpp) - throws through `NotImplemented_nid_no_patch`; behaviour and the PS5 prototypes are unmeasured. The only source of the parameter lists is shadPS4's PS4-derived prototypes (GPLv2, used as a reference only), with no second reference; structure pointers are `void*` because no layout is known.
- [sceInvitationDialogClose](../../../core/libs/prx/libSceInvitationDialog/Export.cpp) (libSceInvitationDialog) - imported by PS4 titles, which do not load without it, and added without an implementation: declared without parameters, every call throws
