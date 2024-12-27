#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct SinhVien{
	char id[50];
	char name[50];
	int age;
};
struct SinhVien sv[100];
int numberStudent=0;//Dem so du lieu sv da nhap vao
//Ham lay du lieu tu file.
void getFile();
//Ham them sinh vien 
void addIntoFile();
//Ham sua thong tin sinh vien
void updateFile();
//Ham xoa thong tin sv 
void deleteFile();
//Ham tim kiem sinh vien
void findFile(); 
//Ham sap xep sinh vien
void sortFile(); 

int main(){
	int choice;
	
	do{
		printf("\n\t MENU \t\n");
		printf("1. In danh sach sinh vien\n");
		printf("2. Them sinh vien\n");
		printf("3. Sua thong tin sinh vien\n");
		printf("4. Xoa thong tin sinh vien\n");
		printf("5. Tim kiem sinh vien\n");
		printf("6. Sap xem sinh vien\n");
		printf("7. Thoat\n");
		printf("\tLua chon cua ban: ");
		scanf("%d", &choice);
		fflush(stdin); 
		switch(choice){
			case 1:
				//In danh sach sinh vien 
				getFile();
				break;
			case 2:
				//Them sinh vien vao file
				addIntoFile();
				break;
			case 3:
				updateFile();
				break;
			case 4:
				deleteFile();
				break;
			case 5:
				findFile(); 
				break;
			case 6:
				sortFile();
				break;
			case 7:
				printf("Thoat!!!!");
				exit(0);
				break;
				
		}
		
	}while(1);
	
	

	return 0;
}
//doc du lieu tu file 
void getFile(){
	//mo file
	FILE *fptr = fopen("danhsachsinhvien.bin", "rb");
	//thao tac voi file
	numberStudent = fread(&sv, sizeof(struct SinhVien), 100, fptr);

	fclose(fptr);
	if(numberStudent==0){
		printf("Danh sach sinh vien rong!");
		return;
	}else{
		for (int i=0; i < numberStudent; i++){
			printf("\n\nThong tin sinh vien thu %d: ", i+1);
			printf("\nid: %s", sv[i].id);
			printf("\nTen sinh vien: %s", sv[i].name);
			printf("\nTuoi: %d", sv[i].age);
		}
	}
	
}



//Them sinh vien
void addIntoFile(){
	
	if (numberStudent>=100){
		printf("Danh sach sinh vien da day!!");
		return;
	}
	struct SinhVien sv1;
	printf("Thong tin sinh vien: ");
	fflush(stdin);
	printf("\nid: ");
	fgets(sv1.id, 50, stdin);
	sv1.id[strlen(sv1.id)-1] = '\0';
	fflush(stdin);
	printf("Ten sinh vien: %s", sv1.name);
	fgets(sv1.name, 50, stdin);
	sv1.name[strlen(sv1.name)-1] = '\0';
	printf("Tuoi: ", sv1.age);
	scanf("%d",&sv1.age);
	
	numberStudent++;
	
	FILE *fptr = fopen("danhsachsinhvien.bin", "ab");
	fwrite( &sv1,sizeof(sv1), 1, fptr);
	fclose(fptr);
	printf("Them sinh vien thanh cong!!");	
}


void updateFile(){
	char check[20];
	int index, temp=0;
	printf("Moi nhap id sinh vien muon sua: ");
	fgets(check, 20, stdin);
	check[strlen(check)-1]='\0';
	for(int i=0; i<numberStudent; i++){
		if(strcmp(check, sv[i].id)==0){
			index = i;
			temp=1;
		}
	}
	if(temp==0){
		printf("Sinh vien khong ton tai !");
	}else{
		printf("Nhap ten Sinh vien: ");
		fgets(sv[index].name, 50, stdin);
		sv[index].name[strlen(sv[index].name)-1]='\0'; 
		printf("Nhap tuoi: ");
		scanf("%d", &sv[index].age);
		
		FILE *file = fopen("danhsachsinhvien.bin", "wb");
			if(file==NULL){
				printf("Loi khong mo duoc file ");
				return;
			}	
		fwrite(&sv,sizeof(struct SinhVien),numberStudent, file);
		fclose(file);
	}
	
	
	
}


void deleteFile(){
	char check[20];
	int index, temp=0;
	printf("Moi nhap id sinh vien muon xoa: ");
	fgets(check, 20, stdin);
	check[strlen(check)-1]='\0';
	for(int i=0; i<numberStudent; i++){
		if(strcmp(check, sv[i].id)==0){
			index = i;
			temp=1;
		}
	}
	if(temp==0){
		printf("Sinh vien khong ton tai !");
	}else{
		for(int i=index;i<numberStudent;i++ ){
			sv[i] = sv[i+1]; 
		}
		numberStudent--; 
				
//		printf("Nhap ten Sinh vien: ");
//		fgets(sv[index].name, 50, stdin);
//		sv[index].name[strlen(sv[index].name)-1]='\0'; 
//		printf("Nhap tuoi: ");
//		scanf("%d", &sv[index].age);		

		FILE *file = fopen("danhsachsinhvien.bin", "wb");
		if(file==NULL){
			printf("Loi khong mo duoc file ");
			return;
		}
		fwrite(&sv,sizeof(struct SinhVien),numberStudent, file);
		fclose(file);
	}
}



//Ham tim kiem sinh vien 
void findFile(){
	char search[20];
	int index=0, temp=0;
	FILE *file = fopen("danhsachsinhvien.bin", "rb");
	if(file==NULL){
		printf("Loi khong mo duoc file ");
		return;
	}
	printf("Moi nhap id sinh vien muon tim: ");
	fgets(search, 20, stdin);
	search[strlen(search) - 1]='\0';
	for(int i=0; i<numberStudent; i++){
		if(strcmp(search, sv[i].id)==0){
			index = i;
			temp=1;
		}
	}
	if(temp==0){
		printf("Khong tim thay!");
	}else{
		printf("Da tim thay: ");
		printf("\nid: %s", sv[index].id);
		printf("\nTen: %s", sv[index].name);
		printf("\nTuoi: %d", sv[index].age);
	}
}



//Ham sap xep sinh vien 
void sortFile(){
	
	FILE *fptr = fopen("danhsachsinhvien.bin", "rb");
	
	if(fptr==NULL){
		printf("Loi khong mo duoc file ");
		return;
	}
	struct SinhVien temp;
	for(int i=0; i<numberStudent; i++){
		for(int j=0; j<numberStudent-1-i; j++){
			if(sv[j].age>sv[j+1].age){
				temp = sv[j];
				sv[j] = sv[j+1];
				sv[j+1] = temp;
			}
		}
	}
	
	for(int i=0; i<numberStudent; i++){
		printf("\nId: %s", sv[i].id);
		printf("\nTen: %s", sv[i].name);
		printf("\nTuoi: %d", sv[i].age);
		
	}
	fclose(fptr);
	
}



