//  Copyright (C) 2001  MandrakeSoft S.A.
//
//    MandrakeSoft S.A.
//    43, rue d'Aboukir
//    75002 Paris - France
//    http://www.linux-mandrake.com/
//    http://www.mandrakesoft.com/
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA


#if BX_USE_PIC_SMF
#  define BX_PIC_SMF  static
#  define BX_PIC_THIS bx_pic.
#else
#  define BX_PIC_SMF
#  define BX_PIC_THIS this->
#endif

#if BX_SUPPORT_SID
class pic;
#endif

typedef struct {
  Bit8u single_PIC;        /* 0=cascaded PIC, 1=master only */
  Bit8u interrupt_offset;  /* programmable interrupt vector offset */
  union {
    Bit8u   slave_connect_mask; /* for master, a bit for each interrupt line
                                   0=not connect to a slave, 1=connected */
    Bit8u   slave_id;           /* for slave, id number of slave PIC */
    } u;
  Bit8u sfnm;              /* specially fully nested mode: 0=no, 1=yes*/
  Bit8u buffered_mode;     /* 0=no buffered mode, 1=buffered mode */
  Bit8u master_slave;      /* master/slave: 0=slave PIC, 1=master PIC */
  Bit8u auto_eoi;          /* 0=manual EOI, 1=automatic EOI */
  Bit8u imr;               /* interrupt mask register, 1=masked */
  Bit8u isr;               /* in service register */
  Bit8u irr;               /* interrupt request register */
  Bit8u read_reg_select;   /* 0=IRR, 1=ISR */
  Bit8u irq;               /* current IRQ number */
  Boolean INT;             /* INT request pin of PIC */
  struct {
    Boolean    in_init;
    Boolean    requires_4;
    int        byte_expected;
    } init;
  Boolean special_mask;
  } bx_pic_t;


class bx_pic_c : public logfunctions {

public:
  bx_pic_c(void);
  ~bx_pic_c(void);
#if BX_SUPPORT_SID
  BX_PIC_SMF void   init(pic *pic_comp);
#else
  BX_PIC_SMF void   init(bx_devices_c *);
#endif
  BX_PIC_SMF void   trigger_irq(unsigned irq_no);
  BX_PIC_SMF void   untrigger_irq(unsigned irq_no);
  BX_PIC_SMF Bit8u  IAC(void);

private:
  struct {
    bx_pic_t master_pic;
    bx_pic_t slave_pic;
    } s;
#if BX_SUPPORT_SID
  pic *pic_component;
#else
  bx_devices_c *devices;
#endif
  static Bit32u read_handler(void *this_ptr, Bit32u address, unsigned io_len);
  static void   write_handler(void *this_ptr, Bit32u address, Bit32u value, unsigned io_len);
#if BX_SUPPORT_SID
 public:
#endif
#if !BX_USE_PIC_SMF
  Bit32u read(Bit32u address, unsigned io_len);
  void   write(Bit32u address, Bit32u value, unsigned io_len);
#endif
#if BX_SUPPORT_SID
 private:
#endif
  BX_PIC_SMF void   service_master_pic(void);
  BX_PIC_SMF void   service_slave_pic(void);
  BX_PIC_SMF void   show_pic_state(void);
  };
#if BX_SUPPORT_SID==0
extern bx_pic_c bx_pic;
#endif
