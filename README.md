# Student-Management-system-SMS-
This project is a simple, menu-driven Student Management System (SMS) written in C, designed to practice structured programming, dynamic memory allocation, file handling, and modular code organization. The program allows users to create, modify, delete, display, save, and load student records using an interactive console interface.
At its core, the system uses a struct Students data type, which stores essential information about each student—name, age, marks, and gender. The program dynamically manages an array of these structures using malloc and realloc, letting the user expand or shrink the list of students at runtime. This approach avoids fixed-size arrays, giving the program flexibility and making memory management a key learning focus.

A set of helper functions ensures that each field is entered correctly. These include get_name, get_age, get_marks, and get_gender, each of which validates input to prevent invalid or out-of-range data from being stored. This validation improves reliability and guards against common input mistakes such as negative values or unsupported characters.

The main functional operations are organized into separate functions:

add_records: Extends the current list by allocating more memory and collecting new student details.

display_records: Prints all stored students in a nicely formatted style.

save_records: Saves the complete student list to a binary file (records.dat) for persistent storage.

load_records: Loads previously saved records by reading the binary file and reallocating memory accordingly.

delete_record: Searches for a student by name, removes the entry, and resizes the memory block.

modify_record: Locates a student and updates the stored details.


The program is controlled through a simple menu that loops until the user chooses to exit. Each option calls the appropriate function and responds with clear feedback, ensuring a smooth user experience.

Overall, this Student Management System serves as a strong introductory project for anyone learning C programming. It covers important concepts such as pointers, dynamic arrays, string handling, file I/O, and program modularity. Its straightforward structure makes it easy to understand, customize, and expand into a more advanced system in the future.
