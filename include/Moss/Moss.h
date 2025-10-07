//                        MIT License
//
//                  Copyright (c) 2025 Toby
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//     /$$      /$$        
//    | $$$    /$$$         
//    | $$$$  /$$$$  /$$$$$$   /$$$$$$$ /$$$$$$$
//    | $$ $$/$$ $$ /$$__  $$ /$$_____//$$_____/
//    | $$  $$$| $$| $$  \ $$|  $$$$$$|  $$$$$$
//    | $$\  $ | $$| $$  | $$ \____  $$\____  $$
//    | $$ \/  | $$|  $$$$$$/ /$$$$$$$//$$$$$$$/
//    |__/     |__/ \______/ |_______/|_______/
//

#pragma once


#ifdef __cplusplus
extern "C" {
#endif

// Moss Framework version
#define MOSS_MAJOR_VERSION 0
#define MOSS_MINOR_VERSION 1
#define MOSS_PATCH_VERSION 0

#define MOSS_VERSION_NUM(major, minor, patch) ((major) * 10000 + (minor) * 100 + (patch))
#define MOSS_VERSION MOSS_VERSION_NUM(MOSS_MAJOR_VERSION, MOSS_MINOR_VERSION, MOSS_PATCH_VERSION)

#if MOSS_VERSION < MOSS_VERSION_NUM(0, 2, 0)
#error "CMoss 0.2.0 or higher is required!"
#endif

#include <Moss/Moss_Platform.h>
#include <Moss/Moss_Renderer.h>
#include <Moss/Moss_Resources.h>
#include <Moss/Moss_Variants.h>
#include <Moss/Moss_Network.h>
#include <Moss/Moss_Physics.h>
#include <Moss/Moss_Audio.h>
#include <Moss/Moss_stdinc.h>
#include <Moss/Moss_XR.h>

#ifdef __cplusplus
}
#endif
