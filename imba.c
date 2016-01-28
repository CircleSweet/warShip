/*
To test that the Linux framebuffer is set up correctly, and that the device permissions
are correct, use the program below which opens the frame buffer and draws a gradient-
filled red square:
retrieved from:
Testing the Linux Framebuffer for Qtopia Core (qt4-x11-4.2.2)
http://cep.xor.aps.anl.gov/software/qt4-x11-4.2.2/qtopiacore-testingframebuffer.html
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

void drawBlock(
    struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *fbp, int startX, int startY, int height, int width, int red, int green, int blue) {
	    // finfo: bawaan
		// vinfo: bawaan
		// startY: posisi awal Y
		// startX: posisi awal X
		// height: tinggi dari block
		// width: lebar dari block
		// rgb: color rgb dari block

	    int x,y;
	    int location = 0;
	    for (y = startY; y < startY+height; y++){
	        for (x = startX; x < startX+width; x++) {
	        	// usleep(2);
	            location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
	                       (y+vinfo.yoffset) * finfo.line_length;

	            if (vinfo.bits_per_pixel == 32) {
	                *(fbp + location) = blue;        // Some bluei
	                *(fbp + location + 1) = green;     // A little green
	                *(fbp + location + 2) = red;    // A lot of red
	                *(fbp + location + 3) = 0;      // No transparency
	        //location += 4;
	            } else  { //assume 16bpp
	                int b = 10;
	                int g = 10;     // A little green
	                int r = 10;    // A lot of red
	                unsigned short int t = r<<11 | g << 5 | b;
	                *((unsigned short int*)(fbp + location)) = t;
	            }
	        }
	 	}
	 }


void line(struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *fbp, int x0, int y0, int x1, int y1) {
 
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  for(;;){
  	drawBlock(finfo, vinfo, fbp, x0, y0, 1, 1, 0, 0, 0);
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}

void ocean(struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *fbp, int x, int y){
	line(finfo, vinfo, fbp, 0+x, 0+y,9+x, 0+y);
	line(finfo, vinfo, fbp, 0+x, 1+y, 9+x, 1+y);
	line(finfo, vinfo, fbp, 0+x, 2+y, 9+x, 2+y);
	line(finfo, vinfo, fbp, 10+x, 3+y, 19+x, 3+y);
	line(finfo, vinfo, fbp, 10+x, 4+y, 19+x, 4+y);	
	line(finfo, vinfo, fbp, 10+x, 5+y, 19+x, 5+y);
	line(finfo, vinfo, fbp, 20+x, 6+y, 29+x, 6+y);
	line(finfo, vinfo, fbp, 20+x, 7+y, 29+x, 7+y);
	line(finfo, vinfo, fbp, 20+x, 8+y, 29+x, 8+y);
	line(finfo, vinfo, fbp, 30+x, 9+y, 39+x, 9+y);
	line(finfo, vinfo, fbp, 30+x, 10+y, 39+x, 10+y);
	line(finfo, vinfo, fbp, 30+x, 11+y, 39+x, 11+y);
	line(finfo, vinfo, fbp, 40+x, 12+y, 49+x, 12+y);
	line(finfo, vinfo, fbp, 40+x, 12+y, 49+x, 12+y);
	line(finfo, vinfo, fbp, 40+x, 12+y, 49+x, 12+y);
	line(finfo, vinfo, fbp, 50+x, 12+y, 59+x, 12+y);
	line(finfo, vinfo, fbp, 50+x, 12+y, 59+x, 12+y);
	line(finfo, vinfo, fbp, 50+x, 12+y, 59+x, 12+y);

}

void shipbimo(struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *fbp) {
	line(finfo, vinfo, fbp, 550, 50, 570, 50); // sayap kiri atas
	line(finfo, vinfo, fbp, 549, 51, 550, 68); //sayap kiri belakang
	line(finfo, vinfo, fbp, 570, 51, 578, 61); // sayap kiri depan
	line(finfo, vinfo, fbp, 530, 70, 515, 55); // badan
	line(finfo, vinfo, fbp, 515, 55, 510, 55); // badan
	line(finfo, vinfo, fbp, 510, 55, 510, 80); // badan
	line(finfo, vinfo, fbp, 530, 70, 598, 60); // badan
	line(finfo, vinfo, fbp, 595, 65, 600, 80); // jendela
	line(finfo, vinfo, fbp, 600, 80, 615, 80); // jendela
	line(finfo, vinfo, fbp, 598, 60, 615, 66); // badan
	line(finfo, vinfo, fbp, 615, 66, 620, 70); // badan
	line(finfo, vinfo, fbp, 620, 70, 620, 85); // badan
	line(finfo, vinfo, fbp, 620, 85, 615, 95); // badan
	line(finfo, vinfo, fbp, 615, 95, 600, 100); // badan
	line(finfo, vinfo, fbp, 600, 100, 585, 105); // badan
	line(finfo, vinfo, fbp, 580, 120, 545, 120); // sayap kanan
	line(finfo, vinfo, fbp, 580, 120, 590, 90); // sayap kanan
	line(finfo, vinfo, fbp, 545, 120, 555, 90); // sayap kanan
	line(finfo, vinfo, fbp, 550, 105, 525, 100); // sayap kanan
	line(finfo, vinfo, fbp, 525, 100, 530, 90); // sayap kanan
	line(finfo, vinfo, fbp, 528, 95, 515, 95); // sayap kanan
	line(finfo, vinfo, fbp, 515, 95, 510, 80); // badan
}

void shipscemo(struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *fbp, int x, int y){
	line(finfo, vinfo, fbp, 0+x, 0+y, 0+x, 130+y);
	line(finfo, vinfo, fbp, 0+x, 0+y, 60+x, 60+y);
	line(finfo, vinfo, fbp, 0+x, 130+y, 60+x, 70+y);
	line(finfo, vinfo, fbp, 60+x, 0+y, 60+x, 130+y);
	line(finfo, vinfo, fbp, 60+x, 0+y, 250+x, 0+y);
	line(finfo, vinfo, fbp, 250+x, 0+y, 450+x, 80+y);
	line(finfo, vinfo, fbp, 400+x, 130+y, 450+x, 80+y);
	line(finfo, vinfo, fbp, 60+x, 130+y, 400+x, 130+y);
}

void huruf(struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *fbp, int x, int y, int red, int green, int blue, char h) {

    switch (h) {
	case 'k' :
		 	drawBlock(finfo, vinfo, fbp, 0+x,0+y, 70, 10, red, green, blue);  
		 	drawBlock(finfo, vinfo, fbp, 10+x,30+y, 10, 10, red, green, blue);  
		 	drawBlock(finfo, vinfo, fbp, 20+x,20+y, 10, 10, red, green, blue);  
		 	drawBlock(finfo, vinfo, fbp, 20+x,40+y, 10, 10, red, green, blue); 	 	  
		 	drawBlock(finfo, vinfo, fbp, 30+x,10+y, 10, 10, red, green, blue); 
		 	drawBlock(finfo, vinfo, fbp, 30+x,50+y, 10, 10, red, green, blue); 
		 	drawBlock(finfo, vinfo, fbp, 40+x,60+y, 10, 10, red, green, blue);
		 	drawBlock(finfo, vinfo, fbp, 40+x,0+y, 10, 10, red, green, blue); 
	 	break;

	case 'p':
			drawBlock(finfo, vinfo, fbp, 0+x,0+y, 70, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 10+x,0+y, 10, 30, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 10+x,40+y, 10, 30, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 40+x,10+y, 30, 10, red, green, blue);
		break;

	case 'h':
			drawBlock(finfo, vinfo, fbp, 0+x,0+y, 70, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 40+x,0+y, 70, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 10+x,30+y, 10, 30, red, green, blue);
		break;

	case 'u':
			drawBlock(finfo, vinfo, fbp, 0+x,0+y, 60, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 40+x,0+y, 60, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 10+x,60+y, 10, 30, red, green, blue);
		break;

	case 'a':
			drawBlock(finfo, vinfo, fbp, 0+x,10+y, 60, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 40+x,10+y, 60, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 10+x,30+y, 10, 30, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 10+x,0+y, 10, 30, red, green, blue);
		break;

	case 't':
			drawBlock(finfo, vinfo, fbp, 0+x,0+y, 10, 50, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 20+x,0+y, 70, 10, red, green, blue);
		break;

	case 'r':
			drawBlock(finfo, vinfo, fbp, 0+x,0+y, 70, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 10+x,0+y, 10, 30, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 10+x,40+y, 10, 30, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 40+x,10+y, 30, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 40+x,50+y, 20, 10, red, green, blue);
		break;

	case 'l':
			drawBlock(finfo, vinfo, fbp, 0+x,60+y, 10, 50, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 0+x,0+y, 70, 10, red, green, blue);
		break;

	case 'i':
			drawBlock(finfo, vinfo, fbp, 20+x,0+y, 70, 10, red, green, blue);
		break;

	case 'n' :
			drawBlock(finfo, vinfo, fbp, 0+x,0+y, 70, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 40+x,0+y, 70, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 10+x,10+y, 10, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 30+x,30+y, 10, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 20+x,20+y, 10, 10, red, green, blue);
        	break;

    	case 'w' :
            		drawBlock(finfo, vinfo, fbp, 0+x,0+y, 70, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 40+x,0+y, 70, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 10+x,50+y, 10, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 20+x,40+y, 10, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 30+x,50+y, 10, 10, red, green, blue);
        	break;
    	case 'z' :
            		drawBlock(finfo, vinfo, fbp, 0+x,0+y, 10, 50, red, green, blue);
          		drawBlock(finfo, vinfo, fbp, 0+x,60+y, 10, 50, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 40+x,10+y, 10, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 30+x,20+y, 10, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 20+x,30+y, 10, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 10+x,40+y, 10, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 0+x,50+y, 10, 10, red, green, blue);
        	break;

    	case 'b' :
            		drawBlock(finfo, vinfo, fbp, 0+x,0+y, 70, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 10+x,0+y, 10, 30, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 10+x,30+y, 10, 30, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 40+x,10+y, 20, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 40+x,40+y, 20, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 10+x,60+y, 10, 30, red, green, blue);
        	break;

    	case 'm' :
            		drawBlock(finfo, vinfo, fbp, 0+x,0+y, 70, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 40+x,0+y, 70, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 10+x,10+y, 10, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 30+x,10+y, 10, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 20+x,20+y, 10, 10, red, green, blue);
        	break;

    	case 'o':
            		drawBlock(finfo, vinfo, fbp, 0+x,10+y, 50, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 40+x,10+y, 50, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 10+x,60+y, 10, 30, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 10+x,0+y, 10, 30, red, green, blue);
        	break;

    	case 'g':
			drawBlock(finfo, vinfo, fbp, 0+x,10+y, 50, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 10+x,0+y, 10, 40, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 10+x,60+y, 10, 40, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 40+x,30+y, 40, 10, red, green, blue);
			drawBlock(finfo, vinfo, fbp, 30+x,30+y, 10, 20, red, green, blue);
		break;

	case 'f' :
        		drawBlock(finfo, vinfo, fbp, 0+x,0+y, 70, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 0+x,0+y, 10, 50, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 0+x,30+y, 10, 50, red, green, blue);
        	break;

    	case 'd' :
            		drawBlock(finfo, vinfo, fbp, 0+x,0+y, 70, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 0+x,0+y, 10, 40, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 0+x,60+y, 10, 40, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 40+x,10+y, 50, 10, red, green, blue);
        	break;

    	case 'y' :
            		drawBlock(finfo, vinfo, fbp, 20+x,30+y, 40, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 0+x,0+y, 20, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 10+x,20+y, 10, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 40+x,0+y, 20, 10, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 30+x,20+y, 10, 10, red, green, blue);
        	break;

    	case '*' :
    /*
 ** **
*******
*******
 *****
  ***
   *
    */
            		drawBlock(finfo, vinfo, fbp, 10+x,y, 10, 20, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 40+x,y, 10, 20, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 0+x,10+y, 20, 70, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 10+x,30+y, 10, 50, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 20+x,40+y, 10, 30, red, green, blue);
            		drawBlock(finfo, vinfo, fbp, 30+x,50+y, 10, 10, red, green, blue);
    }

}

void typesentence(
	struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *fbp, int x, int y, int red, int green, int blue, char* h){
	
	for (int iterate=0; iterate<strlen(h);iterate++){
		
    	huruf(finfo, vinfo, fbp,x+(iterate*60),y, red, green, blue, h[iterate]);

	}

} 

int main()
{

    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize = 0;
    char *fbp = 0;
    int x = 0, y = 0;
    long int location = 0;

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in 37tes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((int)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");

    x = 100; y = 100;       // Where we are going to put the pixel

    int i,fr;
    
    // Draw the BG color
    drawBlock(finfo, vinfo, fbp, 0, 0, 700, 1366, 255, 255, 255); 
    
    int ax = 130;
    int ay = 520;
    for(int i=0;i<5;i++) {     
       line(finfo, vinfo, fbp, ax, ay, 200+i*2*ax, 100);
    }
    shipscemo(finfo, vinfo, fbp, 50, 540);
    close(fbfd);
    return 0;
}

//683x384

















































// disini bisa dipake buat ngeplay, nanti buat animasi
    	// bisa pakai fungsi buat ubah posisi

    	// SEBELUM UBAH huruf, dilihat dulu semua hurufnya

    	// ukuran frame huruf belum sama
    	// kalo mau ganti ukuran huruf, harus diganti
    	// satu per satu parameternya

    	// for (y = 84; y < 674; y++){
	    //     for (x = 83; x < 1273; x++) {
	    //     	coba.r[x][y]=i;
	    //     	coba.g[x][y]=i;
	    //     	coba.b[x][y]=i;
	    //     	}
	    //     }

	    /* huruf A
    	drawBlock(finfo, vinfo, fbp, 100, 200, 200, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 150, 200, 50, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 150, 300, 50, 50, 50, 100, 100);
	 	drawBlock(finfo, vinfo, fbp, 200, 200, 200, 50, 50, 100, 100);
		*/
		
	 	/* huruf I
    	drawBlock(finfo, vinfo, fbp, 125, 200, 25, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 125, 375, 25, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 150, 200, 200, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 175, 200, 25, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 175, 375, 25, 50, 50, 100, 100);
	 	*/

		/* huruf U
    	drawBlock(finfo, vinfo, fbp, 100, 200, 200, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 150, 350, 50, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 200, 200, 200, 50, 50, 100, 100);
    	*/
		
		/* huruf O
		drawBlock(finfo, vinfo, fbp, 100, 200, 200, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 150, 200, 50, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 150, 350, 50, 50, 50, 100, 100);
	 	drawBlock(finfo, vinfo, fbp, 200, 200, 200, 50, 50, 100, 100);
		*/

    	/* huruf L
    	drawBlock(finfo, vinfo, fbp, 150, 200, 200, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 175, 350, 50, 75, 50, 100, 100);
		*/

    	/* huruf H
		drawBlock(finfo, vinfo, fbp, 100, 200, 200, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 150, 275, 50, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 200, 200, 200, 50, 50, 100, 100);
    	*/

    	/* huruf T
    	drawBlock(finfo, vinfo, fbp, 150, 200, 200, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 100, 200, 50, 150, 50, 100, 100);
    	*/

    	/* huruf M (masih cacat)
		drawBlock(finfo, vinfo, fbp, 100, 200, 200, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 185, 200, 200, 35, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 250, 200, 200, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 100, 200, 50, 200, 50, 100, 100);
		*/

		/* huruf G
		drawBlock(finfo, vinfo, fbp, 100, 200, 50, 200, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 100, 200, 250, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 100, 400, 50, 200, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 200, 300, 50, 50, 50, 100, 100);
    	drawBlock(finfo, vinfo, fbp, 250, 300, 100, 50, 50, 100, 100);
    	*/

    	/* huruf K
		drawBlock(finfo, vinfo, fbp, 100, 200, 250, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 150, 300, 50, 100, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 250, 250, 50, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 300, 200, 50, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 250, 350, 50, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 300, 400, 50, 50, 50, 100, 100);
        */     	

		/* huruf R
		drawBlock(finfo, vinfo, fbp, 100, 200, 250, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 150, 200, 50, 100, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 150, 300, 50, 150, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 250, 250, 50, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 250, 400, 50, 50, 50, 100, 100);
		drawBlock(finfo, vinfo, fbp, 200, 350, 50, 50, 50, 100, 100);
		*/	
