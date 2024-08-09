#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAC_GIA 100
#define MAX_NXB 100

typedef struct Book {
    char maSach[20];
    char tenSach[100];
    char tenTacGia[50];
    char nhaXuatBan[50];
    int namXuatBan;
    char theLoai[30];
    struct Book* next;
} Book;

typedef struct NXB {
    char tenNXB[50];
    int soLuong;
    struct NXB* next;
} NXB;

typedef struct TacGia {
    char tenTacGia[50];
    NXB nxb[MAX_NXB];
    int soLuongNXB;
} TacGia;

typedef struct NamXuatBan {
    int nam;
    int soLuong;
    struct NamXuatBan* next;
} NamXuatBan;

typedef struct NXB_ThongKe {
    char tenNXB[50];
    NamXuatBan* dsNamXuatBan;
    struct NXB_ThongKe* next;
} NXB_ThongKe;

typedef struct TheLoai {
    char tenTheLoai[30];
    int soLuong;
    struct TheLoai* next;
} TheLoai;


void nhapThongTinSach(Book* book) {
    printf("Nhap ma sach: ");
    scanf("%s", book->maSach);
    printf("Nhap ten sach: ");
    scanf(" %[^\n]", book->tenSach);
    printf("Nhap ten tac gia: ");
    scanf(" %[^\n]", book->tenTacGia);
    printf("Nhap nha xuat ban: ");
    scanf(" %[^\n]", book->nhaXuatBan);
    printf("Nhap nam xuat ban: ");
    scanf("%d", &book->namXuatBan);
    printf("Nhap the loai: ");
    scanf(" %[^\n]", book->theLoai);
}

void hienThiThongTinSach(const Book* book) {
    printf("%-20s %-30s %-20s %-20s %-10d %-15s\n", book->maSach, book->tenSach, book->tenTacGia, book->nhaXuatBan, book->namXuatBan, book->theLoai);
}

void hienThiDanhSachSach(Book* head) {
    printf("%-20s %-30s %-20s %-20s %-10s %-15s\n", "Ma Sach", "Ten Sach", "Ten Tac Gia", "Nha Xuat Ban", "Nam XB", "The Loai");
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    Book* temp = head;
    while (temp != NULL) {
        hienThiThongTinSach(temp);
        temp = temp->next;
    }
}

void themSachDauDanhSach(Book** head) {
    Book* newBook = (Book*)malloc(sizeof(Book));
    nhapThongTinSach(newBook);
    newBook->next = *head;
    *head = newBook;
}

void themSachCuoiDanhSach(Book** head) {
    Book* newBook = (Book*)malloc(sizeof(Book));
    nhapThongTinSach(newBook);
    newBook->next = NULL;

    if (*head == NULL) {
        *head = newBook;
    }
    else {
        Book* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBook;
    }
}

void themSachGiuaDanhSach(Book** head, int viTri) {
    if (viTri <= 0) {
        themSachDauDanhSach(head);
        return;
    }

    Book* newBook = (Book*)malloc(sizeof(Book));
    nhapThongTinSach(newBook);

    Book* temp = *head;
    for (int i = 0; temp != NULL && i < viTri - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Vi tri khong hop le, them sach vao cuoi danh sach.\n");
        themSachCuoiDanhSach(head);
    }
    else {
        newBook->next = temp->next;
        temp->next = newBook;
    }
}

void xoaSachDauDanhSach(Book** head) {
    if (*head == NULL) {
        printf("Danh sach rong.\n");
        return;
    }

    Book* temp = *head;
    *head = (*head)->next;
    free(temp);
}

void xoaSachCuoiDanhSach(Book** head) {
    if (*head == NULL) {
        printf("Danh sach rong.\n");
        return;
    }

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    Book* temp = *head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }

    free(temp->next);
    temp->next = NULL;
}

void xoaSachGiuaDanhSach(Book** head, int viTri) {
    if (*head == NULL) {
        printf("Danh sach rong.\n");
        return;
    }

    if (viTri <= 0) {
        xoaSachDauDanhSach(head);
        return;
    }

    Book* temp = *head;
    for (int i = 0; temp != NULL && i < viTri - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Vi tri khong hop le.\n");
        return;
    }

    Book* nodeToDelete = temp->next;
    temp->next = temp->next->next;
    free(nodeToDelete);
}


void ghiDanhSachSachVaoFile(Book* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Khong the mo file de ghi");
        return;
    }

    Book* temp = head;
    while (temp != NULL) {
        fprintf(file, "%s\n%s\n%s\n%s\n%d\n%s\n", temp->maSach, temp->tenSach, temp->tenTacGia, temp->nhaXuatBan, temp->namXuatBan, temp->theLoai);
        temp = temp->next;
    }

    fclose(file);
}

void docDanhSachSachTuFile(Book** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Khong the mo file de doc");
        return;
    }

    while (!feof(file)) {
        Book* newBook = (Book*)malloc(sizeof(Book));
        if (fscanf(file, "%s\n%[^\n]\n%[^\n]\n%[^\n]\n%d\n%[^\n]\n", newBook->maSach, newBook->tenSach, newBook->tenTacGia, newBook->nhaXuatBan, &newBook->namXuatBan, newBook->theLoai) == 6) {
            newBook->next = NULL;
            if (*head == NULL) {
                *head = newBook;
            }
            else {
                Book* temp = *head;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newBook;
            }
        }
        else {
            free(newBook);
            break;
        }
    }

    fclose(file);
}

int demSoLuongSach(Book* head) {
    int count = 0;
    Book* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

void chuyenDanhSachThanhMang(Book* head, Book** array) {
    int index = 0;
    Book* temp = head;
    while (temp != NULL) {
        array[index++] = temp;
        temp = temp->next;
    }
}

int soSanhTheoTheLoaiVaMaSach(const void* a, const void* b) {
    Book* bookA = *(Book**)a;
    Book* bookB = *(Book**)b;

    int theLoaiCmp = strcmp(bookA->theLoai, bookB->theLoai);
    if (theLoaiCmp == 0) {
        return strcmp(bookA->maSach, bookB->maSach);
    }
    return theLoaiCmp;
}

void chuyenMangThanhDanhSach(Book** array, int n, Book** head) {
    if (n == 0) return;

    *head = array[0];
    Book* current = *head;
    for (int i = 1; i < n; i++) {
        current->next = array[i];
        current = current->next;
    }
    current->next = NULL;
}

void sapXepDanhSach(Book** head) {
    int n = demSoLuongSach(*head);
    if (n == 0) return;

    Book** array = (Book**)malloc(n * sizeof(Book*));
    chuyenDanhSachThanhMang(*head, array);

    qsort(array, n, sizeof(Book*), soSanhTheoTheLoaiVaMaSach);

    chuyenMangThanhDanhSach(array, n, head);

    free(array);
}

void themSachTheoThuTu(Book** head) {
    Book* newBook = (Book*)malloc(sizeof(Book));
    nhapThongTinSach(newBook);
    newBook->next = NULL;

    if (*head == NULL || soSanhTheoTheLoaiVaMaSach(&newBook, head) <= 0) {
        newBook->next = *head;
        *head = newBook;
    }
    else {
        Book* temp = *head;
        while (temp->next != NULL && soSanhTheoTheLoaiVaMaSach(&temp->next, &newBook) < 0) {
            temp = temp->next;
        }
        newBook->next = temp->next;
        temp->next = newBook;
    }
}

void thongKeSachTheoTacGiaVaNXB(Book* head) {
    TacGia tacGia[MAX_TAC_GIA];
    int soLuongTacGia = 0;

    Book* temp = head;
    while (temp != NULL) {
        int foundTacGia = 0;
        for (int i = 0; i < soLuongTacGia; i++) {
            if (strcmp(tacGia[i].tenTacGia, temp->tenTacGia) == 0) {
                int foundNXB = 0;
                for (int j = 0; j < tacGia[i].soLuongNXB; j++) {
                    if (strcmp(tacGia[i].nxb[j].tenNXB, temp->nhaXuatBan) == 0) {
                        tacGia[i].nxb[j].soLuong++;
                        foundNXB = 1;
                        break;
                    }
                }
                if (!foundNXB) {
                    strcpy(tacGia[i].nxb[tacGia[i].soLuongNXB].tenNXB, temp->nhaXuatBan);
                    tacGia[i].nxb[tacGia[i].soLuongNXB].soLuong = 1;
                    tacGia[i].soLuongNXB++;
                }
                foundTacGia = 1;
                break;
            }
        }
        if (!foundTacGia) {
            strcpy(tacGia[soLuongTacGia].tenTacGia, temp->tenTacGia);
            strcpy(tacGia[soLuongTacGia].nxb[0].tenNXB, temp->nhaXuatBan);
            tacGia[soLuongTacGia].nxb[0].soLuong = 1;
            tacGia[soLuongTacGia].soLuongNXB = 1;
            soLuongTacGia++;
        }
        temp = temp->next;
    }

    for (int i = 0; i < soLuongTacGia; i++) {
        printf("Tac gia: %s\n", tacGia[i].tenTacGia);
        for (int j = 0; j < tacGia[i].soLuongNXB; j++) {
            printf("\tNXB: %s - So luong: %d\n", tacGia[i].nxb[j].tenNXB, tacGia[i].nxb[j].soLuong);          
        }
        printf("\n");
    }
}

void demSoLuongSachNhaXuatBan(Book* head, NXB** dsNXB) {
    Book* temp = head;
    while (temp != NULL) {
        NXB* nxbTemp = *dsNXB;
        int found = 0;
        while (nxbTemp != NULL) {
            if (strcmp(nxbTemp->tenNXB, temp->nhaXuatBan) == 0) {
                nxbTemp->soLuong++;
                found = 1;
                break;
            }
            nxbTemp = nxbTemp->next;
        }

        if (!found) {
            NXB* newNXB = (NXB*)malloc(sizeof(NXB));
            strcpy(newNXB->tenNXB, temp->nhaXuatBan);
            newNXB->soLuong = 1;
            newNXB->next = *dsNXB;
            *dsNXB = newNXB;
        }

        temp = temp->next;
    }
}

void timNhaXuatBanItSachNhat(NXB* dsNXB) {
    if (dsNXB == NULL) {
        printf("Khong co nha xuat ban nao trong danh sach.\n");
        return;
    }

    NXB* minNXB = dsNXB;
    NXB* temp = dsNXB->next;
    while (temp != NULL) {
        if (temp->soLuong < minNXB->soLuong) {
            minNXB = temp;
        }
        temp = temp->next;
    }

    printf("Nha xuat ban co it sach nhat la: %s voi %d quyen sach.\n", minNXB->tenNXB, minNXB->soLuong);
}

void themHoacCapNhatNamXuatBan(NamXuatBan** dsNamXuatBan, int nam) {
    NamXuatBan* temp = *dsNamXuatBan;
    while (temp != NULL) {
        if (temp->nam == nam) {
            temp->soLuong++;
            return;
        }
        temp = temp->next;
    }

    // Nếu năm chưa tồn tại, thêm mới
    NamXuatBan* newNamXuatBan = (NamXuatBan*)malloc(sizeof(NamXuatBan));
    newNamXuatBan->nam = nam;
    newNamXuatBan->soLuong = 1;
    newNamXuatBan->next = *dsNamXuatBan;
    *dsNamXuatBan = newNamXuatBan;
}


void thongKeSachTheoNamXuatBan(Book* head) {
    NXB_ThongKe* dsNXBThongKe = NULL;

    Book* temp = head;
    while (temp != NULL) {
        NXB_ThongKe* nxbTemp = dsNXBThongKe;
        int found = 0;

        while (nxbTemp != NULL) {
            if (strcmp(nxbTemp->tenNXB, temp->nhaXuatBan) == 0) {
                themHoacCapNhatNamXuatBan(&(nxbTemp->dsNamXuatBan), temp->namXuatBan);
                found = 1;
                break;
            }
            nxbTemp = nxbTemp->next;
        }

        if (!found) {
            NXB_ThongKe* newNXBThongKe = (NXB_ThongKe*)malloc(sizeof(NXB_ThongKe));
            strcpy(newNXBThongKe->tenNXB, temp->nhaXuatBan);
            newNXBThongKe->dsNamXuatBan = NULL;
            themHoacCapNhatNamXuatBan(&(newNXBThongKe->dsNamXuatBan), temp->namXuatBan);
            newNXBThongKe->next = dsNXBThongKe;
            dsNXBThongKe = newNXBThongKe;
        }

        temp = temp->next;
    }

    // Hiển thị kết quả thống kê
    NXB_ThongKe* nxbTemp = dsNXBThongKe;
    while (nxbTemp != NULL) {
        printf("Nha xuat ban: %s\n", nxbTemp->tenNXB);
        NamXuatBan* namTemp = nxbTemp->dsNamXuatBan;
        while (namTemp != NULL) {
            printf("\tNam: %d - So luong: %d\n", namTemp->nam, namTemp->soLuong);
            namTemp = namTemp->next;
        }
        nxbTemp = nxbTemp->next;
    }

    // Giải phóng bộ nhớ
    while (dsNXBThongKe != NULL) {
        nxbTemp = dsNXBThongKe;
        dsNXBThongKe = dsNXBThongKe->next;
        while (nxbTemp->dsNamXuatBan != NULL) {
            NamXuatBan* namTemp = nxbTemp->dsNamXuatBan;
            nxbTemp->dsNamXuatBan = nxbTemp->dsNamXuatBan->next;
            free(namTemp);
        }
        free(nxbTemp);
    }
}

void themHoacCapNhatTheLoai(TheLoai** dsTheLoai, const char* theLoai) {
    TheLoai* temp = *dsTheLoai;
    while (temp != NULL) {
        if (strcmp(temp->tenTheLoai, theLoai) == 0) {
            temp->soLuong++;
            return;
        }
        temp = temp->next;
    }

    // Nếu không tìm thấy thể loại, tạo mới và thêm vào danh sách
    TheLoai* newTheLoai = (TheLoai*)malloc(sizeof(TheLoai));
    strcpy(newTheLoai->tenTheLoai, theLoai);
    newTheLoai->soLuong = 1;
    newTheLoai->next = *dsTheLoai;
    *dsTheLoai = newTheLoai;
}

void thongKeSoLuongSachTheoTheLoai(Book* head) {
    TheLoai* dsTheLoai = NULL;
    Book* temp = head;
    while (temp != NULL) {
        themHoacCapNhatTheLoai(&dsTheLoai, temp->theLoai);
        temp = temp->next;
    }

    // Hiển thị kết quả thống kê
    TheLoai* theLoaiTemp = dsTheLoai;
    while (theLoaiTemp != NULL) {
        printf("%s - So luong: %d\n", theLoaiTemp->tenTheLoai, theLoaiTemp->soLuong);
        TheLoai* toFree = theLoaiTemp;
        theLoaiTemp = theLoaiTemp->next;
        free(toFree);
    }
}

void timVaXuatThongTinSach(Book* head, const char* keyword, const char* nxb1, const char* nxb2) {
    int count = 0;
    Book* temp = head;
    printf("%-20s %-30s %-20s %-20s %-10s %-15s\n", "Ma Sach", "Ten Sach", "Ten Tac Gia", "Nha Xuat Ban", "Nam XB", "The Loai");
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    while (temp != NULL) {
        if (strstr(temp->tenSach, keyword) != NULL &&
            (strcmp(temp->nhaXuatBan, nxb1) == 0 || strcmp(temp->nhaXuatBan, nxb2) == 0)) {
            hienThiThongTinSach(temp);
            count++;
        }
        temp = temp->next;
    }
    printf("Tong so luong sach co chua chuoi '%s' do %s va %s xuat ban: %d\n", keyword, nxb1, nxb2, count);
}


void menu(Book** head) {
    int luaChon;
    const char* filename = "books.txt";

    do {
        printf("\nChuong trinh quan ly sach\n");
        printf("1. Nhap thong tin sach (dau danh sach)\n");
        printf("2. Nhap thong tin sach (cuoi danh sach)\n");
        printf("3. Nhap thong tin sach (vi tri giua danh sach)\n");
        printf("4. Xoa sach (dau danh sach)\n");
        printf("5. Xoa sach (cuoi danh sach)\n");
        printf("6. Xoa sach (vi tri giua danh sach)\n");
        printf("7. Hien thi thong tin sach\n");
        printf("8. Ghi danh sach sach vao file (books.txt)\n");
        printf("9. Doc danh sach sach tu file (books.txt)\n");
        printf("10. Sap xep danh sach\n");
        printf("11. Them sach theo thu tu\n");
        printf("12. Thong ke sach theo tac gia va NXB\n");
        printf("13. Tim nha xuat ban co it sach nhat\n");
        printf("14. Thong ke sach theo nam xuat ban cua NXB\n");
        printf("15. Dem so luong sach theo tung the loai\n");
        printf("16. Tim va dem sach chua chuoi 'lap trinh' do NXB DHQG va NXB KHKT xuat ban\n");
        printf("17. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &luaChon);

        int viTri;
        switch (luaChon) {
        case 1:
            themSachDauDanhSach(head);
            break;
        case 2:
            themSachCuoiDanhSach(head);
            break;
        case 3:
            printf("Nhap vi tri: ");
            scanf("%d", &viTri);
            themSachGiuaDanhSach(head, viTri);
            break;
        case 4:
            xoaSachDauDanhSach(head);
            break;
        case 5:
            xoaSachCuoiDanhSach(head);
            break;
        case 6:
            printf("Nhap vi tri: ");
            scanf("%d", &viTri);
            xoaSachGiuaDanhSach(head, viTri);
            break;
        case 7:
            hienThiDanhSachSach(*head);
            break;
        case 8:
            ghiDanhSachSachVaoFile(*head, filename);
            break;
        case 9:
            docDanhSachSachTuFile(head, filename);
            break;
        case 10:
            sapXepDanhSach(head);
            break;
        case 11:
            themSachTheoThuTu(head);
            break;
        case 12:
            thongKeSachTheoTacGiaVaNXB(*head);
            break;
        case 13: {
            NXB* dsNXB = NULL;
            demSoLuongSachNhaXuatBan(*head, &dsNXB);
            timNhaXuatBanItSachNhat(dsNXB);

            // Giai phong bo nho cho danh sach nha xuat ban
            NXB* temp;
            while (dsNXB != NULL) {
                temp = dsNXB;
                dsNXB = dsNXB->next;
                free(temp);
            }
            break;
        }
        case 14:
            thongKeSachTheoNamXuatBan(*head);
            break;
        case 15:
            printf("So luong sach cua tung the loai:\n");
            thongKeSoLuongSachTheoTheLoai(*head);
            break;
        case 16:
            timVaXuatThongTinSach(*head, "Lap Trinh", "NXB DHQG", "NXB KHKT");
            break;
        case 17:
            printf("Thoat chuong trinh.\n");
            break;

        default:
            printf("Lua chon khong hop le. Vui long thu lai.\n");
            break;
        }
    } while (luaChon != 17);
}

int main() {
    Book* head = NULL;

    // Vao menu chinh
    menu(&head);

    // Giai phong bo nho
    Book* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
