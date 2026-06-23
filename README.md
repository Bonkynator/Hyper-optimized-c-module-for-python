# High-Performance 2x2 Matrix Engine (C++ / PyBind11)

**Overview**: A numerically stable, hyper-optimized 2x2 matrix operations library written in native C++ and exposed to Python via PyBind11. 

This module was engineered to bypass Python's memory allocation bottlenecks and global interpreter lock (GIL) overhead for complex analytical workloads. By utilizing `std::array` for strict stack-based memory allocation and implementing direct mathematical proofs, this library provides significantly faster and more stable matrix operations compared to native Python implementations.

---

## Key Technical Features

* **Catastrophic Cancellation Prevention**: The eigenvalue solver is explicitly engineered to prevent precision loss in floating point arithmetic by dynamically checking signs before computing the discriminant.
* **Stack-Level Memory Management**: Avoids standard C++ `std::vector` or Python object allocation by strictly using `std::array<double, 2>`, minimizing heap fragmentation and memory latency.
* **Automated Build Pipeline**: Features a custom 1-click deployment script (`install.py`) built on top of `setuptools` and `pybind11.setup_helpers` for seamless, cross-platform compilation.
* **Zero-Overhead Python Bindings**: Native C++ functions are directly bound to Python, allowing for instant integration into existing Machine Learning or Data Science pipelines.

---

##  Repository Structure

```text
├── matrices.cpp       # Core C++ algorithms and PyBind11 module definitions
├── setup.py           # Python setuptools build configuration
├── requirements.txt   # Required Python packages (PyBind11, setuptools)
├── install.py         # Automated 1 click build and installation script
├── test.py            # Python implementation and benchmark script
└── README.md          # Documentation
---
## System Prerequisites
Because this library compiles native C++ code, your system must have Python 3.x and a standard C++ compiler installed before running the installation scripts.

* **Windows:** Install [Microsoft C++ Build Tools](https://visualstudio.microsoft.com/visual-cpp-build-tools/) (Ensure "Desktop development with C++" is checked).
* **macOS:** Install Xcode Command Line Tools by running `xcode-select --install` in your terminal.
* **Linux (Ubuntu/Debian):** Install standard build tools by running `sudo apt-get install build-essential python3-dev` in your terminal.
---
### Making the module
After that run the ('install.py') script to automatically install all the python modules needed make the c++ module.
## Current status
Currently studying stochastic calculus and will add more functions and features in the future.
