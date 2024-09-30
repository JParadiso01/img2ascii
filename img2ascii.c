#include <stdio.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

char *chars = " .-~=ca#";
#define CHARS_LEN 8
unsigned char *grayscale_data;

void grayScale(unsigned char *data, int width, int height, int comps){
    int grayscale_index = 0;
    for (size_t i = 0; i < (size_t)width*height*comps; i += comps){
        uint32_t avg = ((int)(data[i])*0.21 + (int)(data[i+1])*0.72 + (int)(data[i+2])*0.07);
        grayscale_data[grayscale_index] = avg;
        grayscale_index++;
     }
}

int main(int argc, char **argv){

    if (argc <= 1){
        printf("ERROR: User must provide input image\n");
        exit(1);
    }

    char *filename = argv[1];
    int ok, width, height, comps;
    ok = stbi_info(filename, &width, &height, &comps);

    if (ok == 0){
        printf("ERROR: Image is not a supported format. Please supply one that is.\n");
        exit(1);
    }

    grayscale_data = (unsigned char *)malloc((sizeof(unsigned char))*width*height);  
    unsigned char *data = stbi_load(filename, &width, &height, &comps, 0);
    grayScale(data, width, height, comps);
    printf("%u ", grayscale_data[0]);

    for (int i = 0; i < width*height; i++){
        int index = (int)(((float)grayscale_data[i]/255)*CHARS_LEN)%CHARS_LEN;
        printf("%c ", chars[index]);
        if (i % width == 0){
            printf("\n");
        }
    }

    free(grayscale_data);
    stbi_image_free(data);
    return 0;
}