#include <Adafruit_CircuitPlayground.h> //Libraries

int frames[10][2] = {
    {0, 0},  
    {0, 0},
    {0, 0},  
    {0, 0}, 
    {0, 0},  
    {0, 0},
    {0, 0},  
    {0, 0}, 
    {0, 0},  
    {0, 0},
};

int total[10] = {0,0,0,0,0,0,0,0,0,0};

int finalScore = 0;




//stike/spare variables
int curRoll;
int prevRoll;
int pastRoll;

int lights;


//round/roll variables
bool roll = 0;
int roundAt = 0;


//attach interrupt variables
const int SwitchPin = 7;
volatile bool switchFlag = false;
const int ButtPin = 5; //CHECK THIS
volatile bool buttFlag = false;


bool gameState = true;

void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin();//CPX setup
  Serial.begin(9600); //Serial setup
  while(!Serial); //Don't start until serialopened
  randomSeed(CircuitPlayground.readCap(1)); //sets random based on capacitance so the game is more random each tijme
  //interrupts
  attachInterrupt(digitalPinToInterrupt(SwitchPin), Switched, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ButtPin), Buttons, LOW);

  Serial.println("Beginning game...");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(switchFlag) //if switch game on/off
  {
    delay(5);
    Serial.println("Switched");
    gameState = CircuitPlayground.slideSwitch(); 
    switchFlag = false;
  }

  if(gameState) //if game playing
  {
    CircuitPlayground.redLED(true);
    if(buttFlag) //button pressed
    {
      delay(10);
      Serial.println("Button Pressed");
      Serial.print("Round: ");
      Serial.print(roundAt + 1);
      Serial.print("   Ball: ");
      Serial.println(roll + 1);
      if(!roll) //first roll
      {
        curRoll = random(0,11);
        lights = 10 - curRoll;
      }
      else //second roll
      {
        curRoll = random(0,11-prevRoll);
        lights = lights - curRoll;
      }
      frames[roundAt][roll] = curRoll; //save it to array
      Serial.print("Pins Hit: ");
      Serial.println(frames[roundAt][roll]);
      CircuitPlayground.clearPixels(); 
      for(int k = 0; k < lights; k++) //show remaining pins on pixels
      {
        CircuitPlayground.setPixelColor(k,200,200,200);
      }

      if(roll) //if second roll then next is also next round, and fill total array
      {
        total[roundAt] = frames[roundAt][roll] + frames[roundAt][roll-1];
        if(total[roundAt - 1] == 10) //all pins down last round
        {
          if(frames[roundAt - 1][0] == 10)//if STRIKE
          {
            frames[roundAt - 1][0] = 10 + frames[roundAt][roll-1] + frames[roundAt][roll];
          }
          else //if SPARE
          {
            frames[roundAt-1][1] = 10 + frames[roundAt][roll-1];
          }
          //replace total for last round with corrected score
          total[roundAt - 1] = frames[roundAt - 1][roll] + frames[roundAt - 1][roll-1];
        }
        delay(1000);
        CircuitPlayground.clearPixels();
        roundAt++;
      }
      roll = !roll; //set to next roll
      pastRoll = prevRoll;
      prevRoll = curRoll; //save previous value

      if(roundAt > 9)
      {
        gameState = false; //game over
        Serial.println();
        Serial.println("------Game Over------");
        for(int i = 0; i < 10; i++) //print game scoreboard and total
        {
          Serial.print("Round: ");
          Serial.print(i);
          Serial.print("  ");
          for(int j = 0; j < 2; j++)
          {
            Serial.print("| ");
            Serial.print(frames[i][j]);
            Serial.print(" ");
          }
          Serial.print(" Score: ");
          Serial.println(total[i]);
          finalScore += total[i];
        }
        Serial.print("Total Score: ");
        Serial.println(finalScore);
      }
      else
      {
        Serial.println("Press button to roll again"); //prompt player
        Serial.println();
      }
      buttFlag = false;
    }
  }
  else
  {
    CircuitPlayground.redLED(false); //turn off red LED
  }
}

// Interrupt ISRs
void Switched()
{
  switchFlag = true;
}

void Buttons()
{
  buttFlag = true;
}
