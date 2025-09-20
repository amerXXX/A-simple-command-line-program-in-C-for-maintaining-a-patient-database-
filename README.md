# A-simple-command-line-program-in-C-for-maintaining-a-patient-database-

<img width="1117" height="473" alt="Screenshot from 2025-09-15 15-19-37" src="https://github.com/user-attachments/assets/cb40482e-f5fd-4ce4-b080-0db8b3d57238" />

````markdown
# Patient Registry (C)

A simple command-line program in C for maintaining a patient database (`patientData.txt`).  
Each run appends a new patient record and prints all records.

---

## Features
- Stores patients in plain-text format: `ID Name Age`
- Enforces:
  - Exactly **3 arguments**: `ID Name Age`
  - Positive integer `ID`
  - Age range between **0.0 and 30.0**
  - Maximum **10 patients**
  - No duplicate IDs
- Error handling for all invalid cases

---

## Build

```bash
make
````

This creates the executable `./patient_registry`.

---

## Usage

```bash
./patient_registry <ID> <Name> <Age>
```

### Examples

```bash
./patient_registry 20260 John 25
./patient_registry 20251 Abdullah 23
./patient_registry 20252 Waleed 23
./patient_registry 20253 Ali 19
```

---

## Error Cases

* Missing arguments:

  ```
  Error: Expected 3 arguments (ID Name Age).
  ```

* Non-integer or non-positive ID:

  ```
  Error: Patient ID must be a positive integer.
  ```

* Invalid age:

  ```
  Error: Age must be between 0.0 and 30.0.
  ```

* Duplicate ID:

  ```
  Error: Patient ID already exists!
  ```

* Too many patients:

  ```
  Error: Maximum patient capacity reached!
  ```

---

## Data File

Records are kept in `patientData.txt` in the working directory.
Example:

```
20260 John 25.00
20251 Abdullah 23.00
20252 Waleed 23.00
20253 Ali 19.00
```

---

## Testing

A scripted demo is provided:

```bash
make test
```

This will:

* Print initial records
* Add patients
* Show duplicate-ID error
* Hit the max-capacity error

---

## Project Layout

```
.
├── .gitignore
├── LICENSE
├── README.md
├── main.c
├── patientData.txt

```

---

## License

MIT — see [LICENSE](LICENSE).


