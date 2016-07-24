#include <string>
#include <iostream>
#include <sstream>
#include <list>
#include <algorithm> 
#include <iterator>
#include <ctype.h>
#include <locale>

using namespace std;

class CALSASoundDevice
{
  string name_long;
  string name_short;
  int number;
}


class CALSASoundDevices
{
public:

   std::vector <CALSASoundDevice *> sound_cards;
   std::vector <string> midi_ports;
   
   void get_soundcards();
   void get_MIDI_ports();
  
 
//  CItem (char a_op, double a_val);
};
