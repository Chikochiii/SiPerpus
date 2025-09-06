# SiPerpus 📚

Hi! This is a simple project to practice **C programming**.  
The name is **SiPerpus (Library Information System)**.

This program simulates a basic library system where you can:
- Login & Register accounts
- View popular book list (e.g., Atomic Habits, Rich Dad Poor Dad, etc.)
- Borrow books
- Return books
- Admin can add or remove books

---

## 🔧 Installation (Linux Only)

Follow these steps to install and run the program on Linux:

### 1. Install GCC Compiler
```bash
sudo apt update
sudo apt install build-essential -y
gcc --version
```

### 2. Download the Project
```bash
git clone https://github.com/Chikochiii/SiPerpus.git
cd SiPerpus
```

Or just copy all files (`main.c`, `perpustakaan.c`, `perpustakaan.h`, `install.sh`, `README.md`) into one folder.

### 3. Run the Install Script
```bash
chmod +x install.sh
./install.sh
```

If successful, you will see:
```
✅ Installation complete!
```

### 4. Run the Program
```bash
./perpus
```

---

## ▶️ Usage

1. Run the program:
```
./perpus
```

2. Choose from the main menu:
   - Login (admin / user)
   - Register a new user
   - Exit program

3. Default **admin login**:
```
Username: admin
Password: admin
```

4. **User** can borrow and return books.  
   **Admin** can add or delete books.

---

## 📂 Project Structure

```
siperpus/
│── main.c
│── perpustakaan.c
│── perpustakaan.h
│── install.sh
│── README.md
```

---

## 🎯 Purpose

This project was made just for learning **C language** and simulating a simple library system.  
If you find bugs or errors, it’s normal since this is a beginner project :v.

---

## 📜 License

Free to use, modify, and share 👍

# SiPerpus
