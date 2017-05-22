/**
 * File: port.h
 * Author: Yan Xue <yanxue@paypal.com>
 * Date: 22/05/2017
 */
unsigned char port_byte_in(unsigned short port);
void port_byte_out(unsigned short port, unsigned char data);
unsigned short port_word_in(unsigned short port);
void port_word_out(unsigned short port, unsigned short data);
