//-------------- Arduino --------------

// Connections
// Arduino:           
//                                Serial MP3 Player Module (OPEN-SMART)
// D8 --------------------------- TX
// D7 --------------------------- RX

// Include required libraries:
#include <SoftwareSerial.h>

// Define the RX and TX pins to establish UART communication with the MP3 Player Module.
#define MP3_RX 9 // to TX
#define MP3_TX 10 // to RX

// Define the required MP3 Player Commands:

// Select storage device to TF card
static int8_t select_SD_card[] = {0x7e, 0x03, 0X35, 0x01, 0xef}; // 7E 03 35 01 EF
// Play with index: /01/001xxx.mp3
static int8_t play_first_song[] = {0x7e, 0x04, 0x41, 0x00, 0x01, 0xef}; // 7E 04 41 00 01 EF
// Play with index: /01/002xxx.mp3
static int8_t play_second_song[] = {0x7e, 0x04, 0x41, 0x00, 0x02, 0xef}; // 7E 04 41 00 02 EF


static int8_t play_indx_song[] = {0x7e, 0x04, 0x42, 0x02, 101, 0xef};

// Play the song.
static int8_t play[] = {0x7e, 0x02, 0x01, 0xef}; // 7E 02 01 EF
// Pause the song.
//static int8_t pause[] = {0x7e, 0x02, 0x02, 0xef}; // 7E 02 02 EF

// Define the Serial MP3 Player Module.
//SoftwareSerial MP3(MP3_RX, MP3_TX);
//HardwareSerial Serial1(2);
void setup() {
  // Initiate the serial monitor.
  Serial.begin(9600);
  // Initiate the Serial MP3 Player Module.
  Serial1.begin(9600);
  // Select the SD Card.
  send_command_to_MP3_player(select_SD_card, 5);
}

void loop() {
  // Play the second song.
  //send_command_to_MP3_player(play_indx_song, 6);
  for(int i=1 ; i<101;i++){
    sayNum(i,'A');  
  }
  for(int i=1 ; i<101;i++){
    sayNum(i,'H');  
  }
  for(int i=1 ; i<101;i++){
    sayNum(i,'R');  
  }
  
}


void send_command_to_MP3_player(int8_t command[], int len){
  Serial.print("\nMP3 Command => ");
  for(int i=0;i<len;i++){ Serial1.write(command[i]); Serial.print(command[i], HEX); }
  delay(1000);
}

void sayNum(int num,char language){
  switch (language){
    case 'A':
      play_indx_song[3]=1;
      break;
    case 'H':
      play_indx_song[3]=2;
      break;
    case 'R':
      play_indx_song[3]=3;
      break;
  }
  if(num / 100 > 0 ){
    play_indx_song[4]=100+num / 100;
  send_command_to_MP3_player(play_indx_song, 6);
  delay(250);
  }  
  num = num % 100;
  if(num / 10 > 1 ){
    play_indx_song[4]=10 * (num / 10);
  send_command_to_MP3_player(play_indx_song, 6);
  delay(250);
  }
  if(num / 10 == 1 ){
    play_indx_song[4]= num;
  send_command_to_MP3_player(play_indx_song, 6);
  return;
  }
  
  num = num % 10;
  if(num  > 0 ){
    play_indx_song[4]=num;
  send_command_to_MP3_player(play_indx_song, 6);
  delay(250);
  }
  delay(3000);
}
