#define DLL_TEST_API     _declspec(dllexport)

#include "pch.h"
#include "DllTest.h"

DllTest::DllTest()
{

}

std::string DllTest::testDll()
{
    return "这是一个dll";
}
