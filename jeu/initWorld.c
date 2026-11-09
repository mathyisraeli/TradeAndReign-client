#include "initWorld.h"


void create_array(void)
{
	uint16_t size;
    memcpy(&size, ground_buffer , sizeof(size)); // 2 octets altitude
    size = ntohs(size); 
	uint16_t offset = 2;
	for (uint16_t i = 0; i < size/3; i++)
	{
		switch (ground_buffer[offset++])
		{
			case 0:
				ground_texture[i] = img->t->lim;
				break;
			case 1:
				ground_texture[i] = img->t->lii;
				break;
			case 2:
				ground_texture[i] = img->t->lis;
				break;
			case 3:
				ground_texture[i] = img->t->qua;
				break;
			case 4:
				ground_texture[i] = img->t->qui;
				break;
			case 5:
				ground_texture[i] = img->t->qug;
				break;
			case 6:
				ground_texture[i] = img->t->qus;
				break;
			case 7:
				ground_texture[i] = img->t->quz;
				break;
			case 8:
				ground_texture[i] = img->t->qzc;
				break;
			case 9:
				ground_texture[i] = img->t->qzg;
				break;
			case 10:
				ground_texture[i] = img->t->qzs;
				break;
			case 11:
				ground_texture[i] = img->t->bas;
				break;
			case 12:
				ground_texture[i] = img->t->bai;
				break;
			case 13:
				ground_texture[i] = img->t->bac;
				break;
			case 14:
				ground_texture[i] = img->t->bal;
				break;
			case 15:
				ground_texture[i] = img->t->gra;
				break;
			case 16:
				ground_texture[i] = img->t->gri;
				break;
			case 17:
				ground_texture[i] = img->t->grc;
				break;
			case 18:
				ground_texture[i] = img->t->grt;
				break;
			case 19:
				ground_texture[i] = img->t->grd;
				break;
			case 20:
				ground_texture[i] = img->t->grs;
				break;
			case 21:
				ground_texture[i] = img->t->san;
				break;
			case 22:
				ground_texture[i] = img->t->sai;
				break;
			case 23:
				ground_texture[i] = img->t->sag;
				break;
			case 24:
				ground_texture[i] = img->t->sha;
				break;
			case 25:
				ground_texture[i] = img->t->shv;
				break;
			case 26:
				ground_texture[i] = img->t->shs;
				break;
			case 27:
				ground_texture[i] = img->t->shg;
				break;
			case 28:
				ground_texture[i] = img->t->sht;
				break;
			case 29:
				ground_texture[i] = img->t->shl;
				break;
			case 30:
				ground_texture[i] = img->t->shc;
				break;
			case 31:
				ground_texture[i] = img->t->shi;
				break;
			case 32:
				ground_texture[i] = img->t->shz;
				break;
			case 33:
				ground_texture[i] = img->t->mar;
				break;
			case 34:
				ground_texture[i] = img->t->mai;
				break;
			case 35:
				ground_texture[i] = img->t->gys;
				break;
			case 36:
				ground_texture[i] = img->t->gyp;
				break;
			case 37:
				ground_texture[i] = img->t->wat;
				break;
			case 38:
				ground_texture[i] = img->t->soi;
				break;
			case 39:
				ground_texture[i] = img->t->coa;
				break;
			case 40:
				ground_texture[i] = img->t->sal;
				break;
			case 41:
				ground_texture[i] = img->t->snd;
				break;
			case 42:
				ground_texture[i] = img->t->dus;
				break;
			case 43:
				ground_texture[i] = img->t->sno;
				break;
			case 44:
				ground_texture[i] = img->t->gli;
				break;
			case 45:
				ground_texture[i] = img->t->gqa;
				break;
			case 46:
				ground_texture[i] = img->t->gqz;
				break;
			case 47:
				ground_texture[i] = img->t->gba;
				break;
			case 48:
				ground_texture[i] = img->t->ggr;
				break;
			case 49:
				ground_texture[i] = img->t->gsa;
				break;
			case 50:
				ground_texture[i] = img->t->gsh;
				break;
			case 51:
				ground_texture[i] = img->t->gma;
				break;
			case 52:
				ground_texture[i] = img->t->ggy;
				break;
			case 53:
				ground_texture[i] = img->t->gst;
				break;
			case 54:
				ground_texture[i] = img->t->gco;
				break;
			case 55:
				ground_texture[i] = img->t->iro;
				break;
			case 56:
				ground_texture[i] = img->t->cop;
				break;
			case 57:
				ground_texture[i] = img->t->lea;
				break;
			case 58:
				ground_texture[i] = img->t->zin;
				break;
			case 59:
				ground_texture[i] = img->t->tin;
				break;
			case 60:
				ground_texture[i] = img->t->gol;
				break;
			case 61:
				ground_texture[i] = img->t->sul;
				break;
			case 62:
				ground_texture[i] = img->t->sil;
				break;
		}

		uint16_t alt;
        memcpy(&alt, ground_buffer + offset, sizeof(alt)); // 2 octets altitude
        ground_altitude[i] = ntohs(alt);           // convert network -> host
        offset += sizeof(alt);
	}		
}

