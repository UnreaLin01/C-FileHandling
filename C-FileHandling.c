#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

//���o�ؼи�ƥi�������̤j��
int getDataMaxPosition(char filePath[]){
    int maxPosition;
    FILE *file = fopen(filePath, "r");
    if(file != NULL){
        fseek(file, 0, SEEK_END);
        //ftell()�i���o�ثe��������m
        maxPosition = ftell(file);
        fclose(file);
        return maxPosition;
    }else{
        printf("Can't open the target file\n");
        return -1;
    }
    
}

//�H�мg���覡�󥿸��
void correctData(char filePath[], int position, char data[]){
    int sucess = 0;
    if(position <= getDataMaxPosition(filePath)){
        FILE *file = fopen(filePath, "r+");
        if(fseek(file, position, SEEK_SET) == 0){
            fprintf(file, "%s", data);
            fclose(file);
            sucess = 1;
        }
    }else{
        printf("Can't located to the require position\n");
    }
}

//�H���J���覡�󥿸��
void insertData(char filePath[], int position, char data[]){
    if(position < getDataMaxPosition(filePath)){
        FILE *file = fopen(filePath, "r+");
        FILE *fileTemp = fopen("./temp.txt", "w+");

        if(fseek(file, position, SEEK_SET) == 0){
            char temp[10000] = {0};
            int tempDataLength = 0;
            int x = 0;

            while(fgets(temp, 10000, file) != NULL){
                fprintf(fileTemp,"%s", temp);
            }

            //���o���ɮץi�������̤j��
            fseek(fileTemp, 0, SEEK_END);
            tempDataLength = ftell(fileTemp);
            
            //�N���ɮװ�����m�᪺��ƥ��ƲM��
            fseek(file, position, SEEK_SET);
            for(x = 0; x < tempDataLength; x++){
                fprintf(file, "\b");
            }
            
            //�N�n�g�J����Ʃ�J������m
            fseek(file, position, SEEK_SET);
            fprintf(file, "%s", data);

            //�N�쥻������m�᪺��Ʊq�Ȧs�ɥ[�^��
            fseek(fileTemp, 0, SEEK_SET);
            while(fgets(temp, 10000, fileTemp) != NULL){
                fprintf(file, "%s", temp);
            }
        }
        fclose(file);
        fclose(fileTemp);
    }else{
        printf("Can't located to the require position\n");
    }
}

//�b���̧�M�S�w���r��
void searchWord(char filePath[], char keyword[]){
    FILE *file = fopen(filePath, "r+");
    if(file != NULL){
        char key[10000] = {0};
        char temp[10000] = {0};
        int x = 0;

        strcpy(key, keyword);
        for(x = 0; x < strlen(keyword); x++){
            int temp = 0;
            temp = tolower(keyword[x]);
            key[x] = temp;

        }
        while(fscanf(file, "%s", temp) != EOF){
            printf("%d\n", strcmp(keyword, temp));
        }
        fclose(file);
    }else{
        printf("Can't open the target file\n");
    }
}

//��X���Ҧ����r��
void printWord(char filePath[]){
    FILE *file = fopen(filePath, "r+");
    if(file != NULL){
        char temp[10000] = {0};
        while(fscanf(file, "%s", temp) != EOF){
            printf("%s\n", temp);
        }
    }else{
        printf("Can't open the target file\n");
    }

    
}

void main(){
    printf("%d\n",getDataMaxPosition("./data.txt"));
    printWord("./data.txt");
    //correctData("./data.txt", 20, "the string you want to correct");
    //insertData("./data.txt", 20, "the string you want to insert");
    //searchWord();

}

