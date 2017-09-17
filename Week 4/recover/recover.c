#include <stdio.h>
#include <stdint.h>
#include <string.h>
typedef uint8_t BYTE;
int main (void){
    //Opening file to work
    FILE* card = fopen("card.raw", "r");

    if (card == NULL){
        fprintf(stderr, "Cannot create card.raw.\n");
        return 1;
    }

    FILE* out_file = NULL;
    int no_of_img = 0;

    while (!feof(card))
    {
        BYTE buf[512];
        char img_name[8];
        if ((buf[0] == 0xff) && (buf[1] == 0xd8) && (buf[2] == 0xff) && (buf[3] == 0xe0 || buf[3] == 0xe1) ){
            if (out_file != NULL){
                fclose(out_file);
            }
            sprintf(img_name, "%03d.jpg", no_of_img);
            out_file = fopen(img_name, "w");
            no_of_img++;
            fwrite(buf, sizeof(buf), 1, out_file);
        }
        else if (no_of_img > 0)
        {
            fwrite(buf, sizeof(buf), 1, out_file);
        }
    fread(buf, sizeof(buf), 1, card);
    }
    if (no_of_img > 0)
        fclose(out_file);
    //Closing card
    fclose(card);
    return 0;
}