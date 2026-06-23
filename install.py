import subprocess
import sys
import os

def run_command(command, step_name):
    print(f"\n--[+] {step_name}---")
    try:
        # sys.executable ensures we use the active Python environment
        subprocess.check_call([sys.executable] + command)
        print(f"[✓] Successfully completed: {step_name}")
    except subprocess.CalledProcessError:
        print(f"[✗] Error during {step_name}. Please check the console output above.")
        sys.exit(1)

def main():
    
    # Step 1: Install prerequisites from the text file
    if os.path.exists("requirements.txt"):
        run_command(["-m", "pip", "install", "-r", "requirements.txt"], "Installing prerequisites (pybind11, setuptools)")
    else:
        print("\n---requirements.txt not found. Installing defaults---")
        run_command(["-m", "pip", "install", "pybind11", "setuptools"], "Installing pybind11 and setuptools")
        
    # Step 2: Run the setup.py build pipeline
    run_command(["-m", "pip", "install", "."], "Compiling C++ module via setup.py")
    
    print("\n" + '-'*80)
    print("Installation Complete")
    print("Module is ready to use.")
    print('-'*80 +"\n")

if __name__ == "__main__":
    main()