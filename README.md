# CAU_OOP_Project1

## 1. Overview & How It Works

SIMS is a console-based application designed to manage student records with automated file-based persistence.

## Compilation and Execution Guide

You can compile and run this project using either Microsoft Visual Studio or the command-line g++ compiler.

### Option 1: Microsoft Visual Studio (Recommended on Windows)
1. Double-click `CAU_OOP_Project1.sln` to open the solution in Visual Studio.
2. Set the build configuration to **Debug** (or **Release**) and platform to **x64**.
3. Configure the mandatory command-line argument for file input:
   - Right-click on the project name in **Solution Explorer** and select **Properties**.
   - Navigate to **Configuration Properties** > **Debugging**.
   - In the **Command Arguments** field, enter:
     ```text
     file1.txt
     ```
   - Click **Apply** and then **OK**.
4. Press **Ctrl + F5** (or select *Debug* > *Start Without Debugging*) to build and execute the application.

---

### Option 2: Command-Line Interface (GCC / G++)
1. Open a terminal (PowerShell, Command Prompt, or Bash) in the project folder containing the `.cpp` and `.h` source files.
2. Compile all source files using standard C++14 (or higher):
   ```bash
   g++ -std=c++14 CAU_OOP_Project1.cpp SortStrategy.cpp Student.cpp StudentManager.cpp -o sims.exe
   ```
3. Run the compiled executable by passing the database file name as an argument:
   - **On Windows:**
     ```powershell
     .\sims.exe file1.txt
     ```
   - **On Linux / macOS:**
     ```bash
     ./sims.exe file1.txt
     ```

> **Note:** If `file1.txt` does not exist in the working directory, the system creates it automatically on launch. If it already exists, all existing student records are loaded into memory immediately upon startup.

### Menu Operations
1. **1. Insertion:** Adds a new student record (Name, 10-digit ID, 4-digit Birth Year, Department, Tel). The system detects duplicates and rejects existing IDs with `"Error: Already inserted"`.
2. **2. Search:** Lists all students or filters records by Name, Student ID, Admission Year, Birth Year, or Department. Results are always formatted and displayed using the active sorting rule.
3. **3. Sorting Option:** Configures the active sorting criterion for listings and search results (Default: Sort by Name; or by Student ID, Birth Year, Department).
4. **4. Exit:** Saves all current data to `file1.txt` and terminates the program cleanly.

---

## 2. Technical Choices & Design Patterns

### Singleton Pattern (`StudentManager`)
* **Why:** The system operates on a single database file (`file1.txt`). Allowing multiple manager instances would cause read/write race conditions, memory synchronization issues, and file corruption.
* **How:** The constructor and destructor are private, and copy/assignment operators are disabled (`= delete`). A static method, `StudentManager::getInstance()`, provides a single global access point to coordinate data storage and file I/O safely.

### Strategy Pattern (`SortStrategy`)
* **Why:** The requirements demand switching dynamically among 4 sorting criteria (Name, Student ID, Birth Year, Department) without modifying search or display logic.
* **How:** An abstract base class `SortStrategy` defines a pure virtual `sort()` method. Four concrete classes (`SortByName`, `SortByStudentId`, `SortByBirthYear`, `SortByDepartment`) implement this method using standard `std::sort`. `StudentManager` holds a `std::unique_ptr<SortStrategy>` and dynamically executes the selected sorting policy at runtime.

### Persistence and Encapsulation (`Student`)
* **Pipe Delimiter (`|`):** Fields are serialized using `|` in `file1.txt` to prevent parsing conflicts with multi-word strings (such as departments containing spaces like *Computer Engineering*).
* **Derived Admission Year:** Admission year is not stored redundantly; it is dynamically extracted from the student's ID string (2 + char from 2 to 4, because exchange student ID start with "5" with is not the right year) when queried.