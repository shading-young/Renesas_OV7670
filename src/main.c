/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  Renesas_OV7670                         */
/*      FILE         :  Renesas_OV7670.c                       */
/*      DESCRIPTION  :  Main Program                           */
/*      CPU SERIES   :  RX200                                  */
/*      CPU TYPE     :  RX23T                                  */
/*                                                             */
/*      This file is generated by e2 studio.                   */
/*                                                             */
/***************************************************************/

#include "platform.h"
#include "r_cg_sci.h"

#include "camera.h"

void send_img(unsigned char *image, int width, int height);

void main(void)
{
    unsigned char *image;
    int width, height;

    cam_init();

    while (1) {
        if (read_img_from_FIFO()) {
            get_img(&image, &width, &height);
            send_img(image, width, height);
        }
    }
}

void send_img(unsigned char *image, int width, int height)
{
    while(!send_end);
    send_end = false;
    R_SCI5_Serial_Send(start_c, sizeof(start_c));
    for (int i = 1; i < width * height * 2; i+=2) {
        while(!send_end);
        send_end = false;
        R_SCI5_Serial_Send(image + i, 1);
    }
    while(!send_end);
    send_end = false;
    R_SCI5_Serial_Send(end_c, sizeof(end_c));
}
