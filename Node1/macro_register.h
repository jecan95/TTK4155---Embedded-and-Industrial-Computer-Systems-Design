#ifndef MACRO_REGISTER_H_
#define MACRO_REGISTER_H_

#define set_bit1(reg1, bit)      (reg1 |= (1 << bit))
#define set_bit0(reg2, bit)      (reg2 &= ~(1 << bit))


#endif 