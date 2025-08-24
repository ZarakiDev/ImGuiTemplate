# ImGui Floating Menu Template for iOS

A lightweight and easy to use **ImGui floating menu template** for iOS, designed to support **multitouch**. This template can be compiled with either **Theos** or **Xcode**.

---

## Features

- Floating ImGui menu with multitouch support
- Automatic saving of variables defined within the Settings class (Settings.h)
- Cross-compatibility:
  - **Theos**: supports C++20 and below  
  - **Xcode**: supports C++23 and below  
- Utilities included:
  - **Breakpoint & VTable hook library**  
  - **Pattern scanner library (`CGuardMemory`)**
  - **fmtlib for fast string formatting**

---

## Setup

### Using Theos

1. Open the Makefile and set your target and project configurations.  
2. Ensure your Theos setup supports **C++20 or below**.  
3. Run `make package` or `make clean package` to build.

### Using Xcode

1. Open `Template.xcodeproj` in Xcode.  
2. Ensure the project is set to use **C++23 or below**.  
3. Set target to `Any iOS Device (arm64)` and build.

