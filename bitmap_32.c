/******************* Sistemas Operativos II ***************************/
/***** Alumno: <Cuenta> <Nombre>            ***************************/ 
/***** Tomar en cuenta lo siguiente         ***************************/
/***** *) No se soporta operaciones con bits***************************/
/*
Ejemplo: vamos a pasar a binario 7910
79       1 (impar). Dividimos entre dos:
39       1 (impar). Dividimos entre dos:
19       1 (impar). Dividimos entre dos:
9        1  (impar). Dividimos entre dos:
4        0 (par). Dividimos entre dos:
2        0 (par). Dividimos entre dos:
1        1 (impar).

Por tanto, 79 = 1001111

Binario a Decimal
1001111
=2^0 + 2^1 + 2^3 + 2^4 + 0 + 0 + 2^6 = 79 
*/
/**********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

char *commandList[] = {"print", "write", "read", "get_next", "set_busy", "set_free", "exit"};
const char* FILE_BITMAP = "bitmap32.bin";
/* TODO: 1. Init constants **/
#define BITMAP_SIZE 512 //Numero de elementos int del arreglo que representa el BITMAP
const int BLOCK_SIZE = 512; //Size del bloque en bytes
const int BITS_PER_WORD = 32; //Seize del entero (word) en bits
/******************************/


int BITMAP[BITMAP_SIZE]; // Asignar valores random al arreglo

void printBITMAP();
char *int2bin(int t_value);
int getFreeBlock();
void setBlockBusy(int t_block);
void setBlockFree(int t_block);

//Funciones adicionales
void parseCommand(char *cmd);
void writeBITMAP();
void readBITMAP();

int main(int argc, char *argv[])
{
  char cmd[200];
  int i = 0;
  readBITMAP();

  while (1)
  {
    printf("\r\nCommand>");
    fgets(cmd, 200, stdin);
    if (!strcmp(cmd, "exit\n"))
      break;
    parseCommand(cmd);
  }
}

void parseCommand(char *cmd)
{

  char m_command[200];
  char m_param1[200];

  char *ptr;

  ptr = strtok(cmd, " \n");

  if (ptr != NULL)
    strcpy(m_command, ptr);

  ptr = strtok(NULL, " \n");
  if (ptr != NULL)
    strcpy(m_param1, ptr);

  int i = 7;
  while (i--)
  {
    if (!strcmp(m_command, commandList[i]))
    {
      int arg;
      if (!strcmp("get_next", m_command))
	getFreeBlock();

      if (!strcmp("print", m_command))
        printBITMAP();

      if (!strcmp("set_busy", m_command))
        setBlockBusy(atoi(m_param1));

      if (!strcmp("set_free", m_command))
        setBlockFree(atoi(m_param1));

      if (!strcmp("write", m_command))
        writeBITMAP();

      if (!strcmp("read", m_command))
        readBITMAP();
    }
  }
}


void printBITMAP()
{
  int m_count = BITMAP_SIZE;
  int i = 0;
  int m_res;
  char *m_item;

  for (i = 0; i < m_count; i++)
  {
    m_item = int2bin(BITMAP[i]);
    printf("%s\r\n", m_item);    
  }
  printf("\r\n");
}


char *int2bin(int t_value)
{
  //TODO: 2. retornar la repesentacion del entero en binario
  char *s=malloc(BITS_PER_WORD+1);
  s[BITS_PER_WORD]='\0';
  int i;
  uint8_t mask=1<<(BITS_PER_WORD);
  for(i=0;i<BITS_PER_WORD;i++,mask>>=1)
    s[i]=((t_value &mask)==0) ? '0' : '1';

return s;
}


int getFreeBlock()
{
  //TODO 3. Obtener el siguiente bloque libre (Primero con valor 0)
    int bloques_ocupados;
    int primer_bit;
    int x;
    int y;
    for(x=0;x<512;x++){
        if(BITMAP[x]==0){
            bloques_ocupados=x;
        }
    }
    for(y=0;y<8;y++){
        if((BITMAP[bloques_ocupados]>>y&1)==1){
            primer_bit=y;break;
        }
    }
    int resultado=8*bloques_ocupados+primer_bit;
    return(resultado);
}



void setBlockBusy(int t_block)
{
  //TODO 4. Marcar el bloque como ocupado (Valor = 1)
    int b=floor(t_block/8);
    int numero_bloque=t_block%8;
    BITMAP[b]&=~(1<<numero_bloque);
}

void setBlockFree(int t_block)
{
  //TODO 5. Marcar el bloque como libre (Valor = 0)
    int b=floor(t_block/8);
    int numero_bloque=t_block%8;
    BITMAP[b]|=1<<numero_bloque;   
}

//funcion que almacena el bitmap en un archivo, es necesario ejecutar el comando write
void writeBITMAP()
{
  FILE *fptr;
  if ((fptr = fopen(FILE_BITMAP, "wb")) == NULL)
  {
    printf("Error abriendo el archivo %s", FILE_BITMAP);
    return;
  }

  fwrite(&BITMAP, sizeof(BITMAP), 1, fptr);
  fclose(fptr);
  printf("BITMAP escrito satisfactoriamente ...");
}

//funcion que almacena el bitmap en un archivo, es necesario ejecutar el comando write
void readBITMAP()
{
  FILE *fptr;
  if ((fptr = fopen(FILE_BITMAP, "rb")) == NULL)
  {
    printf("Error abriendo el archivo %s", FILE_BITMAP);
    return;
  }

  fread(&BITMAP, sizeof(BITMAP), 1, fptr);
  fclose(fptr);
  printf("BITMAP leido satisfactoriamente ...");
}
