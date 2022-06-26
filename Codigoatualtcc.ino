//BIBLIOTECAS MÓDULO DE MEMÓRIA 
#include <SdFat.h>

//DECLARAÇÕES MÓDULO DE MEMÓRIA
SdFat sdCard;
SdFile meuArquivo;
 
//PINO LIGADO AO CS DO MÓDULO SD
const int chipSelect = 53;


//PINO ANALOGICO UTILIZADO PARA O SENSOR SOLO 
#define pino_sinal_analogico1 A0
int valor_analogico1, a;

#define pino_sinal_analogico2 A1 
int valor_analogico2, b;

#define pino_sinal_analogico3 A2 
int valor_analogico3, c;
 
#define pino_sinal_analogico4 A3 
int valor_analogico4, d;

//DECLARAÇÃO DAS PORTAS PARA O MÓDULO RELÉ
// SOLO
int rele1 = 10;
int rele2 = 11; 

//TEMPO EM MINUTOS -- 1 MINUTO
unsigned long minuto_1 = 60000;
//int minuto_1 =  100;

void setup()
{
  //DEFINE O PINO RELÉ DO SOLO
  pinMode (rele1, OUTPUT);
  pinMode (rele2, OUTPUT);


  //DEFINE O PINO Solo
  pinMode(pino_sinal_analogico1, INPUT);
  pinMode(pino_sinal_analogico2, INPUT);
  pinMode(pino_sinal_analogico3, INPUT);
  pinMode(pino_sinal_analogico4, INPUT);

  Serial.begin(9600);
}

void loop()
{
 
  /****************************
  ******* SENSOR 01 ********
  ****************************/

  //LER O VALOR DO PINO A0 DO SENSOR
  a = analogRead(pino_sinal_analogico1);
  valor_analogico1 = (1023 - a); 

  Serial.print("VALOR DO SOLO1: ");
  Serial.println(valor_analogico1);
  
  //SOLO SECO
  if (valor_analogico1 > 0 && valor_analogico1 < 400)
  {
    delay(1000);
    //STATUS: SOLO SECO - IRRIGANDO POR 2 MINUTOS(120 SEGUNDOS)

    //GRAVAR DADOS NO ARQUIVO "dados.txt" 
    //INICIALIZA O MÓDULO SD
    if(!sdCard.begin(chipSelect,SPI_HALF_SPEED)){
      sdCard.initErrorHalt();
    }
    //ABERTURA DO ARQUIVO "dados.txt"
    if (!meuArquivo.open("dados.txt", O_RDWR | O_CREAT | O_AT_END))
    {
      sdCard.errorHalt("Erro na abertura do arquivo!");
    }
      
    //GRAVAR DADOS NO CARTÃO SD
    //UMIDADE DO SOLO
    meuArquivo.print("1,120,-999,-999,-999,-999,");meuArquivo.println(valor_analogico1);
    //FECHANDO ARQUIVO
    meuArquivo.close();
    
    digitalWrite(rele1, HIGH);
    delay(minuto_1*2);
    digitalWrite(rele1, LOW);
  }
 
  //SOLO COM UMIDADE MODERADA
  else if (valor_analogico1 >= 400 && valor_analogico1 < 800)
  {
    delay(1000);
    //STATUS: SOLO MODERADO - IRRIGANDO POR 1 MINUTO(60 SEGUNDOS)

    //GRAVAR DADOS NO ARQUIVO "dados.txt" 
    //INICIALIZA O MÓDULO SD
    if(!sdCard.begin(chipSelect,SPI_HALF_SPEED)){
      sdCard.initErrorHalt();
    }
    //ABERTURA DO ARQUIVO "dados.txt"
    if (!meuArquivo.open("dados.txt", O_RDWR | O_CREAT | O_AT_END))
    {
      sdCard.errorHalt("Erro na abertura do arquivo!");
    }
      
    //GRAVAR DADOS NO CARTÃO SD
    //UMIDADE DO SOLO
    meuArquivo.print("1,60,-999,-999,-999,-999,");meuArquivo.println(valor_analogico1);
    //FECHANDO ARQUIVO
    meuArquivo.close();
    
    digitalWrite(rele1, HIGH);
    delay(minuto_1);
    digitalWrite(rele1, LOW);
  }
 
  //SOLO UMIDO
  //(valor_analogico1 > 800 && valor_analogico1 < 1024)
  else 
  {
    delay(1000);
    //STATUS: SOLO SECO - SEM IRRIGAÇÃO  
    //GRAVAR DADOS NO ARQUIVO "dados.txt" 
    //INICIALIZA O MÓDULO SD
    if(!sdCard.begin(chipSelect,SPI_HALF_SPEED)){
      sdCard.initErrorHalt();
    }
    //ABERTURA DO ARQUIVO "dados.txt"
    if (!meuArquivo.open("dados.txt", O_RDWR | O_CREAT | O_AT_END))
    {
      sdCard.errorHalt("Erro na abertura do arquivo!");
    }
      
    //GRAVAR DADOS NO CARTÃO SD
    //UMIDADE DO SOLO
    meuArquivo.print("1,0,-999,-999,-999,-999,");meuArquivo.println(valor_analogico1);
    //FECHANDO ARQUIVO
    meuArquivo.close();
    
  }

  /****************************
  *******   SENSOR 02 ********
  ****************************/

  //LER O VALOR DO PINO A0 DO SENSOR
  b = analogRead(pino_sinal_analogico2);
  valor_analogico2 = (1023 - b); 

  Serial.print("VALOR DO SOLO2: ");
  Serial.println(valor_analogico2);
  
  //SOLO SECO
  if (valor_analogico2 > 0 && valor_analogico2 < 400)
  {
    delay(1000);
    //STATUS: SOLO SECO - IRRIGANDO POR 2 MINUTOS(120 SEGUNDOS)

    //GRAVAR DADOS NO ARQUIVO "dados.txt" 
    //INICIALIZA O MÓDULO SD
    if(!sdCard.begin(chipSelect,SPI_HALF_SPEED)){
      sdCard.initErrorHalt();
    }
    //ABERTURA DO ARQUIVO "dados.txt"
    if (!meuArquivo.open("dados.txt", O_RDWR | O_CREAT | O_AT_END))
    {
      sdCard.errorHalt( "Erro na abertura do arquivo!");
    }
      
    //GRAVAR DADOS NO CARTÃO SD
    //UMIDADE DO SOLO
    meuArquivo.print("2,120,-999,-999,-999,-999,");meuArquivo.println(valor_analogico2);
    //FECHANDO ARQUIVO
    meuArquivo.close();
    
    digitalWrite(rele2, HIGH);
    delay(minuto_1*2);
    digitalWrite(rele2, LOW);
  }
 
  //SOLO COM UMIDADE MODERADA 
  else if (valor_analogico2 >= 400 && valor_analogico2 < 800)
  {
    delay(1000);
    //STATUS: SOLO MODERADO - IRRIGANDO POR 1 MINUTO(60 SEGUNDOS)

    //GRAVAR DADOS NO ARQUIVO "dados.txt" 
    //INICIALIZA O MÓDULO SD
    if(!sdCard.begin(chipSelect,SPI_HALF_SPEED)){
      sdCard.initErrorHalt();
    }
    //ABERTURA DO ARQUIVO "dados.txt"
    if (!meuArquivo.open("dados.txt", O_RDWR | O_CREAT | O_AT_END))
     {
      sdCard.errorHalt("Erro na abertura do arquivo!");
    }
      
    //GRAVAR DADOS NO CARTÃO SD
    //UMIDADE DO SOLO
    meuArquivo.print("2,60,-999,-999,-999,-999,");meuArquivo.println(valor_analogico2);
    //FECHANDO ARQUIVO
    meuArquivo.close();
    
    digitalWrite(rele2, HIGH);
    delay(minuto_1);
    digitalWrite(rele2, LOW);
  }
 
  //SOLO UMIDO
  //(valor_analogico0 > 800 && valor_analogico0 < 1024)
  else 
  {
    delay(1000);
    //STATUS: SOLO SECO - SEM IRRIGAÇÃO  
    //GRAVAR DADOS NO ARQUIVO "dados.txt" 
    //INICIALIZA O MÓDULO SD
    if(!sdCard.begin(chipSelect,SPI_HALF_SPEED)){
      sdCard.initErrorHalt();
    }
    //ABERTURA DO ARQUIVO "dados.txt"
    if (!meuArquivo.open("dados.txt", O_RDWR | O_CREAT | O_AT_END))
    {
      sdCard.errorHalt("Erro na abertura do arquivo!");
    }
      
    //GRAVAR DADOS NO CARTÃO SD
    //UMIDADE DO SOLO
    meuArquivo.print("2,0,-999,-999,-999,-999,");meuArquivo.println(valor_analogico2);
    //FECHANDO ARQUIVO
    meuArquivo.close();
    
  }


  /****************************
  *******   SENSOR 03 ********
  ****************************/

  //LER O VALOR DO PINO A3 DO SENSOR
  c = analogRead(pino_sinal_analogico3);
  valor_analogico3 = (1023 - c); 

  Serial.print("VALOR DO SOLO3: ");
  Serial.println(valor_analogico3);
  
  //SOLO SECO
  if (valor_analogico3 > 0 && valor_analogico3 < 400)
  {
    delay(1000);
    //STATUS: SOLO SECO - IRRIGANDO POR 2 MINUTOS(120 SEGUNDOS)

    //GRAVAR DADOS NO ARQUIVO "dados.txt" 
    //INICIALIZA O MÓDULO SD
    if(!sdCard.begin(chipSelect,SPI_HALF_SPEED)){
      sdCard.initErrorHalt();
    }
    //ABERTURA DO ARQUIVO "dados.txt"
    if (!meuArquivo.open("dados.txt", O_RDWR | O_CREAT | O_AT_END))
    {
      sdCard.errorHalt( "Erro na abertura do arquivo!");
    }
      
    //GRAVAR DADOS NO CARTÃO SD
    //UMIDADE DO SOLO
    meuArquivo.print("3,120,-999,-999,-999,-999,");meuArquivo.println(valor_analogico3);
    //FECHANDO ARQUIVO
    meuArquivo.close();
    
  }
 
  //SOLO COM UMIDADE MODERADA 
  else if (valor_analogico3 >= 400 && valor_analogico3 < 800)
  {
    delay(1000);
    //STATUS: SOLO MODERADO - IRRIGANDO POR 1 MINUTO(60 SEGUNDOS)

    //GRAVAR DADOS NO ARQUIVO "dados.txt" 
    //INICIALIZA O MÓDULO SD
    if(!sdCard.begin(chipSelect,SPI_HALF_SPEED)){
      sdCard.initErrorHalt();
    }
    //ABERTURA DO ARQUIVO "dados.txt"
    if (!meuArquivo.open("dados.txt", O_RDWR | O_CREAT | O_AT_END))
     {
      sdCard.errorHalt("Erro na abertura do arquivo!");
    }
      
    //GRAVAR DADOS NO CARTÃO SD
    //UMIDADE DO SOLO
    meuArquivo.print("3,60,-999,-999,-999,-999,");meuArquivo.println(valor_analogico3);
    //FECHANDO ARQUIVO
    meuArquivo.close();
    
  }
 
  //SOLO UMIDO
  //(valor_analogico3 > 800 && valor_analogico3 < 1024)
  else 
  {
    delay(1000);
    //STATUS: SOLO SECO - SEM IRRIGAÇÃO  
    //GRAVAR DADOS NO ARQUIVO "dados.txt" 
    //INICIALIZA O MÓDULO SD
    if(!sdCard.begin(chipSelect,SPI_HALF_SPEED)){
      sdCard.initErrorHalt();
    }
    //ABERTURA DO ARQUIVO "dados.txt"
    if (!meuArquivo.open("dados.txt", O_RDWR | O_CREAT | O_AT_END))
    {
      sdCard.errorHalt("Erro na abertura do arquivo!");
    }
      
    //GRAVAR DADOS NO CARTÃO SD
    //UMIDADE DO SOLO
    meuArquivo.print("3,0,-999,-999,-999,-999,");meuArquivo.println(valor_analogico3);
    //FECHANDO ARQUIVO
    meuArquivo.close();
    
  }


  /****************************
  *******   SENSOR 04 ********
  ****************************/

  //LER O VALOR DO PINO A3 DO SENSOR
  d = analogRead(pino_sinal_analogico4);
  valor_analogico4 = (1023 - d); 

  Serial.print("VALOR DO SOLO4: ");
  Serial.println(valor_analogico4);
  
  //SOLO SECO
  if (valor_analogico4 > 0 && valor_analogico4 < 400)
  {
    delay(1000);
    //STATUS: SOLO SECO - IRRIGANDO POR 2 MINUTOS(120 SEGUNDOS)

    //GRAVAR DADOS NO ARQUIVO "dados.txt" 
    //INICIALIZA O MÓDULO SD
    if(!sdCard.begin(chipSelect,SPI_HALF_SPEED)){
      sdCard.initErrorHalt();
    }
    //ABERTURA DO ARQUIVO "dados.txt"
    if (!meuArquivo.open("dados.txt", O_RDWR | O_CREAT | O_AT_END))
    {
      sdCard.errorHalt( "Erro na abertura do arquivo!");
    }
      
    //GRAVAR DADOS NO CARTÃO SD
    //UMIDADE DO SOLO
    meuArquivo.print("4,120,-999,-999,-999,-999,");meuArquivo.println(valor_analogico4);
    //FECHANDO ARQUIVO
    meuArquivo.close();
 
  }
 
  //SOLO COM UMIDADE MODERADA 
  else if (valor_analogico4 >= 400 && valor_analogico4 < 800)
  {
    delay(1000);
    //STATUS: SOLO MODERADO - IRRIGANDO POR 1 MINUTO(60 SEGUNDOS)

    //GRAVAR DADOS NO ARQUIVO "dados.txt" 
    //INICIALIZA O MÓDULO SD
    if(!sdCard.begin(chipSelect,SPI_HALF_SPEED)){
      sdCard.initErrorHalt();
    }
    //ABERTURA DO ARQUIVO "dados.txt"
    if (!meuArquivo.open("dados.txt", O_RDWR | O_CREAT | O_AT_END))
     {
      sdCard.errorHalt("Erro na abertura do arquivo!");
    }
      
    //GRAVAR DADOS NO CARTÃO SD
    //UMIDADE DO SOLO
    meuArquivo.print("4,60,-999,-999,-999,-999,");meuArquivo.println(valor_analogico4);
    //FECHANDO ARQUIVO
    meuArquivo.close();
    
  }
 
  //SOLO UMIDO
  //(valor_analogico4 > 800 && valor_analogico4 < 1024)
  else 
  {
    delay(1000);
    //STATUS: SOLO SECO - SEM IRRIGAÇÃO  
    //GRAVAR DADOS NO ARQUIVO "dados.txt" 
    //INICIALIZA O MÓDULO SD
    if(!sdCard.begin(chipSelect,SPI_HALF_SPEED)){
      sdCard.initErrorHalt();
    }
    //ABERTURA DO ARQUIVO "dados.txt"
    if (!meuArquivo.open("dados.txt", O_RDWR | O_CREAT | O_AT_END))
    {
      sdCard.errorHalt("Erro na abertura do arquivo!");
    }
      
    //GRAVAR DADOS NO CARTÃO SD
    //UMIDADE DO SOLO
    meuArquivo.print("4,0,-999,-999,-999,-999,");meuArquivo.println(valor_analogico4);
    //FECHANDO ARQUIVO
    meuArquivo.close();
    
  }


  
  //PARANDO O SISTEMA POR 60 MINUTOS(1 HORA)
  //delay(minuto_1);
  delay(minuto_1*60);
}
