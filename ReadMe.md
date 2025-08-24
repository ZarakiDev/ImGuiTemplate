# ImGui Floating Menu Template for iOS

A lightweight **ImGui floating menu template** for iOS, designed to support **multitouch**. This template can be compiled with either **Theos** (Makefile/tweak) or **Xcode** (Template.xcodeproj), making it easy to integrate into your iOS projects.

---

## Features

- Floating ImGui menu with multitouch support  
- Cross-compatibility:
  - **Theos**: supports C++20 and below  
  - **Xcode**: supports C++23 and below  
- Utilities included:
  - **Breakpoint & VTable hook library**  
  - **Pattern scanner library (`CGuardMemory`)**  
- Ready for quick integration into your own projects  
- GitHub-ready for version control and collaboration  

---

## Setup

### Using Theos

1. Open the Makefile and set your target and project configurations.  
2. Ensure your Theos setup supports **C++20 or below**.  
3. Run `make package` to build and deploy your tweak.

### Using Xcode

1. Open `Template.xcodeproj` in Xcode.  
2. Ensure the project is set to use **C++23 or below**.  
3. Build and run on your iOS device.

---

## Usage

- Integrate the menu template into your app or tweak.  
- Use included utilities for hooking and memory scanning:  
  - **Breakpoint hooks**: pause or inspect code execution.  
  - **VTable hooks**: override virtual functions at runtime.  
  - **CGuardMemory pattern scanner**: locate memory patterns safely.

---

## License

This project is open-source and hosted on **GitHub**. Feel free to fork, contribute, or report issues.

---

## Notes

- Designed for iOS development with **Theos** or **Xcode**.  
- Make sure your compiler version matches the project requirements for proper C++ standard support.  
- Multitouch support is built-in, so you can handle gestures easily.

---

## Contributing

1. Fork the repository  
2. Make your changes  
3. Submit a pull request  

---

**Enjoy building your iOS projects with a floating ImGui menu!**
