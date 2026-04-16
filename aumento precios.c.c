#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int codi;
    float precio;
    char descr[51];
}tPrecios;
int main()
{
    int i;
    float aum;
    tPrecios pre[5]={{110,350,"galletitas"},
                    {120,150,"alfajor"},
                    {130,500,"doritos"},
                    {140,200,"chocolate"},
                    {150,500,"gaseosa"}};
    FILE *arch;
    arch=fopen("Precios.dat","wb");
    if(arch==NULL)
    {
        printf("\nNo se pudo abrir archivo\n");
        system("pause");
        exit(1);
    }
    fwrite(&pre,sizeof(tPrecios),5,arch);
    fseek(arch,0,SEEK_SET);
    fclose(arch);
    arch=fopen("Precios.dat","r+b");
    if(arch==NULL)
    {
        printf("\nNo abrio el archivo\n");
        system("pause");
        exit(1);
    }
    printf("\nCOD:\tPRECIO:\tPRODUCTO:\n");
    fread(&pre,sizeof(pre),1,arch);
    while(!feof(arch))
    {
        for(i=0;i<5;i++)
        {
            printf("\n%d\t%.2f\t%s", pre[i].codi,pre[i].precio,pre[i].descr);
        }
        fread(&pre,sizeof(pre),1,arch);
    }
    fseek(arch,0,SEEK_SET);
    printf("\n\nAgregar cantidad de porcentaje de aumento: \n");
    scanf("%f",&aum);
    aum=aum/100;
    for(i=0;i<5;i++)
    {
        pre[i].precio=pre[i].precio+pre[i].precio*aum;
    }
    fwrite(&pre,sizeof(pre),1,arch);
    fflush(arch);
    fseek(arch,0,SEEK_SET);
    printf("\nSe le hizo un aumento de %.2f porciento a los productos\n",aum*100);
    printf("\nCOD:\tPRECIO:\tPRODUCTO:\n");

    fread(&pre,sizeof(pre),1,arch);
    while(!feof(arch))
    {
        for(i=0;i<5;i++)
        {
            printf("\n%d\t%.2f\t%s",pre[i].codi,pre[i].precio,pre[i].descr);
        }
        fread(&pre,sizeof(pre),1,arch);
    }
    fseek(arch,0,SEEK_SET);
    fclose(arch);
    printf("\n\n\n");
    return 0;
}
