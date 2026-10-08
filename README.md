# CAU_OOP_Project1

## 1. Overview & How It Works

SIMS is a console-based application designed to manage student records with automated file-based persistence.

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