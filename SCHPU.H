#define DC1 0x11
#define DC2 0x12
#define DC3 0x13
#define DC4 0x14
#define ACK 0x06
#define ABORT 0x03
#define CR 0x0D
#define LF 0x0A
#define DATA_READY 0x100

int OUTPORT(char);
void NPort(void); 
void SaveConf(void);
void LoadConf(void);
int Rabchpu(void);
int Upprog(void);
void DIR(char *, int);
void INPUT(char *, char *, int);
void OUTPUT(char *, char *, char *, int);
void DELET(char *, char *, int);
void REMOV(char *, char *, char *, int);
void CREAT(char *, char *, char *, char *, int);
void Podup(void);
void Podkach(void);
void Podcon(void);
void Config(void);
void Neprpod(void);
