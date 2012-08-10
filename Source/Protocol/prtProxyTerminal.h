#pragma once
#include "../resource.h"
#include "prtStream.h"
//---------------------------------------------------------------------------------------


#define MAX_TERMINAL_BUFFER 0x20 //размер буфера для команд
#define MAX_TERMINAL_ARGV 10 //максимальное количество аргументов для строчки






//---------------------------------------------------------------------------------------
/* define the Key codes */
 #define KEY_NUL 0 /**< ^@ Null character */
 #define KEY_SOH 1 /**< ^A Start of heading, = console interrupt */
 #define KEY_STX 2 /**< ^B Start of text, maintenance mode on HP console */
 #define KEY_ETX 3 /**< ^C End of text */
 #define KEY_EOT 4 /**< ^D End of transmission, not the same as ETB */
 #define KEY_ENQ 5 /**< ^E Enquiry, goes with ACK; old HP flow control */
 #define KEY_ACK 6 /**< ^F Acknowledge, clears ENQ logon hand */
 #define KEY_BEL 7 /**< ^G Bell, rings the bell... */
 #define KEY_BS  8 /**< ^H Backspace, works on HP terminals/computers */
 #define KEY_HT  9 /**< ^I Horizontal tab, move to next tab stop */
 #define KEY_LF  10  /**< ^J Line Feed */
 #define KEY_VT  11  /**< ^K Vertical tab */
 #define KEY_FF  12  /**< ^L Form Feed, page eject */
 #define KEY_CR  13  /**< ^M Carriage Return*/
 #define KEY_SO  14  /**< ^N Shift Out, alternate character set */
 #define KEY_SI  15  /**< ^O Shift In, resume defaultn character set */
 #define KEY_DLE 16  /**< ^P Data link escape */
 #define KEY_DC1 17  /**< ^Q XON, with XOFF to pause listings; "okay to send". */
 #define KEY_DC2 18  /**< ^R Device control 2, block-mode flow control */
 #define KEY_DC3 19  /**< ^S XOFF, with XON is TERM=18 flow control */
 #define KEY_DC4 20  /**< ^T Device control 4 */
 #define KEY_NAK 21  /**< ^U Negative acknowledge */
 #define KEY_SYN 22  /**< ^V Synchronous idle */
 #define KEY_ETB 23  /**< ^W End transmission block, not the same as EOT */
 #define KEY_CAN 24  /**< ^X Cancel line, MPE echoes !!! */
 #define KEY_EM  25  /**< ^Y End of medium, Control-Y interrupt */
 #define KEY_SUB 26  /**< ^Z Substitute */
 #define KEY_ESC 27  /**< ^[ Escape, next character is not echoed */
 #define KEY_FS  28  /**< ^\ File separator */
 #define KEY_GS  29  /**< ^] Group separator */
 #define KEY_RS  30  /**< ^^ Record separator, block-mode terminator */
 #define KEY_US  31  /**< ^_ Unit separator */
 #define KEY_DEL 127 /**< Delete (not a real control character...) */
 
 
 /*
 backspace 
 .127.
 
 
 */
//---------------------------------------------------------------------------------------








/* //===================================================================================*
* //                                                                                    *
* // Интерфес терминала, обработка входящих данных и выполнение введеной команды		*
* //------------------------------------------------------------------------------------*
*///
class
	AProxyTerminal
{
	public:
		AProxyTerminal ();

	
	
		bool isCorrect(const BYTE data) const;//проверка, являятся ли данные корректны для терминала
		void execute(const BYTE data, AStream *stream);//Обработка и выделение командной строки


		//отсылка данных терминалу
		static const void sendEnter		(AStream *stream);//послать символ в терминал перевода картеки
		static const void sendCursorUP	(const int line, AStream *stream);//переместить курсор выше на количество линий
		static const void sendClearRight(AStream *stream);//стереть все данные которые находятся справа от курсора

	

	private:
		bool m_connect;//флаг подсоеденения к терминалу
		bool m_isInput;//признак того что идет ввод команды


		char m_Buffer[MAX_TERMINAL_BUFFER];//буфер для команды
		WORD m_count;//количество символов в буфере
		void clearBuffer();//очистка буфера данных
		int getArg(char * argv[]);//разбор буферной строки на команды и параметры


		/*управляющие команды
		*/
		void cmdPushChar	(const BYTE data, AStream *stream);//вставка символа
		void cmdEnter		(AStream *stream);//перевод каретки
		void cmdBackspace	(AStream *stream);//удаление символа
		void cmdConnect		(AStream *stream);//подсоеденение к терминалу
		void cmdCallCommand	(AStream *stream);//приглашение на новую команду
	protected:

		virtual void onInterpretation(const int argc, char * const argv[], AStream *stream){};//Обработка команды

		void exit(AStream *stream);//выход из терминала


};
