#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    int age;
} Student;

void writeToFile(Student students[], int size);

int readFromFile(Student students[]);

void displayAllStudents(Student students[], int size); 

void addStudent(Student students[], int *size); 
    
void editStudent(Student students[], int size);

void deleteStudent(Student students[], int *size);

void searchStudent(Student students[], int size);

void sortStudents(Student students[], int size); 
    
int main() {
    Student students[100];
    int size = readFromFile(students);

    int choice;
    do {
        printf("\nMENU\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayAllStudents(students, size);
                break;
            case 2:
                addStudent(students, &size);
                break;
            case 3:
                editStudent(students, size);
                break;
            case 4:
                deleteStudent(students, &size);
                break;
            case 5:
                searchStudent(students, size);
                break;
            case 6:
                sortStudents(students, size);
                break;
            case 7:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (choice != 7);
    
    return 0;
}
writeToFile(Student students[], int size){
	FILE *file = fopen("students.bin", "wb");
    if (file == NULL) {
        printf("Khong the mo file de ghi.\n");
        return;
    }
    fwrite(students, sizeof(Student), size, file);
    fclose(file);
}

readFromFile(Student students[]){
	FILE *file = fopen("students.bin", "rb");
    int count = 0;
    while (fread(&students[count], sizeof(Student), 1, file)) {
        count++;
    }
    fclose(file);
    return count;
}

displayAllStudents(Student students[], int size){
	for (int i = 0; i < size; i++) {
        printf("%d %s %d\n", students[i].id, students[i].name, students[i].age);
    }
}

addStudent(Student students[], int *size){
	if (*size >= 100) {
        printf("Danh sach sinh vien da day.\n");
        return;
    }
    Student newStudent;
    printf("Nhap ID: ");
    scanf("%d", &newStudent.id);
    getchar();
    printf("Nhap ten sinh vien: ");
    fgets(newStudent.name, sizeof(newStudent.name), stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0;
    printf("Nhap tuoi: ");
    scanf("%d", &newStudent.age);

    students[*size] = newStudent;
    (*size)++;
    writeToFile(students, *size);
}

editStudent(Student students[], int size){
	int id;
    printf("Nhap ID sinh vien can sua: ");
    scanf("%d", &id);
    for (int i = 0; i < size; i++) {
        if (students[i].id == id) {
            printf("Nhap ten moi: ");
            getchar();
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;
            printf("Nhap tuoi moi: ");
            scanf("%d", &students[i].age);
            writeToFile(students, size);
            printf("Thong tin sinh vien da duoc cap nhat.\n");
            return;
        }
    }
    printf("Sinh vien voi ID %d khong tim thay.\n", id);
}

deleteStudent(Student students[], int *size){
	int id;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);
    for (int i = 0; i < *size; i++) {
        if (students[i].id == id) {
            for (int j = i; j < *size - 1; j++) {
                students[j] = students[j + 1];
            }
            (*size)--;
            writeToFile(students, *size);
            printf("Sinh vien voi ID %d da bi xoa.\n", id);
            return;
        }
    }
    printf("Sinh vien voi ID %d khong tim thay.\n", id);
}

searchStudent(Student students[], int size){
	char name[50];
    printf("Nhap ten sinh vien can tim: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < size; i++) {
        if (strstr(students[i].name, name) != NULL) {
            printf("Sinh vien tim thay: ID: %d, Ten: %s, Tuoi: %d\n", students[i].id, students[i].name, students[i].age);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong tim thay sinh vien.\n");
    }
}

sortStudents(Student students[], int size){
	for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (strcmp(students[i].name, students[j].name) > 0) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    writeToFile(students, size);
    printf("Danh sach sinh vien da duoc sap xep theo ten.\n");
}
