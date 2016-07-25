//
// Created by kang on 7/25/16.
//

#ifndef PI_QC12864B_H
#define PI_QC12864B_H
void lcdinit();
void write_com(unsigned char cmd);
void lcd_show(unsigned char *s);
#endif //PI_QC12864B_H
