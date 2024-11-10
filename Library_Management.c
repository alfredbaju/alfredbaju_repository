#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Book {
int id;
char title[50];
char author[50];
int publicationYear;
struct Book* next;
};
struct Book* head = NULL;
void addBook(int id, char* title, char* author, int
publicationYear) {
struct Book* newBook = (struct
Book*)malloc(sizeof(struct Book));
newBook->id = id;
strcpy(newBook->title, title);
strcpy(newBook->author, author);
newBook->publicationYear = publicationYear;
newBook->next = head;
head = newBook;
}
void displayBooks() {
struct Book* ptr = head;
while (ptr != NULL) {
printf("ID: %d, Title: %s, Author: %s, Publication Year:
%d\n"
, ptr->id, ptr->title, ptr->author, ptr->publicationYear);
ptr = ptr->next;
}
}
struct Book* searchBook(int id) {
struct Book* ptr = head;
while (ptr != NULL) {
if (ptr->id == id) {
return ptr;
}
ptr = ptr->next;
}
return NULL;
}
void deleteBook(int id) {
struct Book* ptr = head;
struct Book* prev = NULL;
while (ptr != NULL && ptr->id != id) {
prev = ptr;
ptr = ptr->next;
}
if (ptr == NULL) {
printf("Book not found!\n");
return;
}
if (prev == NULL) {
head = ptr->next;
} else {
prev->next = ptr->next;
}
free(ptr);
printf("Book deleted!\n");
}
void saveToFile(const char* filename) {
FILE* file = fopen(filename,
"w");
if (file == NULL) {
printf("Could not open file for writing!\n");
return;
}
struct Book* ptr = head;
while (ptr != NULL) {
fprintf(file,
"%d,%s,%s,%d\n"
, ptr->id, ptr->title, ptr-
>author, ptr->publicationYear);
ptr = ptr->next;
}
fclose(file);
printf("Data saved to file.\n");
}
void loadFromFile(const char* filename) {
FILE* file = fopen(filename,
"r");
if (file == NULL) {
printf("Could not open file for reading!\n");
return;
}
while (!feof(file)) {
struct Book* newBook = (struct
Book*)malloc(sizeof(struct Book));
fscanf(file,
"%d,%49[^
,],%49[^
,],%d\n"
, &newBook->id,
newBook->title, newBook->author, &newBook-
>publicationYear);
newBook->next = head;
head = newBook;
}
fclose(file);
printf("Data loaded from file.\n");
}
void menu() {
int choice, id, publicationYear;
char title[50], author[50];
while (1) {
printf("\nLibrary Management System\n");
printf("1. Add Book\n");
printf("2. Delete Book\n");
printf("3. Search Book\n");
printf("4. List All Books\n");
printf("5. Save to File\n");
printf("6. Load from File\n");
printf("7. Exit\n");
printf("Enter your choice: ");
scanf("%d"
, &choice);
switch (choice) {
case 1:
printf("Enter book ID: ");
scanf("%d"
, &id);
printf("Enter book title: ");
scanf(" %[^\n]%*c"
, title);
printf("Enter book author: ");
scanf(" %[^\n]%*c"
, author);
printf("Enter publication year: ");
scanf("%d"
, &publicationYear);
addBook(id, title, author, publicationYear);
break;
case 2:
printf("Enter book ID to delete: ");
scanf("%d"
, &id);
deleteBook(id);
break;
case 3:
printf("Enter book ID to search: ");
scanf("%d"
, &id);
struct Book* book = searchBook(id);
if (book != NULL) {
printf("Found: ID: %d, Title: %s, Author: %s,
Publication Year: %d\n"
, book->id, book->title, book->author,
book->publicationYear);
} else {
printf("Book not found!\n");
}
break;
case 4:
displayBooks();
break;
case 5:
saveToFile("library.txt");
break;
case 6:
loadFromFile("library.txt");
break;
case 7:
exit(0);
default:
printf("Invalid choice! Please try again.\n");
}
}
}
int main() {
loadFromFile("library.txt");
menu();
saveToFile("library.txt");
return 0;
}