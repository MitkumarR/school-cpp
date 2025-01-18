### Setting Up vcpkg
1. Clone the vcpkg repository:
git clone https://github.com/microsoft/vcpkg.git

2. Bootstrap vcpkg:
./vcpkg/bootstrap-vcpkg.sh # For Linux/Mac 
.\vcpkg\bootstrap-vcpkg.bat # For Windows

3. Install dependencies:
./vcpkg install

4. Integrate with Visual Studio:
./vcpkg integrate install