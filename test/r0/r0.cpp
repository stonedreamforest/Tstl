#include <ntddk.h>
#define _KERNEL_TSTL
#include <tlist.hpp>
#include "../test.hpp"

EXTERN_C
void DriverUnload(_DRIVER_OBJECT* DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);

    // 销毁
    Test::__destory();
}

EXTERN_C
NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);
    DriverObject->DriverUnload = DriverUnload;

    // 初始化
    Test::__init();

    Test::test_g_class();
    Test::test_l_class();

    return STATUS_SUCCESS;
}