// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

/*
USING RESOURCES
To use PRI resources that are included alongside your library:
- In one file, use
  UTILS_DEFINE_LIBRARY_RESOURCE_SCOPE(L"ResourceScope"). The
  provided scope will be used as the basename for all library
  resource lookups with RS_() or GetLibraryLocalizedString().
- Use RS_(L"ResourceName") for all statically-known resource
  names.
- Use GetLibraryResourceString(string) for all resource lookups
  for keys known only at runtime.
- For any static resource lookups that are deferred through
  another function call, use USES_RESOURCE(L"Key") to ensure the
  key is tracked.
*/

#pragma detect_mismatch("winrt_utils_debug", "0")

#define USES_RESOURCE(x) (x)
#define RS_(x) LocalizedNameForResource(winrt::hstring{x}, L"Content")
#define RS(x) LocalizedNameForResource(x, L"Content")


// For things that need UTF-8 strings
#define RS_A(x) (winrt::to_string(RS_(x)))

// Array-to-pointer decay might technically be avoidable, but this is elegant and clean.
#define UTILS_DEFINE_LIBRARY_RESOURCE_SCOPE(x) \
    __pragma(warning(suppress : 26485));       \
    __declspec(selectany) extern const wchar_t* g_WinRTUtilsLibraryResourceScope{ (x) };


winrt::hstring LocalizedNameForResource(const winrt::hstring name, const winrt::hstring resourceProperty);
winrt::hstring GetLibraryResourceString(const std::wstring_view key);
bool HasLibraryResourceWithName(const std::wstring_view key);
