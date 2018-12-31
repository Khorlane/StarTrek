// StarTrek by Steve Bryant (2014-12-31)
// 
// Influenced by
// "STAR TREK: BY MIKE MAYFIELD, CENTERLINE ENGINEERING"
// "TOTAL INTERACTION GAME - ORIG. 20 OCT 1972"
// which was extracted from HP tape image 16-Nov-2003 by Pete Turnbull
// and, of course, StarTrek TOS (The Original Series)
//
// It's the Enterprise NCC-1701 against 9 Klingon Battle Cruisers
// The Galaxy is a 10,10 sector matrix
// Navigation is by x,y coordinates, e.g. 2,7 5,1 etc
// The Galaxy is: char Galaxy[100] with index ranging from 0 to 99
//  x,y  = Index
//  1,1  =  0
//  5,5  = 44
// 10,10 = 99
// To covert Row,Col to a linear index use:
// Row * 10 - 10 + Col - 1
//  1  * 10 - 10 +  1  - 1 =  10 - 10 +  1 - 1 =  0 +  1 - 1 =   1 - 1 =  0
//  5  * 10 - 10 +  5  - 1 =  50 - 10 +  5 - 1 = 40 +  5 - 1 =  45 - 1 = 44
// 10  * 10 - 10 + 10  - 1 = 100 - 10 + 10 - 1 = 90 + 10 - 1 = 100 - 1 = 99

// Includes
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Global Variables  
char Buf[BUFSIZ];
char Cmd;
int  Energy;
int  EnterpriseCol;
int  EnterpriseIdx;
int  EnterpriseRow;
char Galaxy[100];
int  GalaxyRow;
int  GalaxyCol;
char GameRun;
char QuitForSure;
int  Shields;
int  Torpedoes;

// GamePlay Functions
void SetCourse(void);
void ShortRangeSensorScan(void);
void LongRangeSensorScan(void);
void FirePhasers(void);
void FirePhotonTorpedoes(void);
void ShieldControl(void);
void LibraryComputer(void);
void SelfDestruct(void);
void Quit(void);

// Initialization Functions
void SetTheStage(void);

// Helper Functions
void GetCmd(void);
void GetInput(void);
int  GetRandom(int Max);
void Menu(void);
void SeedRandom(void);
void ShowEnterprise(void);

int main(int argc, char *argv[])
{
  GameRun     = 'Y';
  QuitForSure = 'N';
  SetTheStage();
  while (GameRun == 'Y')
  {
    if (!(Cmd >= '1' && Cmd <= '9'))
    {
      Menu();
      GetCmd();
    }
    switch (Cmd)
    {
      case '1' :
        Cmd = ' ';
        SetCourse();
        break;
      case '2' :
        Cmd = ' ';
        ShortRangeSensorScan();
        break;
      case '3' :
        Cmd = ' ';
        LongRangeSensorScan();
        break;
      case '4' :
        Cmd = ' ';
        FirePhasers();
        break;
      case '5' :
        Cmd = ' ';
        FirePhotonTorpedoes();
        break;
      case '6' :
        Cmd = ' ';
        ShieldControl();
        break;
      case '7' :
        Cmd = ' ';
        LibraryComputer();
        break;
      case '8' :
        Cmd = ' ';
        SelfDestruct();
        break;
      case '9' :
        Cmd = ' ';
        Quit();
        if (QuitForSure == 'Y')
        {
          GameRun = 'N';
        }
        break;
      default:
        printf("\nPlease enter 1-9!\n");
    }
  }
}

void Menu(void)
{
  printf("\n");
  printf("1. Set Course\n");
  printf("2. Short Range Sensor Scan\n");
  printf("3. Long  Range Sensor Scan\n");
  printf("4. Fire Phasers\n");
  printf("5. Fire Photon Torpedoes\n");
  printf("6. Shield Control\n");
  printf("7. Library Computer\n");
  printf("8. Self Destruct\n");
  printf("9. Quit\n");
  printf("\n");
  printf("Command? ");
}

void SetCourse(void)
{
  int  a, b, c, i, j;
  char x [3];
  char y [3];
  char BadCoordinate;

  printf("\n");
  printf("**************\n");
  printf("* Set Course *\n");
  printf("**************\n");
  printf("\n");
  printf("Enter coordinates as x,y\n");
  GetInput();
  i = 0;
  j = 0;
  while (Buf[i] != ',')
  {
    x[j] = Buf[i];
    i++;
    j++;
  }
  x[j] = '\0';
  i++;
  j = 0;
  while (Buf[i] != '\0')
  {
    y[j] = Buf[i];
    i++;
    j++;
  }
  y[j] = '\0';
  GalaxyRow = atoi(x);
  GalaxyCol = atoi(y);
  BadCoordinate = 'N';
  if (GalaxyRow < 0 || GalaxyRow > 10)
  {
    printf("\nInvalid x coordinate\n");
    BadCoordinate = 'Y';
  }
  if (GalaxyCol < 0 || GalaxyCol > 10)
  {
    printf("\nInvalid y coordinate\n");
    BadCoordinate = 'Y';
  }
  if (BadCoordinate == 'Y')
  {
    return;
  }
  i = GalaxyRow * 10 - 10 + GalaxyCol - 1;
  if (Galaxy[i] != ' ')
  {
    printf("That sector is occupied\n");
    GetCmd();
    return;
  }
  a = abs(GalaxyRow - EnterpriseRow);
  b = abs(GalaxyCol - EnterpriseCol);
  c = (int)sqrt((float)(a*a + b*b));
  c = c * 50;
  if (c > Energy)
  {
    printf("Not enough energy, move aborted\n");
    GetCmd();
    return;
  }
  printf("Energy used: %i\n",c);
  Energy = Energy - c;
  Galaxy[EnterpriseIdx] = ' ';
  EnterpriseIdx = i;
  Galaxy[EnterpriseIdx] = 'E';
  EnterpriseRow = GalaxyRow;
  EnterpriseCol = GalaxyCol;
  ShowEnterprise();
  GetCmd();
}

void ShortRangeSensorScan(void)
{
  int i;
  char s1,s2,s3;
  char s4,s5,s6;
  char s7,s8,s9;

  if (Energy < 25)
  {
    printf("Not enough energy to perform scan\n");
    GetCmd();
    return;
  }
  Energy = Energy - 25;
  i = EnterpriseIdx;
  s1 = Galaxy[i-11];
  s2 = Galaxy[i-10];
  s3 = Galaxy[i-9];
  s4 = Galaxy[i-1];
  s5 = Galaxy[i];
  s6 = Galaxy[i+1];
  s7 = Galaxy[i+9];
  s8 = Galaxy[i+10];
  s9 = Galaxy[i+11];
  if (EnterpriseRow == 1)
  {
    s1 = '-';
    s2 = '-';
    s3 = '-';
  }
  if (EnterpriseRow == 10)
  {
    s7 = '-';
    s8 = '-';
    s9 = '-';
  }
  if (EnterpriseCol == 1)
  {
    s1 = '-';
    s4 = '-';
    s7 = '-';
  }
  if (EnterpriseCol == 10)
  {
    s3 = '-';
    s6 = '-';
    s9 = '-';
  }
  printf("\n");
  printf("***************************\n");
  printf("* Short Range Sensor Scan *\n");
  printf("***************************\n");
  printf("\n");
  printf("* * * * * * *\n");
  printf("* %c * %c * %c *\n", s1, s2, s3);
  printf("* * * * * * *\n");
  printf("* %c * %c * %c *\n", s4, s5, s6);
  printf("* * * * * * *\n");
  printf("* %c * %c * %c *\n", s7, s8, s9);
  printf("* * * * * * *\n");
  ShowEnterprise();
  GetCmd();
}

void LongRangeSensorScan(void)
{ 
  int i;
  char s1, s2, s3, s4, s5;
  char s6, s7, s8, s9, s10;
  char s11,s12,s13,s14,s15;
  char s16,s17,s18,s19,s20;
  char s21,s22,s23,s24,s25;
  
  if (Energy < 50)
  {
    printf("Not enough energy to perform scan\n");
    GetCmd();
    return;
  }
  Energy = Energy - 50;
  i   = EnterpriseIdx;
  s1  = Galaxy[i-22];
  s2  = Galaxy[i-21];
  s3  = Galaxy[i-20];
  s4  = Galaxy[i-19];
  s5  = Galaxy[i-18];
  s6  = Galaxy[i-12];
  s7  = Galaxy[i-11];
  s8  = Galaxy[i-10];
  s9  = Galaxy[i-9];
  s10 = Galaxy[i-8];
  s11 = Galaxy[i-2];
  s12 = Galaxy[i-1];
  s13 = Galaxy[i];
  s14 = Galaxy[i+1];
  s15 = Galaxy[i+2];
  s16 = Galaxy[i+8];
  s17 = Galaxy[i+9];
  s18 = Galaxy[i+10];
  s19 = Galaxy[i+11];
  s20 = Galaxy[i+12];
  s21 = Galaxy[i+18];
  s22 = Galaxy[i+19];
  s23 = Galaxy[i+20];
  s24 = Galaxy[i+21];
  s25 = Galaxy[i+22];
  if (EnterpriseRow == 1)
  {
    s1  = '-';
    s2  = '-';
    s3  = '-';
    s4  = '-';
    s5  = '-';
    s6  = '-';
    s7  = '-';
    s8  = '-';
    s9  = '-';
    s10 = '-';
  }
  if (EnterpriseRow == 2)
  {
    s1 = '-';
    s2 = '-';
    s3 = '-';
    s4 = '-';
    s5 = '-';
  }
  if (EnterpriseRow == 9)
  {
    s21 = '-';
    s22 = '-';
    s23 = '-';
    s24 = '-';
    s25 = '-';
  }
  if (EnterpriseRow == 10)
  {
    s16 = '-';
    s17 = '-';
    s18 = '-';
    s19 = '-';
    s20 = '-';
    s21 = '-';
    s22 = '-';
    s23 = '-';
    s24 = '-';
    s25 = '-';
  }
  if (EnterpriseCol == 1)
  {
    s1  = '-';
    s6  = '-';
    s11 = '-';
    s16 = '-';
    s21 = '-';
    s2  = '-';
    s7  = '-';
    s12 = '-';
    s17 = '-';
    s22 = '-';
  }
  if (EnterpriseCol == 2)
  {
    s1  = '-';
    s6  = '-';
    s11 = '-';
    s16 = '-';
    s21 = '-';
  }
  if (EnterpriseCol == 9)
  {
    s5  = '-';
    s10 = '-';
    s15 = '-';
    s20 = '-';
    s25 = '-';
  }
  if (EnterpriseCol == 10)
  {
    s4  = '-';
    s9  = '-';
    s14 = '-';
    s19 = '-';
    s24 = '-';
    s5  = '-';
    s10 = '-';
    s15 = '-';
    s20 = '-';
    s25 = '-';
  }
  printf("\n");
  printf("**************************\n");
  printf("* Long Range Sensor Scan *\n");
  printf("**************************\n");
  printf("\n");
  printf("* * * * * * * * * * *\n");
  printf("* %c * %c * %c * %c * %c *\n", s1,  s2,  s3,  s4,  s5);
  printf("* * * * * * * * * * *\n");
  printf("* %c * %c * %c * %c * %c *\n", s6,  s7,  s8,  s9,  s10);
  printf("* * * * * * * * * * *\n");
  printf("* %c * %c * %c * %c * %c *\n", s11, s12, s13, s14, s15);
  printf("* * * * * * * * * * *\n");
  printf("* %c * %c * %c * %c * %c *\n", s16, s17, s18, s19, s20);
  printf("* * * * * * * * * * *\n");
  printf("* %c * %c * %c * %c * %c *\n", s21, s22, s23, s24, s25);
  printf("* * * * * * * * * * *\n");
  ShowEnterprise();
  GetCmd();
}

void FirePhasers(void)
{
  printf("\n");
  printf("****************\n");
  printf("* Fire Phasers *\n");
  printf("****************\n");
  printf("\n");
  GetInput();
}

void FirePhotonTorpedoes(void)
{
  printf("\n");
  printf("*************************\n");
  printf("* Fire Photon Torpedoes *\n");
  printf("*************************\n");
  printf("\n");
  GetInput();
}

void ShieldControl(void)
{
  char c;
  char FromTo;
  int  Amount;

  printf("\n");
  printf("******************\n");
  printf("* Shield Control *\n");
  printf("******************\n");
  printf("\n");
  ShowEnterprise();
  c = ' ';
  while (!(c == 't' || c == 'T' || c == 'f' || c == 'F'))
  {
    printf("Transfer To or From Shields? T-F\n");
    GetInput();
    c = Buf[0];
  }
  FromTo = c;
  printf("How much energy do you wish to transfer?\n");
  GetInput();
  Amount = atoi(Buf);
  if (FromTo == 't' || FromTo == 'T')
  {
    if (Amount > Energy)
    {
      printf("You don't have that much energy\n");
      GetCmd();
      return;
    }
    Shields = Shields + Amount;
    Energy  = Energy  - Amount;
  }  if (FromTo == 'f' || FromTo == 'F')
  {
    if (Amount > Shields)
    {
      printf("You don't have that much energy in the shields\n");
      GetCmd();
      return;
    }
    Shields = Shields - Amount;
    Energy  = Energy  + Amount;
  }
  printf("Transfer complete\n");
  ShowEnterprise();
  GetCmd();
}

void LibraryComputer(void)
{
  printf("\n");
  printf("********************\n");
  printf("* Library Computer *\n");
  printf("********************\n");
  printf("\n");
  GetInput();
}

void SelfDestruct(void)
{
  printf("\n");
  printf("*****************\n");
  printf("* Self Destruct *\n");
  printf("*****************\n");
  printf("\n");
  GetInput();
}

void Quit(void)
{
  printf("Are you sure? Y-N\n");
  GetInput();
  if (Buf[0] == 'Y')
  {
    QuitForSure = 'Y';
    printf("\nGood-bye\n\n");
    printf("Hit enter\n");
    GetInput();
  }
}

//****************************//
//* Initialization Functions *//
//****************************//
void SetTheStage(void)
{
  int  i;
  int  k;
  char Placed;
  
  SeedRandom();
  Energy    = 10000;
  Shields   = 0;
  Torpedoes = 5;
  // Clear the Galaxy
  for (i = 0; i < 100; i++)
  {
    Galaxy[i] = ' ';
  }
  // Place the Enterprise
  i = GetRandom(100);
  Galaxy[i] = 'E';
  EnterpriseIdx = i;
  EnterpriseRow = ((int)(i / 10)) + 1;
  EnterpriseCol = i - ((EnterpriseRow - 1) * 10) + 1;
  // Thar be Kingons
  for (k = 1; k < 10; k++)
  {
    Placed = 'N';
    while (Placed == 'N')
    {
      i = GetRandom(100);
      if (Galaxy[i] == ' ')
      {
        Galaxy[i] = 'K';
        Placed = 'Y';
      }
    }
  }
}

//********************//
//* Helper Functions *//
//********************//
void GetCmd(void)
{
  GetInput();
  Cmd = Buf[0];
}

void GetInput(void)
{
  char *p;

  if (fgets(Buf, sizeof(Buf), stdin) != NULL)
  {
    if ((p = strchr(Buf, '\n')) != NULL)
    {
      *p = '\0';
    }
  }
}

int GetRandom(int Max)
{
  int x;
  x = rand() % Max;
  return x;
}

void SeedRandom(void)
{
  srand((unsigned int)time(NULL));
}

void ShowEnterprise(void)
{
  printf("The Enterprise is at: %i,%i\n",EnterpriseRow,EnterpriseCol);
  printf("Energy %i\n",Energy);
  printf("Shields %i\n",Shields);
  printf("Torpedoes %i\n",Torpedoes);
}