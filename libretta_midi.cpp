
#include <alsa/asoundlib.h>     /* Interface to the ALSA system */

// function declarations:
void  print_midi_ports          (void);
void  print_card_list           (void);
void  list_midi_devices_on_card (int card);
void  list_subdevice_info       (snd_ctl_t *ctl, int card, int device);
int   is_input                  (snd_ctl_t *ctl, int card, int device, int sub);
int   is_output                 (snd_ctl_t *ctl, int card, int device, int sub);
void  error                     (const char *format, ...);

///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
   // print_card_list();  // prints a list of all card devices (not only MIDI)
   print_midi_ports();
   return 0;
}

///////////////////////////////////////////////////////////////////////////


CALSA::~CALSA()
{
   for (size_t i = 0; i < sound_cards.size(); i++)
      delete sound_cards[i]; 
}




void CALSASoundDevices::get_soundcards()
{
   int status;
   int card = -1;
   char* longname = NULL;
   char* shortname = NULL;

   if ((status = snd_card_next(&card)) < 0) 
      {
       error("cannot determine card number: %s", snd_strerror(status));
       return;
      }
      
   if (card < 0) 
      {
       error("no sound cards found");
       return;
      }
      
   while (card >= 0) 
        {
         CALSASoundDevice *d = new CALSASoundDevice;
         
         //printf("Card %d:", card);
         if ((status = snd_card_get_name (card, &shortname)) == 0) 
            d->shortname = shortname;
          
            /*{
             error("cannot determine card shortname: %s", snd_strerror(status));
             break;
            }*/
      
        if ((status = snd_card_get_longname(card, &longname)) == 0)
            d->longname = longname;
        
        /*{
         error("cannot determine card longname: %s", snd_strerror(status));
         break;
      }*/
        
        d->number = card;
        
        sound_cards.push_back (d);
            
        
      //printf("\tLONG NAME:  %s\n", longname);
      //printf("\tSHORT NAME: %s\n", shortname);
      if ((status = snd_card_next(&card)) < 0) 
        {
       //  error("cannot determine card number: %s", snd_strerror(status));
         break;
      }
   } 
}





void list_subdevice_info (snd_ctl_t *ctl, int card, int device) 
{
   snd_rawmidi_info_t *info;
   const char *name;
   const char *sub_name;
   int subs, subs_in, subs_out;
   int sub, in, out;
   int status;

   snd_rawmidi_info_alloca(&info);
   snd_rawmidi_info_set_device(info, device);

   snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_INPUT);
   snd_ctl_rawmidi_info(ctl, info);

   subs_in = snd_rawmidi_info_get_subdevices_count(info);
   snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_OUTPUT);
   snd_ctl_rawmidi_info(ctl, info);

   subs_out = snd_rawmidi_info_get_subdevices_count(info);
   subs = subs_in > subs_out ? subs_in : subs_out;

   sub = 0;
   in = out = 0;

   if ((status = is_output(ctl, card, device, sub)) < 0) {
      error("cannot get rawmidi information %d:%d: %s",
            card, device, snd_strerror(status));
      return;
   } else if (status)
      out = 1;

   if (status == 0) {
      if ((status = is_input(ctl, card, device, sub)) < 0) {
         error("cannot get rawmidi information %d:%d: %s",
               card, device, snd_strerror(status));
         return;
      }
   } else if (status) 
      in = 1;

   if (status == 0)
      return;

   name = snd_rawmidi_info_get_name(info);
   sub_name = snd_rawmidi_info_get_subdevice_name(info);
   if (sub_name[0] == '\0') {
      if (subs == 1) {
         printf("%c%c  hw:%d,%d    %s\n", 
                in  ? 'I' : ' ', 
                out ? 'O' : ' ',
                card, device, name);
      } else
         printf("%c%c  hw:%d,%d    %s (%d subdevices)\n",
                in  ? 'I' : ' ', 
                out ? 'O' : ' ',
                card, device, name, subs);
   } else {
      sub = 0;
      for (;;) {
         printf("%c%c  hw:%d,%d,%d  %s\n",
                in ? 'I' : ' ', out ? 'O' : ' ',
                card, device, sub, sub_name);
         if (++sub >= subs)
            break;

         in = is_input(ctl, card, device, sub);
         out = is_output(ctl, card, device, sub);
         snd_rawmidi_info_set_subdevice(info, sub);
         if (out) {
            snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_OUTPUT);
            if ((status = snd_ctl_rawmidi_info(ctl, info)) < 0) {
               error("cannot get rawmidi information %d:%d:%d: %s",
                     card, device, sub, snd_strerror(status));
               break;
            } 
         } else {
            snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_INPUT);
            if ((status = snd_ctl_rawmidi_info(ctl, info)) < 0) {
               error("cannot get rawmidi information %d:%d:%d: %s",
                     card, device, sub, snd_strerror(status));
               break;
            }
         }
         sub_name = snd_rawmidi_info_get_subdevice_name(info);
      }
   }
}




void list_midi_devices_on_card (int card) 
{
   snd_ctl_t *ctl;
   char name[32];
   int device = -1;
   int status;
   
   sprintf(name, "hw:%d", card);
   
   if ((status = snd_ctl_open(&ctl, name, 0)) < 0) {
      error("cannot open control for card %d: %s", card, snd_strerror(status));
      return;
   }
   do {
      status = snd_ctl_rawmidi_next_device(ctl, &device);
      if (status < 0) {
         error("cannot determine device number: %s", snd_strerror(status));
         break;
      }
      if (device >= 0) {
         list_subdevice_info(ctl, card, device);
      }
   } while (device >= 0);
   snd_ctl_close(ctl);
}



void CALSASoundDevices::get_MIDI_ports ()
{
   int status;
   int card = -1;  

   if ((status = snd_card_next (&card)) < 0) {
      error("cannot determine card number: %s", snd_strerror(status));
      return;
   }
   if (card < 0) {
      error("no sound cards found");
      return;
   }
   printf("\nDir Device    Name\n");
   printf("====================================\n");
   while (card >= 0) {
      list_midi_devices_on_card(card);
      if ((status = snd_card_next(&card)) < 0) {
         error("cannot determine card number: %s", snd_strerror(status));
         break;
      }
   } 
   printf("\n");
}







//////////////////////////////
//
// is_input -- returns true if specified card/device/sub can output MIDI data.
//

int is_input(snd_ctl_t *ctl, int card, int device, int sub) {
   snd_rawmidi_info_t *info;
   int status;

   snd_rawmidi_info_alloca(&info);
   snd_rawmidi_info_set_device(info, device);
   snd_rawmidi_info_set_subdevice(info, sub);
   snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_INPUT);
   
   if ((status = snd_ctl_rawmidi_info(ctl, info)) < 0 && status != -ENXIO) {
      return status;
   } else if (status == 0) {
      return 1;
   }

   return 0;
}



//////////////////////////////
//
// is_output -- returns true if specified card/device/sub can output MIDI data.
//

int is_output(snd_ctl_t *ctl, int card, int device, int sub) {
   snd_rawmidi_info_t *info;
   int status;

   snd_rawmidi_info_alloca(&info);
   snd_rawmidi_info_set_device(info, device);
   snd_rawmidi_info_set_subdevice(info, sub);
   snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_OUTPUT);
   
   if ((status = snd_ctl_rawmidi_info(ctl, info)) < 0 && status != -ENXIO) {
      return status;
   } else if (status == 0) {
      return 1;
   }

   return 0;
}



//////////////////////////////
//
// error -- print error message
//

void error(const char *format, ...) {
   va_list ap;
   va_start(ap, format);
   vfprintf(stderr, format, ap);
   va_end(ap);
   putc('\n', stderr);
}


