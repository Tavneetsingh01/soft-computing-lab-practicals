# This Repository contains the lab Programs for On-Going Soft Computing Lab (CSP 3035) Spring 2025
<hr>

![C Version](https://img.shields.io/badge/C-99-blue)
![CMake Version](https://img.shields.io/badge/CMake-3.29-red)
## The following are the list of programs with their `.c` code files.

<table style="border-collapse: collapse; width: 100%;">
    <tr>
        <th style="border: 1px solid black; padding: 8px;"><b>Program</b></th>
        <th style="border: 1px solid black; padding: 8px;"><b>Code File</b></th>
    </tr>
    <tr>
        <td style="border: 1px solid black; padding: 8px;"><b>Q1. Design and simulate the behaviour of AND Gate using Perceptron Network in C for bipolar inputs and targets.</b></td>
        <td style="border: 1px solid black; padding: 8px;"><a href="/Single_Layer_Preceptron_For_Bipolar_AND_Gate.c">Single Layer Preceptron For Bipolar AND Gate</a></td>
    </tr>
    <tr>
        <td style="border: 1px solid black; padding: 8px;"><b>Q2. Design and simulate the behaviour of OR Gate using Adaline Network in C for bipolar inputs and targets.</b></td>
        <td style="border: 1px solid black; padding: 8px;"><a href="/Adaline_Network_For_OR_Gate_Bipolar_Inputs_and_Targets.c">Adaline Network For OR Gate Bipolar Inputs and Targets</a></td>
    </tr>
</table>

## Environment Setup (Setting up GCC)

### Windows (x86_64)
1. Download the latest MinGW release from [MinGW Builds](https://github.com/niXman/mingw-builds-binaries/releases).
2. Choose the `x86_64-14.2.0-release-posix-seh-ucrt-rt_v12-rev1.7z` release for modern 64-bit systems  (note: the version might change in the future, but `x86_64_posix-seh-ucrt` is the main identifier).
3. Extract the contents of the downloaded file to a directory of your choice.
4. Add the `bin` directory of the extracted MinGW to your system's `PATH` environment variable:
    - Open the Start Menu, search for "Environment Variables", and select "Edit the system environment variables".
    - In the System Properties window, click on the "Environment Variables" button.
    - In the Environment Variables window, find the `Path` variable in the "System variables" section and click "Edit".
    - Click "New" and add the path to the `bin` directory of the extracted MinGW (e.g., `C:\path\to\mingw\bin`).
    - Click "OK" to close all windows.
5. Verify the installation by opening a command prompt and running `gcc --version`.

### Windows (ARM AArch64)
1. Download the latest ARM GCC toolchain from [Arm Developer](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm).
2. Choose the appropriate release for your system.
3. Extract the contents of the downloaded file to a directory of your choice.
4. Add the `bin` directory of the extracted toolchain to your system's `PATH` environment variable:
    - Open the Start Menu, search for "Environment Variables", and select "Edit the system environment variables".
    - In the System Properties window, click on the "Environment Variables" button.
    - In the Environment Variables window, find the `Path` variable in the "System variables" section and click "Edit".
    - Click "New" and add the path to the `bin` directory of the extracted toolchain (e.g., `C:\path\to\arm\bin`).
    - Click "OK" to close all windows.
5. Verify the installation by opening a command prompt and running `arm-none-eabi-gcc --version`.

#### You can also use WSL2 for this:
1. Follow the instructions to set up WSL2 [here](https://docs.microsoft.com/en-us/windows/wsl/install).
2. Install a Linux distribution from the Microsoft Store (e.g., Ubuntu).
3. Open the WSL2 terminal and install GCC using the package manager:
    - For Debian-based distributions (e.g., Ubuntu):
      ```sh
      sudo apt update
      sudo apt install build-essential
      ```
4. Verify the installation by running `gcc --version` in the WSL2 terminal.

#### Linux
1. Open a terminal.
2. Install GCC using the package manager:
    - For Debian-based distributions (e.g., Ubuntu):
      ```sh
      sudo apt update
      sudo apt install build-essential
      ```
    - For Red Hat-based distributions (e.g., Fedora):
      ```sh
      sudo dnf install gcc
      ```
3. Verify the installation by running `gcc --version` in the terminal.

#### macOS
1. Open a terminal.
2. Install Xcode Command Line Tools by running:
   ```sh
   xcode-select --install
   ```
3. Verify the installation by running `gcc --version` in the terminal.

### Open to Contributions
Contributions are welcomed to this project! If you would like to contribute, please follow these steps:  
1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Make your changes and commit them with clear and concise messages.
4. Push your changes to your forked repository.
5. Create a pull request to the main repository.

## License
This project is licensed under the MIT License - see the [LICENSE](/LICENSE) file for details.