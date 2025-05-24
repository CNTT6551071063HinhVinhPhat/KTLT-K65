#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SinhVien {
    int mssv;
    char hoten[50];
    float diemtb;
    char lop[10];
    struct SinhVien* next;
} SinhVien;

SinhVien* addSinhVien(int mssv, char* hoten, float diemtb, char* lop) {
    SinhVien* sv = (SinhVien*)malloc(sizeof(SinhVien));
    if (sv == NULL) {
        printf("Cap phat bo nho that bai!\n");
        return NULL;
    }
    sv->mssv = mssv;
    strcpy(sv->hoten, hoten);
    sv->diemtb = diemtb;
    strcpy(sv->lop, lop);
    sv->next = NULL;
    return sv;
}

void themSinhVien(SinhVien** head, int mssv, char* hoten, float diemtb, char* lop) {
    SinhVien* sv = addSinhVien(mssv, hoten, diemtb, lop);
    sv->next = *head;
    *head = sv;
}

void hienThiDanhSach(SinhVien* head) {
    if (head == NULL) {
        printf("Danh sach sinh vien trong!\n");
        return;
    }
    printf("\nDanh sach sinh vien:\n");
    printf("%-10s | %-20s | %-10s | %-10s\n", "MSSV", "Ho ten", "Diem TB", "Lop");
    while (head != NULL) {
        printf("%-10d | %-20s | %-10.2f | %-10s\n", head->mssv, head->hoten, head->diemtb, head->lop);
        head = head->next;
    }
}

void xoaSinhVien(SinhVien** head, int mssv) {
    SinhVien* temp = *head, *prev = NULL;

    if (temp != NULL && temp->mssv == mssv) {
        *head = temp->next;
        free(temp);
        printf("Da xoa sinh vien co MSSV: %d\n", mssv);
        return;
    }

    while (temp != NULL && temp->mssv != mssv) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Khong tim thay sinh vien co MSSV: %d\n", mssv);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Da xoa sinh vien co MSSV: %d\n", mssv);
}

void sapXepTangDan(SinhVien** head) {
    if (*head == NULL || (*head)->next == NULL)
        return;

    SinhVien *i, *j;
    for (i = *head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->diemtb > j->diemtb) {
                int tempMSSV = i->mssv;
                char tempHoten[50], tempLop[10];
                float tempDiem = i->diemtb;

                strcpy(tempHoten, i->hoten);
                strcpy(tempLop, i->lop);

                i->mssv = j->mssv;
                strcpy(i->hoten, j->hoten);
                strcpy(i->lop, j->lop);
                i->diemtb = j->diemtb;

                j->mssv = tempMSSV;
                strcpy(j->hoten, tempHoten);
                strcpy(j->lop, tempLop);
                j->diemtb = tempDiem;
            }
        }
    }
    printf("Danh sach da duoc sap xep theo diem tang dan!\n");
    hienThiDanhSach(*head);
}

void sapXepGiamDan(SinhVien** head) {
    if (*head == NULL || (*head)->next == NULL)
        return;

    SinhVien *i, *j;
    for (i = *head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->diemtb < j->diemtb) {
                int tempMSSV = i->mssv;
                char tempHoten[50], tempLop[10];
                float tempDiem = i->diemtb;

                strcpy(tempHoten, i->hoten);
                strcpy(tempLop, i->lop);

                i->mssv = j->mssv;
                strcpy(i->hoten, j->hoten);
                strcpy(i->lop, j->lop);
                i->diemtb = j->diemtb;

                j->mssv = tempMSSV;
                strcpy(j->hoten, tempHoten);
                strcpy(j->lop, tempLop);
                j->diemtb = tempDiem;
            }
        }
    }
    printf("Danh sach da duoc sap xep theo diem giam dan!\n");
    hienThiDanhSach(*head);
}

void ghiFile(SinhVien* head, char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Mo file de ghi that bai!\n");
        return;
    }
    while (head != NULL) {
        fprintf(fp, "%d,%s,%.2f,%s\n", head->mssv, head->hoten, head->diemtb, head->lop);
        head = head->next;
    }
    fclose(fp);
    printf("Da ghi danh sach vao file: %s\n", filename);
}

void docFile(SinhVien** head, char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Mo file de doc that bai!\n");
        return;
    }
    int mssv;
    char hoten[50], lop[10];
    float diemtb;
    while (fscanf(fp, "%d,%49[^,],%f,%9s", &mssv, hoten, &diemtb, lop) != EOF) {
        themSinhVien(head, mssv, hoten, diemtb, lop);
    }
    fclose(fp);
    printf("Da doc danh sach tu file: %s\n", filename);
}

void thongKeTheoLop(SinhVien* head) {
    if (head == NULL) {
        printf("Danh sach sinh vien trong!\n");
        return;
    }
    char cacLop[100][10];
    int soLuong[100] = {0};
    int lopCount = 0;
    SinhVien* temp = head;
    while (temp != NULL) {
        int daTonTai = 0;
        for (int i = 0; i < lopCount; i++) {
            if (strcmp(cacLop[i], temp->lop) == 0) {
                soLuong[i]++;
                daTonTai = 1;
                break;
            }
        }
        if (!daTonTai) {
            strcpy(cacLop[lopCount], temp->lop);
            soLuong[lopCount] = 1;
            lopCount++;
        }
        temp = temp->next;
    }
    printf("\nThong ke sinh vien theo lop:\n");
    for (int i = 0; i < lopCount; i++) {
        printf("Lop: %s - So sinh vien: %d\n", cacLop[i], soLuong[i]);
    }
}

SinhVien* timSinhVien(SinhVien* head, int mssv) {
    while (head != NULL) {
        if (head->mssv == mssv)
            return head;
        head = head->next;
    }
    return NULL;
}

void chinhSuaSinhVien(SinhVien* head, int mssv) {
    SinhVien* sv = timSinhVien(head, mssv);
    if (sv == NULL) {
        printf("Khong tim thay sinh vien co MSSV: %d\n", mssv);
        return;
    }
    printf("Nhap ho ten moi: ");
    fgets(sv->hoten, sizeof(sv->hoten), stdin);
    sv->hoten[strcspn(sv->hoten, "\n")] = '\0';
    
    printf("Nhap diem trung binh moi: ");
    scanf("%f", &sv->diemtb);
    getchar();
    
    printf("Nhap lop moi: ");
    fgets(sv->lop, sizeof(sv->lop), stdin);
    sv->lop[strcspn(sv->lop, "\n")] = '\0';
    
    printf("Da cap nhat thong tin sinh vien!\n");
}

int main() {
    SinhVien* danhSach = NULL;
    int choice, mssv;
    char hoten[50], lop[10];
    float diemtb;
    char filename[50] = "sinhvien.txt";
    
    do {
        printf("\n===== QUAN LY SINH VIEN =====\n");
        printf("1: Them sinh vien\n");
        printf("2: Xoa sinh vien\n");
        printf("3: Hien thi danh sach\n");
        printf("4: Sap xep theo diem tang dan\n");
        printf("5: Sap xep theo diem giam dan\n");
        printf("6: Ghi danh sach vao file\n");
        printf("7: Doc danh sach tu file\n");
        printf("8: Thong ke sinh vien theo lop\n");
        printf("9: Tim sinh vien theo MSSV\n");
        printf("10: Chinh sua thong tin sinh vien\n");
        printf("11: Thoat\n");
        printf("Chon: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                printf("Nhap MSSV: ");
                scanf("%d", &mssv);
                getchar();
                printf("Nhap ho ten: ");
                fgets(hoten, sizeof(hoten), stdin);
                hoten[strcspn(hoten, "\n")] = '\0';
                printf("Nhap diem trung binh: ");
                scanf("%f", &diemtb);
                getchar();
                printf("Nhap lop: ");
                fgets(lop, sizeof(lop), stdin);
                lop[strcspn(lop, "\n")] = '\0';
                themSinhVien(&danhSach, mssv, hoten, diemtb, lop);
                break;
            case 2:
                printf("Nhap MSSV de xoa: ");
                scanf("%d", &mssv);
                getchar();
                xoaSinhVien(&danhSach, mssv);
                break;
            case 3:
                hienThiDanhSach(danhSach);
                break;
            case 4:
                sapXepTangDan(&danhSach);
                break;
            case 5:
                sapXepGiamDan(&danhSach);
                break;
            case 6:
                ghiFile(danhSach, filename);
                printf("Ghi file thanh cong");
                break;
            case 7:
                docFile(&danhSach, filename);
                break;
            case 8:
                thongKeTheoLop(danhSach);
                break;
            case 9:
            {
                printf("Nhap MSSV can tim: ");
                scanf("%d", &mssv);
                getchar();
                SinhVien* sv = timSinhVien(danhSach, mssv);
                if (sv != NULL) {
                    printf("\nThong tin sinh vien:\n");
                    printf("MSSV: %d\n", sv->mssv);
                    printf("Ho ten: %s\n", sv->hoten);
                    printf("Diem TB: %.2f\n", sv->diemtb);
                    printf("Lop: %s\n", sv->lop);
                } else {
                    printf("Khong tim thay sinh vien co MSSV: %d\n", mssv);
                }
            }
                break;
            case 10:
                printf("Nhap MSSV cua sinh vien can chinh sua: ");
                scanf("%d", &mssv);
                getchar();
                chinhSuaSinhVien(danhSach, mssv);
                break;
            case 11:
                printf("Thoat chuong trinh thanh cong!\n");
                break;
            default:
                printf("Lua chon khong hop le!Vui long chi chon tu 1 den 11\n");
        }
    } while (choice != 11);
    
    return 0;
}

